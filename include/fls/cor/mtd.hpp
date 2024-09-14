#ifndef FLS_COR_MTD_HPP
#define FLS_COR_MTD_HPP

#include "fls/common/byte_c.hpp"
#include "fls/stt/histogram.hpp"
#include "fls/stt/minmax.hpp"

namespace fastlanes {
class BaseMtd {};
template <typename T>
class Mtd : public BaseMtd {
public:
	explicit Mtd(n_t cap);    //
	virtual ~Mtd() = default; //
public:
	n_t    Size() const;        //
	n_t    UnusedSize() const;  //
	n_t    Cardinality() const; //
	n_t    Count() const;       //
	n_t    VecCount() const;    //
	double Occupancy() const;   //
	double Ratio() const;       //
	T      Min() const;         //
	T      Max() const;         //
	void   Reset();             //
	void   Reset(n_t c);        //
public:
	const byte_c cap;           // Capacity.
	byte_c       size;          //
	byte_c       compressed_sz; //
	MinMax<T>    min_max;       //
	Histogram<T> histogram;     //
};
} // namespace fastlanes
#endif // FLS_COR_MTD_HPP
