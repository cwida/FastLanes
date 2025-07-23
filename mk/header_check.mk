# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/header_check.mk
# ────────────────────────────────────────────────────────
include mk/venv.mk

PYTHON := $(VENV_DIR)/bin/python3
SCRIPT := scripts/header_check.py

.PHONY: check-header fix-header

check-header: venv
	$(PYTHON) $(SCRIPT) --check

fix-header: venv
	$(PYTHON) $(SCRIPT)
