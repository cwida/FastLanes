# mk/embeddings.mk — Generate sentence embeddings
# -----------------------------------------------------------
# Targets:
#   make install      – create .venv & install deps
#   make generate     – run generate_embedding.py
#   make clean        – delete __pycache__
#   make venv-clean   – remove .venv entirely
# -----------------------------------------------------------

PROJECT_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)
VENV_DIR     := $(PROJECT_ROOT)/.venv
SCRIPTS_DIR  := $(PROJECT_ROOT)/scripts
SCRIPT       := $(abspath $(SCRIPTS_DIR)/generate_embedding.py)

ifeq ($(OS),Windows_NT)
  PYTHON := $(VENV_DIR)/Scripts/python.exe
  PIP    := $(VENV_DIR)/Scripts/pip.exe
else
  PYTHON := $(VENV_DIR)/bin/python3
  PIP    := $(VENV_DIR)/bin/pip
endif

.DEFAULT_GOAL := help
.PHONY: help venv install generate clean venv-clean

help:
	@echo "Targets:"
	@echo "  make install     – create .venv & install deps"
	@echo "  make generate    – run generate_embedding.py"
	@echo "  make clean       – delete __pycache__"
	@echo "  make venv-clean  – remove .venv"

# 1️⃣  Create virtual-env if missing
venv:
	@if [ ! -d "$(VENV_DIR)" ]; then \
		echo "Creating virtualenv…"; \
		python3 -m venv "$(VENV_DIR)"; \
	else \
		echo ".venv already exists."; \
	fi

# 2️⃣  Install required packages
install: venv
	$(PIP) install --upgrade pip
	$(PIP) install torch torchvision numpy pandas pyarrow

# 3️⃣  Generate embeddings (single absolute command)
generate: install
	@echo "Running generate_embedding.py inside $(VENV_DIR)…"
	"$(PYTHON)" "$(SCRIPT)"

# 4️⃣  House-keeping helpers
clean-embeddings:
	find . -type d -name "__pycache__" -exec rm -rf {} +

venv-clean:
	rm -rf "$(VENV_DIR)"
