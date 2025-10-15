# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# mk/format.mk
# ────────────────────────────────────────────────────────
IMAGE             := ghcr.io/azimafroozeh/clang-format-python/clang-format-python:14
UBUNTU_IMAGE      := ubuntu:22.04
DIRS              := examples src benchmark test data/include python cuda galp
EXCLUDES          := --exclude src/include/fls/json/nlohmann \
                     --exclude src/include/flatbuffers \
                     --exclude src/primitives \
                     --exclude examples/rust_example



# shared docker‐run prefix
DOCKER := docker run --rm -v "$$(pwd)":/app -w /app

# the actual clang-format invocation
FMT_CMD := python3 scripts/run-clang-format.py \
           -r $(DIRS) \
           --extensions='c,h,C,H,cpp,hpp,cc,hh,cxx,hxx,cu,cuh' \
           $(EXCLUDES)


.PHONY: format clang-format format-check rust-format-check check-docker

# check if docker daemon is running
check-docker:
	@docker info > /dev/null 2>&1 || \
	{ $(call echo_error,❌ Docker is not running. Please start Docker and retry.); exit 1; }

clang-format: check-docker
	$(call echo_start,Running clang-format with Docker…)
	$(DOCKER) $(UBUNTU_IMAGE) \
	  bash -c "apt update && apt install -y python3 clang-format-14 && \
	           ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	           $(FMT_CMD) -i"
	$(call echo_done,clang-format run complete.)

format-check: check-docker
	$(call echo_start,Checking formatting…)
	$(DOCKER) $(UBUNTU_IMAGE) \
	  bash -c "apt update && apt install -y clang-format-14 python3 && \
	           ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	           $(FMT_CMD)"
	$(call echo_done,Formatting check complete.)
