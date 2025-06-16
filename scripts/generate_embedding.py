#!/usr/bin/env python3
"""
Embed images in <this_dir>/flower_photos/daisy.

* Local runs require the folder.
* CI (CI=true) skips gracefully if it’s missing.
"""

import json
import os
import sys
from glob import glob
from pathlib import Path

import numpy as np
import torch
from PIL import Image
from torchvision import transforms


def main() -> None:
    script_dir = Path(__file__).resolve().parent
    data_dir = script_dir.parent / "data" / "flower_photos" / "daisy"

    # skip on CI if dataset absent
    if not data_dir.is_dir():
        if os.getenv("CI") == "true":
            print(f"[CI] '{data_dir}' not found – skipping embedding generation.")
            sys.exit(0)
        raise FileNotFoundError(f"Directory '{data_dir}' not found; clone the dataset first.")

    print("Embedding images from:", data_dir)

    transform = transforms.Compose([
        transforms.Resize(256),
        transforms.CenterCrop(224),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406],
                             [0.229, 0.224, 0.225]),
    ])

    img_paths = (
            glob(str(data_dir / "*.jpg"))
            + glob(str(data_dir / "*.jpeg"))
            + glob(str(data_dir / "*.png"))
    )
    img_paths.sort()
    if not img_paths:
        print("No images found; nothing to embed.")
        return

    # output directory
    output_root = script_dir.parent / "data" / "embedding"
    output_root.mkdir(parents=True, exist_ok=True)

    # ---------- single-column embeddings ----------
    col_vecs = [
        transform(Image.open(p).convert("RGB")).unsqueeze(0).numpy().reshape(-1)
        for p in img_paths
    ]
    mat_cols = np.stack(col_vecs, axis=1)
    np.savetxt(
        output_root / "all_embeddings_columns.csv",
        mat_cols, fmt="%.6f", delimiter="|"
    )
    print(f"[single-column]  shape={mat_cols.shape} saved to all_embeddings_columns.csv")

    # ---------- RGB-split embeddings ----------
    rgb_blocks, rgb_names = [], []
    for p in img_paths:
        tensor = transform(Image.open(p).convert("RGB")).unsqueeze(0)
        arr = tensor.numpy().transpose(0, 2, 3, 1).reshape(-1, 3)
        rgb_blocks.append(arr)
        base = Path(p).stem
        rgb_names += [f"{base}_R", f"{base}_G", f"{base}_B"]

    mat_rgb = np.hstack(rgb_blocks)
    np.savetxt(
        output_root / "all_embeddings_rgb_columns.csv",
        mat_rgb, fmt="%.6f", delimiter="|"
    )
    print(f"[RGB-columns ]  shape={mat_rgb.shape} saved to all_embeddings_rgb_columns.csv")

    schema = {"columns": [
        {"name": n, "type": "FLOAT", "index": str(i), "nullability": "NULL"}
        for i, n in enumerate(rgb_names)
    ]}
    with open(output_root / "schema.json", "w") as f:
        json.dump(schema, f, indent=2)
    print("schema.json written.")


if __name__ == "__main__":
    main()
