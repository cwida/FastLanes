# ─────────────────────────────────────────────────────────────
# Settings
# ─────────────────────────────────────────────────────────────
VENV := .venv

# pick the right venv‐paths on Windows vs. Unix
ifeq ($(OS),Windows_NT)
  PYTHON   := $(VENV)/Scripts/python.exe
  PIP      := $(VENV)/Scripts/pip.exe
  ACTIVATE := $(VENV)/Scripts/activate
else
  PYTHON   := $(VENV)/bin/python3
  PIP      := $(VENV)/bin/pip
  ACTIVATE := $(VENV)/bin/activate
endif

# Clean artefacts that skbuild-core creates
CLEAN_SKBUILD := rm -rf skbuild-editable dist

# ─────────────────────────────────────────────────────────────
# Helpers for colored echo
# ─────────────────────────────────────────────────────────────
define echo_done
	@echo "\033[0;32m$(1)\033[0m"
endef

define echo_start
	@echo "\033[0;33m$(1)\033[0m"
endef

# ─────────────────────────────────────────────────────────────
# Virtual-env bootstrap
# ─────────────────────────────────────────────────────────────
$(ACTIVATE):
	$(call echo_start,🐍 Setting up virtual environment…)
	python3 -m venv $(VENV)
	$(call echo_done,🐍 Virtual environment setup complete.)
	$(call echo_start,📦 Installing base Python dependencies…)
	$(PYTHON) -m pip install --upgrade pip
	$(PYTHON) -m pip install clang-format Faker
	$(call echo_done,📦 Base Python dependencies installed.)

# ─────────────────────────────────────────────────────────────
# Clang-format helpers
# ─────────────────────────────────────────────────────────────
IMAGE := ghcr.io/azimafroozeh/clang-format-python/clang-format-python:14

format:
	$(call echo_start,Formatting…)
	docker run --rm -v "$$(pwd)":/app -w /app $(IMAGE) \
	    bash -c "python3 scripts/run-clang-format.py -r examples include src benchmark python test data/include -i --exclude include/fls/json/nlohmann"
	$(call echo_done,Formatting complete.)

clang-format:
	$(call echo_start,Running clang-format with Docker…)
	docker run --rm -v "$$(pwd)":/app -w /app ubuntu:22.04 \
	    bash -c "apt update && apt install -y python3 clang-format-14 && ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	             python3 scripts/run-clang-format.py -r examples include src benchmark test data/include python -i --exclude include/fls/json/nlohmann"
	$(call echo_done,clang-format run complete.)

format-check:
	$(call echo_start,Checking formatting…)
	docker run --rm -v "$$(pwd)":/app -w /app ubuntu:22.04 \
	    bash -c "apt update && apt install -y clang-format-14 python3 && ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	             python3 scripts/run-clang-format.py -r examples include src benchmark test data/include python --exclude include/fls/json/nlohmann"
	$(call echo_done,Formatting check complete.)

# ─────────────────────────────────────────────────────────────
# Data & history helpers
# ─────────────────────────────────────────────────────────────
generate_synthetic_data: $(ACTIVATE)
	$(call echo_start,🐣 Generating synthetic data…)
	$(PIP) install Faker
	cd scripts && PYTHONPATH=$(PWD) ../$(PYTHON) generate_synthetic_data.py \
		--num-records 5000 \
		--output ../data/synthetic_users.csv
	$(call echo_done,Synthetic data generated.)

check_fastlanes_result_history: $(ACTIVATE)
	$(call echo_start,Checking CSV history…)
	cd scripts && ../$(PYTHON) check_fastlanes_result_history.py
	$(call echo_done,CSV history check complete.)

time_ctest:
	$(call echo_start,Running ctest with timing…)
	cd cmake-build-release && time ctest --output-on-failure
	$(call echo_done,ctest run complete.)

# ─────────────────────────────────────────────────────────────
# Python bindings
# ─────────────────────────────────────────────────────────────
PY_DEPS = \
  cmake>=3.22 \
  "scikit-build-core>=0.11,<0.12" \
  "pybind11>=2.12,<2.13" \
  "setuptools_scm[toml]>=7,<8" \
  pytest \
  ninja>=1.5 \
  pyproject_metadata \
  Faker

TEST_DIR := python/tests

# Helper: quote each dep, skip empties
quote_deps = $(foreach dep,$(PY_DEPS),$(dep))

.PHONY: check_python_deps rebuild_python_debug rebuild_python_release \
        clean_python run_example_python test_python \
        build_wheel_release upload_pypi upload_testpypi build_sdist \
        generate_footer

check_python_deps: $(ACTIVATE)
	$(call echo_start,📦 Ensuring Python build deps…)
	$(PIP) install --upgrade $(call quote_deps)
	$(call echo_done,Python build dependencies ensured.)

rebuild_python_debug: $(ACTIVATE)
	$(call echo_start,🔄 Rebuilding PyFastLanes bindings (Debug)…)
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Debug \
	CMAKE_BUILD_PARALLEL_LEVEL=12 \
	CMAKE_VERBOSE_MAKEFILE=ON \
	PIP_VERBOSE=1 \
	$(PYTHON) -m pip install -e . --no-build-isolation -v
	$(call echo_done,PyFastLanes bindings rebuilt (Debug).)

rebuild_python_release: $(ACTIVATE)
	$(call echo_start,🚀 Rebuilding PyFastLanes bindings (Release)…)
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Release \
	CMAKE_BUILD_PARALLEL_LEVEL=12 \
	CMAKE_VERBOSE_MAKEFILE=ON \
	PIP_VERBOSE=1 \
	$(PYTHON) -m pip install -e . --no-build-isolation -v
	$(call echo_done,PyFastLanes bindings rebuilt (Release).)

clean_python:
	$(call echo_start,🧹 Cleaning Python artefacts…)
	rm -rf skbuild-editable dist
	find python/pyfastlanes -name '_pyfastlanes*.so' -delete
	find . -name '__pycache__'   -exec rm -rf {} +
	find . -name '*.pyc'         -delete
	$(call echo_done,Python artefacts cleaned.)

run_example_python: $(ACTIVATE)
	$(call echo_start,🚀 Running example…)
	$(PYTHON) examples/python_example.py
	$(call echo_done,Example run complete.)

test_python: rebuild_python_release
	$(call echo_start,🧪 Running unit tests…)
	PYTHONPATH=$(PWD)/python $(PYTHON) -m pytest -q $(TEST_DIR)
	$(call echo_done,Unit tests complete.)

# ─────────────────────────────────────────────────────────────
# Wheel build & upload
# ─────────────────────────────────────────────────────────────
build_wheel_release: $(ACTIVATE)
	$(call echo_start,📦 Building PyFastLanes wheel (Release)…)
	$(PIP) install --upgrade $(call quote_deps)
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Release \
	CMAKE_BUILD_PARALLEL_LEVEL=12 \
	CMAKE_VERBOSE_MAKEFILE=ON \
	PIP_VERBOSE=1 \
	$(PYTHON) -m build --wheel --no-isolation --outdir dist
	$(call echo_done,PyFastLanes wheel built (Release).)

upload_pypi: $(ACTIVATE)
	$(call echo_start,🚀 Uploading to PyPI…)
	$(PYTHON) -m twine upload dist/*
	$(call echo_done,Upload to PyPI complete.)

upload_testpypi: $(ACTIVATE)
	$(call echo_start,🧪 Uploading to TestPyPI…)
	$(PYTHON) -m twine upload --repository testpypi dist/*
	$(call echo_done,Upload to TestPyPI complete.)

build_sdist: $(ACTIVATE)
	$(call echo_start,📦 Building source distribution…)
	$(PIP) install --upgrade setuptools wheel
	$(PIP) install --upgrade $(call quote_deps)
	$(PYTHON) -m build --sdist --no-isolation --outdir dist
	$(call echo_done,Source distribution built.)

# ─────────────────────────────────────────────────────────────
# Generate FlatBuffers C++ code for footer schema (with DataType)
# ─────────────────────────────────────────────────────────────
FBS_DIR := flatbuffers_schemas
FBS_OUT := include/fls/footer

generate_footer:
	$(call echo_start,🔍 Checking for schema files…)
	@if [ ! -d "$(FBS_DIR)" ]; then \
	  echo "❌ Schema directory '$(FBS_DIR)' not found."; exit 1; \
	fi
	@if [ ! -f "$(FBS_DIR)/datatype.fbs" ]; then \
	  echo "❌ '$(FBS_DIR)/datatype.fbs' not found."; exit 1; \
	fi
	@if [ ! -f "$(FBS_DIR)/footer.fbs" ]; then \
	  echo "❌ '$(FBS_DIR)/footer.fbs' not found."; exit 1; \
	fi
	$(call echo_done,Schema files check complete.)

	$(call echo_start,📦 Generating FlatBuffers C++ (footer + datatype)…)
	@mkdir -p "$(FBS_OUT)"
	@flatc --cpp \
	       --gen-object-api \
	       --scoped-enums \
	       --no-emit-min-max-enum-values \
	       -I "$(FBS_DIR)" \
	       -o "$(FBS_OUT)" \
	       "$(FBS_DIR)/datatype.fbs" \
	       "$(FBS_DIR)/decimal_type.fbs" \
	       "$(FBS_DIR)/footer.fbs" \
	       "$(FBS_DIR)/operator_token.fbs" \
	       "$(FBS_DIR)/rpn.fbs" \
	       "$(FBS_DIR)/column_descriptor.fbs" \
	       "$(FBS_DIR)/rowgroup_descriptor.fbs" \
	       "$(FBS_DIR)/table_descriptor.fbs"
	$(call echo_done,✅ FlatBuffers C++ generated in $(FBS_OUT))
