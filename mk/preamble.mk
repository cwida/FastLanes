# mk/preamble.mk  – echo helpers *plus* repo root detection
define echo_done
	@echo "\033[0;32m$(1)\033[0m"
endef
define echo_start
	@echo "\033[0;33m$(1)\033[0m"
endef

# Absolute path to the directory that contains this mk/ folder (= project root)
REPO_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)
export REPO_ROOT            # so every included .mk file can see it
