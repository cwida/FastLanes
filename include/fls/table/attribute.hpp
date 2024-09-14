#ifndef FLS_TABLE_ATTRIBUTE_HPP
#define FLS_TABLE_ATTRIBUTE_HPP

#include "fls/std/string.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class TypedCol;
/*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class Attribute {
public:
	Attribute() = delete;

public:
	static void Ingest(TypedCol<PT>& typed_column, const string& val_str);
	static bool IsNull(const string& val_str);
	static PT   Cast(const string& val_str);
	static PT   Null();
};

} // namespace fastlanes
#endif // FLS_TABLE_ATTRIBUTE_HPP
