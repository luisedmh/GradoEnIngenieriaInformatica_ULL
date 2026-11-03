import argparse
import json
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np


ROOT = Path(__file__).resolve().parents[1]


def load_results(results_dir):
    records = []
    for path in Path(results_dir).glob("*.json"):
        record = json.loads(path.read_text(encoding="utf-8"))
        metrics = record.get("metrics")
        if record.get("returncode") == 0 and metrics:
            records.append(record)
    if not records:
        raise ValueError(f"No successful benchmark results found in {results_dir}")
    return sorted(records, key=lambda record: (record["test"], record["run"]))


def plot_timings(results_dir, output_dir=None, output_format="png"):
    records = load_results(results_dir)
    labels = [f"{record['test']} #{record['run']}" for record in records]
    training = [record["metrics"]["training_seconds"] * 1000 for record in records]
    inference = [record["metrics"]["inference_seconds"] * 1000 for record in records]
    total = [record["duration_seconds"] for record in records]
    positions = np.arange(len(records))
    width = 0.36

    figure, axis = plt.subplots(figsize=(max(8, len(records) * 1.5), 6))
    axis.bar(positions - width / 2, training, width, label="Training")
    axis.bar(positions + width / 2, inference, width, label="Inference")
    axis.set_ylabel("Model time (ms)")
    axis.set_xticks(positions, labels, rotation=20, ha="right")
    axis.grid(axis="y", alpha=0.3)
    wall_axis = axis.twinx()
    wall_axis.plot(positions, total, color="black", marker="o", label="Total process")
    wall_axis.set_ylabel("Total process time (s)")
    handles, legend_labels = axis.get_legend_handles_labels()
    wall_handles, wall_labels = wall_axis.get_legend_handles_labels()
    axis.legend(handles + wall_handles, legend_labels + wall_labels, loc="upper left")
    axis.set_title("Benchmark Timings")
    figure.tight_layout()

    if output_format == "show":
        plt.show()
        return None
    output_dir = Path(output_dir or Path(results_dir) / "plots")
    output_dir.mkdir(parents=True, exist_ok=True)
    output_path = output_dir / f"timings.{output_format}"
    figure.savefig(output_path)
    plt.close(figure)
    return output_path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("results_dir", nargs="?", type=Path, default=ROOT / "results")
    parser.add_argument("--output-dir", type=Path)
    parser.add_argument("--format", default="png", choices=("png", "svg", "pdf", "show"))
    args = parser.parse_args()
    plot_timings(args.results_dir, args.output_dir, args.format)


if __name__ == "__main__":
    main()
