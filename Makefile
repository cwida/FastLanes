# ─────────────────────────────────────────────────────────────
# Root Makefile
# ─────────────────────────────────────────────────────────────
SHELL := /usr/bin/env bash

MK_DIR := mk

-include $(wildcard $(MK_DIR)/*.mk)

.PHONY: all clean

all: build-cpp build-rust  # etc…

clean:
	@$(MAKE) clean-cpp
	@$(MAKE) clean-rust
	@$(MAKE) clean-python
