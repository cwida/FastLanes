#include <pybind11/pybind11.h>
#include "fastlanes.hpp"

namespace py = pybind11;

void bind_connection(py::module_ &);

PYBIND11_MODULE(_fastlanes, m)
{
	m.doc() = "Python bindings for FastLanes";
	m.def("get_version", &fastlanes::Info::get_version);

	bind_connection(m);
}
