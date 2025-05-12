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
# Helper for green echo
# ─────────────────────────────────────────────────────────────
define echo_green
	@echo "\033[0;32m$(1)\033[0m"
endef

# ─────────────────────────────────────────────────────────────
# Virtual-env bootstrap
# ─────────────────────────────────────────────────────────────
$(ACTIVATE):
	$(call echo_green, "🐍 Setting up virtual environment…")
	python3 -m venv $(VENV)
	$(call echo_green, "📦 Installing base Python dependencies…")
	# use `python -m pip` so that pip can self-upgrade on Windows
	$(PYTHON) -m pip install --upgrade pip
	$(PYTHON) -m pip install clang-format Faker     # global dev tools

# ─────────────────────────────────────────────────────────────
# Clang-format helpers
# ─────────────────────────────────────────────────────────────
IMAGE := ghcr.io/azimafroozeh/clang-format-python/clang-format-python:14

format:
	$(call echo_green,"Formatting…")
	docker run --rm -v "$$(pwd)":/app -w /app $(IMAGE) \
	    bash -c "python3 scripts/run-clang-format.py -r examples include src benchmark python test data/include -i --exclude include/fls/json/nlohmann"

clang-format:
	$(call echo_green, "Running clang-format with Docker…")
	docker run --rm -v "$$(pwd)":/app -w /app ubuntu:22.04 \
	    bash -c "apt update && apt install -y python3 clang-format-14 && ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	             python3 scripts/run-clang-format.py -r examples include src benchmark test data/include python -i --exclude include/fls/json/nlohmann"

format-check:
	$(call echo_green, "Checking formatting…")
	docker run --rm -v "$$(pwd)":/app -w /app ubuntu:22.04 \
	    bash -c "apt update && apt install -y clang-format-14 python3 && ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	             python3 scripts/run-clang-format.py -r examples include src benchmark test data/include python --exclude include/fls/json/nlohmann"

# ─────────────────────────────────────────────────────────────
# Data & history helpers
# ─────────────────────────────────────────────────────────────
generate_synthetic_data: $(ACTIVATE)
	$(call echo_green, "🐣 Generating synthetic data…")
	# ensure Faker is installed
	$(PIP) install Faker
	cd scripts && PYTHONPATH=$(PWD) ../$(PYTHON) generate_synthetic_data.py \
		--num-records 5000 \
		--output ../data/synthetic_users.csv

check_fastlanes_result_history: $(ACTIVATE)
	$(call echo_green, "Checking CSV history…")
	cd scripts && ../$(PYTHON) check_fastlanes_result_history.py

time_ctest:
	$(call echo_green, "Running ctest with timing…")
	cd cmake-build-release && time ctest --output-on-failure

# ─────────────────────────────────────────────────────────────
# Python bindings
# ─────────────────────────────────────────────────────────────
# >>> keep *one* word per line, no trailing back-slash on the last entry <<<
PY_DEPS = \
  cmake>=3.22 \
  scikit-build-core>=0.11,<0.12 \
  pybind11>=2.12,<2.13 \
  setuptools_scm[toml]>=7,<8 \
  pytest \
  ninja>=1.5 \
  pyproject_metadata \
  Faker

TEST_DIR := python/tests

# Helper: quote each dep, skip empties
quote_deps = $(foreach dep,$(PY_DEPS),"$(dep)")

.PHONY: check_python_deps rebuild_python_debug rebuild_python_release \
        clean_python run_example_python test_python \
        build_wheel_release upload_pypi upload_testpypi build_sdist

check_python_deps: $(ACTIVATE)
	$(call echo_green, "📦 Ensuring Python build deps…")
	$(PIP) install --upgrade $(call quote_deps)

rebuild_python_debug: $(ACTIVATE)
	@echo "🔄 Rebuilding PyFastLanes bindings (Debug)…"
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Debug \
	CMAKE_BUILD_PARALLEL_LEVEL=12 \
	CMAKE_VERBOSE_MAKEFILE=ON \
	PIP_VERBOSE=1 \
	$(PYTHON) -m pip install -e . --no-build-isolation -v

rebuild_python_release: $(ACTIVATE)
	@echo "🚀 Rebuilding PyFastLanes bindings (Release)…"
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Release \
	CMAKE_BUILD_PARALLEL_LEVEL=12 \
	CMAKE_VERBOSE_MAKEFILE=ON \
	PIP_VERBOSE=1 \
	$(PYTHON) -m pip install -e . --no-build-isolation -v

clean_python:
	$(call echo_green,"🧹 Cleaning Python artefacts…")
	rm -rf skbuild-editable dist
	find python/pyfastlanes -name '_pyfastlanes*.so' -delete
	find . -name '__pycache__'   -exec rm -rf {} +
	find . -name '*.pyc'         -delete

run_example_python: $(ACTIVATE)
	$(call echo_green,"🚀 Running example…")
	$(PYTHON) examples/python_example.py

test_python: rebuild_python_release
	$(call echo_green, "🧪 Running unit tests…")
	PYTHONPATH=$(PWD)/python $(PYTHON) -m pytest -q $(TEST_DIR)

# ─────────────────────────────────────────────────────────────
# Wheel build & upload
# ─────────────────────────────────────────────────────────────
build_wheel_release: $(ACTIVATE)
	@echo "📦 Building PyFastLanes wheel (Release)…"
	$(PIP) install --upgrade $(call quote_deps)
	$(CLEAN_SKBUILD)
	CMAKE_BUILD_TYPE=Release \
	CMAKE_BUILD_PARALLEL_LEVEL=12 \
	CMAKE_VERBOSE_MAKEFILE=ON \
	PIP_VERBOSE=1 \
	$(PYTHON) -m build --wheel --no-isolation --outdir dist

upload_pypi: $(ACTIVATE)
	$(call echo_green, "🚀 Uploading to PyPI…")
	$(PYTHON) -m twine upload dist/*

upload_testpypi: $(ACTIVATE)
	$(call echo_green, "🧪 Uploading to TestPyPI…")
	$(PYTHON) -m twine upload --repository testpypi dist/*

# ─────────────────────────────────────────────────────────────
# Build just the source distribution
# ─────────────────────────────────────────────────────────────
build_sdist: $(ACTIVATE)
	$(call echo_green, "📦 Building source distribution…")
	$(PIP) install --upgrade setuptools wheel
	$(PIP) install --upgrade $(call quote_deps)
	$(PYTHON) -m build --sdist --no-isolation --outdir dist


# ─────────────────────────────────────────────────────────────
# Generate FlatBuffers C++ code for footer schema (with DataType)
# ─────────────────────────────────────────────────────────────

FBS_DIR    := flatbuffers_schemas
FBS_OUT    := include/fls/footer

.PHONY: generate_footer
generate_footer:
	@echo "🔍 Checking for schema files..."
	@if [ ! -d "$(FBS_DIR)" ]; then \
	  echo "❌ Schema directory '$(FBS_DIR)' not found."; exit 1; \
	fi
	@if [ ! -f "$(FBS_DIR)/datatype.fbs" ]; then \
	  echo "❌ '$(FBS_DIR)/datatype.fbs' not found."; exit 1; \
	fi
	@if [ ! -f "$(FBS_DIR)/footer.fbs" ]; then \
	  echo "❌ '$(FBS_DIR)/footer.fbs' not found."; exit 1; \
	fi

	@echo "📦 Generating FlatBuffers C++ (footer + datatype)…"
	@mkdir -p "$(FBS_OUT)"
	@flatc --cpp \
	       --gen-object-api \
	       --scoped-enums \
	       --no-emit-min-max-enum-values \
	       -I "$(FBS_DIR)" \
	       -o "$(FBS_OUT)" \
		   "$(FBS_DIR)/datatype.fbs" \
		   "$(FBS_DIR)/operator_token.fbs" \
		   "$(FBS_DIR)/footer.fbs"

	@echo "✅ FlatBuffers C++ generated in $(FBS_OUT)"



