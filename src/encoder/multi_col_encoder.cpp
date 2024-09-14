
namespace fastlanes {
//
// up<AllExpEncodedCol> MultiColEncoder::test(const Schema& footer, const Rowgroup& bff, const TmpSubPlan& sub_plan) {
// 	FLS_ABORT("USE EXPERIMENTAL")
// 	/**/
// 	AllExpEncodedCol res;
// 	auto             src_idx = sub_plan.src_idx;
// 	auto             type    = footer.schema[src_idx].logical_type;
// 	up<TDic<str_pt>> src_str_dic;
//
// 	ExpEncodedCol exp_res {{0, 0, sub_plan.exp}, 0};
// 	bsz_t         bsz {0};
//
// 	switch (type) {
// 	case LT::INVALID: {
// 	} break;
// 	case LT::DOUBLE: {
// 	} break;
// 	case LT::INT64: {
// 		auto&               src_col = std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 		TColEncoder<i64_pt> src_chunk {};
// 		res = int64_encoder_up->EncodeDict(src_col).GetAll();
// 		// region TODO
// 		const Expression& exp   = res.exp_result_vec.front().expression;
// 		n_t               n_tup = src_col.size();
//
// 		src_chunk.Reset();
// 		src_chunk.ExtInitCompress(exp.exp, exp.var);
// 		src_chunk.ExtAnalyze(src_col.data(), n_tup);
// 		// endregion
//
// 		for (auto tgt_idx : sub_plan.group) {
// 			type = footer.schema[tgt_idx].logical_type;
// 			// region TODO
// 			EngineState  tgt_eng_stt;
// 			AnalyzeState tgt_alz_stt(tgt_eng_stt);
// 			// endregion
//
// 			switch (type) {
// 			case LT::INVALID: {
// 			} break;
// 			case LT::DOUBLE: {
// 			} break;
// 			case LT::INT64: {
// 				auto& tgt_col = std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[tgt_idx])->data;
// 				// region TODO
// 				TColEncoder<i64_pt> tgt_chunk {};
// 				tgt_chunk.Reset();
// 				tgt_chunk.ExtInitCompress(exp.exp, exp.var);
// 				tgt_chunk.ExtAnalyze(tgt_col.data(), n_tup);
// 				// endregion
// 				bsz += dict_fac<i64_pt>::exp_multi_dic_create(src_col, tgt_col);
// 			} break;
// 			case LT::STR: {
// 				auto& tgt_col = std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[tgt_idx])->data;
// 				// region TODO
// 				TColEncoder<str_pt> tgt_chunk {};
// 				tgt_chunk.Reset();
// 				tgt_chunk.ExtInitCompress(exp.exp, exp.var);
// 				tgt_chunk.ExtAnalyze(tgt_col.data(), n_tup);
// 				// endregion
// 				bsz += dict_fac<i64_pt>::exp_multi_dic_create(src_col, tgt_col);
// 			} break;
// 			case LT::FALLBACK: {
// 			} break;
// 				// TODO [FIXME]
// 			default:
// 				break;
// 			}
// 		}
//
// 	} break;
// 	case LT::STR: {
// 		auto&               src_col = std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 		TColEncoder<str_pt> src_chunk {};
// 		res = str_encoder_up->EncodeDict(src_col).GetAll();
// 		// region Description
// 		const Expression& exp   = res.exp_result_vec.front().expression;
// 		n_t               n_tup = src_col.size();
//
// 		src_chunk.Reset();
// 		src_chunk.ExtInitCompress(exp.exp, exp.var);
// 		src_chunk.ExtAnalyze(src_col.data(), n_tup);
// 		// endregion
//
// 		for (auto tgt_idx : sub_plan.group) {
// 			type = footer.schema[tgt_idx].logical_type;
//
// 			switch (type) {
// 			case LT::INVALID: {
// 			} break;
// 			case LT::DOUBLE: {
// 			} break;
// 			case LT::INT64: {
// 				auto& tgt_col = std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[tgt_idx])->data;
// 				// region Description
// 				TColEncoder<i64_pt> tgt_chunk {};
// 				tgt_chunk.Reset();
// 				tgt_chunk.ExtInitCompress(exp.exp, exp.var);
// 				tgt_chunk.ExtAnalyze(tgt_col.data(), n_tup);
// 				// endregion
// 				bsz += dict_fac<str_pt>::exp_multi_dic_create(src_col, tgt_col);
// 			} break;
// 			case LT::STR: {
// 				auto& tgt_col = std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[tgt_idx])->data;
// 				// region Description
// 				TColEncoder<str_pt> tgt_chunk {};
// 				tgt_chunk.Reset();
// 				tgt_chunk.ExtInitCompress(exp.exp, exp.var);
// 				tgt_chunk.ExtAnalyze(tgt_col.data(), n_tup);
// 				// endregion
// 				bsz += dict_fac<str_pt>::exp_multi_dic_create(src_col, tgt_col);
// 			} break;
// 			case LT::FALLBACK: {
// 			} break;
// 				// TODO [FIXME]
// 			default:
// 				break;
// 			}
// 		}
//
// 	} break;
// 	case LT::FALLBACK: {
// 	} break;
// 		// TODO [FIXME]
// 	default:
// 		break;
// 	}
//
// 	exp_res.bsz = bsz;
// 	res.exp_result_vec.push_back(exp_res);
// 	return std::make_unique<AllExpEncodedCol>(res);
// }
//
// up<AllExpEncodedCol> MultiColEncoder::test(const Schema& footer, const std::string& csv_file, TmpSubPlan& sub_plan) {
// 	FLS_ABORT("USE EXPERIMENTAL")
//
// 	/**/
// 	Rowgroup bff(const_cast<Schema&>(footer));
// 	bff.ReadCsv(csv_file);
//
// 	FLS_ASSERT_E(bff.n_tup, 1024UL * 64)
//
// 	auto res_up = test(footer, bff, sub_plan);
// 	std::cout << *res_up;
//
// 	return res_up;
// }
//
// MultiColEncoder::MultiColEncoder() {
// 	/**/
// 	int64_encoder_up = std::make_unique<ExpColEncoder<i64_pt>>(TEMPORARY, WITHOUT_VERIFICATION);
// 	str_encoder_up   = std::make_unique<ExpColEncoder<str_pt>>(TEMPORARY, WITHOUT_VERIFICATION);
// }
//
// up<AllExpEncodedCol>
// MultiColEncoder::only_dict_test(const Schema& footer, const Rowgroup& bff, const TmpSubPlan& sub_plan) {
// 	AllExpEncodedCol res;
// 	auto             idx  = sub_plan.idx;
// 	auto             type = footer.schema[idx].logical_type;
// 	ExpEncodedCol    exp_res {{0, 0, sub_plan.exp}, 0};
// 	bsz_t            bsz {0};
//
// 	switch (type) {
// 	case LT::INT64: {
// 		auto& src_col = std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[idx])->data;
// 		bsz += dict_fac<i64_pt>::exp_multi_dic_create(src_col);
// 	} break;
// 	case LT::STR: {
// 		auto& src_col = std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[idx])->data;
// 		bsz += dict_fac<str_pt>::exp_multi_dic_create(src_col);
// 	} break;
// 	case LT::DOUBLE: {
// 		auto& src_col = std::get<up<TypedCol<dbl_pt>>>(bff.internal_rowgroup[idx])->data;
// 		bsz += dict_fac<dbl_pt>::exp_multi_dic_create(src_col);
// 	} break;
// 		// TODO [FIXME]
// 	default:
// 		break;
// 	}
//
// 	exp_res.bsz = bsz;
// 	res.exp_result_vec.push_back(exp_res);
// 	return std::make_unique<AllExpEncodedCol>(res);
// }
//
// up<AllExpEncodedCol> MultiColEncoder::exp_test(const Schema& footer, const Rowgroup& bff, const TmpSubPlan& sub_plan)
// {
// 	/**/
// 	AllExpEncodedCol res;
// 	auto             tgt_idx = sub_plan.idx;
// 	auto             type    = footer.schema[tgt_idx].logical_type;
// 	ExpEncodedCol    exp_res {{0, 0, sub_plan.exp}, 0};
// 	bsz_t            bsz {0};
//
// 	switch (type) {
// 	case LT::INT64: {
// 		auto  src_idx = sub_plan.src_idx;
// 		auto& tgt_col = std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[tgt_idx])->data;
// 		type          = footer.schema[src_idx].logical_type;
// 		switch (type) {
// 		case LT::INVALID: {
// 		} break;
// 		case LT::DOUBLE: {
// 			auto& src_col = std::get<up<TypedCol<dbl_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<dbl_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::INT64: {
// 			auto& src_col = std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<i64_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::STR: {
// 			auto& src_col = std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<str_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::FALLBACK: {
// 		} break;
// 			// TODO [FIXME]
// 		default:
// 			break;
// 		}
//
// 	} break;
// 	case LT::STR: {
// 		auto  src_idx = sub_plan.src_idx;
// 		auto& tgt_col = std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[tgt_idx])->data;
// 		type          = footer.schema[src_idx].logical_type;
// 		switch (type) {
// 		case LT::INVALID: {
// 		} break;
// 		case LT::DOUBLE: {
// 			auto& src_col = std::get<up<TypedCol<dbl_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<dbl_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::INT64: {
// 			auto& src_col = std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<i64_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::STR: {
// 			auto& src_col = std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<str_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::FALLBACK: {
// 		} break;
// 			// TODO [FIXME]
// 		default:
// 			break;
// 		}
// 	} break;
// 	case LT::DOUBLE: {
// 		auto  src_idx = sub_plan.src_idx;
// 		auto& tgt_col = std::get<up<TypedCol<dbl_pt>>>(bff.internal_rowgroup[tgt_idx])->data;
// 		type          = footer.schema[src_idx].logical_type;
// 		switch (type) {
// 		case LT::INVALID: {
// 		} break;
// 		case LT::DOUBLE: {
// 			auto& src_col = std::get<up<TypedCol<dbl_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<dbl_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::INT64: {
// 			auto& src_col = std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<i64_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::STR: {
// 			auto& src_col = std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[src_idx])->data;
// 			bsz += dict_fac<str_pt>::exp_multi_dic_create(src_col, tgt_col);
// 		} break;
// 		case LT::FALLBACK: {
// 		} break;
// 			// TODO [FIXME]
// 		default:
// 			break;
// 		}
// 	} break;
// 	default:
// 		FLS_ABORT("IMPLEMENT!")
// 	}
//
// 	exp_res.bsz = bsz;
// 	res.exp_result_vec.push_back(exp_res);
// 	return std::make_unique<AllExpEncodedCol>(res);
// }
//
// up<AllExpEncodedCol>
// MultiColEncoder::exp_test(const Schema& footer, const std::string& csv_file, TmpSubPlan& sub_plan) {
// 	/**/
// 	Rowgroup bff(const_cast<Schema&>(footer));
// 	bff.ReadCsv(csv_file);
//
// 	FLS_ASSERT_E(bff.n_tup, 1024UL * 64)
//
// 	auto res_up = exp_test(footer, bff, sub_plan);
// 	std::cout << *res_up;
//
// 	return res_up;
// }
//
// up<AllExpEncodedCol>
// MultiColEncoder::exp_only_dict_test(const Schema& footer, const Rowgroup& bff, const TmpSubPlan& sub_plan) {
// 	/**/
// 	FLS_ABORT("IMPLEMENT IT")
// 	return {};
// }

} // namespace fastlanes