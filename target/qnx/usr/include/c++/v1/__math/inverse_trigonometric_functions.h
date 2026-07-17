//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MATH_INVERSE_TRIGONOMETRIC_FUNCTIONS_H
#define _LIBCPP___MATH_INVERSE_TRIGONOMETRIC_FUNCTIONS_H

#include <__config>
#include <__type_traits/enable_if.h>
#include <__type_traits/is_arithmetic.h>
#include <__type_traits/is_integral.h>
#include <__type_traits/is_same.h>
#include <__type_traits/promote.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __math {

// acos

inline _LIBCPP_HIDE_FROM_ABI float acos(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::acosf(__x);
#else
  return __builtin_acosf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double acos(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::acos(__x);
#else
  return __builtin_acos(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double acos(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::acosl(__x);
#else
  return __builtin_acosl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double acos(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::acos((double)__x);
#else
  return __builtin_acos((double)__x);
#endif
}

// asin

inline _LIBCPP_HIDE_FROM_ABI float asin(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::asinf(__x);
#else
  return __builtin_asinf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double asin(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::asin(__x);
#else
  return __builtin_asin(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double asin(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::asinl(__x);
#else
  return __builtin_asinl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double asin(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::asin((double)__x);
#else
  return __builtin_asin((double)__x);
#endif
}

// atan

inline _LIBCPP_HIDE_FROM_ABI float atan(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::atanf(__x);
#else
  return __builtin_atanf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double atan(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::atan(__x);
#else
  return __builtin_atan(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double atan(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::atanl(__x);
#else
  return __builtin_atanl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double atan(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::atan((double)__x);
#else
  return __builtin_atan((double)__x);
#endif
}

// atan2

inline _LIBCPP_HIDE_FROM_ABI float atan2(float __y, float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::atan2f(__y, __x);
#else
  return __builtin_atan2f(__y, __x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double atan2(double __x, double __y) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::atan2(__x, __y);
#else
  return __builtin_atan2(__x, __y);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double atan2(long double __y, long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::atan2l(__y, __x);
#else
  return __builtin_atan2l(__y, __x);
#endif
}

template <class _A1, class _A2, __enable_if_t<is_arithmetic<_A1>::value && is_arithmetic<_A2>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI typename __promote<_A1, _A2>::type atan2(_A1 __y, _A2 __x) _NOEXCEPT {
  using __result_type = typename __promote<_A1, _A2>::type;
  static_assert((!(_IsSame<_A1, __result_type>::value && _IsSame<_A2, __result_type>::value)), "");
  return __math::atan2((__result_type)__y, (__result_type)__x);
}

} // namespace __math

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MATH_INVERSE_TRIGONOMETRIC_FUNCTIONS_H
