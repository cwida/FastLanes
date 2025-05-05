#include "fls/reader/table_reader.hpp"
#include "fls/footer/table_descriptor.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl/filesystem.h>
namespace py = pybind11;

void bind_table_reader(py::module_& m) {
	py::class_<fastlanes::TableReader, std::shared_ptr<fastlanes::TableReader>>(m, "TableReader")
	    .def("to_csv", &fastlanes::TableReader::to_csv, py::arg("file_path"));
}