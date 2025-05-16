# mk/cpp.mk — C++ CMake rules

PREFIX       ?= /usr/local
BUILD_DIR    ?= build
CMAKE        ?= cmake
CMAKE_FLAGS  ?= -DCMAKE_INSTALL_PREFIX=$(PREFIX)
CMAKE_BUILD  ?= $(CMAKE) --build $(BUILD_DIR)

.PHONY: build-cpp install clean-cpp

build-cpp:
	$(call echo_start,Configuring & building C++…)
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		$(CMAKE) $(CMAKE_FLAGS) .. && \
		$(CMAKE_BUILD)
	$(call echo_done,C++ build complete.)

install: build-cpp
	$(call echo_start,Installing C++ library to $(PREFIX)…)
	$(CMAKE) --install $(BUILD_DIR) --prefix $(PREFIX)
	$(call echo_done,C++ install complete.)

clean-cpp:
	$(call echo_start,Cleaning C++ build…)
	rm -rf $(BUILD_DIR)
	$(call echo_done,C++ clean complete.)
