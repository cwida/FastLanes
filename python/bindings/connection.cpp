#include "fastlanes.hpp"
#include <pybind11/stl/filesystem.h>   // for std::filesystem::path
#include <pybind11/pybind11.h>
namespace py = pybind11;

void bind_connection(py::module_ &m)
{
	py::class_<fastlanes::Connection>(m, "Connection")
		.def(py::init<>())
		.def("read_csv",
			 &fastlanes::Connection::read_csv,
			 py::arg("dir_path"),
			 "Read CSV files from directory")
		.def("__enter__", [](fastlanes::Connection &c) { return &c; })
		.def("__exit__",  [](fastlanes::Connection &c, py::object, py::object, py::object) { c.reset(); });
}
