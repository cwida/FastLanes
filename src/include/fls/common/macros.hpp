#ifndef FLS_COMMON_MACROS_HPP
#define FLS_COMMON_MACROS_HPP

#include "fls/expression/data_type.hpp"

/*---------------------------------------------------------------------------------------------------------------------\
 * Internal MACROs:
\---------------------------------------------------------------------------------------------------------------------*/
#define FLS_UNUSED(x)                 (void)(x)

/*---------------------------------------------------------------------------------------------------------------------\
 * Class Template Specialization
\---------------------------------------------------------------------------------------------------------------------*/
#define FLS_CTS(CLASS_TEMPLATE, TYPE) template class CLASS_TEMPLATE<TYPE>;

/*---------------------------------------------------------------------------------------------------------------------\
 * ALL Class Template Specialization
\---------------------------------------------------------------------------------------------------------------------*/
#define FLS_ALL_CTS(CLASS_TEMPLATE)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, u08_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, u16_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, u32_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, u64_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, i08_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, i16_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, i32_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, i64_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, flt_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, dbl_pt)                                                                                    \
	FLS_CTS(CLASS_TEMPLATE, str_pt)

//	FLS_CTS(CLASS_TEMPLATE, bool)

/*---------------------------------------------------------------------------------------------------------------------\
 * Function Template Specialization \
\---------------------------------------------------------------------------------------------------------------------*/
#define FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, TYPE, ...) template RETURN_ARG FUNCTION_TEMPLATE<TYPE>(__VA_ARGS__);

/*---------------------------------------------------------------------------------------------------------------------\
 * ALL Function Template Specialization
\---------------------------------------------------------------------------------------------------------------------*/
#define FLS_ALL_FTS(RETURN_ARG, FUNCTION_TEMPLATE, ...)                                                                \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, uint8_t, __VA_ARGS__)                                                       \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, uint16_t, __VA_ARGS__)                                                      \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, uint32_t, __VA_ARGS__)                                                      \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, uint64_t, __VA_ARGS__)                                                      \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, int8_t, __VA_ARGS__)                                                        \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, int16_t, __VA_ARGS__)                                                       \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, int32_t, __VA_ARGS__)                                                       \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, i64_pt, __VA_ARGS__)                                                        \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, float, __VA_ARGS__)                                                         \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, dbl_pt, __VA_ARGS__)                                                        \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, bool, __VA_ARGS__)                                                          \
	FLS_FTS(RETURN_ARG, FUNCTION_TEMPLATE, str_pt, __VA_ARGS__)

#endif // FLS_COMMON_MACROS_HPP
