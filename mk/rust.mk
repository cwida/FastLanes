# ────────────────────────────────────────────────────────────────
#  Rust bindings – build, install, publish
#  (auto-included from the project-root Makefile)
# ────────────────────────────────────────────────────────────────
ifndef RUST_MK_INCLUDED
RUST_MK_INCLUDED := yes

include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/preamble.mk

# ----------------------------------------------------------------
# Paths
# ----------------------------------------------------------------
MK_DIR      := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR := $(abspath $(MK_DIR)/..)
CRATE_ROOT  := $(PROJECT_DIR)/rust
PREFIX      := $(PROJECT_DIR)/build/install
OUT_DIR     := $(CRATE_ROOT)/target          # Cargo’s build dir
VENDOR_DIR  := $(CRATE_ROOT)/vendor/fastlanes

NUM_JOBS ?= $(shell sysctl -n hw.ncpu 2>/dev/null || echo 8)

CARGO ?= cargo
C_ENV  := C_INCLUDE_PATH=$(PREFIX)/include \
          LIBRARY_PATH=$(PREFIX)/lib \
          CXXFLAGS=-I$(PREFIX)/include

# ----------------------------------------------------------------
# Build / install / publish
# ----------------------------------------------------------------
.PHONY: build-rust install-rust publish-rust dry-run-rust \
        clean-rust clean-vendor rust-format run-rust-example \
        update-fastlanes-src

build-rust:
	@echo "Building Rust crate (release, $(NUM_JOBS) jobs)…"
	CMAKE_BUILD_PARALLEL_LEVEL=$(NUM_JOBS) \
	$(CARGO) build --release \
	  --manifest-path $(CRATE_ROOT)/Cargo.toml \
	  --jobs $(NUM_JOBS)
	@echo "Rust build complete."

install-rust: build-rust
	@echo "Installing Rust crate into $(PREFIX)…"
	$(C_ENV) \
	$(CARGO) install \
	  --path $(CRATE_ROOT) \
	  --root $(PREFIX) \
	  --jobs $(NUM_JOBS)

# ── Publish helpers ─────────────────────────────────────────────
publish-rust:
	@echo "Publishing Rust crate to crates.io…"
	$(C_ENV) \
	RUSTFLAGS="-L$(PREFIX)/lib" \
	$(CARGO) publish --manifest-path $(CRATE_ROOT)/Cargo.toml

dry-run-rust:
	@echo "Dry-run publishing Rust crate…"
	$(C_ENV) \
	RUSTFLAGS="-L$(PREFIX)/lib" \
	$(CARGO) publish --manifest-path $(CRATE_ROOT)/Cargo.toml --dry-run

# ----------------------------------------------------------------
# Clean & misc
# ----------------------------------------------------------------
clean-vendor:
	@echo "Removing vendored FastLanes sources …"
	@rm -rf $(VENDOR_DIR)
	@git rm -r --cached $(VENDOR_DIR) 2>/dev/null || true

clean-rust: clean-vendor
	@echo "Cleaning Rust build …"
	$(CARGO) clean --manifest-path $(CRATE_ROOT)/Cargo.toml
	@echo "Rust clean complete."

run-rust-example: build-rust
	@echo "Running Rust example ‘rust_example’…"
	cd $(CRATE_ROOT) && \
	CC="$(CC)" CXX="$(CXX)" \
	C_INCLUDE_PATH="$(PREFIX)/include" \
	LIBRARY_PATH="$(PREFIX)/lib" \
	cargo run --jobs $(NUM_JOBS) --example rust_example

rust-format:
	@echo "Formatting Rust sources …"
	$(CARGO) fmt --manifest-path $(CRATE_ROOT)/Cargo.toml
	@echo "Rust formatting complete."

# ----------------------------------------------------------------
# Vendored-source maintenance helper
#   • Re-create rust/vendor/fastlanes from the current workspace
#     while skipping build artefacts.
# ----------------------------------------------------------------
update-fastlanes-src:
	@echo "▶ Refreshing vendored FastLanes sources from workspace …"

	# 1) Start from a clean slate
	@rm -rf $(VENDOR_DIR)
	@mkdir -p $(VENDOR_DIR)

	# 2) Copy the source folders & top-level CMakeLists.txt
	rsync -a --delete \
	    --exclude='.git' \
	    --exclude='build' \
	    --exclude='CMakeFiles' \
	    --exclude='*.o' --exclude='*.obj' --exclude='*.d' \
	    --exclude='*.a' --exclude='*.so' --exclude='*.dylib' --exclude='*.dll' \
	    --exclude='Makefile' \
	    --exclude='*cmake_install.cmake' --exclude='*CTestTestfile.cmake' \
	    $(PROJECT_DIR)/CMakeLists.txt \
	    $(PROJECT_DIR)/include \
	    $(PROJECT_DIR)/src \
	    $(VENDOR_DIR)/

	@echo "▶ Staging refreshed vendored sources …"
	@git add $(VENDOR_DIR)

	# 3) Commit only if something actually changed
	@git diff --cached --quiet || \
	  git commit -m "Refresh vendored FastLanes sources from workspace" || true



endif  # RUST_MK_INCLUDED
