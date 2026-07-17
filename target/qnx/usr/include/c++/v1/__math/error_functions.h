//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MATH_ERROR_FUNCTIONS_H
#define _LIBCPP___MATH_ERROR_FUNCTIONS_H

#include <__config>
#include <__type_traits/enable_if.h>
#include <__type_traits/is_integral.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __math {

// erf

inline _LIBCPP_HIDE_FROM_ABI float erf(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::erff(__x);
#else
  return __builtin_erff(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double erf(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::erf(__x);
#else
  return __builtin_erf(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double erf(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::erfl(__x);
#else
  return __builtin_erfl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double erf(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::erf((double)__x);
#else
  return __builtin_erf((double)__x);
#endif
}

// erfc

inline _LIBCPP_HIDE_FROM_ABI float erfc(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::erfcf(__x);
#else
  return __builtin_erfcf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double erfc(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::erfc(__x);
#else
  return __builtin_erfc(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double erfc(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::erfcl(__x);
#else
  return __builtin_erfcl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double erfc(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::erfc((double)__x);
#else
  return __builtin_erfc((double)__x);
#endif
}

} // namespace __math

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MATH_ERROR_FUNCTIONS_H
