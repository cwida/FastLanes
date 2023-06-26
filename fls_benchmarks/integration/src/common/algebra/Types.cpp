#include "common/algebra/Types.hpp"
#include "common/runtime/Types.hpp"

namespace algebra {

Integer::operator std::string() const { return "Integer"; }
size_t Integer::rt_size() const { return sizeof(types::Integer); };
const std::string& Integer::cppname() const {
   static std::string cppname = "Integer";
   return cppname;
}

BigInt::operator std::string() const { return "BigInt"; }
size_t BigInt::rt_size() const { return sizeof(int64_t); };
const std::string& BigInt::cppname() const {
   static std::string cppname = "BigInt";
   return cppname;
}

Date::operator std::string() const { return "Integer"; }
size_t Date::rt_size() const { return sizeof(types::Date); };
const std::string& Date::cppname() const {
   static std::string cppname = "Date";
   return cppname;
}

Numeric::Numeric(uint32_t s, uint32_t p) : size(s), precision(p) {}
Numeric::operator std::string() const { return "Integer"; }
size_t Numeric::rt_size() const {
   /* currently, all numerics are of same size */
   return sizeof(types::Numeric<40, 2>);
};
const std::string& Numeric::cppname() const {
   static std::string cppname;
   cppname = "Numeric<" + std::to_string(size) + "," +
             std::to_string(precision) + ">";
   return cppname;
}

Char::Char(uint32_t s) : size(s) {}
Char::operator std::string() const { return "Char"; }
size_t Char::rt_size() const { return size == 1 ? 1 : size + 1; };
const std::string& Char::cppname() const {
   static std::string cppname;
   cppname = "Char<" + std::to_string(size) + ">";
   return cppname;
}

Varchar::Varchar(uint32_t s) : size(s) {}
Varchar::operator std::string() const { return "Varchar"; }
size_t Varchar::rt_size() const { return size + 1; };
const std::string& Varchar::cppname() const {
   static std::string cppname;
   cppname = cppname = "Varchar<" + std::to_string(size) + ">";
   return cppname;
}
}
