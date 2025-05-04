# ---------------------------------------------------------------------------
# Virtual-env configuration (cross-platform)
# ---------------------------------------------------------------------------
VENV := .venv

ifeq ($(OS),Windows_NT)
  PYTHON := $(VENV)/Scripts/python.exe
else
  PYTHON := $(VENV)/bin/python3
endif

PIP := $(PYTHON) -m pip   # always use python -m pip

# Coloured echo helper
define echo_green
	@echo "\033[0;32m$(1)\033[0m"
endef

# ---------------------------------------------------------------------------
# Virtual-env bootstrap (creates a marker file .created)
# ---------------------------------------------------------------------------
$(VENV)/.created:
	$(call echo_green, "Setting up virtual environment...")
	python3 -m venv $(VENV)

	$(call echo_green, "Installing dependencies...")
	$(PIP) install --upgrade pip
	$(PIP) install clang-format faker   # add other deps as needed
	@touch $@

# ---------------------------------------------------------------------------
# Formatting helpers (via pre-built docker image)
# ---------------------------------------------------------------------------
IMAGE := ghcr.io/azimafroozeh/clang-format-python/clang-format-python:14
SRC_DIRS := examples include src benchmark test data/include
EXCLUDE  := --exclude include/fls/json/nlohmann

format:
	$(call echo_green, "Formatting sources…")
	docker run --rm -v "$$(pwd)":/app -w /app $(IMAGE) bash -c \
	    "python3 scripts/run-clang-format.py -r $(SRC_DIRS) -i $(EXCLUDE)"

format-check:
	$(call echo_green, "Checking formatting…")
	docker run --rm -v "$$(pwd)":/app -w /app $(IMAGE) bash -c \
	    "python3 scripts/run-clang-format.py -r $(SRC_DIRS) $(EXCLUDE)"

# Optional: run clang-format inside a vanilla Ubuntu container
clang-format:
	$(call echo_green, "Running clang-format in vanilla Ubuntu container…")
	docker run --rm -v "$$(pwd)":/app -w /app ubuntu:22.04 bash -c '\
	  apt update && \
	  apt install -y python3 clang-format-14 && \
	  ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	  python3 scripts/run-clang-format.py -r $(SRC_DIRS) -i $(EXCLUDE)'

# ---------------------------------------------------------------------------
# Synthetic data & helper scripts
# ---------------------------------------------------------------------------
generate_synthetic_data: $(VENV)/.created
	$(call echo_green, "Generating synthetic data…")
	cd scripts && PYTHONPATH=$(PWD) ../$(PYTHON) generate_synthetic_data.py

check_fastlanes_result_history: $(VENV)/.created
	$(call echo_green, "Checking FastLanes result history…")
	cd scripts && ../$(PYTHON) check_fastlanes_result_history.py

# ---------------------------------------------------------------------------
# Misc utilities
# ---------------------------------------------------------------------------
time_ctest:
	$(call echo_green, "Running ctest with timing…")
	cd cmake-build-release && time ctest --output-on-failure

# ---------------------------------------------------------------------------
# Declare phony targets
# ---------------------------------------------------------------------------
.PHONY: format format-check clang-format \
        generate_synthetic_data check_fastlanes_result_history time_ctest
