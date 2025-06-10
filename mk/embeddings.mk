# Makefile for fls_embedding_issues (with .venv + torch, torchvision, numpy, pandas, pyarrow)
# -------------------------------------------------------------------------------
# Usage:
#   make install    # create .venv (if needed) and install dependencies
#   make run        # run embedding.py inside .venv
#   make clean      # remove __pycache__ directories
#   make venv-clean # delete the .venv folder

# Directory for the virtual environment
VENV_DIR := .venv

# Paths inside the virtualenv
PYTHON := $(VENV_DIR)/bin/python
PIP    := $(VENV_DIR)/bin/pip

.DEFAULT_GOAL := help

.PHONY: help venv install run clean venv-clean

help:
	@echo "Available targets:"
	@echo "  make install     ─ Create .venv (if missing) and install dependencies"
	@echo "  make run         ─ Ensure .venv is ready, then run embedding.py"
	@echo "  make clean       ─ Delete all __pycache__ folders"
	@echo "  make venv-clean  ─ Remove the entire .venv folder"

# Create a new virtual environment if it doesn't exist
venv:
	@if [ ! -d "$(VENV_DIR)" ]; then \
		echo "Creating virtualenv at $(VENV_DIR)..."; \
		python3 -m venv $(VENV_DIR); \
	else \
		echo ".venv already exists."; \
	fi

# Install torch, torchvision, numpy, pandas, and pyarrow into the venv
install: venv
	@echo "Upgrading pip inside .venv..."
	$(PIP) install --upgrade pip
	@echo "Installing torch, torchvision, numpy, pandas, and pyarrow into .venv..."
	$(PIP) install torch torchvision numpy pandas pyarrow

# Run embedding.py using the venv’s python interpreter
run: install
	@echo "Running embedding.py inside .venv..."
	$(PYTHON) ../scripts/generate_embedding.py

# Remove all __pycache__ folders
clean:
	@echo "Cleaning up __pycache__..."
	find . -type d -name "__pycache__" -exec rm -rf {} +

# Delete the entire .venv folder (so you can start fresh)
venv-clean:
	@echo "Deleting $(VENV_DIR)..."
	rm -rf $(VENV_DIR)
