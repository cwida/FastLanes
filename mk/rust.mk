# mk/rust.mk
CARGO ?= cargo

.PHONY: build-rust test clean-rust

build-rust:
	$(call echo_start,Building Rust crate…)
	$(CARGO) -C $(REPO_ROOT) build
	$(call echo_done,Rust build complete.)

test: build-cpp build-rust
	$(call echo_start,Running Rust tests…)
	$(CARGO) -C $(REPO_ROOT) test -- --nocapture
	$(call echo_done,Rust tests complete.)

clean-rust:
	$(call echo_start,Cleaning Rust build…)
	$(CARGO) -C $(REPO_ROOT) clean
	$(call echo_done,Rust clean complete.)
