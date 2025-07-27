# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/preamble.mk
# ────────────────────────────────────────────────────────
ifndef PREAMBLE_MK_INCLUDED
PREAMBLE_MK_INCLUDED := yes

# mk/preamble.mk — Helpers for colored echo + root paths

define echo_done
	@echo "\033[0;32m$(1)\033[0m"
endef

define echo_start
	@echo "\033[0;33m$(1)\033[0m"
endef

# ── Root paths ─────────────────────────────────────────────────────

# if that directory’s name is “mk”, repo-root is its parent; else it is itself
ifeq ($(notdir $(MKFILE_PATH)),mk)
REPO_ROOT := $(abspath $(MKFILE_PATH)/..)
else
REPO_ROOT := $(MKFILE_PATH)
endif

# CRATE_ROOT always under repo
CRATE_ROOT := $(REPO_ROOT)/rust

# ── Parallelism ────────────────────────────────────────────────────
NUM_JOBS := $(shell                            \
	if command -v nproc >/dev/null 2>&1; then  \
	  nproc --all;                           \
	elif command -v sysctl >/dev/null 2>&1; then \
	  sysctl -n hw.logicalcpu;              \
	else                                      \
	  echo $${NUMBER_OF_PROCESSORS:-1};     \
	fi)

# ── Exports & Info ─────────────────────────────────────────────────

export REPO_ROOT CRATE_ROOT NUM_JOBS

# only print during normal runs
ifneq ($(MAKECMDGOALS),detect-cpu)
$(info REPO_ROOT:   $(REPO_ROOT))
$(info CRATE_ROOT:  $(CRATE_ROOT))
$(info NUM_JOBS:    $(NUM_JOBS))
endif

# ── CI helper ─────────────────────────────────────────────────────
.PHONY: detect-cpu
detect-cpu:
	@echo "BUILD_THREADS=$(NUM_JOBS)"

endif # PREAMBLE_MK_INCLUDED
