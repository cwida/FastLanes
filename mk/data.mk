# mk/data.mk — Data & history helpers (cwd-agnostic)

# Project root (parent of mk/)
PROJECT_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

# Include python.mk to pull in ACTIVATE, PYTHON, PIP, and check_python_deps
include $(PROJECT_ROOT)/mk/python.mk

# Data and scripts directories
DATA_DIR := $(PROJECT_ROOT)/data
SCRIPTS  := $(PROJECT_ROOT)/scripts

.PHONY: generate_synthetic_data check_fastlanes_result_history time_ctest

generate_synthetic_data: check_python_deps $(ACTIVATE)
	$(call echo_start,Generating synthetic data…)
	# Ensure Faker is installed in the venv
	$(PIP) install --upgrade Faker
	# Run the data-generation script from the project root
	cd $(SCRIPTS) && \
		PYTHONPATH=$(PROJECT_ROOT) $(PYTHON) generate_synthetic_data.py \
		--num-records 5000 \
		--output $(DATA_DIR)/synthetic_users.csv
	$(call echo_done,Synthetic data generated.)

time_ctest:
	$(call echo_start,Running ctest with timing…)
	# Run from the cmake-build-release directory under project root
	cd $(PROJECT_ROOT)/cmake-build-release && \
		time ctest --output-on-failure
	$(call echo_done,ctest run complete.)