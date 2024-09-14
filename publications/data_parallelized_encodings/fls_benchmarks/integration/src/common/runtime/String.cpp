#include "common/runtime/String.hpp"

using namespace std;

inline bool fmemcmp(const char* __restrict__ left,
                    const char* __restrict__ right, uint32_t size) {
   for (uint32_t i = 0; i < size; ++i)
      if (left[i] != right[i]) {
         return false;
      }
   return true;
}

SmallStringView::SmallStringView(std::experimental::string_view& s) {
   assign(s);
}

SmallStringView::SmallStringView(const char* start, uint32_t end) {
   assign(start, end);
}
SmallStringView::SmallStringView(const SmallStringView& o) {
   raw.first = o.raw.first;
   raw.second = o.raw.second;
}

SmallStringView::SmallStringView() { raw.first = 0; }

bool operator==(const SmallStringView& lhs, const SmallStringView& rhs) {
   if (lhs.raw.first != rhs.raw.first)
      return false;
   if (lhs.isInlined())
      return lhs.raw.second == rhs.raw.second;
   return fmemcmp(lhs.data(), rhs.data(), lhs.size());
}

bool operator==(const SmallStringView& lhs,
                const std::experimental::string_view& rhs) {
   auto size = lhs.size();
   if (size != rhs.size())
      return false;
   return fmemcmp(lhs.data(), rhs.data(), size);
}

bool SmallStringView::isInlined() const { return size() <= foldCapacity; }

std::ostream& operator<<(std::ostream& os, const SmallStringView& str) {
   os.write(str.data(), str.size());
   return os;
}

void SmallStringView::assign(const char* start, uint32_t size) {

   // assure zero padding if prefix is smaller than 4
   raw.first = 0;
   setSize(size);
   if (isInlined()) {
      // copy complete string to internal storage
      raw.second = 0;
      std::memcpy(inlined.data, start, size);
   } else {
      // copy prefix to internal
      std::memcpy(heap.prefix, start, 4);
      // store pointer to input
      setStrPtr(start);
   }
}

void SmallStringView::assign(string& data) { assign(data.data(), data.size()); }

void SmallStringView::assign(std::experimental::string_view& data) {
   assign(data.data(), data.size());
}

void SmallStringView::clear() { raw.first = 0; }

inline uint32_t SmallStringView::size() const { return inlined.size; }
inline const char* SmallStringView::data() const {
   if (isInlined())
      return inlined.data;
   else
      return heap.data;
}

inline void SmallStringView::setSize(uint32_t s) { inlined.size = s; }
inline void SmallStringView::setStrPtr(const char* str) { heap.data = str; }
