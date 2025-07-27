# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/quick_fuzz.mk
# ────────────────────────────────────────────────────────
# mk/quick_fuzz.mk

# ──────────────────────────────────────────────────────────
#  Bump & verify fuzz seed helper targets
# ──────────────────────────────────────────────────────────
PYTHON        := python3

# point ROOT at repo root (parent of this mk/ directory)
ROOT          := $(shell dirname $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))

BUMP_SCRIPT   := $(ROOT)/scripts/bump_fuzz_seed.py
VERIFY_SCRIPT := $(ROOT)/scripts/verify_seed_bump.py

# ──────────────────────────────────────────────────────────
#  bump: run the fuzz seed bump script
# ──────────────────────────────────────────────────────────
.PHONY: bump
bump:
	@echo "Bumping fuzz seed…"
	$(PYTHON) $(BUMP_SCRIPT)

# ──────────────────────────────────────────────────────────
#  verify: ensure base_seed is exactly +1 over dev's
# ──────────────────────────────────────────────────────────
.PHONY: verify
verify:
	@echo "Verifying fuzz seed bump…"
	$(PYTHON) $(VERIFY_SCRIPT)
