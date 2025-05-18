# mk/preamble.mk — Helpers for colored echo + root paths

define echo_done
	@echo "\033[0;32m$(1)\033[0m"
endef

define echo_start
	@echo "\033[0;33m$(1)\033[0m"
endef

# ── Root paths ─────────────────────────────────────────────────────

# REPO_ROOT: the directory containing mk/
REPO_ROOT   := $(patsubst %/,%,$(abspath $(dir $(lastword $(MAKEFILE_LIST)))))
# CRATE_ROOT: where your Rust crate lives now
CRATE_ROOT  := $(REPO_ROOT)/rust

# ── Parallelism ────────────────────────────────────────────────────

# NUM_JOBS: number of online processors
NUM_JOBS    := $(shell getconf _NPROCESSORS_ONLN)

# ── Exports & Info ─────────────────────────────────────────────────

export REPO_ROOT CRATE_ROOT NUM_JOBS

# print out for visibility
$(info REPO_ROOT:  $(REPO_ROOT))
$(info CRATE_ROOT: $(CRATE_ROOT))
$(info NUM_JOBS:   $(NUM_JOBS))

# ── CI helper ─────────────────────────────────────────────────────
# detect-cpu
#   Emits a single line   BUILD_THREADS=<n>
#   suitable for appending directly to $GITHUB_ENV
.PHONY: detect-cpu
detect-cpu:
	@{ \
	if command -v nproc >/dev/null 2>&1; then \
	  echo "BUILD_THREADS=$$(nproc --all)"; \
	elif command -v sysctl >/dev/null 2>&1; then \
	  echo "BUILD_THREADS=$$(sysctl -n hw.logicalcpu)"; \
	else \
	  echo "BUILD_THREADS=$${NUMBER_OF_PROCESSORS:-1}"; \
	fi; \
	}
