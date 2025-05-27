# mk/scripts.mk — Scripts helpers (cwd-agnostic)

# Project root (parent of mk/)
PROJECT_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

# Include python.mk to pull in ACTIVATE, PYTHON, PIP, and check_python_deps
include $(PROJECT_ROOT)/mk/python.mk

# Scripts directory
SCRIPTS := $(PROJECT_ROOT)/scripts

.PHONY: run_csv_extractor

run_csv_extractor: check_python_deps $(ACTIVATE)
	$(call echo_start,Running CSV extractor…)
	# Ensure pandas is installed in the venv
	$(PIP) install --upgrade pandas
	# Run the csv_extractor script from the scripts directory
	cd $(SCRIPTS) && \
		PYTHONPATH=$(PROJECT_ROOT) $(PYTHON) csv_extractor.py
	$(call echo_done,CSV extraction complete.)
