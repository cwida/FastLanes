# mk/format.mk — Clang‐format / formatting helpers

# Include guard to prevent multiple inclusion
ifndef MK_FORMAT_MK_INCLUDED
MK_FORMAT_MK_INCLUDED := 1

IMAGE := ghcr.io/azimafroozeh/clang-format-python/clang-format-python:14
SCRIPT := scripts/run-clang-format.py

.PHONY: format clang-format format-check detect-cpu

# ─── Guards ────────────────────────────────────────────────────────────────────

# Skip Docker check on GitHub Actions and for detect-cpu target
ifeq ($(filter detect-cpu,$(MAKECMDGOALS)),)
ifndef GITHUB_ACTIONS
# Ensure Docker is installed locally
ifeq ($(shell command -v docker 2>/dev/null),)
$(error Docker is required but not installed. Please install Docker: https://docs.docker.com/get-docker/)
endif
endif
endif

# Ensure Python 3 is installed
ifeq ($(shell command -v python3 2>/dev/null),)
$(error Python 3 is required but not installed. Please install Python 3.)
endif

# Ensure the formatting script exists
ifeq ($(wildcard $(SCRIPT)),)
$(error Cannot find $(SCRIPT); please check that you’re in the project root and that the file exists.)
endif

# ─── Targets ────────────────────────────────────────────────────────────────────

format:
	$(call echo_start,Formatting…)
	docker run --rm \
	  -v "$(PWD)":/app -w /app \
	  $(IMAGE) \
	  bash -c "python3 $(SCRIPT) \
	    -r examples include src benchmark python test data/include \
	    -i --exclude include/fls/json/nlohmann"
	$(call echo_done,Formatting complete.)

clang-format:
	$(call echo_start,Running clang-format with Docker…)
	docker run --rm \
	  -v "$(PWD)":/app -w /app \
	  ubuntu:22.04 \
	  bash -c "apt update && apt install -y python3 clang-format-14 && \
	           ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	           python3 $(SCRIPT) \
	             -r examples include src benchmark test data/include python \
	             -i --exclude include/fls/json/nlohmann"
	$(call echo_done,clang-format run complete.)

format-check:
	$(call echo_start,Checking formatting…)
	docker run --rm \
	  -v "$(PWD)":/app -w /app \
	  ubuntu:22.04 \
	  bash -c "apt update && apt install -y clang-format-14 python3 && \
	           ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	           python3 $(SCRIPT) \
	             -r examples include src benchmark test data/include python \
	             --exclude include/fls/json/nlohmann"
	$(call echo_done,Formatting check complete.)

# Placeholder target for CPU detection, skip Docker requirements
detect-cpu:
	@echo "Detecting CPU cores..." # implementation elsewhere

endif # MK_FORMAT_MK_INCLUDED
