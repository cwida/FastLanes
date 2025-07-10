# root Makefile
include mk/preamble.mk
include mk/python.mk
include mk/format.mk
include mk/cpp.mk
include mk/rust.mk
include mk/data.mk
include mk/scripts.mk
include mk/embeddings.mk
include mk/flatbuffers.mk
include mk/quick_fuzz.mk

.PHONY: all clean clang-format format-check rust-format-check format

all: build-cpp build-rust

clean:
	$(MAKE) clean-cpp clean-rust clean-python

format: clang-format
