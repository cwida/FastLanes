# root Makefile
include mk/preamble.mk   # echo helpers first
include mk/python.mk     # defines $(ACTIVATE) $(PYTHON) $(PIP) …
include mk/format.mk
include mk/cpp.mk
include mk/rust.mk
include mk/data.mk       # uses $(ACTIVATE) and $(PIP)
include mk/scripts.mk

.PHONY: all clean
all: build-cpp build-rust          # or whatever top-level build you need

clean:
	$(MAKE) clean-cpp clean-rust clean-python
