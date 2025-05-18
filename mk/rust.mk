# mk/rust.mk — build/install Rust bindings after C++ is installed
ifndef RUST_MK_INCLUDED
RUST_MK_INCLUDED := yes

# ── common helpers and C++ rules ───────────────────────────────────
include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/preamble.mk
include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/cpp.mk

# ── compute paths relative to this file’s directory ────────────────
MK_DIR      := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR := $(abspath $(MK_DIR)/..)

# ── override crate root and install prefix ─────────────────────────
CRATE_ROOT  := $(PROJECT_DIR)/rust
PREFIX      := $(PROJECT_DIR)/build/install

# ── config ─────────────────────────────────────────────────────────
CARGO       ?= cargo
C_ENV       := \
  C_INCLUDE_PATH=$(PREFIX)/include \
  LIBRARY_PATH=$(PREFIX)/lib \
  CXXFLAGS=-I$(PREFIX)/include

# ── targets ────────────────────────────────────────────────────────
.PHONY: build-rust install-rust clean-rust

# 1. Build Rust *after* C++ is installed
build-rust: install-cpp
	@echo "Building Rust crate (release, $(NUM_JOBS) jobs)…"
	# point the C/C++ compiler at your freshly installed headers & libs
	CXXFLAGS="-I$(PREFIX)/include" \
	C_INCLUDE_PATH="$(PREFIX)/include" \
	LIBRARY_PATH="$(PREFIX)/lib" \
	$(CARGO) build --release \
	  --manifest-path $(CRATE_ROOT)/Cargo.toml \
	  --jobs $(NUM_JOBS)
	@echo "Rust build complete."

# 2. Install Rust *after* C++ is installed
install-rust: install-cpp
	$(call echo_start,Installing Rust crate …)
	$(C_ENV) \
	$(CARGO) install --path $(CRATE_ROOT) \
	  --root $(PREFIX) \
	  --jobs $(NUM_JOBS)
	$(call echo_done,Rust install complete.)

run-rust-example: build-rust
	@echo "Running Rust example ‘rust_example’…"
	# If your crate root is e.g. ./rust:
	cd $(CRATE_ROOT) && \
	C_INCLUDE_PATH="$(PREFIX)/include" \
	LIBRARY_PATH="$(PREFIX)/lib" \
	cargo run --example rust_example

# 3. Clean Rust only (no C++!):
clean-rust:
	$(call echo_start,Cleaning Rust build…)
	$(CARGO) clean --manifest-path $(CRATE_ROOT)/Cargo.toml
	$(call echo_done,Rust clean complete.)

# 4. Top-level “clean” kills *both* C++ and Rust
clean: clean-cpp clean-rust

endif  # RUST_MK_INCLUDED
