# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# data/example/extract_sentences.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""
extract_sentences.py
────────────────────────────────────────────────────────────────────────
• Collect sentences from two PDFs (FastLanes PVLDB + CWI tech-report).
• KEEP digits; only strip interior CSV-dangerous delimiters (',', ';', '|', TAB).
• Keep every “normal” English sentence (>5 words, ends with . ! ?, etc.).
• Truncate the final list so its length is the largest multiple of 1024
  (0 rows if fewer than 1024 sentences total).
• Write papers.csv (single column, no header, UNIX line endings) and
  re-emit via pandas to guarantee string dtype.
• Suppress pdfminer’s “Cannot set gray non-stroke color …” messages
  by raising its log level to ERROR.
"""

import io
import os
import re
import csv
import string
import requests
import pandas as pd
import contextlib
import sys
import logging
from pdfminer.high_level import extract_text

# ───────────────────── suppress pdfminer warnings ──────────────────
# Raise pdfminer’s log-level so INFO/WARNING (including invalid-color complaints) are not printed.
logging.getLogger("pdfminer").setLevel(logging.ERROR)
logging.getLogger("pdfminer.pdfinterp").setLevel(logging.ERROR)
# Alternatively, to catch any sub-loggers:
# for name in logging.root.manager.loggerDict:
#     if name.startswith("pdfminer"):
#         logging.getLogger(name).setLevel(logging.ERROR)

# ───────────────────── configuration ─────────────────────────────────
PDF_URLS = [
    "https://www.vldb.org/pvldb/vol16/p2132-afroozeh.pdf",
    "https://ir.cwi.nl/pub/33334/33334.pdf",
]

UA_HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)",
    "Accept": "application/pdf",
}

# ───────────────────── regex helpers ─────────────────────────────────
HYPHEN_FIX = re.compile(r'(?<=\w)-\s+(?=\w)')  # join “com- pression”
MULTISPACE = re.compile(r'\s+')
WORD_RE = re.compile(r'[A-Za-z]')
VOWEL_RE = re.compile(r'[aeiouAEIOU]')
UPPER_LINE = re.compile(r'^[A-Z0-9 ─\-:;]+$')
HEAD_TOKS = {
    'abstract', 'introduction', 'related', 'conclusion', 'future',
    'figure', 'fig.', 'table', 'listing', 'algorithm', 'section',
    'copyright', 'doi', 'issn', 'license', 'reference', 'references',
}
DELIM_CLEAN = str.maketrans('', '', ',;|\t')  # strip “, ; | TAB”


# ───────────────────── helper functions ──────────────────────────────
def fetch_pdf(url: str) -> bytes:
    r = requests.get(url, headers=UA_HEADERS, timeout=30)
    r.raise_for_status()
    return r.content


def pdf_to_text(pdf_bytes: bytes) -> str:
    # Redirect stderr to suppress any remaining warnings on stderr
    buf = io.StringIO()
    with contextlib.redirect_stderr(buf):
        text = extract_text(io.BytesIO(pdf_bytes))
    return text


def normalise_spaces(txt: str) -> str:
    txt = HYPHEN_FIX.sub('', txt)
    return MULTISPACE.sub(' ', txt).strip()


def sentence_chunks(txt: str) -> list[str]:
    return [seg.strip() + '.' for seg in txt.split('.') if seg.strip()]


def looks_like_heading(chunk: str) -> bool:
    lo = chunk.lower()
    first = lo.split()[0].strip(string.punctuation)
    return (
            first in HEAD_TOKS or lo.startswith('doi:') or
            re.fullmatch(r'\[\d+]', chunk.strip()) or
            re.fullmatch(r'\d{1,4}', chunk.strip())
    )


def good_sentence(s: str) -> bool:
    if len(s) < 20 or s[-1] not in '.!?':
        return False
    if not (WORD_RE.search(s) and VOWEL_RE.search(s)):
        return False
    if UPPER_LINE.fullmatch(s) or looks_like_heading(s):
        return False
    if len(s.split()) < 6:
        return False
    lower = sum(c.islower() for c in s)
    upper = sum(c.isupper() for c in s)
    return lower and lower >= upper * 0.2


def clean_sentence(s: str) -> str:
    """Strip outer quotes and remove CSV delimiters, KEEP digits."""
    return s.strip('“”"').translate(DELIM_CLEAN)


def harvest_sentences(url: str) -> list[str]:
    try:
        text = pdf_to_text(fetch_pdf(url))
    except requests.HTTPError as e:
        print(f"⚠️  Skipping {url}: {e}", file=sys.stderr)
        return []
    text = normalise_spaces(text)
    return [
        clean_sentence(seg)
        for seg in sentence_chunks(text)
        if good_sentence(seg)
    ]


def main() -> None:
    sentences: list[str] = []
    for u in PDF_URLS:
        sentences.extend(harvest_sentences(u))

    # truncate to largest multiple of 1024
    if len(sentences) >= 1024:
        sentences = sentences[: len(sentences) - (len(sentences) % 1024)]
    else:
        sentences = []

    out_path = os.path.join(os.path.dirname(__file__), "papers.csv")

    # write via csv.writer
    with open(out_path, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f, lineterminator="\n")
        writer.writerows([[s] for s in sentences])

    # enforce single string column via pandas (use correct keyword `lineterminator`)
    pd.read_csv(out_path, header=None, names=["sentence"], dtype=str) \
        .to_csv(out_path, header=False, index=False, lineterminator="\n")

    print(f"✅  {len(sentences)} sentences (multiple of 1024) → {out_path}")


if __name__ == "__main__":
    main()
