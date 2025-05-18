# mk/format.mk — Clang‐format / formatting helpers

IMAGE := ghcr.io/azimafroozeh/clang-format-python/clang-format-python:14

.PHONY: format clang-format format-check

format:
	$(call echo_start,Formatting…)
	docker run --rm -v "$$(pwd)":/app -w /app $(IMAGE) \
	  bash -c "python3 scripts/run-clang-format.py \
	    -r examples include src benchmark python test data/include \
	    -i \
	    --exclude include/fls/json/nlohmann \
	    --exclude include/flatbuffers"
	$(call echo_done,Formatting complete.)

clang-format:
	$(call echo_start,Running clang-format with Docker…)
	docker run --rm -v "$$(pwd)":/app -w /app ubuntu:22.04 \
	  bash -c "apt update && apt install -y python3 clang-format-14 && \
	           ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	           python3 scripts/run-clang-format.py \
	             -r examples include src benchmark test data/include python \
	             -i \
	             --exclude include/fls/json/nlohmann \
	             --exclude include/flatbuffers \
	           "
	$(call echo_done,clang-format run complete.)

format-check:
	$(call echo_start,Checking formatting…)
	docker run --rm -v "$$(pwd)":/app -w /app ubuntu:22.04 \
	  bash -c "apt update && apt install -y clang-format-14 python3 && \
	           ln -s /usr/bin/clang-format-14 /usr/bin/clang-format && \
	           python3 scripts/run-clang-format.py \
	             -r examples include src benchmark test data/include python \
	             --exclude include/fls/json/nlohmann"
	$(call echo_done,Formatting check complete.)
