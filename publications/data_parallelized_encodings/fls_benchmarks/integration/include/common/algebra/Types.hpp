#pragma once
#include <string>

namespace algebra {

struct Type {
   virtual operator std::string() const = 0;
   virtual const std::string& cppname() const = 0;
   virtual size_t rt_size() const = 0;
   virtual ~Type() = default;
};

struct Integer : public Type {
   virtual operator std::string() const override;
   virtual const std::string& cppname() const override;
   virtual size_t rt_size() const override;
};

struct BigInt : public Type {
   virtual operator std::string() const override;
   virtual const std::string& cppname() const override;
   virtual size_t rt_size() const override;
};

struct Date : public Type {
   virtual operator std::string() const override;
   virtual const std::string& cppname() const override;
   virtual size_t rt_size() const override;
};

class Numeric : public Type {
 public:
   uint32_t size = 0;
   uint32_t precision = 0;

   Numeric(uint32_t size, uint32_t precision);
   virtual operator std::string() const override;
   virtual const std::string& cppname() const override;
   virtual size_t rt_size() const override;
};

struct Char : public Type {
   uint32_t size = 0;
   virtual operator std::string() const override;
   virtual const std::string& cppname() const override;
   Char(uint32_t size);
   virtual size_t rt_size() const override;
};

struct Varchar : public Type {
   uint32_t size = 0;
   virtual operator std::string() const override;
   virtual const std::string& cppname() const override;
   Varchar(uint32_t size);
   virtual size_t rt_size() const override;
};
}
