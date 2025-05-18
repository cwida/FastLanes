# mk/preamble.mk — Helpers for colored echo + root paths

define echo_done
	@echo "\033[0;32m$(1)\033[0m"
endef

define echo_start
	@echo "\033[0;33m$(1)\033[0m"
endef

# ── Root paths ─────────────────────────────────────────────────────

REPO_ROOT   := $(patsubst %/,%,$(abspath $(dir $(lastword $(MAKEFILE_LIST)))))
CRATE_ROOT  := $(REPO_ROOT)/rust

# ── Parallelism ────────────────────────────────────────────────────

# NUM_JOBS: number of logical processors (Linux, macOS, Windows fallback)
NUM_JOBS := $(shell                                                  \
  if command -v nproc >/dev/null 2>&1; then                             \
    nproc --all;                                                       \
  elif command -v sysctl >/dev/null 2>&1; then                          \
    sysctl -n hw.logicalcpu;                                           \
  else                                                                  \
    echo $${NUMBER_OF_PROCESSORS:-1};                                   \
  fi)

# ── Exports & Info ─────────────────────────────────────────────────

export REPO_ROOT CRATE_ROOT NUM_JOBS

# Only print these on normal builds—skip when the sole goal is detect-cpu
ifneq ($(filter detect-cpu,$(MAKECMDGOALS)),detect-cpu)
$(info REPO_ROOT:  $(REPO_ROOT))
$(info CRATE_ROOT: $(CRATE_ROOT))
$(info NUM_JOBS:   $(NUM_JOBS))
endif

# ── CI helper ─────────────────────────────────────────────────────
# detect-cpu: emit exactly BUILD_THREADS=<n>
.PHONY: detect-cpu
detect-cpu:
	@echo "BUILD_THREADS=$(NUM_JOBS)"
