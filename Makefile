# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# Makefile
# ────────────────────────────────────────────────────────
SHELL        := /bin/bash
VERBOSE      ?= 0
REPO_ROOT    ?= $(CURDIR)
BUILD_DIR    ?= build
CRATE_ROOT   ?= $(REPO_ROOT)/rust
PREFIX       ?= $(REPO_ROOT)/build/install
CARGO        ?= $(shell command -v cargo 2>/dev/null)
CTEST        ?= $(shell command -v ctest 2>/dev/null)
NUM_JOBS     ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Test-specific config (separate build dir and build type)
TEST_BUILD_DIR  ?= $(BUILD_DIR)/tests
TEST_BUILD_TYPE ?= Release

# Includes
include mk/preamble.mk     # colors + root paths
include mk/python.mk       # Python bindings
include mk/format.mk       # Formatting helpers
include mk/cpp.mk          # C++ build/test/install
include mk/rust.mk         # Rust integration
include mk/data.mk         # Data preparation
include mk/scripts.mk      # General scripts
include mk/embeddings.mk   # Embeddings + venv setup
include mk/flatbuffers.mk  # FlatBuffers generation
include mk/quick_fuzz.mk   # Fuzz testing
include mk/header_check.mk # Header checks

.DEFAULT_GOAL := help

.PHONY: all build install test test-cpp help help-main \
        configure-cpp-tests build-cpp-tests

# Build
all: build
build: build-cpp

# Install
install: install-cpp

# Format
.PHONY: format
format: clang-format
	@echo "✅ Formatting complete (clang-format)."

# Help
help: help-main
help-main:
	@echo "Targets:"
	@echo "  make build                    - Build C++ components"
	@echo "  make install                  - Install C++ artefacts"
	@echo "  make test [TEST_BUILD_TYPE=]  - Configure+build+run tests in a separate tree (Debug by default)"
	@echo "  make format                   - Run clang-format on all source directories"
	@echo "  make bump                     - Bump fuzz seed version"
	@echo "  make verify                   - Verify fuzz seed bump correctness"
	@echo "  make check-header             - Verify file headers"
	@echo "  make fix-header               - Automatically fix headers"
	@echo "  make help                     - Show this message"
	@echo
	@echo "Variables (override via CLI):"
	@echo "  BUILD_DIR=$(BUILD_DIR)"
	@echo "  TEST_BUILD_DIR=$(TEST_BUILD_DIR)"
	@echo "  TEST_BUILD_TYPE=$(TEST_BUILD_TYPE)"
	@echo "  PREFIX=$(PREFIX)"
	@echo "  CRATE_ROOT=$(CRATE_ROOT)"
	@echo "  NUM_JOBS=$(NUM_JOBS)"
	@echo "  VERBOSE=$(VERBOSE)"
	@echo "  CMAKE_EXTRA_FLAGS=$(CMAKE_EXTRA_FLAGS)"
