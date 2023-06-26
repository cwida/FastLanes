#ifdef __SSE4_2__
#include <nmmintrin.h>
#endif
#include "common/runtime/Types.hpp"
//---------------------------------------------------------------------------
#include <ctime>
//---------------------------------------------------------------------------
// HyPer
// (c) Thomas Neumann 2010
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace types {
//---------------------------------------------------------------------------
const char* memmemSSE(const char *haystack, size_t len, const char *needleStr, size_t needleLength) {
#ifdef __SSE4_2__
   if (len<16||needleLength>16)
      return (const char*)memmem(haystack,len,needleStr,needleLength);

   union {
      __m128i v;
      char c[16];
   } needle;
   memcpy(needle.c,needleStr,needleLength);

   unsigned pos=0;
   while (len-pos>=16) {
      __m128i chunk=_mm_loadu_si128(reinterpret_cast<const __m128i*>(haystack+pos));
      unsigned result=_mm_cmpestri(needle.v,needleLength,chunk,16,_SIDD_CMP_EQUAL_ORDERED);
      if (16-result>=needleLength)
         return haystack+pos+result; else
         pos+=result;
   }

   // check rest
   pos=len-16;
   __m128i chunk=_mm_loadu_si128(reinterpret_cast<const __m128i*>(haystack+pos));
   unsigned result=_mm_cmpestri(needle.v,needleLength,chunk,16,_SIDD_CMP_EQUAL_ORDERED);
   if (16-result>=needleLength)
      return haystack+pos+result; else
      return NULL;

#else
   return (const char*)memmem(haystack,len,needleStr,needleLength);
#endif
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out,const Integer& value)
{
   out << value.value;
   return out;
}
//---------------------------------------------------------------------------
Integer Integer::castString(const char* str,uint32_t strLen)
   // Cast a string to an integer value
{
   auto iter=str,limit=str+strLen;

   // Trim WS
   while ((iter!=limit)&&((*iter)==' ')) ++iter;
   while ((iter!=limit)&&((*(limit-1))==' ')) --limit;

   // Check for a sign
   bool neg=false;
   if (iter!=limit) {
      if ((*iter)=='-') {
         neg=true;
         ++iter;
      } else if ((*iter)=='+') {
         ++iter;
      }
   }

   // Parse
   if (iter==limit)
      throw "invalid number format: found non-integer characters";

   int64_t result=0;
   unsigned digitsSeen=0;
   for (;iter!=limit;++iter) {
      char c=*iter;
      if ((c>='0')&&(c<='9')) {
         result=(result*10)+(c-'0');
         ++digitsSeen;
      } else if (c=='.') {
         break;
      } else {
         throw "invalid number format: invalid character in integer string";
      }
   }

   if (digitsSeen>10)
      throw "invalid number format: too many characters (32bit integers can at most consist of 10 numeric characters)";

   Integer r;
   r.value=neg?-result:result;
   return r;
}
//---------------------------------------------------------------------------
static const uint64_t msPerDay = 24*60*60*1000;
//---------------------------------------------------------------------------
static unsigned mergeTime(unsigned hour,unsigned minute,unsigned second,unsigned ms)
   // Merge into ms since midnight
{
   return ms+(1000*second)+(60*1000*minute)+(60*60*1000*hour);
}
//---------------------------------------------------------------------------
static unsigned mergeJulianDay(unsigned year, unsigned month, unsigned day)
   // Algorithm from the Calendar FAQ
{
   unsigned a = (14 - month) / 12;
   unsigned y = year + 4800 - a;
   unsigned m = month + (12*a) - 3;

   return day + ((153*m+2)/5) + (365*y) + (y/4) - (y/100) + (y/400) - 32045;
}
//---------------------------------------------------------------------------
static void splitJulianDay(unsigned jd, unsigned& year, unsigned& month, unsigned& day)
   // Algorithm from the Calendar FAQ
{
   unsigned a = jd + 32044;
   unsigned b = (4*a+3)/146097;
   unsigned c = a-((146097*b)/4);
   unsigned d = (4*c+3)/1461;
   unsigned e = c-((1461*d)/4);
   unsigned m = (5*e+2)/153;

   day = e - ((153*m+2)/5) + 1;
   month = m + 3 - (12*(m/10));
   year = (100*b) + d - 4800 + (m/10);
}
//---------------------------------------------------------------------------
Integer extractYear(const Date& d)
{
   unsigned year,month,day;
   splitJulianDay(d.value,year,month,day);
   Integer r(year);
   return r;
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out,const Date& value)
   // Output
{
   unsigned year,month,day;
   splitJulianDay(value.value,year,month,day);

   char buffer[30];
   snprintf(buffer,sizeof(buffer),"%04u-%02u-%02u",year,month,day);
   return out << buffer;
}
//---------------------------------------------------------------------------
Date Date::castString(std::string s){return castString(s.data(), s.size());}
//---------------------------------------------------------------------------
Date Date::castString(const char* str,uint32_t strLen)
   // Cast a string to a date
{
   auto iter=str,limit=str+strLen;

   // Trim WS
   while ((iter!=limit)&&((*iter)==' ')) ++iter;
   while ((iter!=limit)&&((*(limit-1))==' ')) --limit;

   // Year
   unsigned year=0;
   while (true) {
      if (iter==limit) throw "invalid date format";
      char c=*(iter++);
      if (c=='-') break;
      if ((c>='0')&&(c<='9')) {
         year=10*year+(c-'0');
      } else throw "invalid date format";
   }
   // Month
   unsigned month=0;
   while (true) {
      if (iter==limit) throw "invalid date format";
      char c=*(iter++);
      if (c=='-') break;
      if ((c>='0')&&(c<='9')) {
         month=10*month+(c-'0');
      } else throw "invalid date format";
   }
   // Day
   unsigned day=0;
   while (true) {
      if (iter==limit) break;
      char c=*(iter++);
      if ((c>='0')&&(c<='9')) {
         day=10*day+(c-'0');
      } else throw "invalid date format";
   }

   // Range check
   if ((year>9999)||(month<1)||(month>12)||(day<1)||(day>31))
      throw "invalid date format";
   Date d;
   d.value=mergeJulianDay(year,month,day);
   return d;
}
//---------------------------------------------------------------------------
Timestamp Timestamp::castString(const char* str,uint32_t strLen)
   // Cast a string to a timestamp value
{
   if ((strLen==4)&&(strncmp(str,"NULL",4)==0))
      return null();

   auto iter=str,limit=str+strLen;

   // Trim WS
   while ((iter!=limit)&&((*iter)==' ')) ++iter;
   while ((iter!=limit)&&((*(limit-1))==' ')) --limit;

   // Year
   unsigned year=0;
   while (true) {
      if (iter==limit) throw "invalid timestamp format";
      char c=*(iter++);
      if (c=='-') break;
      if ((c>='0')&&(c<='9')) {
         year=10*year+(c-'0');
      } else throw "invalid timestamp format";
   }
   // Month
   unsigned month=0;
   while (true) {
      if (iter==limit) throw "invalid timestamp format";
      char c=*(iter++);
      if (c=='-') break;
      if ((c>='0')&&(c<='9')) {
         month=10*month+(c-'0');
      } else throw "invalid timestamp format";
   }
   // Day
   unsigned day=0;
   while (true) {
      if (iter==limit) break;
      char c=*(iter++);
      if (c==' ') break;
      if ((c>='0')&&(c<='9')) {
         day=10*day+(c-'0');
      } else throw "invalid timestamp format";
   }

   // Range check
   if ((year>9999)||(month<1)||(month>12)||(day<1)||(day>31))
      throw "invalid timestamp format";
   uint64_t date=mergeJulianDay(year,month,day);

   // Hour
   unsigned hour=0;
   while (true) {
      if (iter==limit) throw "invalid timestamp format";
      char c=*(iter++);
      if (c==':') break;
      if ((c>='0')&&(c<='9')) {
         hour=10*hour+(c-'0');
      } else throw "invalid timestamp format";
   }
   // Minute
   unsigned minute=0;
   while (true) {
      if (iter==limit) throw "invalid timestamp format";
      char c=*(iter++);
      if (c==':') break;
      if ((c>='0')&&(c<='9')) {
         minute=10*minute+(c-'0');
      } else throw "invalid timestamp format";
   }
   // Second
   unsigned second=0;
   while (true) {
      if (iter==limit) break;
      char c=*(iter++);
      if (c=='.') break;
      if ((c>='0')&&(c<='9')) {
         second=10*second+(c-'0');
      } else throw "invalid timestamp format";
   }
   // Millisecond
   unsigned ms=0;
   while (iter!=limit) {
      char c=*(iter++);
      if ((c>='0')&&(c<='9')) {
         ms=10*ms+(c-'0');
      } else throw "invalid timestamp format";
   }

   // Range check
   if ((hour>=24)||(minute>=60)||(second>=60)||(ms>=1000))
      throw "invalid timestamp format";
   uint64_t time=mergeTime(hour,minute,second,ms);

   // Merge
   Timestamp t;
   t.value=(date*msPerDay)+time;
   return t;
}
//---------------------------------------------------------------------------
Timestamp Timestamp::null()
   // NULL
{
   Timestamp result;
   result.value=0;
   return result;
}
//---------------------------------------------------------------------------
static void splitTime(unsigned value,unsigned& hour,unsigned& minute,unsigned& second,unsigned& ms)
   // Split ms since midnight
{
   ms=value%1000; value/=1000;
   second=value%60; value/=60;
   minute=value%60; value/=60;
   hour=value%24;
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out,const Timestamp& value)
   // Output
{
   if (value==Timestamp::null())
      out << "NULL";

   unsigned year,month,day;
   splitJulianDay(value.value/msPerDay,year,month,day);
   unsigned hour,minute,second,ms;
   splitTime(value.value%msPerDay,hour,minute,second,ms);

   char buffer[50];
   if (ms)
      snprintf(buffer,sizeof(buffer),"%04u-%02u-%02u %u:%02u:%02u.%03u",year,month,day,hour,minute,second,ms); else
      snprintf(buffer,sizeof(buffer),"%04u-%02u-%02u %u:%02u:%02u",year,month,day,hour,minute,second);
   return out << buffer;
}
//---------------------------------------------------------------------------
/*
std::ostream& operator<<(std::ostream& out,const Timestamp& value)
   // Output
{
   time_t v=value.getRaw();
   if (!v) {
      out << "NULL";
   } else {
      char buffer[27];
      ctime_r(&v,buffer);
      if ((*buffer)&&(buffer[strlen(buffer)-1]=='\n'))
         buffer[strlen(buffer)-1]=0;
      out << '\"' << buffer << '\"';
   }
   return out;
}
*/
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
