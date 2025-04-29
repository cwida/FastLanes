VENV := .venv
PYTHON := $(VENV)/bin/python3
PIP := $(VENV)/bin/pip

# Define echo_green for colored output
define echo_green
	@echo "\033[0;32m$(1)\033[0m"
endef

# Ensure virtual environment is created
$(VENV)/bin/activate:
	$(call echo_green, "Setting up virtual environment...")
	python3 -m venv $(VENV)
	$(call echo_green, "Installing dependencies...")
	$(PIP) install --upgrade pip
	$(PIP) install clang-format faker  # Add other dependencies here

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


# Generate synthetic data
generate_syntethic_data: $(VENV)/bin/activate
	$(call echo_green, "Generating synthetic data")
	cd scripts && PYTHONPATH=$(PWD) ../$(PYTHON) generate_synthetic_data.py

# Run CSV history script
check_fastlanes_result_history: $(VENV)/bin/activate
	$(call echo_green, "Checking CSV history and comparing versions...")
	cd scripts && ../$(PYTHON) check_fastlanes_result_history.py

# Time ctest
time_ctest:
	$(call echo_green, "Running ctest with timing...")
	cd cmake-build-release && time ctest --output-on-failure
