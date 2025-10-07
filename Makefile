# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# Makefile
# ────────────────────────────────────────────────────────

# Defaults (override via CLI: make BUILD_DIR=out PREFIX=/usr/local)
SHELL        := /bin/bash
REPO_ROOT    ?= $(CURDIR)
BUILD_DIR    ?= build
CRATE_ROOT   ?= $(REPO_ROOT)/rust
PREFIX       ?= $(REPO_ROOT)/build/install
CARGO        ?= $(shell command -v cargo 2>/dev/null)
CTEST        ?= $(shell command -v ctest 2>/dev/null)
NUM_JOBS     ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Include modules
include mk/preamble.mk
include mk/cpp.mk

.DEFAULT_GOAL := help

.PHONY: all build install help help-main

# Aggregate builds
all: build
build: build-cpp

# Install (C++ only)
install: install-cpp

# Help
help: help-main

help-main:
	@echo "Primary targets:"
	@echo "  make build        - Build C++ components"
	@echo "  make install      - Install C++ artefacts"
	@echo "  make help         - Show this message"
	@echo
	@echo "Variables (override via CLI):"
	@echo "  BUILD_DIR=$(BUILD_DIR)"
	@echo "  PREFIX=$(PREFIX)"
	@echo "  CRATE_ROOT=$(CRATE_ROOT)"
	@echo "  NUM_JOBS=$(NUM_JOBS)"
