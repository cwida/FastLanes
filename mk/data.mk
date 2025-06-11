# mk/data.mk — Build the synthetic-users CSV
# ------------------------------------------

PROJECT_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)
-include $(PROJECT_ROOT)/mk/python.mk           # non-fatal if missing

VENV   ?= $(PROJECT_ROOT)/.venv
PYTHON ?= $(VENV)/bin/python3                   # python.exe on Win via python.mk
PIP    ?= $(PYTHON) -m pip

DATA_DIR    := $(PROJECT_ROOT)/data
SCRIPTS_DIR := $(PROJECT_ROOT)/scripts
DATA_SCRIPT := $(abspath $(SCRIPTS_DIR)/generate_synthetic_data.py)

.PHONY: generate_synthetic_data time_ctest

# 1️⃣  Generate data/synthetic_users.csv (5 000 rows)
generate_synthetic_data: $(ACTIVATE)
	$(call echo_start,Generating synthetic data…)

	$(PIP) install --upgrade Faker

	@if [ ! -e "$(VENV)/bin/python" ] && [ -e "$(VENV)/bin/python3" ]; then \
		ln -sf python3 "$(VENV)/bin/python"; \
	fi

	PYTHONPATH=$(PROJECT_ROOT) "$(PYTHON)" "$(DATA_SCRIPT)"

	$(call echo_done,Synthetic data generated.)

# 2️⃣  Convenience: run ctest with wall-clock timing
time_ctest:
	$(call echo_start,Running ctest with timing…)
	cd "$(PROJECT_ROOT)/cmake-build-release" && time ctest --output-on-failure
	$(call echo_done,ctest run complete.)
