//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MATH_ROOTS_H
#define _LIBCPP___MATH_ROOTS_H

#include <__config>
#include <__type_traits/enable_if.h>
#include <__type_traits/is_integral.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __math {

// sqrt

inline _LIBCPP_HIDE_FROM_ABI float sqrt(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sqrtf(__x);
#else
  return __builtin_sqrtf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double sqrt(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sqrt(__x);
#else
  return __builtin_sqrt(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double sqrt(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sqrtl(__x);
#else
  return __builtin_sqrtl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double sqrt(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sqrt((double)__x);
#else
  return __builtin_sqrt((double)__x);
#endif
}

// cbrt

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI float cbrt(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cbrtf(__x);
#else
  return __builtin_cbrtf(__x);
#endif
}

template <class = int>
_LIBCPP_NODISCARD_EXT _LIBCPP_HIDE_FROM_ABI double cbrt(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cbrt(__x);
#else
  return __builtin_cbrt(__x);
#endif
}

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI long double cbrt(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cbrtl(__x);
#else
  return __builtin_cbrtl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI double cbrt(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cbrt((double)__x);
#else
  return __builtin_cbrt((double)__x);
#endif
}

} // namespace __math

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MATH_ROOTS_H
