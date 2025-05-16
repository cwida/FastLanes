# mk/preamble.mk — Helpers for colored echo

define echo_done
	@echo "\033[0;32m$(1)\033[0m"
endef

define echo_start
	@echo "\033[0;33m$(1)\033[0m"
endef
