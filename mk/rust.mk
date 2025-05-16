# mk/rust.mk — Rust build & test rules

CARGO ?= cargo

.PHONY: build-rust test clean-rust

build-rust:
	$(call echo_start,Building Rust crate…)
	$(CARGO) build
	$(call echo_done,Rust build complete.)

# make sure C++ is built first so linking works
test: build-cpp build-rust
	$(call echo_start,Running Rust tests…)
	$(CARGO) test -- --nocapture
	$(call echo_done,Rust tests complete.)

clean-rust:
	$(call echo_start,Cleaning Rust build…)
	$(CARGO) clean
	$(call echo_done,Rust clean complete.)
