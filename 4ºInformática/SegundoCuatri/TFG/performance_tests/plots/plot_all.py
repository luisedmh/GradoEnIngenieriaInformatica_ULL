import argparse
from pathlib import Path

from plot_accuracy import plot_accuracy
from plot_throughput import plot_throughput
from plot_timings import plot_timings


ROOT = Path(__file__).resolve().parents[1]


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("results_dir", nargs="?", type=Path, default=ROOT / "results")
    parser.add_argument("--output-dir", type=Path)
    parser.add_argument("--format", default="png", choices=("png", "svg", "pdf", "show"))
    return parser.parse_args()


def main():
    args = parse_args()
    output_dir = args.output_dir or args.results_dir / "plots"
    plot_timings(args.results_dir, output_dir, args.format)
    plot_throughput(args.results_dir, output_dir, args.format)
    plot_accuracy(args.results_dir, output_dir, args.format)


if __name__ == "__main__":
    main()
