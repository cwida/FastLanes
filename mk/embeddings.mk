# mk/embeddings.mk
# -------------------------------------------------------------------------------
# Usage:
#   make install     # create .venv (if needed) and install dependencies
#   make generate    # run generate_embedding.py inside .venv
#   make clean       # remove __pycache__ directories
#   make venv-clean  # delete the .venv folder
# -------------------------------------------------------------------------------

VENV_DIR := .venv

ifeq ($(OS),Windows_NT)
  PYTHON := $(VENV_DIR)/Scripts/python.exe
  PIP    := $(VENV_DIR)/Scripts/pip.exe
else
  PYTHON := $(VENV_DIR)/bin/python
  PIP    := $(VENV_DIR)/bin/pip
endif

.DEFAULT_GOAL := help

.PHONY: help venv install generate clean venv-clean

help:
	@echo "Available targets:"
	@echo "  make install     ─ Create .venv (if missing) and install dependencies"
	@echo "  make generate    ─ Ensure .venv is ready, then run generate_embedding.py"
	@echo "  make clean       ─ Delete all __pycache__ folders"
	@echo "  make venv-clean  ─ Remove the entire .venv folder"

venv:
	@if [ ! -d "$(VENV_DIR)" ]; then \
		echo "Creating virtualenv at $(VENV_DIR)..."; \
		python3 -m venv $(VENV_DIR); \
	else \
		echo "$(VENV_DIR) already exists."; \
	fi

install: venv
	@echo "Upgrading pip inside $(VENV_DIR)..."
	$(PIP) install --upgrade pip
	@echo "Installing torch, torchvision, numpy, pandas, pyarrow into $(VENV_DIR)..."
	$(PIP) install torch torchvision numpy pandas pyarrow

generate: install
	@echo "Running generate_embedding.py inside $(VENV_DIR)..."
	$(PYTHON) ../scripts/generate_embedding.py

clean:
	@echo "Cleaning up __pycache__..."
	find . -type d -name "__pycache__" -exec rm -rf {} +

venv-clean:
	@echo "Deleting $(VENV_DIR)..."
	rm -rf $(VENV_DIR)
