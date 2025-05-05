// fastlanes_bindings.cpp
#include "fastlanes.hpp"
#include <pybind11/iostream.h> // optional: redirect C++ logs
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_fastlanes, m) {
	m.doc() = "Python bindings for FastLanes";

	// --- free-standing helpers -----------
	m.def("get_version", &fastlanes::Info::get_version);
}
