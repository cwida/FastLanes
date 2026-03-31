# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/embeddings.mk
# ────────────────────────────────────────────────────────
# -----------------------------------------------------------
# Targets:
#   make install-embeddings-python – create .venv & install deps
#   make generate-embeddings       – run generate_embedding.py
#   make clean-embeddings          – delete __pycache__
#   make venv-clean                – remove .venv entirely
# -----------------------------------------------------------

include mk/venv.mk

PROJECT_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)
VENV_DIR     := $(PROJECT_ROOT)/.venv
SCRIPTS_DIR  := $(PROJECT_ROOT)/scripts
SCRIPT       := $(abspath $(SCRIPTS_DIR)/generate_embedding.py)

ifeq ($(OS),Windows_NT)
  VENV_PY := $(VENV_DIR)/Scripts/python.exe
else
  VENV_PY := $(VENV_DIR)/bin/python
endif

.DEFAULT_GOAL := help
.PHONY: help install-embeddings-python generate-embeddings clean-embeddings venv-clean

help:
	@echo "Targets:"
	@echo "  make install-embeddings-python  – create .venv & install deps"
	@echo "  make generate-embeddings        – run generate_embedding.py"
	@echo "  make clean-embeddings           – delete __pycache__"
	@echo "  make venv-clean                 – remove .venv"

# 1️⃣  Install deps (and auto-repair if venv was built with Python 3.13)
install-embeddings-python: venv
	@if [ -f "$(VENV_DIR)/pyvenv.cfg" ] && \
	    grep -qE '^version = 3\.13' "$(VENV_DIR)/pyvenv.cfg"; then \
	    echo "⚠️  .venv uses Python 3.13 — recreating with ‘python’ on PATH"; \
	    rm -rf "$(VENV_DIR)"; \
	    python -m venv "$(VENV_DIR)"; \
	fi

	# ── 1. upgrade pip ────────────────────────────────────────────
	"$(VENV_PY)" -m pip install --upgrade pip

	# ── 2. install NumPy-1.x (+ pandas / pyarrow versions still built on it)
	"$(VENV_PY)" -m pip install "numpy<2" "pandas<2.3" "pyarrow<16"

	# ── 3. install PyTorch / torchvision from the official wheel index
	"$(VENV_PY)" -m pip install torch torchvision \
	              --extra-index-url https://download.pytorch.org/whl/cpu

# 2️⃣  Generate embeddings
generate-embeddings: install-embeddings-python
	@echo "Running generate_embedding.py with $$($(VENV_PY) --version) …"
	"$(VENV_PY)" "$(SCRIPT)"

# 3️⃣  House-keeping helpers
clean-embeddings:
	find . -type d -name "__pycache__" -exec rm -rf {} +

venv-clean:
	rm -rf "$(VENV_DIR)"
