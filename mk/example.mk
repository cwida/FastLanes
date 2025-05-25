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
    clean-examples

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

endif  # EXAMPLES_MK_INCLUDED
