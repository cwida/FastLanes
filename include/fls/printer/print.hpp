#ifndef FLS_PRINTER_PRINT_HPP
#define FLS_PRINTER_PRINT_HPP

#ifdef NDEBUG
#define FLS_PRINT(...)      ;
#define FLS_BASIC_WARN(...) ;
#define FLS_BASIC_OK(...)   ;

#else
#include "fls/printer/color.hpp"
#include <iostream>
#define FLS_PRINT(...)      std::cerr << fmt::format(__VA_ARGS__);
#define FLS_BASIC_WARN(...) std::cout << fastlanes::debug::yellow << fmt::format(__VA_ARGS__) << fastlanes::debug::def;
#define FLS_BASIC_OK(...)   std::cout << fastlanes::debug::green << fmt::format(__VA_ARGS__) << fastlanes::debug::def;

#endif

// #define FLS_OK(Msg)                                                                                                    \
// 	FLS_BASIC_OK("FILE: {}:{} \n"                                                                                      \
// 	             "FUNC: {} Executed!\n"                                                                                \
// 	             "1MSG: {} \n"                                                                                         \
// 	             "									=================\n",                                              \
// 	             __FILE__,                                                                                             \
// 	             __LINE__,                                                                                             \
// 	             __PRETTY_FUNCTION__,                                                                                  \
// 	             Msg)

// #define FLS_WARN(Msg)                                                                                                  \
// 	FLS_BASIC_WARN("FILE: {}:{} \n"                                                                                    \
// 	               "FUNC: {} Executed!\n"                                                                              \
// 	               "1MSG: {} \n"                                                                                       \
// 	               "									=================\n",                                          \
// 	               __FILE__,                                                                                           \
// 	               __LINE__,                                                                                           \
// 	               __PRETTY_FUNCTION__,                                                                                \
// 	               Msg)

// #define FLS_PRINT_1MSG(Msg)                                                                                            \
// 	FLS_PRINT("FILE: {}:{} \n"                                                                                         \
// 	          "FUNC: {} Executed!\n"                                                                                   \
// 	          "1MSG: {} \n"                                                                                            \
// 	          "									=================\n",                                                  \
// 	          __FILE__,                                                                                                \
// 	          __LINE__,                                                                                                \
// 	          __PRETTY_FUNCTION__,                                                                                     \
// 	          Msg)
// TODO[FMT]

// #define FLS_PRINT_2MSG(...)                                                                                            \
// 	FLS_PRINT("FILE: {}:{} \n"                                                                                         \
// 	          "FUNC: {} Executed!\n"                                                                                   \
// 	          "2MSG: {} {} \n"                                                                                         \
// 	          "									=================\n",                                                  \
// 	          __FILE__,                                                                                                \
// 	          __LINE__,                                                                                                \
// 	          __PRETTY_FUNCTION__,                                                                                     \
// 	          __VA_ARGS__)

// #define FLS_PRINT_3MSG(...)                                                                                            \
// 	FLS_PRINT("FILE: {}:{} \n"                                                                                         \
// 	          "FUNC: {} Executed!\n"                                                                                   \
// 	          "3MSG: {} {} {} \n"                                                                                      \
// 	          "									=================\n",                                                  \
// 	          __FILE__,                                                                                                \
// 	          __LINE__,                                                                                                \
// 	          __PRETTY_FUNCTION__,                                                                                     \
// 	          __VA_ARGS__)

// #define FLS_PRINT_4MSG(...)                                                                                            \
// 	FLS_PRINT("FILE: {}:{} \n"                                                                                         \
// 	          "FUNC: {} Executed!\n"                                                                                   \
// 	          "4MSG: {} {} {} {} \n"                                                                                   \
// 	          "									=================\n",                                                  \
// 	          __FILE__,                                                                                                \
// 	          __LINE__,                                                                                                \
// 	          __PRETTY_FUNCTION__,                                                                                     \
// 	          __VA_ARGS__)

#define FLS_OK(Msg)         ;
#define FLS_PRINT_4MSG(...) ;
#define FLS_PRINT_6MSG(...) ;
#define FLS_PRINT_1MSG(Msg) ;
#define FLS_PRINT_2MSG(...) ;
#define FLS_PRINT_3MSG(...) ;
#define FLS_WARN(Msg)       ;

// #define FLS_PRINT_6MSG(...)                                                                                            \
// 	FLS_PRINT("FILE: {}:{} \n"                                                                                         \
// 	          "FUNC: {} Executed!\n"                                                                                   \
// 	          "4MSG: {} {} {} {} {} {} \n"                                                                             \
// 	          "									=================\n",                                                  \
// 	          __FILE__,                                                                                                \
// 	          __LINE__,                                                                                                \
// 	          __PRETTY_FUNCTION__,                                                                                     \
// 	          __VA_ARGS__)

#endif
