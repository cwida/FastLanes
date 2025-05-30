#ifndef FLS_CMN_STP_HPP
#define FLS_CMN_STP_HPP

#include <cstddef>
#include <cstdint>
#include <utility>

namespace fastlanes {
class RefC {
public:
	virtual ~RefC() = default; //
public:
	uint64_t c;
	RefC()
	    : c(1) {
	}
	void Inc() {
		++c;
	}
	void Dec() {
		--c;
	}
	uint32_t GetPn() const {
		return c;
	}
};

template <typename T>
class stp { /* NOLINT*/
public:
	explicit stp();                  // Default constructor, constructs an empty stp.
	explicit stp(std::nullptr_t);    // Construct a stp that wraps raw pointer.
	explicit stp(RefC* r, T* p);     //
	stp(const stp& sp);              //
	stp(stp&& sp) noexcept;          //
	stp& operator=(stp sp) noexcept; // Copy assignment.
	~stp();                          // No effect if stp is empty or use_count() > 1, otherwise release the resources.

	template <class U>
	stp(RefC* r, U* p) {
		ptr   = p;
		ref_c = r;
	}
	// Conversion constructor.
	template <typename U>
	explicit stp(const stp<U>& sp)
	    : ptr(nullptr)
	    , ref_c(nullptr) {
		if (sp.ptr) {
			ptr   = sp.ptr;
			ref_c = sp.ref_c;
			ref_c->Inc();
		}
	}
	// move  constructor.
	template <class U>
	explicit stp(stp<U>&& sp) noexcept
	    : ptr {sp.ptr}
	    , ref_c {sp.ref_c} {
		sp.ptr   = nullptr;
		sp.ref_c = nullptr;
	}

public:
	void    Release();
	int64_t UseCount() const noexcept; // Return use count (use count == 0 if stp is empty).
	T&      operator*() const noexcept {
		     return *ptr;
	} // Dereference pointer to managed object.
	T* operator->() const noexcept {
		return ptr;
	} //
	T* Get() const noexcept {
		return ptr;
	} // Return the contained pointer.
	explicit operator bool() const noexcept {
		return (ptr);
	} // Check if there is an associated managed object.
	void Reset() noexcept {
		Release();
	} // Resets stp to empty.
public:
	T*    ptr;   //
	RefC* ref_c; // reference counter.
};

template <class T>
struct ObjectAndBlock : public RefC {
public:
	T object;

public:
	template <class... ARGS>
	explicit ObjectAndBlock(ARGS&&... args)
	    : object(std::forward<ARGS>(args)...) {
	}
};

template <class T, class... ARGS>
stp<T> make_stp(ARGS&&... args) { /* NOLINT. */
	auto tmp_object = new ObjectAndBlock<T>(std::forward<ARGS>(args)...);
	return stp<T>(tmp_object, &(tmp_object->object));
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Implementation
\---------------------------------------------------------------------------------------------------------------------*/
template <typename T>
stp<T>::stp()
    : ptr(nullptr)
    , ref_c(nullptr) {
}

template <typename T>
stp<T>::stp(std::nullptr_t)
    : ptr(nullptr)
    , ref_c(nullptr) {
}

template <typename T>
stp<T>::stp(RefC* r, T* p) {
	ptr   = p;
	ref_c = r;
}

template <typename T>
stp<T>::stp(stp&& sp) noexcept
    : ptr {sp.ptr}
    , ref_c {sp.ref_c} {
	sp.ptr   = nullptr;
	sp.ref_c = nullptr;
}

template <typename T>
stp<T>::stp(const stp& sp)
    : ptr(nullptr)
    , ref_c(nullptr) {
	if (sp.ptr) {
		ptr   = sp.ptr;
		ref_c = sp.ref_c;
		ref_c->Inc();
	}
}

template <typename T>
void stp<T>::Release() {
	if (ptr && ref_c) {
		ref_c->Dec();
		if ((ref_c->GetPn()) == 0) {
			delete ref_c;
		}
	}
	ref_c = nullptr;
	ptr   = nullptr;
}

template <typename T>
int64_t stp<T>::UseCount() const noexcept {
	if (ptr) {
		return ref_c->GetPn();
	} else {
		return 0;
	}
}

template <typename T>
stp<T>& stp<T>::operator=(stp sp) noexcept {
	std::swap(this->ptr, sp.ptr);
	std::swap(this->ref_c, sp.ref_c);
	return *this;
}

template <typename T>
stp<T>::~stp() {
	Release();
}

// Operator overloading.
template <typename T, typename U>
inline bool operator==(const stp<T>& sp1, const stp<U>& sp2) {
	return sp1.get() == sp2.get();
}

template <typename T>
inline bool operator==(const stp<T>& sp, std::nullptr_t) noexcept {
	return !sp;
}

template <typename T, typename U>
inline bool operator!=(const stp<T>& sp1, const stp<U>& sp2) {
	return sp1.get() != sp2.get();
}

template <typename T>
inline bool operator!=(const stp<T>& sp, std::nullptr_t) noexcept {
	return sp.get();
}

template <typename T>
inline bool operator!=(std::nullptr_t, const stp<T>& sp) noexcept {
	return sp.get();
}
} // namespace fastlanes
#endif // FLS_CMN_STP_HPP