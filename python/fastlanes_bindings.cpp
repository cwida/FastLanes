// fastlanes_bindings.cpp
#include "fastlanes.hpp"
#include <pybind11/iostream.h> // optional: redirect C++ logs
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl/filesystem.h>

namespace py = pybind11;

PYBIND11_MODULE(_fastlanes, m) {
	m.doc() = "Python bindings for FastLanes";

	// --- free-standing helpers -----------
	m.def("get_version", &fastlanes::Info::get_version);

	// --- bind Config -----------
	py::class_<fastlanes::Config>(m, "Config")
	    .def(py::init<>(), "Default configuration")
	    .def_readwrite("is_forced_schema_pool", &fastlanes::Config::is_forced_schema_pool)
	    .def_readwrite("forced_schema_pool", &fastlanes::Config::forced_schema_pool)
	    .def_readwrite("is_forced_schema", &fastlanes::Config::is_forced_schema)
	    .def_readwrite("forced_schema", &fastlanes::Config::forced_schema)
	    .def_readwrite("sample_size", &fastlanes::Config::sample_size)
	    .def_readwrite("n_vector_per_rowgroup", &fastlanes::Config::n_vector_per_rowgroup)
	    .def_readwrite("inline_footer", &fastlanes::Config::inline_footer);

	// --- bind Connection -----------
	py::class_<fastlanes::Connection>(m, "Connection")
	    // constructors
	    .def(py::init<>(), "Default Connection")
	    .def(py::init<const fastlanes::Config&>(), py::arg("config"), "Construct a Connection with a custom Config")

	    // chainable methods
	    .def("read_csv", &fastlanes::Connection::read_csv, py::arg("dir_path"), "Read CSV files from directory")
	    // .def("read_json", &fastlanes::Connection::read_json, py::arg("dir_path"), "Read JSON files from directory")
	    // .def("read_fls",
	    //      &fastlanes::Connection::read_fls,
	    //      py::arg("dir_path"),
	    //      "Read a .fls file and return a TableReader")
	    // .def("to_fls", &fastlanes::Connection::to_fls, py::arg("dir_path"), "Serialize to .fls in directory")
	    // // .def("spell", &fastlanes::Connection::spell, "Finalize and prepare for writing/reading")
	    // .def("reset", &fastlanes::Connection::reset, "Reset the Connection to its initial state")
	    //
	    // // schema/pool forcing
	    // .def("force_schema_pool",
	    //      &fastlanes::Connection::force_schema_pool,
	    //      py::arg("tokens"),
	    //      "Force the schema pool (list of OperatorToken)")
	    // .def("get_forced_schema_pool", &fastlanes::Connection::get_forced_schema_pool, "Get the forced schema pool")
	    //
	    // .def("force_schema",
	    //      &fastlanes::Connection::force_schema,
	    //      py::arg("tokens"),
	    //      "Force the schema (list of OperatorToken)")
	    // .def("get_forced_schema", &fastlanes::Connection::get_forced_schema, "Get the forced schema")
	    //
	    // // sampling
	    // .def("set_sample_size",
	    //      &fastlanes::Connection::set_sample_size,
	    //      py::arg("n_vectors"),
	    //      "Set the sample size (in vectors)")
	    // .def("get_sample_size", &fastlanes::Connection::get_sample_size, "Get the sample size")
	    //
	    // .def("set_n_vectors_per_rowgroup",
	    //      &fastlanes::Connection::set_n_vectors_per_rowgroup,
	    //      py::arg("n_vectors"),
	    //      "Set number of vectors per rowgroup")
	    //
	    // .def("inline_footer", &fastlanes::Connection::inline_footer, "Inline footer into the file")
	    //
	    // // status/query
	    // .def("verify_fls",
	    //      &fastlanes::Connection::verify_fls,
	    //      py::arg("file_path"),
	    //      "Verify a .fls file; returns a Status enum")
	    //
	    // // table access
	    // .def("get_table", &fastlanes::Connection::get_table, "Get the underlying Table object")

	    // destructor handled automatically

	    // context‐manager support
	    .def("__enter__", [](fastlanes::Connection& c) { return &c; })
	    .def("__exit__", [](fastlanes::Connection& c, py::object, py::object, py::object) { c.reset(); });
}
