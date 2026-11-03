import argparse
import json
import time
from pathlib import Path

import numpy as np


def sigmoid(values):
    return 1.0 / (1.0 + np.exp(-np.clip(values, -30, 30)))


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--samples", type=int, default=2000)
    parser.add_argument("--features", type=int, default=32)
    parser.add_argument("--hidden", type=int, default=32)
    parser.add_argument("--epochs", type=int, default=5)
    parser.add_argument("--batch-size", type=int, default=128)
    parser.add_argument("--learning-rate", type=float, default=0.05)
    parser.add_argument("--inference-runs", type=int, default=20)
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--output-dir", type=Path)
    return parser.parse_args()


def main():
    args = parse_args()
    rng = np.random.default_rng(args.seed)
    inputs = rng.normal(size=(args.samples, args.features)).astype(np.float32)
    target_weights = rng.normal(size=(args.features, 1)).astype(np.float32)
    targets = (inputs @ target_weights > 0).astype(np.float32)
    weights_1 = (rng.normal(size=(args.features, args.hidden)) * 0.1).astype(np.float32)
    bias_1 = np.zeros((1, args.hidden), dtype=np.float32)
    weights_2 = (rng.normal(size=(args.hidden, 1)) * 0.1).astype(np.float32)
    bias_2 = np.zeros((1, 1), dtype=np.float32)

    training_start = time.perf_counter()
    for _ in range(args.epochs):
        for start in range(0, args.samples, args.batch_size):
            batch = inputs[start : start + args.batch_size]
            expected = targets[start : start + args.batch_size]
            hidden = np.maximum(batch @ weights_1 + bias_1, 0)
            predicted = sigmoid(hidden @ weights_2 + bias_2)
            output_gradient = (predicted - expected) / len(batch)
            hidden_gradient = (output_gradient @ weights_2.T) * (hidden > 0)
            weights_2 -= args.learning_rate * (hidden.T @ output_gradient)
            bias_2 -= args.learning_rate * output_gradient.sum(axis=0, keepdims=True)
            weights_1 -= args.learning_rate * (batch.T @ hidden_gradient)
            bias_1 -= args.learning_rate * hidden_gradient.sum(axis=0, keepdims=True)
    training_seconds = time.perf_counter() - training_start

    inference_start = time.perf_counter()
    for _ in range(args.inference_runs):
        predictions = sigmoid(np.maximum(inputs @ weights_1 + bias_1, 0) @ weights_2 + bias_2)
    inference_seconds = time.perf_counter() - inference_start
    accuracy = float(((predictions >= 0.5) == targets).mean())
    metrics = {
        "training_seconds": training_seconds,
        "inference_seconds": inference_seconds,
        "inference_runs": args.inference_runs,
        "samples_per_second": args.samples * args.inference_runs / inference_seconds,
        "accuracy": accuracy,
        "samples": args.samples,
        "features": args.features,
        "hidden": args.hidden,
        "epochs": args.epochs,
        "batch_size": args.batch_size,
        "seed": args.seed,
    }

    if args.output_dir:
        args.output_dir.mkdir(parents=True, exist_ok=True)
        (args.output_dir / "metrics.json").write_text(
            json.dumps(metrics, indent=2), encoding="utf-8"
        )
    print(json.dumps(metrics))


if __name__ == "__main__":
    main()
