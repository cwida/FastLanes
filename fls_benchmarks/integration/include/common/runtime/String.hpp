#pragma once

#include <algorithm>
#include <cstring>
#include <experimental/string_view>
#include <iostream>
#include <string>

class SmallStringView {
 public:
   SmallStringView(std::experimental::string_view& s);

   SmallStringView(const char* start, uint32_t end);

   SmallStringView(const SmallStringView& o);

   SmallStringView();

   static const uint32_t foldCapacity = 12;
   inline friend bool operator==(const SmallStringView& lhs,
                                 const SmallStringView& rhs);

   bool isInlined() const;

   inline friend bool operator==(const SmallStringView& lhs,
                                 const std::experimental::string_view& rhs);

   friend std::ostream& operator<<(std::ostream& os,
                                   const SmallStringView& str);

   void assign(const char* start, uint32_t size);

   inline void assign(std::string& data);

   inline void assign(std::experimental::string_view& data);

   void clear();

   inline uint32_t size() const;

   inline const char* data() const;

 private:
   union {
      struct {
         uint64_t first;
         uint64_t second;
      } raw;
      struct {
         uint32_t size;
         char data[12];
      } inlined;
      struct {
         uint32_t size;
         char prefix[4];
         const char* data;
      } heap;
   };

   static_assert(sizeof(raw) == 16, "Bad data size");
   static_assert(sizeof(inlined) == 16, "Bad data size");
   static_assert(sizeof(heap) == 16, "Bad data size");

   inline void setSize(uint32_t s);

   inline void setStrPtr(const char* str);
};
