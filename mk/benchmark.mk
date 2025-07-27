# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/benchmark.mk
# ────────────────────────────────────────────────────────
# mk/benchmark.mk
# ────────────────
# Runs benchmark/result/galp/plot.py from *inside* its own folder,
# so the script can see the neighbouring patch.csv file.

# ── Virtual‑env (absolute so it still works after any cd)
VENV_DIR := $(abspath ../.venv)

PYTHON3  := $(VENV_DIR)/bin/python3
PYTHON   := $(if $(wildcard $(PYTHON3)),$(PYTHON3),$(VENV_DIR)/bin/python)
PIP      := $(PYTHON) -m pip

# ── Script location (relative to project root)
PY_SCRIPT       := benchmark/result/galp/plot.py
PY_SCRIPT_DIR   := $(dir $(PY_SCRIPT))     # benchmark/result/galp/
PY_SCRIPT_NAME  := $(notdir $(PY_SCRIPT))  # plot.py

.PHONY: venv plot clean-venv

venv:
	@echo "Creating virtualenv in $(VENV_DIR)…"
	@test -d $(VENV_DIR) || python3 -m venv $(VENV_DIR)
	@echo "Installing deps into venv…"
	@$(PIP) install --upgrade pip pandas matplotlib

plot: venv
	@echo "Plotting from patch.csv…"
	# 1) cd to project root  2) cd into script’s folder  3) run script
	@cd .. && cd $(PY_SCRIPT_DIR) && $(PYTHON) $(PY_SCRIPT_NAME)
	@echo "Done."

clean-venv:
	@rm -rf $(VENV_DIR)
	@echo "Removed venv."
