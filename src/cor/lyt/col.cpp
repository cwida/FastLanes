#include "fls/cor/lyt/col.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/io/external_memory.hpp"

namespace fastlanes {
template <typename T>
Col<T>::Col()
    : m_count {0} {
	m_buffer.resize(CFG::ROW_GROUP_SIZE);
}

template <typename T>
T* Col<T>::operator[](n_t i) {
	if constexpr (std::is_same<T, bool>()) {
		FLS_ABORT("Not Supported")
	} else {
		FLS_ASSERT(i >= 0, "negative index.", " ");
		FLS_ASSERT(m_count != 0, "0 size.", " ");
		FLS_ASSERT(i < m_count, "Out of range index.", " ");

		return &(m_buffer[i]);
	}
	return nullptr;
}

template <typename T>
void Col<T>::Share(T* data, n_t c) {
}

template <typename T>
void Col<T>::Insert(T* data, n_t c) {
	if constexpr (std::is_same<T, bool>()) {
		FLS_ABORT("Not Supported")
	} else {
		FLS_ASSERT(m_count + c <= CFG::ROW_GROUP_SIZE, " ", "over_capacity");

		ExternalMemory::Copy(m_buffer.data() + m_count, data, c * sizeof(T));
		m_count += c;
	}
}

template <typename T>
T* Col<T>::Data() {
	//	return m_buffer.data();
	return nullptr;
}

template <typename T>
n_t Col<T>::Count() const {
	return m_count;
}

template <typename T>
byte_c Col<T>::Size() const {
	return byte_c {sizeof(T) * m_buffer.size()};
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(Col)
} // namespace fastlanes