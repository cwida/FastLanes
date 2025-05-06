#include "fls/footer/table_descriptor.hpp"
#include "fls/reader/table_reader.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void bind_table_reader(py::module_& m) {
	py::class_<fastlanes::TableReader, fastlanes::up<fastlanes::TableReader>> cls(m, "TableReader");

	cls.def(
	       "to_csv", [](fastlanes::TableReader& self, const char* path) { self.to_csv(path); }, py::arg("file_path"))
	    .def("__repr__", [](const fastlanes::TableReader&) { return "<fastlanes.TableReader>"; })
	    .def("__dir__", []() {
		    return std::vector<std::string> {
		        "to_csv", "__repr__", "__dir__"
		        // Add more method/field names as you expose them
		    };
	    });
}
