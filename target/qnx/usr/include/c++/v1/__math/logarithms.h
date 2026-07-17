//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MATH_LOGARITHMS_H
#define _LIBCPP___MATH_LOGARITHMS_H

#include <__config>
#include <__type_traits/enable_if.h>
#include <__type_traits/is_integral.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __math {

// log

inline _LIBCPP_HIDE_FROM_ABI float log(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::logf(__x);
#else
  return __builtin_logf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double log(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log(__x);
#else
  return __builtin_log(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double log(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::logl(__x);
#else
  return __builtin_logl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double log(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log((double)__x);
#else
  return __builtin_log((double)__x);
#endif
}

// log10

inline _LIBCPP_HIDE_FROM_ABI float log10(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log10f(__x);
#else
  return __builtin_log10f(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double log10(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log10(__x);
#else
  return __builtin_log10(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double log10(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log10l(__x);
#else
  return __builtin_log10l(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double log10(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log10((double)__x);
#else
  return __builtin_log10((double)__x);
#endif
}

// ilogb

inline _LIBCPP_HIDE_FROM_ABI int ilogb(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::ilogbf(__x);
#else
  return __builtin_ilogbf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double ilogb(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::ilogb(__x);
#else
  return __builtin_ilogb(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI int ilogb(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::ilogbl(__x);
#else
  return __builtin_ilogbl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI int ilogb(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::ilogb((double)__x);
#else
  return __builtin_ilogb((double)__x);
#endif
}

// log1p

inline _LIBCPP_HIDE_FROM_ABI float log1p(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log1pf(__x);
#else
  return __builtin_log1pf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double log1p(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log1p(__x);
#else
  return __builtin_log1p(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double log1p(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log1pl(__x);
#else
  return __builtin_log1pl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double log1p(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log1p((double)__x);
#else
  return __builtin_log1p((double)__x);
#endif
}

// log2

inline _LIBCPP_HIDE_FROM_ABI float log2(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log2f(__x);
#else
  return __builtin_log2f(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double log2(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log2(__x);
#else
  return __builtin_log2(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double log2(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log2l(__x);
#else
  return __builtin_log2l(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double log2(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::log2((double)__x);
#else
  return __builtin_log2((double)__x);
#endif
}

// logb

inline _LIBCPP_HIDE_FROM_ABI float logb(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::logbf(__x);
#else
  return __builtin_logbf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double logb(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::logb(__x);
#else
  return __builtin_logb(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double logb(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::logbl(__x);
#else
  return __builtin_logbl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double logb(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::logb((double)__x);
#else
  return __builtin_logb((double)__x);
#endif
}

} // namespace __math

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MATH_LOGARITHMS_H
