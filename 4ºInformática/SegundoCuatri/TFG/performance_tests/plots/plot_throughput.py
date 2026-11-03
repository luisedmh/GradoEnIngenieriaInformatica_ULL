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
        if record.get("returncode") == 0 and record.get("metrics"):
            records.append(record)
    if not records:
        raise ValueError(f"No successful benchmark results found in {results_dir}")
    return sorted(records, key=lambda record: (record["test"], record["run"]))


def plot_throughput(results_dir, output_dir=None, output_format="png"):
    records = load_results(results_dir)
    labels = [f"{record['test']} #{record['run']}" for record in records]
    values = [record["metrics"]["samples_per_second"] / 1_000_000 for record in records]
    positions = np.arange(len(records))

    figure, axis = plt.subplots(figsize=(max(8, len(records) * 1.5), 6))
    bars = axis.bar(positions, values, color="tab:blue")
    axis.bar_label(bars, fmt="%.2f")
    axis.set_ylim(0, max(values) * 1.15)
    axis.set_xticks(positions, labels, rotation=20, ha="right")
    axis.set_ylabel("Throughput (million samples/s)")
    axis.set_title("Inference Throughput")
    axis.grid(axis="y", alpha=0.3)
    figure.tight_layout()

    if output_format == "show":
        plt.show()
        return None
    output_dir = Path(output_dir or Path(results_dir) / "plots")
    output_dir.mkdir(parents=True, exist_ok=True)
    output_path = output_dir / f"throughput.{output_format}"
    figure.savefig(output_path)
    plt.close(figure)
    return output_path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("results_dir", nargs="?", type=Path, default=ROOT / "results")
    parser.add_argument("--output-dir", type=Path)
    parser.add_argument("--format", default="png", choices=("png", "svg", "pdf", "show"))
    args = parser.parse_args()
    plot_throughput(args.results_dir, args.output_dir, args.format)


if __name__ == "__main__":
    main()
