# ─────────────────────────────────────────────────────────────
# Root Makefile
# ─────────────────────────────────────────────────────────────
SHELL := /usr/bin/env bash

# any global vars/helpers you still want here…
# (e.g. your echo_done / echo_start definitions)

MK_DIR := mk

# include **all** .mk files under mk/
-include $(wildcard $(MK_DIR)/*.mk)

.PHONY: all clean

# build whatever non-python bits you still have:
all: build-cpp build-rust  # etc…

clean:
	@$(MAKE) clean-cpp
	@$(MAKE) clean-rust
	@$(MAKE) clean-python
