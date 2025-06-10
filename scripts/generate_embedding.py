# scripts/generate_embedding.py

import os
from glob import glob
import torch
from torchvision import transforms
from PIL import Image
import numpy as np
from pathlib import Path
import json


def main():
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    script_path = os.path.abspath(__file__)
    print("This script is located at:", script_path)

    # 1. Specify the directory to process (relative to this script)
    script_dir = Path(__file__).resolve().parent
    data_dir = script_dir / "flower_photos" / "daisy"
    assert data_dir.is_dir(), f"Directory {data_dir} does not exist or is not a folder."

    # 2. Define image preprocessing (consistent with training/validation)
    data_transform = transforms.Compose([
        transforms.Resize(256),
        transforms.CenterCrop(224),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406],
                             [0.229, 0.224, 0.225])
    ])

    # 3. Traverse all image files in the directory (only process .jpg/.jpeg/.png)
    img_paths = (
            glob(os.path.join(data_dir, "*.jpg"))
            + glob(os.path.join(data_dir, "*.jpeg"))
            + glob(os.path.join(data_dir, "*.png"))
    )
    img_paths.sort()  # Maintain order for reproducibility

    if len(img_paths) == 0:
        print(f"No jpg/jpeg/png images found in {data_dir}.")
        return

    # 4. Prepare saving directory for single-column output
    output_dir = script_dir / "embedding"
    os.makedirs(output_dir, exist_ok=True)

    # ----------------------------
    # A) Single column format: Flatten each image into a 150528×1 vector → Final shape (150528, N_images)
    # ----------------------------
    embeddings_cols = []
    for img_path in img_paths:
        image = Image.open(img_path).convert("RGB")
        img_tensor = data_transform(image)
        img_tensor = torch.unsqueeze(img_tensor, dim=0)
        arr = img_tensor.cpu().numpy().reshape(-1)
        embeddings_cols.append(arr)

    all_embeddings_cols = np.stack(embeddings_cols, axis=1)
    cols_csv = output_dir / "all_embeddings_columns.csv"
    np.savetxt(cols_csv, all_embeddings_cols, fmt="%.6f", delimiter="|")

    print(f"[Single column format] Processing complete: {len(img_paths)} images, "
          f"vector length = {all_embeddings_cols.shape[0]}, saved to: {cols_csv}\n")

    # ----------------------------
    # B) Three column format: Flatten each image into separate R,G,B columns → shape (50176, 3*N_images)
    # ----------------------------
    embeddings_rgb = []
    colnames_rgb = []

    for img_path in img_paths:
        image = Image.open(img_path).convert("RGB")
        img_tensor = data_transform(image)
        img_tensor = torch.unsqueeze(img_tensor, dim=0)

        arr_rgb = (
            img_tensor
            .cpu()
            .numpy()
            .transpose(0, 2, 3, 1)
            .reshape(-1, 3)
        )
        embeddings_rgb.append(arr_rgb)

        base = os.path.splitext(os.path.basename(img_path))[0]
        colnames_rgb += [f"{base}_R", f"{base}_G", f"{base}_B"]

    all_embeddings_rgb = np.hstack(embeddings_rgb)

    rgb_dir = script_dir.parent / "data" / "embedding"
    os.makedirs(rgb_dir, exist_ok=True)

    rgb_csv = rgb_dir / "all_embeddings_rgb_columns.csv"
    np.savetxt(rgb_csv, all_embeddings_rgb, fmt="%.6f", delimiter="|")

    # 8) Save schema for RGB columns with proper structure
    schema_entries = []
    for idx, name in enumerate(colnames_rgb):
        schema_entries.append({
            "name": name,
            "type": "FLOAT",
            "index": str(idx),
            "nullability": "NULL"
        })
    schema = {"columns": schema_entries}
    schema_path = rgb_dir / "schema.json"
    with open(schema_path, 'w') as f:
        json.dump(schema, f, indent=2)

    print(f"[Three column format] Processing complete: {len(img_paths)} images, "
          f"rows per (R,G,B) image = {all_embeddings_rgb.shape[0]}, "
          f"total columns = {all_embeddings_rgb.shape[1]}, saved to: {rgb_csv}\n")
    print(f"Schema saved to: {schema_path}\n")


if __name__ == "__main__":
    main()
