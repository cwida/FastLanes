# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/venv.mk
# ────────────────────────────────────────────────────────
ifndef VENV_TARGET_DEFINED
VENV_TARGET_DEFINED := 1

VENV_DIR := ../.venv

.PHONY: venv
venv:
	@test -d $(VENV_DIR) || python3 -m venv $(VENV_DIR)

endif
