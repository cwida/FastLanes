// NOLINTBEGIN

#ifndef FASTLANES_H
#define FASTLANES_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// datatype
enum data_t : uint8_t {
	INVALID    = 0,
	DOUBLE     = 1,
	INT8       = 2,
	INT16      = 3,
	INT32      = 4,
	INT64      = 5,
	UINT8      = 6,
	UINT16     = 7,
	UINT32     = 8,
	UINT64     = 9,
	STR        = 10,
	BOOLEAN    = 11,
	DATE       = 12,
	FLOAT      = 13,
	BYTE_ARRAY = 14,
	LIST       = 15,
	STRUCT     = 16,
	MAP        = 17,
	FALLBACK   = 18,
};

// i64_t encoding expression type
enum i64_expr_encoding_t : uint8_t {
	I64_UNCOMPRESSED   = 0,
	I64_FFOR_NO_PATCH  = 1,
	I64_DELTA_NO_PATCH = 11,
};

// double encoding expression type
enum dbl_expr_encoding_t : uint8_t {
	DBL_UNCOMPRESSED = 0,
	DBL_ALP          = 1,
};

// Opaque pointer type for Connection
typedef struct Connection connection_cpi;

// C API functions
connection_cpi* fls_cpi_connection_open();                                // open a new fastlanes connection
void            fls_cpi_connection_close(connection_cpi* fls_connection); // close  the fastlanes connection

/*--------------------------------------------------------------------------------------------------------------------*\
 * Version  0.1 : after meeting at Jul 30, 2024 from 5:00 PM to 5:30 PM, participents:  @Azim @Raunak @Weston
 + enable caching one vector.
 + metadata size is given back to  the user of this api.
\*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * notes
 - in : input parameters
 - out : output parameters
\*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * Encode
 - encode n values of data type of size in_bytes_per_value.
 - return true if encoded_size <= out_capacity.
 - return false if encoded_size > out_capacity.
\*--------------------------------------------------------------------------------------------------------------------*/
bool encode_from_memory(void*     in_data,             // pointer to data.
                        uint64_t  in_n_input,          // number of values needs to be encoded.
                        uint64_t  in_capacity,         // capacity.
                        uint8_t*  out_encoded_data,    // pointer to where the encoded data should be written.
                        uint64_t* out_encoded_size,    // encoded size.
                        uint64_t* out_metadadata_size, // metadata size, metadata starts from out_encoded_data pointer.
                        enum data_t in_datatype,
                        uint8_t     in_expression_type);

/*--------------------------------------------------------------------------------------------------------------------*\
 * decode
\*--------------------------------------------------------------------------------------------------------------------*/
void decode_to_memory(uint8_t*    in_encoded_data, // pointer to encoded_data
                      void*       out_data,        // pointer to output data
                      enum data_t in_datatype);

/*--------------------------------------------------------------------------------------------------------------------*\
 * init_random_access
 - requirment : out_metadadata_size bytes from in_encoded_data is ALREADY loaded.
\*--------------------------------------------------------------------------------------------------------------------*/
void init_random_access(uint8_t*  in_encoded_data, // pointer to encoded data
                        uint64_t  in_vector_id,    // vector id
                        uint64_t* output_n_buffer, // number of buffers needs to be loaded
                        uint64_t* output_buffer    // pointer to array of pair of [offset, size]
);

/*--------------------------------------------------------------------------------------------------------------------*\
 * random_access
\*--------------------------------------------------------------------------------------------------------------------*/
void random_access(uint8_t*  in_encoded_data,             // pointer to encoded data
                   uint64_t  in_vector_id,                // vector id
                   uint64_t* output_n_buffer,             // number of buffers needs to be loaded
                   uint64_t* output_pair_offset_and_size, // pointer to array of pair of [offset, size]
                   uint8_t** output_buffers,              // pointer to buffers
                   uint8_t*  out_deencoded_vector         // pointer to where the deencoded vector should be stored
);

#ifdef __cplusplus
}
#endif

#endif // FASTLANES_H

// NOLINTEND
