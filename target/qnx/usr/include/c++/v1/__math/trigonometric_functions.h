//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MATH_TRIGONOMETRIC_FUNCTIONS_H
#define _LIBCPP___MATH_TRIGONOMETRIC_FUNCTIONS_H

#include <__config>
#include <__type_traits/enable_if.h>
#include <__type_traits/is_integral.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __math {

// cos

inline _LIBCPP_HIDE_FROM_ABI float cos(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cosf(__x);
#else
  return __builtin_cosf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double cos(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cos(__x);
#else
  return __builtin_cos(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double cos(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cosl(__x);
#else
  return __builtin_cosl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double cos(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cos((double)__x);
#else
  return __builtin_cos((double)__x);
#endif
}

// sin

inline _LIBCPP_HIDE_FROM_ABI float sin(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sinf(__x);
#else
  return __builtin_sinf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double sin(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sin(__x);
#else
  return __builtin_sin(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double sin(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sinl(__x);
#else
  return __builtin_sinl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double sin(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sin((double)__x);
#else
  return __builtin_sin((double)__x);
#endif
}

// tan

inline _LIBCPP_HIDE_FROM_ABI float tan(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::tanf(__x);
#else
  return __builtin_tanf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double tan(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::tan(__x);
#else
  return __builtin_tan(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double tan(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::tanl(__x);
#else
  return __builtin_tanl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double tan(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::tan((double)__x);
#else
  return __builtin_tan((double)__x);
#endif
}

} // namespace __math

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MATH_TRIGONOMETRIC_FUNCTIONS_H
