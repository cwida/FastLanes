#include "fastlanes.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl/filesystem.h> // for std::filesystem::path
namespace py = pybind11;

void bind_connection(py::module_& m) {
	py::class_<fastlanes::Connection>(m, "Connection")
	    .def(py::init<>())
	    .def("read_csv",
	         &fastlanes::Connection::read_csv,
	         py::arg("dir_path"),
	         "Read CSV files from directory",
	         py::return_value_policy::reference_internal)
	    .def("to_fls",
	         &fastlanes::Connection::to_fls,
	         py::arg("dir_path"),
	         "Write to fastlanes file format",
	         py::return_value_policy::reference_internal)
	    .def("read_fls",
	         &fastlanes::Connection::read_fls,
	         py::arg("dir_path"),
	         "Read a .fls file and return a FastLanes Reader",
	         py::return_value_policy::move)
	    .def("inline_footer",
	         &fastlanes::Connection::inline_footer,
	         "Enable footer inlining",
	         py::return_value_policy::reference_internal)
	    .def("__enter__", [](fastlanes::Connection& c) { return &c; })
	    .def("__exit__", [](fastlanes::Connection& c, py::object, py::object, py::object) { c.reset(); });
}
