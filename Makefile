VENV := .venv

# OS-aware Python/Pip paths
ifeq ($(OS),Windows_NT)
  PYTHON := $(VENV)/Scripts/python.exe
  PIP := $(VENV)/Scripts/pip.exe
else
  PYTHON := $(VENV)/bin/python3
  PIP := $(VENV)/bin/pip
endif

# Define echo_green for colored output
define echo_green
	@echo "\033[0;32m$(1)\033[0m"
endef

# Marker for virtualenv setup
$(VENV)/.created:
	$(call echo_green, "Setting up virtual environment...")
	python3 -m venv $(VENV)
	$(call echo_green, "Installing dependencies...")
	$(PIP) install --upgrade pip
	$(PIP) install clang-format faker  # Add other dependencies here
	@touch $@

IMAGE := ghcr.io/azimafroozeh/clang-format-python/clang-format-python:14

format:
	$(call echo_green,"Formatting…")
	docker run --rm -v "$$(pwd)":/app -w /app $(IMAGE) bash -c "\
	    python3 scripts/run-clang-format.py -r examples include src benchmark test data/include \
	    -i --exclude include/fls/json/nlohmann"

format-check:
	$(call echo_green,"Checking formatting…")
	docker run --rm -v "$$(pwd)":/app -w /app $(IMAGE) bash -c "\
	    python3 scripts/run-clang-format.py -r examples include src benchmark test data/include \
	    --exclude include/fls/json/nlohmann"

# Run clang-format using Docker (with install step)
clang-format:
	$(call echo_green, "Running clang-format with Docker for consistent formatting...")
	docker run --rm -v "$$(pwd)":/app -w /app ubuntu:22.04 bash -c "\
	    apt update && \
	    apt install -y python3 clang-format-14 && \
	    ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	    python3 scripts/run-clang-format.py -r examples include src benchmark test data/include -i --exclude include/fls/json/nlohmann"

# Generate synthetic data
generate_synthetic_data: $(VENV)/.created
	$(call echo_green, "Generating synthetic data...")
	cd scripts && PYTHONPATH=$(PWD) ../$(PYTHON) generate_synthetic_data.py

# Run CSV history script
check_fastlanes_result_history: $(VENV)/.created
	$(call echo_green, "Checking CSV history and comparing versions...")
	cd scripts && ../$(PYTHON) check_fastlanes_result_history.py

# Time ctest
time_ctest:
	$(call echo_green, "Running ctest with timing...")
	cd cmake-build-release && time ctest --output-on-failure
