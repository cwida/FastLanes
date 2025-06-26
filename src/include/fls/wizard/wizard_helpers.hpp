#ifndef WIZARD_HELPERS_HPP
#define WIZARD_HELPERS_HPP

namespace fastlanes {
void gather_statistics(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& column_descriptors);
void init(vector<up<ColumnDescriptorT>>& column_descriptors);

void constant_check(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& column_descriptors);
void null_check(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& column_descriptors);
void equality_check(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& column_descriptors);
void map_1t1_check(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& footer);

bool IsDetermined(const ColumnDescriptorT& column_descriptor);

n_t TryExpr(const rowgroup_pt&       col,
            const ColumnDescriptorT& column_descriptor,
            const OperatorToken&     token,
            RowgroupDescriptorT&     footer,
            n_t                      sample_size);

OperatorToken ChooseBestExpr(const std::vector<up<ExpressionResultT>>& options);

/*--------------------------------------------------------------------------------------------------------------------*\
 * Dictionary Check
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
vector<OperatorToken>& get_dict_pool(n_t index_data_type) {

	auto converted_data_type = static_cast<DataType>(index_data_type);

	switch (converted_data_type) {
	case DataType::UINT32: {
		static vector<OperatorToken> FLS_STR_POOL = {
		    OperatorToken::EXP_DICT_STR_U32,
		    OperatorToken::EXP_FSST_DICT_STR_U32,
		    OperatorToken::EXP_FSST12_DICT_STR_U32,
		};
		if constexpr (std::is_same_v<PT, fls_string_t>) {
			return FLS_STR_POOL;
		} else {
			FLS_UNREACHABLE()
		}
	}
	case DataType::UINT16: {
		static vector<OperatorToken> FLS_STR_POOL = {
		    OperatorToken::EXP_DICT_STR_U16,
		    OperatorToken::EXP_FSST_DICT_STR_U16,
		    OperatorToken::EXP_FSST12_DICT_STR_U16, //
		};
		if constexpr (std::is_same_v<PT, fls_string_t>) {
			return FLS_STR_POOL;
		} else {
			FLS_UNREACHABLE()
		}
	}
	case DataType::UINT8: {
		static vector<OperatorToken> FLS_STR_POOL = {
		    OperatorToken::EXP_DICT_STR_U08,
		    OperatorToken::EXP_FSST_DICT_STR_U08,
		    OperatorToken::EXP_FSST12_DICT_STR_U08, //
		};

		if constexpr (std::is_same_v<PT, fls_string_t>) {
			return FLS_STR_POOL;
		} else {
			FLS_UNREACHABLE()
		}
	}
	default:
		FLS_UNREACHABLE();
	}

	FLS_UNREACHABLE()
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Dictionary Check
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
vector<OperatorToken>& get_dict_encoding_pool(n_t index_data_type) {

	auto converted_data_type = static_cast<DataType>(index_data_type);

	switch (converted_data_type) {
	case DataType::UINT32: {
		static vector<OperatorToken> I64_DICT_POOL = {
		    OperatorToken::EXP_DICT_I64_FFOR_U32,
		    OperatorToken::EXP_DICT_I64_FFOR_SLPATCH_U32 //
		};

		static vector<OperatorToken> I32_DICT_POOL = {
		    OperatorToken::EXP_DICT_I32_FFOR_U32,
		    OperatorToken::EXP_DICT_I32_FFOR_SLPATCH_U32 //
		};

		static vector<OperatorToken> DBL_DICT_POOL = {
		    OperatorToken::EXP_DICT_DBL_FFOR_U32,
		    OperatorToken::EXP_DICT_DBL_FFOR_SLPATCH_U32 //
		};

		static vector<OperatorToken> FLT_DICT_POOL = {
		    OperatorToken::EXP_DICT_FLT_FFOR_U32,
		    OperatorToken::EXP_DICT_FLT_FFOR_SLPATCH_U32 //
		};

		static vector<OperatorToken> FLS_STR_POOL = {
		    OperatorToken::EXP_DICT_STR_FFOR_U32,                //
		    OperatorToken::EXP_DICT_STR_FFOR_SLPATCH_U32,        //
		    OperatorToken::EXP_FSST_DICT_STR_FFOR_U32,           //
		    OperatorToken::EXP_FSST_DICT_STR_FFOR_SLPATCH_U32,   //
		    OperatorToken::EXP_FSST12_DICT_STR_FFOR_SLPATCH_U32, //
		};

		if constexpr (std::is_same_v<PT, fls_string_t>) {
			return FLS_STR_POOL;
		} else if constexpr (std::is_same_v<PT, i64_pt>) {
			return I64_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, i32_pt>) {
			return I32_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, i16_pt>) {
			FLS_UNREACHABLE()
		} else if constexpr (std::is_same_v<PT, i08_pt>) {
			FLS_UNREACHABLE()
		} else if constexpr (std::is_same_v<PT, dbl_pt>) {
			return DBL_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, flt_pt>) {
			return DBL_DICT_POOL;
		} else {
			FLS_UNREACHABLE()
		}
	}

	case DataType::UINT16: {
		static vector<OperatorToken> I64_DICT_POOL = {
		    OperatorToken::EXP_DICT_I64_FFOR_U16,
		    OperatorToken::EXP_DICT_I64_FFOR_SLPATCH_U16, //
		};

		static vector<OperatorToken> I32_DICT_POOL = {
		    OperatorToken::EXP_DICT_I32_FFOR_U16,
		    OperatorToken::EXP_DICT_I32_FFOR_SLPATCH_U16, //
		};

		static vector<OperatorToken> I16_DICT_POOL = {
		    OperatorToken::EXP_DICT_I16_FFOR_U16,
		    OperatorToken::EXP_DICT_I16_FFOR_SLPATCH_U16, //
		};

		static vector<OperatorToken> I08_DICT_POOL = {
		    //
		};

		static vector<OperatorToken> DBL_DICT_POOL = {
		    OperatorToken::EXP_DICT_DBL_FFOR_U16,
		    OperatorToken::EXP_DICT_DBL_FFOR_SLPATCH_U16, //
		};

		static vector<OperatorToken> FLT_DICT_POOL = {
		    OperatorToken::EXP_DICT_FLT_FFOR_U16,
		    OperatorToken::EXP_DICT_FLT_FFOR_SLPATCH_U16, //
		};

		static vector<OperatorToken> FLS_STR_POOL = {
		    OperatorToken::EXP_DICT_STR_FFOR_U16,                //
		    OperatorToken::EXP_DICT_STR_FFOR_SLPATCH_U16,        //
		    OperatorToken::EXP_FSST_DICT_STR_FFOR_U16,           //
		    OperatorToken::EXP_FSST_DICT_STR_FFOR_SLPATCH_U16,   //
		    OperatorToken::EXP_FSST12_DICT_STR_FFOR_SLPATCH_U16, //
		};
		if constexpr (std::is_same_v<PT, fls_string_t>) {
			return FLS_STR_POOL;
		} else if constexpr (std::is_same_v<PT, i64_pt>) {
			return I64_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, i32_pt>) {
			return I32_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, i16_pt>) {
			return I16_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, i08_pt>) {
			return I08_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, dbl_pt>) {
			return DBL_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, flt_pt>) {
			return FLT_DICT_POOL;
		} else {
			FLS_UNREACHABLE()
		}
	}

	case DataType::UINT8: {
		static vector<OperatorToken> I64_DICT_POOL = {
		    OperatorToken::EXP_DICT_I64_FFOR_U08,
		    OperatorToken::EXP_DICT_I64_FFOR_SLPATCH_U08 //
		};

		static vector<OperatorToken> I32_DICT_POOL = {
		    OperatorToken::EXP_DICT_I32_FFOR_U08,
		    OperatorToken::EXP_DICT_I32_FFOR_SLPATCH_U08 //
		};

		static vector<OperatorToken> I16_DICT_POOL = {
		    OperatorToken::EXP_DICT_I16_FFOR_U08,
		    OperatorToken::EXP_DICT_I16_FFOR_SLPATCH_U08 //
		};

		static vector<OperatorToken> I08_DICT_POOL = {
		    OperatorToken::EXP_DICT_I08_FFOR_U08,
		    OperatorToken::EXP_DICT_I08_FFOR_SLPATCH_U08 //
		};

		static vector<OperatorToken> DBL_DICT_POOL = {
		    OperatorToken::EXP_DICT_DBL_FFOR_U08,
		    OperatorToken::EXP_DICT_DBL_FFOR_SLPATCH_U08 //
		};

		static vector<OperatorToken> FLT_DICT_POOL = {
		    OperatorToken::EXP_DICT_FLT_FFOR_U08,
		    OperatorToken::EXP_DICT_FLT_FFOR_SLPATCH_U08 //
		};

		static vector<OperatorToken> FLS_STR_POOL = {
		    OperatorToken::EXP_DICT_STR_FFOR_U08,
		    OperatorToken::EXP_DICT_STR_FFOR_SLPATCH_U08,
		    OperatorToken::EXP_FSST_DICT_STR_FFOR_U08,
		    OperatorToken::EXP_FSST_DICT_STR_FFOR_SLPATCH_U08,   //
		    OperatorToken::EXP_FSST12_DICT_STR_FFOR_U08,         //
		    OperatorToken::EXP_FSST12_DICT_STR_FFOR_SLPATCH_U08, //
		};

		static vector<OperatorToken> U08_DICT_POOL = {
		    // TODO
		};

		if constexpr (std::is_same_v<PT, fls_string_t>) {
			return FLS_STR_POOL;
		} else if constexpr (std::is_same_v<PT, i64_pt>) {
			return I64_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, i32_pt>) {
			return I32_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, i16_pt>) {
			return I16_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, i08_pt>) {
			return I08_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, dbl_pt>) {
			return DBL_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, flt_pt>) {
			return FLT_DICT_POOL;
		} else if constexpr (std::is_same_v<PT, u08_pt>) {
			return U08_DICT_POOL;
		} else {
			FLS_UNREACHABLE()
		}
	}
	default:
		FLS_UNREACHABLE();
	}

	FLS_UNREACHABLE()
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Expression Check
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
vector<OperatorToken>& get_pool() {
	static vector<OperatorToken> I64_POOL = {
	    OperatorToken::EXP_RLE_I64_SLPATCH_U16,
	    OperatorToken::EXP_FFOR_SLPATCH_I64,
	    OperatorToken::EXP_DELTA_I64,
	    OperatorToken::EXP_RLE_I64_U16,
	    OperatorToken::EXP_UNCOMPRESSED_I64,
	    OperatorToken::EXP_FFOR_I64,
	    OperatorToken::EXP_FREQUENCY_I64,
	    OperatorToken::EXP_CROSS_RLE_I64,
	};

	static vector<OperatorToken> I32_POOL = {
	    OperatorToken::EXP_RLE_I32_SLPATCH_U16,
	    OperatorToken::EXP_FFOR_SLPATCH_I32,
	    OperatorToken::EXP_DELTA_I32,
	    OperatorToken::EXP_RLE_I32_U16,
	    OperatorToken::EXP_UNCOMPRESSED_I32,
	    OperatorToken::EXP_FFOR_I32,
	    OperatorToken::EXP_FREQUENCY_I32,
	    OperatorToken::EXP_CROSS_RLE_I32, //
	};

	static vector<OperatorToken> I16_POOL = {
	    OperatorToken::EXP_RLE_I16_SLPATCH_U16,
	    OperatorToken::EXP_FFOR_SLPATCH_I16,
	    OperatorToken::EXP_DELTA_I16,
	    OperatorToken::EXP_RLE_I16_U16,
	    OperatorToken::EXP_UNCOMPRESSED_I16,
	    OperatorToken::EXP_FFOR_I16,
	    OperatorToken::EXP_FREQUENCY_I16,
	    OperatorToken::EXP_CROSS_RLE_I16, //
	};

	static vector<OperatorToken> I08_POOL = {
	    OperatorToken::EXP_RLE_I08_SLPATCH_U16,
	    OperatorToken::EXP_FFOR_SLPATCH_I08,
	    OperatorToken::EXP_DELTA_I08,
	    OperatorToken::EXP_RLE_I08_U16,
	    OperatorToken::EXP_UNCOMPRESSED_I08,
	    OperatorToken::EXP_FFOR_I08,
	    OperatorToken::EXP_FREQUENCY_I08,
	    OperatorToken::EXP_CROSS_RLE_I08, //
	};

	static vector<OperatorToken> U08_POOL = {
	    OperatorToken::EXP_UNCOMPRESSED_U08, //
	};

	static vector<OperatorToken> DBL_POOL = {
	    OperatorToken::EXP_RLE_DBL_SLPATCH_U16,
	    OperatorToken::EXP_RLE_DBL_U16,
	    OperatorToken::EXP_UNCOMPRESSED_DBL,
	    OperatorToken::EXP_ALP_DBL,
	    OperatorToken::EXP_ALP_RD_DBL,
	    OperatorToken::EXP_FREQUENCY_DBL,
	    OperatorToken::EXP_CROSS_RLE_DBL, //
	};

	static vector<OperatorToken> FLT_POOL = {
	    OperatorToken::EXP_UNCOMPRESSED_FLT,
	    OperatorToken::EXP_RLE_FLT_SLPATCH_U16,
	    OperatorToken::EXP_RLE_FLT_U16,
	    OperatorToken::EXP_ALP_FLT,
	    OperatorToken::EXP_ALP_RD_FLT,
	    OperatorToken::EXP_FREQUENCY_FLT,
	    OperatorToken::EXP_CROSS_RLE_FLT, //
	};

	static vector<OperatorToken> STR_POOL = {
	    OperatorToken::EXP_RLE_STR_SLPATCH_U16,
	    OperatorToken::EXP_FSST_DELTA,
	    OperatorToken::EXP_FSST12_DELTA,
	    OperatorToken::EXP_FSST_DELTA_SLPATCH,
	    OperatorToken::EXP_FSST12_DELTA_SLPATCH,
	    OperatorToken::EXP_RLE_STR_U16,
	    OperatorToken::EXP_UNCOMPRESSED_STR,
	    OperatorToken::EXP_FREQUENCY_STR,
	    OperatorToken::EXP_CROSS_RLE_STR, //
	};

	if constexpr (std::is_same_v<PT, fls_string_t>) {
		return STR_POOL;
	} else if constexpr (std::is_same_v<PT, i64_pt>) {
		return I64_POOL;
	} else if constexpr (std::is_same_v<PT, i32_pt>) {
		return I32_POOL;
	} else if constexpr (std::is_same_v<PT, i16_pt>) {
		return I16_POOL;
	} else if constexpr (std::is_same_v<PT, i08_pt>) {
		return I08_POOL;
	} else if constexpr (std::is_same_v<PT, dbl_pt>) {
		return DBL_POOL;
	} else if constexpr (std::is_same_v<PT, flt_pt>) {
		return FLT_POOL;
	} else if constexpr (std::is_same_v<PT, u08_pt>) {
		return U08_POOL;
	} else {
		FLS_UNREACHABLE()
	}

	FLS_UNREACHABLE()
}

bool IsDictionaryEncodingRequired(const ColumnDescriptorT& column_descriptor);
bool IsDictionaryChoosingRequired(const ColumnDescriptorT& column_descriptor);

DataType FindBestDataTypeForColumn(const col_pt& col);
} // namespace fastlanes

#endif // WIZARD_HELPERS_HPP
