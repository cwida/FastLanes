#include "fls/cor/mtd.hpp"
#include "fls/cfg/cfg.hpp"

namespace fastlanes {
template <typename T>
Mtd<T>::Mtd(n_t cap)
    : cap {cap}
    , size {0}
    , compressed_sz {0}
    , min_max {}
    , histogram {} {
}

template <typename T>
n_t Mtd<T>::Count() const {
	return size.Count<T>();
}

template <typename T>
double Mtd<T>::Ratio() const {
	return size / compressed_sz;
}

template <typename T>
n_t Mtd<T>::UnusedSize() const {
	return size - compressed_sz;
}

template <typename T>
T Mtd<T>::Min() const {
	return min_max.min;
}

template <typename T>
T Mtd<T>::Max() const {
	return min_max.max;
}

template <typename T>
void Mtd<T>::Reset() {
	min_max.Reset();
	histogram.Reset();
	compressed_sz.reset();
}

template <typename T>
n_t Mtd<T>::VecCount() const {
	return Count() / fastlanes::CFG::VEC_TUP_C;
}

template <typename T>
double Mtd<T>::Occupancy() const {
	return compressed_sz / cap;
}

template <typename T>
n_t Mtd<T>::Cardinality() const {
	FLS_ASSERT(histogram.val_vec.size() != 0, "Hist.size is zero. Call cal before use!", " ");

	return histogram.val_vec.size();
}

template <typename T>
n_t Mtd<T>::Size() const {
	return size.Val();
}
template <typename T>
void Mtd<T>::Reset(n_t c) {
	min_max.Reset();
	histogram.Reset();
	compressed_sz.reset();
	size = byte_c {c * sizeof(T)};
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(Mtd)
// CHECK
// {
// template class Mtd<parquet::FixedLenByteArray>;
// template class Mtd<parquet::Int96>;
// template class Mtd<parquet::ByteArray>;
// }
} // namespace fastlanes