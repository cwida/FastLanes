// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/micro-benchmarks.cu
// ────────────────────────────────────────────────────────
#include "engine/data.cuh"
#include "engine/enums.cuh"
#include "engine/verification.cuh"
#include "flsgpu/flsgpu-api.cuh"
#include "generated-bindings/kernel-bindings.cuh"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

struct ProgramParameters {
	enums::DataType            data_type;
	enums::Kernel              kernel;
	uint32_t                   unpack_n_vecs;
	uint32_t                   unpack_n_vals;
	enums::Unpacker            unpacker;
	enums::Patcher             patcher;
	data::ValueRange<vbw_t>    bit_width_range;
	data::ValueRange<uint16_t> ec_range;
	size_t                     n_values;
	uint32_t                   n_samples;
	enums::Print               print_option;
};

struct CLIArgs {
	std::string data_type;
	std::string kernel;
	uint32_t    unpack_n_vecs;
	uint32_t    unpack_n_vals;
	std::string patcher;
	std::string unpacker;
	vbw_t       start_vbw;
	vbw_t       end_vbw;
	uint16_t    start_ec;
	uint16_t    end_ec;
	size_t      n_vecs;
	uint32_t    n_samples;
	uint32_t    print_debug;

	CLIArgs(const int argc, char** argv) {
		constexpr int32_t CORRECT_ARG_COUNT = 14;
		if (argc != CORRECT_ARG_COUNT) {
			throw std::invalid_argument("Wrong arg count.\n");
		}

		int32_t argcounter = 0;
		data_type          = argv[++argcounter];
		kernel             = argv[++argcounter];
		unpack_n_vecs      = std::stoul(argv[++argcounter]);
		unpack_n_vals      = std::stoul(argv[++argcounter]);
		unpacker           = argv[++argcounter];
		patcher            = argv[++argcounter];
		start_vbw          = std::stoul(argv[++argcounter]);
		end_vbw            = std::stoul(argv[++argcounter]);
		start_ec           = std::stoul(argv[++argcounter]);
		end_ec             = std::stoul(argv[++argcounter]);
		n_vecs             = std::stoul(argv[++argcounter]);
		n_samples          = std::stoul(argv[++argcounter]);
		print_debug        = std::stoul(argv[++argcounter]);
	}

	ProgramParameters parse() {
		return ProgramParameters {
		    enums::string_to_data_type(data_type),
		    enums::string_to_kernel(kernel),
		    unpack_n_vecs,
		    unpack_n_vals,
		    enums::string_to_unpacker(unpacker),
		    enums::string_to_patcher(patcher),
		    data::ValueRange<vbw_t>(start_vbw, end_vbw),
		    data::ValueRange<uint16_t>(start_ec, end_ec),
		    n_vecs * consts::VALUES_PER_VECTOR,
		    n_samples,
		    static_cast<enums::Print>(print_debug),
		};
	}

private:
};

template <typename T, typename ColumnT>
verification::ExecutionResult<T> decompress_column(const ColumnT column, const ProgramParameters params) {
	auto     column_device = column.copy_to_device();
	const T* out           = bindings::decompress_column<T, typename ColumnT::DeviceColumnT>(
        column_device, params.unpack_n_vecs, params.unpack_n_vals, params.unpacker, params.patcher, params.n_samples);
	flsgpu::host::free_column(column_device);

	const T* correct_out = data::bindings::decompress(column);
	auto     result      = verification::compare_data(correct_out, out, params.n_values);
	delete correct_out;
	delete out;
	return result;
}

template <typename T, typename ColumnT>
verification::ExecutionResult<T>
query_column(const ColumnT column, const ProgramParameters params, const bool query_result, const T magic_value) {
	auto       column_device = column.copy_to_device();
	const bool answer        = bindings::query_column<T, typename ColumnT::DeviceColumnT>(column_device,
                                                                                   params.unpack_n_vecs,
                                                                                   params.unpack_n_vals,
                                                                                   params.unpacker,
                                                                                   params.patcher,
                                                                                   magic_value,
                                                                                   params.n_samples);
	flsgpu::host::free_column(column_device);

	// Weird hack to avoid refactor_
	T a = query_result ? 1.0 : 0.0;
	T b = answer ? 1.0 : 0.0;

	return verification::compare_data(&a, &b, 1);
}

template <typename T, typename ColumnT>
verification::ExecutionResult<T>
query_multi_column(const ColumnT column, const ProgramParameters params, const bool query_result, const T magic_value) {
	const bool answer = bindings::query_multi_column<T, ColumnT>(column,
	                                                             params.unpack_n_vecs,
	                                                             params.unpack_n_vals,
	                                                             params.unpacker,
	                                                             params.patcher,
	                                                             magic_value,
	                                                             params.n_samples);

	// Weird hack to avoid refactor_
	T a = query_result ? 1.0 : 0.0;
	T b = answer ? 1.0 : 0.0;

	return verification::compare_data(&a, &b, 1);
}

template <typename T, typename ColumnT>
verification::ExecutionResult<T>
execute_kernel(const ColumnT column, const ProgramParameters params, const bool query_result, const T magic_value) {
	if (params.kernel == enums::Kernel::Decompress) {
		return decompress_column<T, ColumnT>(column, params);
	} else if (params.kernel == enums::Kernel::Query) {
		return query_column<T, ColumnT>(column, params, query_result, magic_value);
	} else if (params.kernel == enums::Kernel::QueryMultiColumn) {
		return query_multi_column<T, ColumnT>(column, params, query_result, magic_value);
	} else {
		throw std::invalid_argument("Kernel not implemented yet.\n");
	}
}

template <typename T>
std::vector<verification::ExecutionResult<T>> execute_ffor(const ProgramParameters params) {
	using UINT_T = typename utils::same_width_uint<T>::type;
	auto results = std::vector<verification::ExecutionResult<T>>();

	for (vbw_t vbw {params.bit_width_range.min}; vbw <= params.bit_width_range.max; ++vbw) {
		auto vbw_range = data::ValueRange<vbw_t>(vbw);
		if (params.kernel == enums::Kernel::QueryMultiColumn) {
			vbw_range = params.bit_width_range;
		}
		bool                        query_result = false;
		T                           magic_value  = consts::as<T>::MAGIC_NUMBER;
		flsgpu::host::FFORColumn<T> column;

		if (params.kernel == enums::Kernel::Query) {
			auto [_query_result, _column] =
			    data::columns::generate_binary_ffor_column<T>(params.n_values, vbw_range, params.unpack_n_vecs);
			query_result = _query_result;
			column       = _column;
		} else {
			column = data::columns::generate_random_ffor_column<T>(
			    params.n_values, vbw_range, data::ValueRange<T>(0, 100), params.unpack_n_vecs);
		}

		if (params.kernel == enums::Kernel::QueryMultiColumn) {
			// We do not want query multicolumn to ever find a full lane of the
			// value to query to limit write bandwidth
			magic_value = std::numeric_limits<T>::max();
		}

		results.push_back(execute_kernel<T, flsgpu::host::FFORColumn<T>>(column, params, query_result, magic_value));

		flsgpu::host::free_column(column);

		if (params.kernel == enums::Kernel::QueryMultiColumn) {
			break;
		}
	}

	return results;
}

template <typename T>
std::vector<verification::ExecutionResult<T>> execute_alp(const ProgramParameters params) {
	using UINT_T = typename utils::same_width_uint<T>::type;
	auto results = std::vector<verification::ExecutionResult<T>>();

	// for (vbw_t vbw{params.bit_width_range.min}; vbw <=
	// params.bit_width_range.max; ++vbw) {
	{
		bool query_result = false;
		T    magic_value  = consts::as<T>::MAGIC_NUMBER;

		auto column = data::columns::generate_alp_column<T>(
		    params.n_values, params.bit_width_range, data::ValueRange<uint16_t>(0), params.unpack_n_vecs);
		for (uint16_t ec {params.ec_range.min}; ec <= params.ec_range.max; ++ec) {
			column = data::columns::modify_alp_exception_count(column, ec);

			if (params.kernel == enums::Kernel::Query) {
				auto [_query_result, _magic_value] =
				    data::columns::get_value_to_query<T, flsgpu::host::ALPColumn<T>>(column);
				query_result = _query_result;
				magic_value  = _magic_value;
			}

			if (params.patcher == enums::Patcher::Dummy || params.patcher == enums::Patcher::Stateless ||
			    params.patcher == enums::Patcher::Stateful) {
				results.push_back(
				    execute_kernel<T, flsgpu::host::ALPColumn<T>>(column, params, query_result, magic_value));
			} else {
				auto column_extended = column.create_extended_column();

				results.push_back(execute_kernel<T, flsgpu::host::ALPExtendedColumn<T>>(
				    column_extended, params, query_result, magic_value));

				flsgpu::host::free_column(column_extended);
			}
		}

		flsgpu::host::free_column(column);
	}

	return results;
}

int main(int argc, char** argv) {
	CLIArgs           args(argc, argv);
	ProgramParameters params = args.parse();

	int32_t exit_code   = 0;
	bool    print_debug = params.print_option != enums::Print::PrintNothing;
	switch (params.data_type) {
	case enums::DataType::U32:
		exit_code = verification::process_results(execute_ffor<uint32_t>(params), print_debug);
		break;
	case enums::DataType::U64:
		exit_code = verification::process_results(execute_ffor<uint64_t>(params), print_debug);
		break;
	case enums::DataType::F32:
		exit_code = verification::process_results(execute_alp<float>(params), print_debug);
		break;
	case enums::DataType::F64:
		exit_code = verification::process_results(execute_alp<double>(params), print_debug);
		break;
	}

	if (params.print_option == enums::Print::PrintDebugExit0) {
		exit(0);
	}

	exit(exit_code);
}
