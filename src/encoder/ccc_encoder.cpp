
namespace fastlanes {

// for (const auto& sub_plan : plan_up->sub_plan_vec) {
// 	auto col_idx = sub_plan->idx;
// 	switch (sub_plan->action) {
// 	case ActionT::DICT_1TN_SRC: {
// 		switch (mtd_vec[sub_plan->idx].logical_type) {
// 		case LT::INT64: {
// 			auto result = tab_encoder->i64_tester_up->EncodeDict(
// 			    std::get<up<TypedCol<i64_pt>>>(bff.internal_rowgroup[col_idx])->data);
// 			result.col_idx = col_idx; // TODO HACKY
// 			std::cout << result;
// 			res.col_result_vec.push_back(result);
// 			break;
// 		}
// 		case LT::STR: {
// 			auto result = tab_encoder->str_tester_up->EncodeDict(
// 			    std::get<up<TypedCol<str_pt>>>(bff.internal_rowgroup[col_idx])->data);
// 			result.col_idx = col_idx; // TODO HACKY
// 			std::cout << result;
// 			res.col_result_vec.push_back(result);
// 			break;
// 		}
// 		case LT::DOUBLE: {
// 			auto result = tab_encoder->dbl_tester_up->EncodeDict(
// 			    std::get<up<TypedCol<dbl_pt>>>(bff.internal_rowgroup[col_idx])->data);
// 			result.col_idx = col_idx; // TODO HACKY
// 			std::cout << result;
// 			res.col_result_vec.push_back(result);
// 			break;
// 		}
// 			// TODO [FIXME]
// 		default:
// 			break;
// 		}
// 	} break;
// 	case ActionT::DICT_1TN_TGT: {
// 		auto res_up     = multi_col_encoder->exp_test(schema, bff, *sub_plan);
// 		res_up->col_idx = col_idx;
// 		std::cout << *res_up;
// 		res.col_result_vec.push_back(*res_up);
// 	} break;
// 	case ActionT::ONLY_DICT: {
// 		auto res_up     = multi_col_encoder->only_dict_test(schema, bff, *sub_plan);
// 		res_up->col_idx = col_idx;
// 		std::cout << *res_up;
// 		res.col_result_vec.push_back(*res_up);
// 	} break;
// 	case ActionT::DICT_1T1: {
// 		auto res_up     = multi_col_encoder->test(schema, bff, *sub_plan);
// 		res_up->col_idx = col_idx;
// 		res_up->exp_result_vec.emplace_back();
// 		std::cout << *res_up;
// 		res.col_result_vec.push_back(*res_up);
// 	} break;
// 	case ActionT::SKIP: {
// 		AllExpEncodedCol result;
// 		result.col_idx = col_idx; // TODO HACKY
// 		result.exp_result_vec.emplace_back();
// 		res.col_result_vec.push_back(result);
// 	} break;
// 	case ActionT::TRY_ALL: {
// 		switch (mtd_vec[sub_plan->idx].logical_type) {
// 		case LT::DOUBLE:
// 		case LT::INT64:
// 		case LT::STR: {
// 			AllExpEncodedCol result;
// 			result.col_idx = col_idx; // TODO HACKY
// 			result.exp_result_vec.emplace_back();
// 			res.col_result_vec.push_back(result);
// 		}
//

} // namespace fastlanes