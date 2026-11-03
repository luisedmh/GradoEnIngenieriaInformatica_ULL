import argparse
import json
import os
import platform
import re
import statistics
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def safe_name(value):
    return re.sub(r"[^a-zA-Z0-9._-]+", "-", str(value)).strip("-_") or "test"


def expand(value, context):
    value = str(value)
    for key, replacement in context.items():
        value = value.replace("{" + key + "}", str(replacement))
    return value


def load_config(path):
    config = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(config.get("command"), list) or not config["command"]:
        raise ValueError(f"{path}: command must be a non-empty list")
    return config


def execute(command, cwd, env, timeout):
    started_at = datetime.now().astimezone()
    clock = time.perf_counter()
    try:
        process = subprocess.run(
            command,
            cwd=cwd,
            env=env,
            capture_output=True,
            text=True,
            timeout=timeout,
        )
        returncode = process.returncode
        stdout = process.stdout
        stderr = process.stderr
        timed_out = False
    except subprocess.TimeoutExpired as error:
        returncode = None
        stdout = error.stdout or ""
        stderr = error.stderr or ""
        timed_out = True
    except OSError as error:
        returncode = None
        stdout = ""
        stderr = str(error)
        timed_out = False
    return {
        "started_at": started_at.isoformat(),
        "ended_at": datetime.now().astimezone().isoformat(),
        "duration_seconds": time.perf_counter() - clock,
        "returncode": returncode,
        "timed_out": timed_out,
        "stdout": stdout.decode(errors="replace") if isinstance(stdout, bytes) else stdout,
        "stderr": stderr.decode(errors="replace") if isinstance(stderr, bytes) else stderr,
    }


def run_config(config_path, args):
    config = load_config(config_path)
    name = safe_name(config.get("name", config_path.stem))
    runs = args.runs if args.runs is not None else int(config.get("runs", 3))
    warmups = args.warmups if args.warmups is not None else int(config.get("warmups", 1))
    base_seed = args.seed if args.seed is not None else int(config.get("seed", 42))
    timeout = args.timeout if args.timeout is not None else config.get("timeout_seconds")
    if runs < 1 or warmups < 0:
        raise ValueError("runs must be positive and warmups cannot be negative")

    results_dir = (args.results_dir or ROOT / "results").resolve()
    results_dir.mkdir(parents=True, exist_ok=True)
    parameters = config.get("parameters", {})
    cwd = Path(expand(config.get("cwd", ROOT), {"root": ROOT, "config_dir": config_path.parent}))
    if not cwd.is_absolute():
        cwd = (config_path.parent / cwd).resolve()
    records = []

    for index in range(warmups + runs):
        is_warmup = index < warmups
        run_number = index + 1 if is_warmup else index - warmups + 1
        seed = base_seed if is_warmup else base_seed + run_number - 1
        stamp = datetime.now().astimezone().strftime("%Y%m%d_%H%M%S_%f")
        label = f"warmup-{run_number:02d}" if is_warmup else f"run-{run_number:02d}"
        stem = f"{stamp}_{name}_{label}"
        artifacts_dir = results_dir / f"{stem}_files"
        artifacts_dir.mkdir()
        context = {
            **parameters,
            "python": sys.executable,
            "root": ROOT,
            "config_dir": config_path.parent,
            "seed": seed,
            "run": run_number,
            "artifacts_dir": artifacts_dir,
        }
        command = [expand(value, context) for value in config["command"]]
        env = os.environ.copy()
        env.update({str(key): expand(value, context) for key, value in config.get("env", {}).items()})
        env["PYTHONHASHSEED"] = str(seed)
        env["BENCHMARK_SEED"] = str(seed)
        env["BENCHMARK_ARTIFACTS_DIR"] = str(artifacts_dir)
        print(f"{name} {label}: running", flush=True)
        result = execute(command, cwd, env, timeout)

        if is_warmup:
            if result["returncode"] != 0:
                print(result["stderr"], file=sys.stderr)
                return 1
            continue

        record = {
            "test": name,
            "config": str(config_path),
            "run": run_number,
            "seed": seed,
            "command": command,
            "parameters": parameters,
            "artifacts_dir": str(artifacts_dir),
            "system": {
                "hostname": platform.node(),
                "platform": platform.platform(),
                "processor": platform.processor(),
                "python": sys.version,
            },
            **result,
        }
        metrics_path = artifacts_dir / "metrics.json"
        if metrics_path.exists():
            record["metrics"] = json.loads(metrics_path.read_text(encoding="utf-8"))
        output_path = results_dir / f"{stem}.json"
        output_path.write_text(json.dumps(record, indent=2, ensure_ascii=False), encoding="utf-8")
        records.append(record)
        status = "ok" if result["returncode"] == 0 else "failed"
        print(f"{name} {label}: {status} in {result['duration_seconds']:.4f}s -> {output_path.name}")
        if result["returncode"] != 0:
            print(result["stderr"], file=sys.stderr)
            return 1

    durations = [record["duration_seconds"] for record in records]
    print(
        f"{name}: mean={statistics.mean(durations):.4f}s "
        f"stdev={statistics.stdev(durations) if len(durations) > 1 else 0.0:.4f}s "
        f"min={min(durations):.4f}s max={max(durations):.4f}s"
    )
    training_times = [record.get("metrics", {}).get("training_seconds") for record in records]
    if all(value is not None for value in training_times):
        print(f"{name}: training mean={statistics.mean(training_times):.4f}s")
    return 0


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("configs", nargs="*", type=Path)
    parser.add_argument("--runs", type=int)
    parser.add_argument("--warmups", type=int)
    parser.add_argument("--seed", type=int)
    parser.add_argument("--timeout", type=float)
    parser.add_argument("--results-dir", type=Path)
    return parser.parse_args()


def main():
    args = parse_args()
    configs = args.configs or [ROOT / "configs" / "small_model.json"]
    for config_path in configs:
        if run_config(config_path.resolve(), args):
            return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
