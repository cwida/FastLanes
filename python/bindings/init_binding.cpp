#include "fastlanes.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void bind_connection(py::module_&);
void bind_table_reader(py::module_&);

PYBIND11_MODULE(_fastlanes, m) {
	m.doc() = "Python bindings for FastLanes";
	m.def("get_version", &fastlanes::Info::get_version);
	m.def("connect", &fastlanes::connect);

	bind_connection(m);
	bind_table_reader(m);
}
