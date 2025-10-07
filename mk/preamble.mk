# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/preamble.mk
# ────────────────────────────────────────────────────────
ifndef PREAMBLE_MK_INCLUDED
PREAMBLE_MK_INCLUDED := yes

# mk/preamble.mk — Helpers for colored echo + root paths

# ── Coloring (portable; disable with COLOR=0) ───────────
COLOR ?= 1
ifeq ($(COLOR),1)
  _Y := $(shell tput setaf 3 2>/dev/null || printf '\033[0;33m')
  _G := $(shell tput setaf 2 2>/dev/null || printf '\033[0;32m')
  _R := $(shell tput sgr0   2>/dev/null || printf '\033[0m')
else
  _Y :=
  _G :=
  _R :=
endif

define echo_done
	@printf '%s%s%s\n' '$(_G)' '$(1)' '$(_R)'
endef

define echo_start
	@printf '%s%s%s\n' '$(_Y)' '$(1)' '$(_R)'
endef

# ── Root paths ──────────────────────────────────────────
MKFILE_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
ifeq ($(notdir $(MKFILE_DIR)),mk)
  REPO_ROOT ?= $(abspath $(MKFILE_DIR)/..)
else
  REPO_ROOT ?= $(MKFILE_DIR)
endif

CRATE_ROOT ?= $(REPO_ROOT)/rust

# ── Parallelism ─────────────────────────────────────────
NUM_JOBS ?= $(shell                                      \
	if command -v nproc >/dev/null 2>&1; then           \
	  nproc --all;                                      \
	elif command -v sysctl >/dev/null 2>&1; then        \
	  sysctl -n hw.logicalcpu;                          \
	else                                                \
	  echo $${NUMBER_OF_PROCESSORS:-1};                 \
	fi)

# ── Exports & Info ──────────────────────────────────────
export REPO_ROOT CRATE_ROOT NUM_JOBS

# only print when VERBOSE=1
ifeq ($(VERBOSE),1)
$(info REPO_ROOT:   $(REPO_ROOT))
$(info CRATE_ROOT:  $(CRATE_ROOT))
$(info NUM_JOBS:    $(NUM_JOBS))
endif

# ── CI helper ───────────────────────────────────────────
.PHONY: detect-cpu
detect-cpu:
	@echo "BUILD_THREADS=$(NUM_JOBS)"

endif # PREAMBLE_MK_INCLUDED
