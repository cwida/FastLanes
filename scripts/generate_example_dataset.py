import requests
import io
import csv
import re
from pdfminer.high_level import extract_text

# URL of the PDF to download
pdf_url = "https://www.vldb.org/pvldb/vol16/p2132-afroozeh.pdf"

def download_pdf_bytes(url):
    """
    Downloads a PDF from the given URL and returns its raw bytes.
    """
    resp = requests.get(url)
    resp.raise_for_status()
    return resp.content

def extract_text_from_pdf_bytes(pdf_bytes):
    """
    Uses pdfminer.six to extract all text from a PDF (given as bytes).
    Returns the entire text as one string.
    """
    return extract_text(io.BytesIO(pdf_bytes))

def split_into_sentences(full_text):
    """
    Splits a block of text into sentences using a regex that looks for
    sentence-ending punctuation (., ?, !) followed by whitespace.
    Returns a list of stripped, non-empty sentences.
    """
    # The pattern (?<=[\.!?])\s+ finds whitespace right after '.', '!', or '?'
    raw_sentences = re.split(r'(?<=[\.!?])\s+', full_text)
    # Strip each sentence and drop any that are empty after stripping
    sentences = [s.strip() for s in raw_sentences if s.strip()]
    return sentences

def write_sentences_to_csv(sentences, output_filepath):
    """
    Writes each sentence in `sentences` as a separate row in a single-column CSV file.
    """
    with open(output_filepath, mode="w", newline="", encoding="utf-8") as csvfile:
        writer = csv.writer(csvfile)
        for sentence in sentences:
            writer.writerow([sentence])

if __name__ == "__main__":
    # 1. Download the PDF bytes
    pdf_data = download_pdf_bytes(pdf_url)

    # 2. Extract the full text from the PDF
    full_text = extract_text_from_pdf_bytes(pdf_data)

    # 3. Split the text into individual sentences
    sentences = split_into_sentences(full_text)

    # 4. Write each sentence as one row in a CSV (no header)
    output_file = "afroozeh_paper_sentences.csv"
    write_sentences_to_csv(sentences, output_file)

    print(f"Wrote {len(sentences)} sentences to '{output_file}'.")
