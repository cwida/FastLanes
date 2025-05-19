# ─────────────────────────────────────────────────────────────
# Build and install Rust bindings after C++ is installed
# This file is auto-included by the root Makefile:
#   no need to invoke with “-f mk/rust.mk”
# Usage:
#   make build-rust      # build Rust crate (release) after C++ install
#   make install-rust    # install Rust crate after C++ install
#   make run-rust-example # build + run the “rust_example”
#   make clean-rust      # clean only Rust build artifacts
# ─────────────────────────────────────────────────────────────

ifndef RUST_MK_INCLUDED
RUST_MK_INCLUDED := yes

# ─────────────────────────────────────────────────────────────
# Common helpers & C++ rules
# ─────────────────────────────────────────────────────────────
include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/preamble.mk
include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/cpp.mk

# ─────────────────────────────────────────────────────────────
# Compute paths relative to this file’s directory
# ─────────────────────────────────────────────────────────────
MK_DIR      := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR := $(abspath $(MK_DIR)/..)

# ─────────────────────────────────────────────────────────────
# Override crate root and install prefix
# ─────────────────────────────────────────────────────────────
CRATE_ROOT  := $(PROJECT_DIR)/rust
PREFIX      := $(PROJECT_DIR)/build/install

# ─────────────────────────────────────────────────────────────
# Configuration
# ─────────────────────────────────────────────────────────────
CARGO       ?= cargo
C_ENV       := \
  C_INCLUDE_PATH=$(PREFIX)/include \
  LIBRARY_PATH=$(PREFIX)/lib \
  CXXFLAGS=-I$(PREFIX)/include

# ─────────────────────────────────────────────────────────────
# Targets
# ─────────────────────────────────────────────────────────────
.PHONY: build-rust install-rust run-rust-example clean-rust clean

# Build Rust *after* C++ is installed
build-rust: install-cpp
	@echo "Building Rust crate (release, $(NUM_JOBS) jobs)…"
	CXXFLAGS="-I$(PREFIX)/include" \
	C_INCLUDE_PATH="$(PREFIX)/include" \
	LIBRARY_PATH="$(PREFIX)/lib" \
	$(CARGO) build --release \
	  --manifest-path $(CRATE_ROOT)/Cargo.toml \
	  --jobs $(NUM_JOBS)
	@echo "Rust build complete."

# Install Rust *after* C++ is installed
install-rust: install-cpp
	$(call echo_start,Installing Rust crate …)
	$(C_ENV) \
	$(CARGO) install --path $(CRATE_ROOT) \
	  --root $(PREFIX) \
	  --jobs $(NUM_JOBS)
	$(call echo_done,Rust install complete.)

# Build then run the “rust_example” in your crate
run-rust-example: build-rust
	@echo "Running Rust example ‘rust_example’…"
	cd $(CRATE_ROOT) && \
	C_INCLUDE_PATH="$(PREFIX)/include" \
	LIBRARY_PATH="$(PREFIX)/lib" \
	cargo run --example rust_example

# Clean Rust only (no C++)
clean-rust:
	$(call echo_start,Cleaning Rust build…)
	$(CARGO) clean --manifest-path $(CRATE_ROOT)/Cargo.toml
	$(call echo_done,Rust clean complete.)

# Top-level clean kills *both* C++ and Rust
clean: clean-cpp clean-rust

endif  # RUST_MK_INCLUDED
