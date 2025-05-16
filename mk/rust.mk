# mk/rust.mk — Rust build & test rules

# ── locate this makefile and compute the project root ─────────────
MKFILE_PATH   := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PROJECT_ROOT  := $(abspath $(MKFILE_PATH)/..)

# ── where your actual Rust crate is (so Cargo.toml lives there) ──
# override it on the command line if your crate folder is named differently
CRATE_DIR     ?= $(PROJECT_ROOT)/rust
MANIFEST_PATH := $(CRATE_DIR)/Cargo.toml
LOCK_FILE     := $(CRATE_DIR)/Cargo.lock

CARGO ?= cargo

.PHONY: build-rust test clean-rust

build-rust:
	$(call echo_start,Building Rust crate in $(CRATE_DIR)…)
	cd $(CRATE_DIR) && $(CARGO) build
	$(call echo_done,Rust build complete.)

test: build-cpp build-rust
	$(call echo_start,Running Rust tests…)
	cd $(CRATE_DIR) && $(CARGO) test -- --nocapture
	$(call echo_done,Rust tests complete.)

clean-rust:
	$(call echo_start,Cleaning Rust build…)
	cd $(CRATE_DIR) && $(CARGO) clean
	$(call echo_start,Removing Cargo.lock…)
	rm -f $(LOCK_FILE)
	$(call echo_done,Rust clean complete.)
