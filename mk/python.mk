# mk/python.mk

# ──────────────────────────────────────────────────────────
#  Python helper targets – build, test, publish wheels
# ──────────────────────────────────────────────────────────
ifndef PYTHON_MK_INCLUDED
PYTHON_MK_INCLUDED := yes

# ─────────────────────────────────────────────────────────────
# Python bindings & packaging  (cwd‑agnostic)
# ─────────────────────────────────────────────────────────────

# Project root is the parent directory of mk/
PROJECT_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

# Virtual‑env and common paths (absolute)
VENV      := $(PROJECT_ROOT)/.venv
DIST_DIR  := $(PROJECT_ROOT)/dist

# --- venv paths differ on Windows vs. Unix ------------------
ifeq ($(OS),Windows_NT)
  ACTIVATE := $(VENV)/Scripts/activate
  PYTHON   := $(VENV)/Scripts/python.exe
else
  ACTIVATE := $(VENV)/bin/activate
  PYTHON   := $(VENV)/bin/python3
endif

PIP := $(PYTHON) -m pip   # always use the project‑local python above

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
# Virtual‑env bootstrap
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

PY_DEPS = \
  'cmake>=3.22' \
  'scikit-build-core>=0.11.3,<0.12' \
  'pybind11>=2.12,<2.13' \
  'setuptools_scm[toml]>=8,<9' \
  'pytest' \
  'ninja>=1.5' \
  'pyproject_metadata' \
  'Faker' \
  'twine>=4.0.0'


TEST_DIR := $(PROJECT_ROOT)/python/tests
quote_deps = $(foreach dep,$(PY_DEPS),$(dep))

.PHONY: check_python_deps rebuild_python_debug rebuild_python_release \
        clean_python run_example_python test_python \
        build_wheel_release upload_pypi upload_testpypi build_sdist \
        generate_footer incremental_python_release incremental_python_debug

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
	$(PYTHON) -m pip install -e $(PROJECT_ROOT) --no-build-isolation -v \
	  --config-settings=cmake.build-type=Debug
	$(call echo_done,PyFastLanes bindings rebuilt (Debug).)

rebuild_python_release: check_python_deps $(ACTIVATE)
	$(call echo_start,Rebuilding PyFastLanes bindings (Release)…)
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Release \
	  CMAKE_BUILD_PARALLEL_LEVEL=12 \
	  CMAKE_VERBOSE_MAKEFILE=ON \
	  PIP_VERBOSE=1 \
	  $(PYTHON) -m pip install -e $(PROJECT_ROOT) --no-build-isolation -v
	$(call echo_done,PyFastLanes bindings rebuilt (Release).)

clean-python:
	$(call echo_start, Cleaning Python artefacts…)
	rm -rf $(PROJECT_ROOT)/skbuild-editable $(DIST_DIR) $(VENV)
	find $(PROJECT_ROOT)/python/pyfastlanes -name '_pyfastlanes*.so' -delete
	find $(PROJECT_ROOT) -name '__pycache__' -exec rm -rf {} +
	find $(PROJECT_ROOT) -name '*.pyc' -delete
	$(call echo_done, Python artefacts cleaned.)

run_example_python: $(ACTIVATE)
	$(call echo_start,Running example…)
	$(PYTHON) $(PROJECT_ROOT)/examples/python_example.py
	$(call echo_done,Example run complete.)

test_python: rebuild_python_release
	$(call echo_start,Running unit tests…)
	PYTHONPATH=$(PROJECT_ROOT)/python $(PYTHON) -m pytest -q $(TEST_DIR)
	$(call echo_done,Unit tests complete.)

incremental_python_release: check_python_deps $(ACTIVATE)
	$(call echo_start,Incremental rebuild PyFastLanes bindings (Release)…)
	CMAKE_BUILD_TYPE=Release \
	  CMAKE_BUILD_PARALLEL_LEVEL=12 \
	  CMAKE_VERBOSE_MAKEFILE=ON \
	  PIP_VERBOSE=1 \
	  $(PYTHON) -m pip install -e $(PROJECT_ROOT) --no-build-isolation -v
	$(call echo_done,Incremental build complete.)

incremental_python_debug: check_python_deps $(ACTIVATE)
	$(call echo_start,Incremental debug rebuild PyFastLanes bindings…)
	CMAKE_BUILD_TYPE=Debug \
	  CMAKE_BUILD_PARALLEL_LEVEL=12 \
	  CMAKE_VERBOSE_MAKEFILE=ON \
	  PIP_VERBOSE=1 \
	  $(PYTHON) -m pip install -e $(PROJECT_ROOT) --no-build-isolation -v
	$(call echo_done,Incremental debug build complete.)

build_wheel_release: check_python_deps $(ACTIVATE)
	$(call echo_start,Building PyFastLanes wheel (Release)…)
	# Ensure the PEP-517 “build” frontend is available
	$(PIP) install --upgrade setuptools wheel build
	# Update any CMake/pybind11/etc. dependencies
	$(PIP) install --upgrade $(call quote_deps)
	$(CLEAN_SKBUILD)
	$(PYTHON) -m build --wheel --no-isolation --outdir $(DIST_DIR) $(PROJECT_ROOT)
	$(call echo_done,PyFastLanes wheel built (Release).)

upload_pypi: check_python_deps $(ACTIVATE)
	$(call echo_start,Uploading to PyPI…)
	$(PYTHON) -m twine upload $(DIST_DIR)/*
	$(call echo_done,Upload to PyPI complete.)

upload_testpypi: check_python_deps $(ACTIVATE)
	$(call echo_start,Uploading to TestPyPI…)
	$(PYTHON) -m twine upload --repository testpypi $(DIST_DIR)/*
	$(call echo_done,Upload to TestPyPI complete.)

build_sdist: check_python_deps $(ACTIVATE)
	$(call echo_start,Building source distribution…)
	$(PIP) install --upgrade setuptools wheel build
	$(PIP) install --upgrade $(call quote_deps)
	$(PYTHON) -m build --sdist --no-isolation --outdir $(DIST_DIR) $(PROJECT_ROOT)
	$(call echo_done,Source distribution built.)

endif   # PYTHON_MK_INCLUDED
