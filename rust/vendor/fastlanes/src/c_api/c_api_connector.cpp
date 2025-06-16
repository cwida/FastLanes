#include "fastlanes.h"
#include "fls/connection.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/predicate_operator.hpp"
#include "fls/reader/segment.hpp"
#include "fls/table/table.hpp"

extern "C" {

connection_cpi* fls_cpi_connection_open() {
	//
	return reinterpret_cast<connection_cpi*>(new fastlanes::Connection());
};

void fls_cpi_connection_close(connection_cpi* fls_connection) {
	delete reinterpret_cast<fastlanes::Connection*>(fls_connection);
}

bool encode_from_memory(void*     in_data,
                        uint64_t  in_n_input,
                        uint64_t  in_capacity,
                        uint8_t*  out_encoded_data,
                        uint64_t* out_encoded_size,
                        uint64_t* out_metadadata_size,
                        data_t    in_datatype,
                        uint8_t   in_expression_type) {

	return true;
}
}
