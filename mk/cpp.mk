# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/cpp.mk
# ────────────────────────────────────────────────────────
# mk/cpp.mk — C++ CMake rules (Release build, verbose output, parallelized via NUM_JOBS)

# 1) Load colored‐echo macros, REPO_ROOT/CRATE_ROOT and NUM_JOBS
include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/preamble.mk

# 2) Compute project root (one directory up from mk/)
MKFILE_PATH  := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PROJECT_ROOT := $(abspath $(MKFILE_PATH)/..)

# 3) Configuration variables
#    By default we install into build/install under the repo root.
PREFIX       ?= $(PROJECT_ROOT)/build/install
BUILD_DIR    ?= build
CMAKE        ?= cmake

# 4) CMake flags: Release build + verbose FastLanes output
CMAKE_FLAGS  ?= \
  -DCMAKE_INSTALL_PREFIX=$(PREFIX) \
  -DCMAKE_BUILD_TYPE=Release \
  -DFLS_ENABLE_VERBOSE_OUTPUT=ON

# Build in parallel using all available jobs
CMAKE_BUILD  ?= $(CMAKE) --build $(PROJECT_ROOT)/$(BUILD_DIR) --parallel $(NUM_JOBS)

# 5) Targets
.PHONY: build-cpp install-cpp clean-cpp

build-cpp:
	$(call echo_start,Configuring & building C++ (Release, verbose, $(NUM_JOBS) jobs)…)
	mkdir -p $(PROJECT_ROOT)/$(BUILD_DIR)
	cd $(PROJECT_ROOT)/$(BUILD_DIR) && \
	  $(CMAKE) $(CMAKE_FLAGS) $(PROJECT_ROOT) && \
	  $(CMAKE_BUILD)
	$(call echo_done,C++ build complete.)

install-cpp: build-cpp
	$(call echo_start,Installing C++ library to $(PREFIX) (using $(NUM_JOBS) jobs)…)
	$(CMAKE) --install $(PROJECT_ROOT)/$(BUILD_DIR) \
	            --prefix $(PREFIX) \
	            --parallel $(NUM_JOBS)
	$(call echo_done,C++ install complete.)

clean-cpp:
	$(call echo_start,Cleaning C++ build…)
	rm -rf $(PROJECT_ROOT)/$(BUILD_DIR)
	$(call echo_done,C++ clean complete.)
