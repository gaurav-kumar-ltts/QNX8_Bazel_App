//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MATH_HYPERBOLIC_FUNCTIONS_H
#define _LIBCPP___MATH_HYPERBOLIC_FUNCTIONS_H

#include <__config>
#include <__type_traits/enable_if.h>
#include <__type_traits/is_integral.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __math {

// cosh

inline _LIBCPP_HIDE_FROM_ABI float cosh(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::coshf(__x);
#else
  return __builtin_coshf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double cosh(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cosh(__x);
#else
  return __builtin_cosh(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double cosh(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::coshl(__x);
#else
  return __builtin_coshl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double cosh(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::cosh((double)__x);
#else
  return __builtin_cosh((double)__x);
#endif
}

// sinh

inline _LIBCPP_HIDE_FROM_ABI float sinh(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sinhf(__x);
#else
  return __builtin_sinhf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double sinh(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sinh(__x);
#else
  return __builtin_sinh(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double sinh(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sinhl(__x);
#else
  return __builtin_sinhl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double sinh(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::sinh((double)__x);
#else
  return __builtin_sinh((double)__x);
#endif
}

// tanh

inline _LIBCPP_HIDE_FROM_ABI float tanh(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::tanhf(__x);
#else
  return __builtin_tanhf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double tanh(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::tanh(__x);
#else
  return __builtin_tanh(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double tanh(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::tanhl(__x);
#else
  return __builtin_tanhl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double tanh(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::tanh((double)__x);
#else
  return __builtin_tanh((double)__x);
#endif
}

} // namespace __math

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MATH_HYPERBOLIC_FUNCTIONS_H
