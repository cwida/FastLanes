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
# FastLanes – cross-platform Makefile preamble
# ─────────────────────────────────────────────────────────────
VENV := .venv

# --- venv paths differ on Windows vs. Unix ------------------
ifeq ($(OS),Windows_NT)
  ACTIVATE := $(VENV)/Scripts/activate
  PYTHON   := $(VENV)/Scripts/python.exe
else
  ACTIVATE := $(VENV)/bin/activate
  PYTHON   := $(VENV)/bin/python3
endif

PIP := $(PYTHON) -m pip   # ← always use the OS-specific python above


# --- pick the interpreter that *creates* the venv -----------
ifeq ($(OS),Windows_NT)
  CREATE_PY := py -3
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Darwin)
    BREW_PYTHON ?= /opt/homebrew/bin/python3
    ALT_BREW_PY ?= /usr/local/bin/python3
    ifneq ($(shell test -x $(BREW_PYTHON) && echo yes),yes)
      ifeq ($(shell test -x $(ALT_BREW_PY) && echo yes),yes)
        BREW_PYTHON := $(ALT_BREW_PY)
      else
        BREW_PYTHON := python3
      endif
    endif
    CREATE_PY := $(BREW_PYTHON)
  else
    CREATE_PY := python3
  endif
endif


# ─────────────────────────────────────────────────────────────
# Virtual-env bootstrap
# ─────────────────────────────────────────────────────────────
$(ACTIVATE):
	$(call echo_start,Setting up virtual environment…)
	rm -rf $(VENV)
	$(CREATE_PY) -m venv $(VENV)
	$(call echo_done,Virtual environment setup complete.)

	$(call echo_start,Installing base Python dependencies…)
	$(PYTHON) -m pip install --upgrade pip
	$(PYTHON) -m pip install clang-format Faker
	$(call echo_done,Base Python dependencies installed.)


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
	$(call echo_start,Generating synthetic data…)
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
# Python bindings & packaging
# ─────────────────────────────────────────────────────────────
PY_DEPS = \
  cmake>=3.22 \
  "scikit-build-core>=0.11,<0.12" \
  "pybind11>=2.12,<2.13" \
  "setuptools_scm[toml]>=7,<8" \
  pytest \
  ninja>=1.5 \
  pyproject_metadata \
  Faker \
  twine>=4.0.0

TEST_DIR := python/tests
quote_deps = $(foreach dep,$(PY_DEPS),$(dep))

.PHONY: check_python_deps rebuild_python_debug rebuild_python_release \
        clean_python run_example_python test_python \
        build_wheel_release upload_pypi upload_testpypi build_sdist \
        generate_footer

check_python_deps: $(ACTIVATE)
	$(call echo_start,Ensuring Python build deps…)
	$(PIP) install --upgrade $(call quote_deps)
	$(call echo_done,Python build dependencies ensured.)

rebuild_python_debug: check_python_deps $(ACTIVATE)
	$(call echo_start,Rebuilding PyFastLanes bindings (Debug)…)
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_PARALLEL_LEVEL=12 \
	CMAKE_VERBOSE_MAKEFILE=ON \
	PIP_VERBOSE=1 \
	$(PYTHON) -m pip install -e . --no-build-isolation -v \
	  --config-settings=cmake.build-type=Debug
	$(call echo_done,PyFastLanes bindings rebuilt (Debug).)


rebuild_python_release: check_python_deps $(ACTIVATE)
	$(call echo_start,Rebuilding PyFastLanes bindings (Release)…)
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Release \
	  CMAKE_BUILD_PARALLEL_LEVEL=12 \
	  CMAKE_VERBOSE_MAKEFILE=ON \
	  PIP_VERBOSE=1 \
	  $(PYTHON) -m pip install -e . --no-build-isolation -v
	$(call echo_done,PyFastLanes bindings rebuilt (Release).)

clean_python:
	$(call echo_start, Cleaning Python artefacts…)
	# Remove scikit-build editable tree, distribution archives, and the virtual environment
	rm -rf skbuild-editable dist .venv
	# Delete any built extension modules (in case they linger elsewhere)
	find python/pyfastlanes -name '_pyfastlanes*.so' -delete
	# Purge byte-code caches
	find . -name '__pycache__'   -exec rm -rf {} +
	find . -name '*.pyc'         -delete
	$(call echo_done, Python artefacts cleaned.)


run_example_python: $(ACTIVATE)
	$(call echo_start,Running example…)
	$(PYTHON) examples/python_example.py
	$(call echo_done,Example run complete.)

test_python: rebuild_python_release
	$(call echo_start,Running unit tests…)
	PYTHONPATH=$(PWD)/python $(PYTHON) -m pytest -q $(TEST_DIR)
	$(call echo_done,Unit tests complete.)

incremental_python_release: check_python_deps $(ACTIVATE)
	$(call echo_start,Incremental rebuild PyFastLanes bindings (Release)…)
	CMAKE_BUILD_TYPE=Release \
	  CMAKE_BUILD_PARALLEL_LEVEL=12 \
	  CMAKE_VERBOSE_MAKEFILE=ON \
	  PIP_VERBOSE=1 \
	  $(PYTHON) -m pip install -e . --no-build-isolation -v
	$(call echo_done,Incremental build complete.)

incremental_python_debug: check_python_deps $(ACTIVATE)
	$(call echo_start,Incremental debug rebuild PyFastLanes bindings…)
	CMAKE_BUILD_TYPE=Debug \
	  CMAKE_BUILD_PARALLEL_LEVEL=12 \
	  CMAKE_VERBOSE_MAKEFILE=ON \
	  PIP_VERBOSE=1 \
	  $(PYTHON) -m pip install -e . --no-build-isolation -v
	$(call echo_done,Incremental debug build complete.)

build_wheel_release: check_python_deps $(ACTIVATE)
	$(call echo_start,Building PyFastLanes wheel (Release)…)
	$(PIP) install --upgrade $(call quote_deps)
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Release \
	  CMAKE_BUILD_PARALLEL_LEVEL=12 \
	  CMAKE_VERBOSE_MAKEFILE=ON \
	  PIP_VERBOSE=1 \
	  $(PYTHON) -m build --wheel --no-isolation --outdir dist
	$(call echo_done,PyFastLanes wheel built (Release).)

upload_pypi: check_python_deps $(ACTIVATE)
	$(call echo_start,Uploading to PyPI…)
	$(PYTHON) -m twine upload dist/*
	$(call echo_done,Upload to PyPI complete.)

upload_testpypi: check_python_deps $(ACTIVATE)
	$(call echo_start,Uploading to TestPyPI…)
	$(PYTHON) -m twine upload --repository testpypi dist/*
	$(call echo_done,Upload to TestPyPI complete.)

build_sdist: check_python_deps $(ACTIVATE)
	$(call echo_start,Building source distribution…)
	$(PIP) install --upgrade setuptools wheel build
	$(PIP) install --upgrade $(call quote_deps)
	$(PYTHON) -m build --sdist --no-isolation --outdir dist
	$(call echo_done,Source distribution built.)
