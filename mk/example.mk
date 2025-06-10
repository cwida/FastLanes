ifndef EXAMPLES_MK_INCLUDED
EXAMPLES_MK_INCLUDED := yes

# ─────────────────────────────────────────────────────────────
# Common helpers & C++ rules
# ─────────────────────────────────────────────────────────────
include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/preamble.mk

# ─────────────────────────────────────────────────────────────
# Compute paths relative to this file’s directory
# ─────────────────────────────────────────────────────────────
MK_DIR       := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR  := $(abspath $(MK_DIR)/..)
EXAMPLES_DIR := $(PROJECT_DIR)/examples

# ─────────────────────────────────────────────────────────────
# Install prefix (inherited from root Makefile)
# ─────────────────────────────────────────────────────────────
PREFIX       := $(PROJECT_DIR)/build/install

# ─────────────────────────────────────────────────────────────
# Phony targets
# ─────────────────────────────────────────────────────────────
.PHONY: \
    run-c-api-example \
    run-cpp-example \
    run-python-example \
    run-cmake-example \
    run-rust-example \
    clean-examples \
    venv-python-example \
    install-python-deps \
    run-pdf-example \
    clean-pdf-example

# ─────────────────────────────────────────────────────────────
# Run the Rust example
# ─────────────────────────────────────────────────────────────
run-rust-example:
	@echo "Running Rust example…"
	cd $(EXAMPLES_DIR)/rust_example && \
	cargo run --bin rust_example

# ─────────────────────────────────────────────────────────────
# Run the Python example (assumes the C++ lib is in PYTHONPATH)
# ─────────────────────────────────────────────────────────────
run-python-example: install-cpp
	@echo "Running Python example…"
	PYTHONPATH=$(PREFIX)/lib/python3/site-packages \
	    python3 $(EXAMPLES_DIR)/python_example.py

# ─────────────────────────────────────────────────────────────
# Build & run the CMake-based example project
# ─────────────────────────────────────────────────────────────
run-cmake-example: install-cpp
	@echo "Building CMake example…"
	mkdir -p $(EXAMPLES_DIR)/build
	cd $(EXAMPLES_DIR)/build && \
	  cmake .. -DCMAKE_PREFIX_PATH=$(PREFIX) && \
	  $(MAKE)
	@echo "Running CMake example…"
	# adjust the executable name below if different
	$(EXAMPLES_DIR)/build/cpp_example

# ─────────────────────────────────────────────────────────────
# Clean up all example artifacts
# ─────────────────────────────────────────────────────────────
clean-examples:
	@echo "Cleaning examples…"
	rm -f $(EXAMPLES_DIR)/c_api \
	       $(EXAMPLES_DIR)/cpp_example
	rm -rf $(EXAMPLES_DIR)/build

# ─────────────────────────────────────────────────────────────
# Python virtual environment for PDF sentence-extraction example
# ─────────────────────────────────────────────────────────────

VENV_DIR    := $(EXAMPLES_DIR)/.venv
PYTHON      := $(VENV_DIR)/bin/python
PIP         := $(VENV_DIR)/bin/pip
PDF_SCRIPT  := $(PROJECT_DIR)/data/example/extract_sentences.py
CSV_OUTPUT  := $(PROJECT_DIR)/data/example/papers.csv

# Create a Python virtual environment
venv-python-example:
	@echo "Creating virtual environment in $(VENV_DIR)…"
	python3 -m venv $(VENV_DIR)

# Install required Python dependencies into the virtual environment
install-python-deps: venv-python-example
	@echo "Installing Python dependencies…"
	$(PIP) install --upgrade pip
	$(PIP) install requests pdfminer.six pandas

# Run the PDF sentence-extraction script
run-pdf-example: install-python-deps
	@echo "Extracting sentences from PDF and writing to CSV…"
	$(PYTHON) $(PDF_SCRIPT)

# Clean up the virtual environment and generated CSV
clean-pdf-example:
	@echo "Cleaning PDF example artifacts…"
	rm -rf $(VENV_DIR)
	rm -f $(CSV_OUTPUT)

endif  # EXAMPLES_MK_INCLUDED
