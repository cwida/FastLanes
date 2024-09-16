#include "fastlanes.h"
#include "fls/connection.hpp"

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

	fastlanes::Connection::encode_from_memory(in_data,
	                                          in_n_input,
	                                          in_capacity,
	                                          out_encoded_data,
	                                          out_encoded_size,
	                                          static_cast<fastlanes::DataType>(in_datatype),
	                                          in_expression_type);

	return true;
}

void decode_to_memory(uint8_t* in_encoded_data, void* out_data, data_t in_datatype) {
	fastlanes::Connection::decode_to_memory(in_encoded_data, out_data, static_cast<fastlanes::DataType>(in_datatype));
}
}
