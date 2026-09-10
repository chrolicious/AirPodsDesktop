#pragma once
// Compatibility shim for building with VS2022+ against Qt 6.5.x (msvc2019 build).
// Force-included via /FI so all TUs get these fixes.

// <assert.h> resolves to Source/Assert.h on Windows (case-insensitive FS + -I Source/).
// Source/Assert.h only defines APD_ASSERT, not the standard assert() macro.
// Define assert() here so DirectXMath/WinRT headers get the macro they expect.
#include <assert.h>
#ifndef assert
#  ifdef NDEBUG
#    define assert(expression) ((void)0)
#  else
extern "C" __declspec(dllimport) void __cdecl _wassert(wchar_t const*, wchar_t const*, unsigned);
#    define assert(expression) \
         ((void)((!!(expression)) || (_wassert(L ## #expression, L"" __FILE__, (unsigned)(__LINE__)), 0)))
#  endif
#endif
#include <iterator>
#include <cstddef>

// stdext::checked_array_iterator was removed from MSVC STL in VS2022+.
// Qt 6.5.x msvc2019 headers still reference it in template code.
#if defined(_MSC_VER) && !defined(_HAS_CHECKED_ITERATORS)
namespace stdext {
    template<class T>
    class checked_array_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = typename std::iterator_traits<T>::value_type;
        using difference_type = typename std::iterator_traits<T>::difference_type;
        using pointer = typename std::iterator_traits<T>::pointer;
        using reference = typename std::iterator_traits<T>::reference;

        checked_array_iterator(T ptr, std::size_t) : ptr_(ptr) {}
        checked_array_iterator(T ptr, std::size_t, std::size_t off) : ptr_(ptr + off) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }
        reference operator[](difference_type n) const { return ptr_[n]; }

        checked_array_iterator& operator++() { ++ptr_; return *this; }
        checked_array_iterator operator++(int) { auto t = *this; ++ptr_; return t; }
        checked_array_iterator& operator--() { --ptr_; return *this; }
        checked_array_iterator operator--(int) { auto t = *this; --ptr_; return t; }

        checked_array_iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        checked_array_iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }

        friend checked_array_iterator operator+(checked_array_iterator it, difference_type n) { it += n; return it; }
        friend checked_array_iterator operator+(difference_type n, checked_array_iterator it) { it += n; return it; }
        friend checked_array_iterator operator-(checked_array_iterator it, difference_type n) { it -= n; return it; }
        friend difference_type operator-(const checked_array_iterator& a, const checked_array_iterator& b) { return a.ptr_ - b.ptr_; }

        bool operator==(const checked_array_iterator& o) const { return ptr_ == o.ptr_; }
        bool operator!=(const checked_array_iterator& o) const { return ptr_ != o.ptr_; }
        bool operator<(const checked_array_iterator& o) const { return ptr_ < o.ptr_; }
        bool operator>(const checked_array_iterator& o) const { return ptr_ > o.ptr_; }
        bool operator<=(const checked_array_iterator& o) const { return ptr_ <= o.ptr_; }
        bool operator>=(const checked_array_iterator& o) const { return ptr_ >= o.ptr_; }

        T base() const { return ptr_; }
    private:
        T ptr_;
    };

    template<class T>
    checked_array_iterator<T> make_checked_array_iterator(T ptr, std::size_t size, std::size_t offset = 0) {
        return checked_array_iterator<T>(ptr, size, offset);
    }
}
#endif
