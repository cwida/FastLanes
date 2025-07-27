// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// fsst/data/include/data.hpp
// ────────────────────────────────────────────────────────
#ifndef DATA_HPP
#define DATA_HPP

#include <array>
#include <string>

namespace data {
using std::array;
using std::pair;
using std::string_view;

class dbtext {
public:
	// Define all the string_view constants for paths
	static constexpr string_view HEX {FSST_CMAKE_SOURCE_DIR "/data/dbtext/hex"};
	static constexpr string_view YAGO {FSST_CMAKE_SOURCE_DIR "/data/dbtext/yago"};
	static constexpr string_view EMAIL {FSST_CMAKE_SOURCE_DIR "/data/dbtext/email"};
	static constexpr string_view WIKI {FSST_CMAKE_SOURCE_DIR "/data/dbtext/wiki"};
	static constexpr string_view UUID {FSST_CMAKE_SOURCE_DIR "/data/dbtext/uuid"};
	static constexpr string_view URLS2 {FSST_CMAKE_SOURCE_DIR "/data/dbtext/urls2"};
	static constexpr string_view URLS {FSST_CMAKE_SOURCE_DIR "/data/dbtext/urls"};
	static constexpr string_view FIRSTNAME {FSST_CMAKE_SOURCE_DIR "/data/dbtext/firstname"};
	static constexpr string_view LASTNAME {FSST_CMAKE_SOURCE_DIR "/data/dbtext/lastname"};
	static constexpr string_view CITY {FSST_CMAKE_SOURCE_DIR "/data/dbtext/city"};
	static constexpr string_view CREDENTIALS {FSST_CMAKE_SOURCE_DIR "/data/dbtext/credentials"};
	static constexpr string_view STREET {FSST_CMAKE_SOURCE_DIR "/data/dbtext/street"};
	static constexpr string_view MOVIES {FSST_CMAKE_SOURCE_DIR "/data/dbtext/movies"};
	static constexpr string_view FAUST {FSST_CMAKE_SOURCE_DIR "/data/dbtext/faust"};
	static constexpr string_view HAMLET {FSST_CMAKE_SOURCE_DIR "/data/dbtext/hamlet"};
	static constexpr string_view CHINESE {FSST_CMAKE_SOURCE_DIR "/data/dbtext/chinese"};
	static constexpr string_view JAPANESE {FSST_CMAKE_SOURCE_DIR "/data/dbtext/japanese"};
	static constexpr string_view WIKIPEDIA {FSST_CMAKE_SOURCE_DIR "/data/dbtext/wikipedia"};
	static constexpr string_view GENOME {FSST_CMAKE_SOURCE_DIR "/data/dbtext/genome"};
	static constexpr string_view LOCATION {FSST_CMAKE_SOURCE_DIR "/data/dbtext/location"};
	static constexpr string_view C_NAME {FSST_CMAKE_SOURCE_DIR "/data/dbtext/c_name"};
	static constexpr string_view L_COMMENT {FSST_CMAKE_SOURCE_DIR "/data/dbtext/l_comment"};
	static constexpr string_view PS_COMMENT {FSST_CMAKE_SOURCE_DIR "/data/dbtext/ps_comment"};

	// Map of dataset names to their paths
	static constexpr std::array<std::pair<string_view, string_view>, 23> NAME_TO_PATH_MAP = {
	    {{"hex", HEX},
	     {"yago", YAGO},
	     {"email", EMAIL},
	     {"wiki", WIKI},
	     {"uuid", UUID},
	     {"urls2", URLS2},
	     {"urls", URLS},
	     {"firstname", FIRSTNAME},
	     {"lastname", LASTNAME},
	     {"city", CITY},
	     {"credentials", CREDENTIALS},
	     {"street", STREET},
	     {"movies", MOVIES},
	     {"faust", FAUST},
	     {"hamlet", HAMLET},
	     {"chinese", CHINESE},
	     {"japanese", JAPANESE},
	     {"wikipedia", WIKIPEDIA},
	     {"genome", GENOME},
	     {"location", LOCATION},
	     {"c_name", C_NAME},
	     {"l_comment", L_COMMENT},
	     {"ps_comment", PS_COMMENT}}};
};

class test {
public:
	// Define all the string_view constants for paths
	static constexpr string_view test_0 {FSST_CMAKE_SOURCE_DIR "/data/test/generated.csv"};

	// Map of dataset names to their paths
	static constexpr std::array<std::pair<string_view, string_view>, 1> NAME_TO_PATH_MAP = {{{"test_0", test_0}}};
};

// clang-format on
} // namespace data

#endif // DATA_HPP
