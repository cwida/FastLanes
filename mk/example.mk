ifndef EXAMPLES_MK_INCLUDED
EXAMPLES_MK_INCLUDED := yes

# ─────────────────────────────────────────────────────────────
# Common helpers & C++ rules
# ─────────────────────────────────────────────────────────────
include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/preamble.mk
include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/cpp.mk

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

# -----------------------------------------------------------------
# Compiler configuration
# -----------------------------------------------------------------
# These targets rely on standard C/C++ compilers being available.
# Override CC/CXX if clang or another toolchain should be used.

# Default compilers (override via environment). Works on Unix and Windows
CC  ?= cc
CXX ?= c++
# Windows executables use .exe extension
EXE_EXT :=
ifeq ($(OS),Windows_NT)
  EXE_EXT := .exe
endif

# Runtime library path for running examples.
# These settings ensure the FastLanes shared library is
# discoverable across Linux, macOS and Windows when executing
# the example binaries.
RUN_ENV :=
ifeq ($(OS),Windows_NT)
  RUN_ENV := PATH=$(PREFIX)/bin;$(PATH)
else ifeq ($(shell uname -s),Darwin)
  RUN_ENV := DYLD_LIBRARY_PATH=$(PREFIX)/lib:$(DYLD_LIBRARY_PATH)
else
  RUN_ENV := LD_LIBRARY_PATH=$(PREFIX)/lib:$(LD_LIBRARY_PATH)
endif

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
# Build & run the standalone C++ example
# Requires a C++20 capable compiler (clang++ or g++).
# ─────────────────────────────────────────────────────────────
run-cpp-example: install-cpp
	@echo "Building C++ example…"
	$(CXX) -std=c++20 $(EXAMPLES_DIR)/cpp_example.cpp -I$(PREFIX)/include \
       -L$(PREFIX)/lib -lFastLanes -o $(EXAMPLES_DIR)/cpp_example$(EXE_EXT)
	@echo "Running C++ example…"
	$(RUN_ENV) $(EXAMPLES_DIR)/cpp_example$(EXE_EXT)

# ─────────────────────────────────────────────────────────────
# Build & run the C API example
# Requires a C compiler such as clang or gcc.
# ─────────────────────────────────────────────────────────────
run-c-api-example: install-cpp
	@echo "Building C API example…"
	$(CC) -std=c11 $(EXAMPLES_DIR)/c_api.c -I$(PREFIX)/include \
       -L$(PREFIX)/lib -lFastLanes -o $(EXAMPLES_DIR)/c_api$(EXE_EXT)
	@echo "Running C API example…"
	$(RUN_ENV) $(EXAMPLES_DIR)/c_api$(EXE_EXT)

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
