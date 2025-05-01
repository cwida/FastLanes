# generate_fastlanes_files.py
# ─────────────────────────────────────────────────────────────────────────
"""
Creates FastLanes sample files:
    ./valid.fls
    ./bad_header_magic.fls
    ./bad_footer_magic.fls
    ./bad_version.fls
    ./missing_footer.fls
    ./truncated_header.fls

All files follow the little-endian format:
    [magic (8)]     → "FastLane" → 0x656E614C74736146
    [version (8)]   → "S|V0.1.0" → 0x302E312E30567C53
    [size (8)]      → uint64 payload size (e.g., 16)
    [payload (N)]   → 16 random bytes
    [footer (8)]    → repeat magic
"""
import os, struct, pathlib

# ────────────────────────────────────── Constants (little-endian)
FASTLANES_MAGIC_BYTES   = 0x656E614C74736146  # "FastLane"
FASTLANES_VERSION_0_1_0 = 0x302E312E30567C53  # "S|V0.1.0"
PAYLOAD_SIZE            = 16

# ────────────────────────────────────── Helper
def write_file(
        fname,
        header_magic    = FASTLANES_MAGIC_BYTES,
        footer_magic    = FASTLANES_MAGIC_BYTES,
        version         = FASTLANES_VERSION_0_1_0,
        add_footer      = True,
        truncate_header = False,
        omit_footer     = False
):
    payload = os.urandom(PAYLOAD_SIZE)
    hdr  = struct.pack("<Q", header_magic)
    hdr += struct.pack("<Q", version)
    hdr += struct.pack("<Q", len(payload))

    if truncate_header:
        # Actually truncate to < 24 bytes: write only 20 bytes
        body = hdr[:20]  # missing part of payload size
    else:
        body = hdr + payload
        if not omit_footer:
            body += struct.pack("<Q", footer_magic)

    pathlib.Path(fname).write_bytes(body)

# ────────────────────────────────────── Main
if __name__ == "__main__":
    out_dir = pathlib.Path(".").resolve()

    write_file(out_dir / "valid.fls")
    write_file(out_dir / "bad_header_magic.fls", header_magic=0xBAD0C0DEBAD0C0DE)
    write_file(out_dir / "bad_footer_magic.fls", footer_magic=0xDEADBEEFCAFEBABE)
    write_file(out_dir / "bad_version.fls",      version     =0x0123456789ABCDEF)
    write_file(out_dir / "missing_footer.fls",   omit_footer =True)
    write_file(out_dir / "truncated_header.fls", truncate_header=True)

    print(f"✅ FastLanes test files generated in: {out_dir}")
