// #include "fastlanes.h"
// #include <inttypes.h>
// #include <math.h>
// #include <stddef.h>
// #include <stdio.h>
// #include <stdlib.h>
//
// int main() {
//
// 	// double
// 	{
// 		const enum data_t              data_type             = DOUBLE;
// 		const uint64_t                 expr_pool_size        = 2;
// 		const enum dbl_expr_encoding_t expression_pool[]     = {DBL_UNCOMPRESSED, DBL_ALP};
// 		const char*                    expression_pool_str[] = {"DBL_UNCOMPRESSED", "DBL_ALP"};
// 		// int64_t
//
// 		// init
// 		const int64_t N_TUP      = 64 * 1024;
// 		const int64_t INPUT_SIZE = N_TUP * sizeof(double);
// 		const int64_t CAPACITY   = 2 * INPUT_SIZE;
// 		double        input_arr[N_TUP];
// 		uint8_t       encoded_buf[CAPACITY];
// 		double        output_arr[N_TUP];
// 		uint64_t      encoded_bsz;
// 		uint64_t      mtd_bsz;
//
// 		// initialize values;
// 		for (int64_t i = 0; i < N_TUP; ++i) {
// 			input_arr[i] = 1241.52;
// 		}
//
// 		printf("-- compression ratio of each expression: \n");
// 		for (uint64_t expr_idx = 0; expr_idx < expr_pool_size; expr_idx++) {
// 			const enum dbl_expr_encoding_t expression_encoding_type = expression_pool[expr_idx];
//
// 			// encode
// 			encode_from_memory(input_arr, //
// 			                   N_TUP,
// 			                   CAPACITY,
// 			                   encoded_buf,
// 			                   &encoded_bsz,
// 			                   &mtd_bsz,
// 			                   data_type,
// 			                   expression_encoding_type);
//
// 			// decode
// 			decode_to_memory(encoded_buf, output_arr, data_type);
//
// 			// verify
// 			for (int64_t i = 0; i < N_TUP; ++i) {
// 				if (output_arr[i] != input_arr[i]) {
// 					printf("--ERROR output_arr[%" PRId64 "] != i\n", i);
// 					exit(EXIT_FAILURE);
// 				}
// 			}
//
// 			const double compression_ratio = (double)INPUT_SIZE / (double)encoded_bsz;
// 			printf("-- %s : %.2fX\n", expression_pool_str[expr_idx], compression_ratio);
// 		}
// 	}
//
// 	// int64_t
// 	{
// 		// expression pool for type int64_t
// 		const enum data_t              data_type                 = INT64;
// 		const uint64_t                 expr_pool_size            = 3;
// 		const enum i64_expr_encoding_t int64_t_expression_pool[] = {
// 		    I64_UNCOMPRESSED, I64_FFOR_NO_PATCH, I64_DELTA_NO_PATCH};
// 		const char* int64_t_expression_pool_str[] = {"I64_UNCOMPRESSED", "I64_FFOR_NO_PATCH", "I64_DELTA_NO_PATCH"};
// 		// int64_t
//
// 		// init
// 		const int64_t N_TUP      = 64 * 1024;
// 		const int64_t INPUT_SIZE = N_TUP * sizeof(int64_t);
// 		const int64_t CAPACITY   = 2 * INPUT_SIZE;
// 		int64_t       input_arr[N_TUP];
// 		uint8_t       encoded_buf[CAPACITY];
// 		int64_t       output_arr[N_TUP];
// 		uint64_t      encoded_bsz;
// 		uint64_t      mtd_bsz;
//
// 		// initialize values;
// 		for (int64_t i = 0; i < N_TUP; ++i) {
// 			input_arr[i] = i;
// 		}
//
// 		printf("-- compression ratio of each expression: \n");
// 		for (uint64_t expr_idx = 0; expr_idx < expr_pool_size; expr_idx++) {
// 			const enum i64_expr_encoding_t expression_encoding_type = int64_t_expression_pool[expr_idx];
//
// 			// encode
// 			encode_from_memory(input_arr, //
// 			                   N_TUP,
// 			                   CAPACITY,
// 			                   encoded_buf,
// 			                   &encoded_bsz,
// 			                   &mtd_bsz,
// 			                   data_type,
// 			                   expression_encoding_type);
//
// 			// decode
// 			decode_to_memory(encoded_buf, output_arr, data_type);
//
// 			// verify
// 			for (int64_t i = 0; i < N_TUP; ++i) {
// 				if (output_arr[i] != input_arr[i]) {
// 					printf("--ERROR output_arr[%" PRId64 "] != i\n", i);
// 					exit(EXIT_FAILURE);
// 				}
// 			}
//
// 			const double compression_ratio = (double)INPUT_SIZE / (double)encoded_bsz;
// 			printf("-- %s : %.2fX\n", int64_t_expression_pool_str[expr_idx], compression_ratio);
// 		}
// 	}
// }