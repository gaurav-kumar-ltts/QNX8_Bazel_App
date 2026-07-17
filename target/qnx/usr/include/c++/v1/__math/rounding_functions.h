//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MATH_ROUNDING_FUNCTIONS_H
#define _LIBCPP___MATH_ROUNDING_FUNCTIONS_H

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

// ceil

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI float ceil(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::ceilf(__x);
#else
  return __builtin_ceilf(__x);
#endif
}

template <class = int>
_LIBCPP_NODISCARD_EXT _LIBCPP_HIDE_FROM_ABI double ceil(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::ceil(__x);
#else
  return __builtin_ceil(__x);
#endif
}

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI long double ceil(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::ceill(__x);
#else
  return __builtin_ceill(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI double ceil(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::ceil((double)__x);
#else
  return __builtin_ceil((double)__x);
#endif
}

// floor

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI float floor(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::floorf(__x);
#else
  return __builtin_floorf(__x);
#endif
}

template <class = int>
_LIBCPP_NODISCARD_EXT _LIBCPP_HIDE_FROM_ABI double floor(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::floor(__x);
#else
  return __builtin_floor(__x);
#endif
}

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI long double floor(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::floorl(__x);
#else
  return __builtin_floorl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI double floor(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::floor((double)__x);
#else
  return __builtin_floor((double)__x);
#endif
}

// llrint

inline _LIBCPP_HIDE_FROM_ABI long long llrint(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::llrintf(__x);
#else
  return __builtin_llrintf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI long long llrint(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::llrint(__x);
#else
  return __builtin_llrint(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long long llrint(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::llrintl(__x);
#else
  return __builtin_llrintl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI long long llrint(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::llrint((double)__x);
#else
  return __builtin_llrint((double)__x);
#endif
}

// llround

inline _LIBCPP_HIDE_FROM_ABI long long llround(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::llroundf(__x);
#else
  return __builtin_llroundf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI long long llround(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::llround(__x);
#else
  return __builtin_llround(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long long llround(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::llroundl(__x);
#else
  return __builtin_llroundl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI long long llround(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::llround((double)__x);
#else
  return __builtin_llround((double)__x);
#endif
}

// lrint

inline _LIBCPP_HIDE_FROM_ABI long lrint(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::lrintf(__x);
#else
  return __builtin_lrintf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI long lrint(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::lrint(__x);
#else
  return __builtin_lrint(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long lrint(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::lrintl(__x);
#else
  return __builtin_lrintl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI long lrint(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::lrint((double)__x);
#else
  return __builtin_lrint((double)__x);
#endif
}

// lround

inline _LIBCPP_HIDE_FROM_ABI long lround(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::lroundf(__x);
#else
  return __builtin_lroundf(__x);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI long lround(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::lround(__x);
#else
  return __builtin_lround(__x);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long lround(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::lroundl(__x);
#else
  return __builtin_lroundl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI long lround(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::lround((double)__x);
#else
  return __builtin_lround((double)__x);
#endif
}

// nearbyint

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI float nearbyint(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nearbyintf(__x);
#else
  return __builtin_nearbyintf(__x);
#endif
}

template <class = int>
_LIBCPP_NODISCARD_EXT _LIBCPP_HIDE_FROM_ABI double nearbyint(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nearbyint(__x);
#else
  return __builtin_nearbyint(__x);
#endif
}

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI long double nearbyint(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nearbyintl(__x);
#else
  return __builtin_nearbyintl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI double nearbyint(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nearbyint((double)__x);
#else
  return __builtin_nearbyint((double)__x);
#endif
}

// nextafter

inline _LIBCPP_HIDE_FROM_ABI float nextafter(float __x, float __y) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nextafterf(__x, __y);
#else
  return __builtin_nextafterf(__x, __y);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double nextafter(double __x, double __y) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nextafter(__x, __y);
#else
  return __builtin_nextafter(__x, __y);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double nextafter(long double __x, long double __y) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nextafterl(__x, __y);
#else
  return __builtin_nextafterl(__x, __y);
#endif
}

template <class _A1, class _A2, __enable_if_t<is_arithmetic<_A1>::value && is_arithmetic<_A2>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI typename __promote<_A1, _A2>::type nextafter(_A1 __x, _A2 __y) _NOEXCEPT {
  using __result_type = typename __promote<_A1, _A2>::type;
  static_assert((!(_IsSame<_A1, __result_type>::value && _IsSame<_A2, __result_type>::value)), "");
  return __math::nextafter((__result_type)__x, (__result_type)__y);
}

// nexttoward

inline _LIBCPP_HIDE_FROM_ABI float nexttoward(float __x, long double __y) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nexttowardf(__x, __y);
#else
  return __builtin_nexttowardf(__x, __y);
#endif
}

template <class = int>
_LIBCPP_HIDE_FROM_ABI double nexttoward(double __x, long double __y) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nexttoward(__x, __y);
#else
  return __builtin_nexttoward(__x, __y);
#endif
}

inline _LIBCPP_HIDE_FROM_ABI long double nexttoward(long double __x, long double __y) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nexttowardl(__x, __y);
#else
  return __builtin_nexttowardl(__x, __y);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
inline _LIBCPP_HIDE_FROM_ABI double nexttoward(_A1 __x, long double __y) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::nexttoward((double)__x, __y);
#else
  return __builtin_nexttoward((double)__x, __y);
#endif
}

// rint

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI float rint(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::rintf(__x);
#else
  return __builtin_rintf(__x);
#endif
}

template <class = int>
_LIBCPP_NODISCARD_EXT _LIBCPP_HIDE_FROM_ABI double rint(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::rint(__x);
#else
  return __builtin_rint(__x);
#endif
}

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI long double rint(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::rintl(__x);
#else
  return __builtin_rintl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI double rint(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::rint((double)__x);
#else
  return __builtin_rint((double)__x);
#endif
}

// round

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI float round(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::round(__x);
#else
  return __builtin_round(__x);
#endif
}

template <class = int>
_LIBCPP_NODISCARD_EXT _LIBCPP_HIDE_FROM_ABI double round(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::round(__x);
#else
  return __builtin_round(__x);
#endif
}

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI long double round(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::roundl(__x);
#else
  return __builtin_roundl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI double round(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::round((double)__x);
#else
  return __builtin_round((double)__x);
#endif
}

// trunc

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI float trunc(float __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::truncf(__x);
#else
  return __builtin_trunc(__x);
#endif
}

template <class = int>
_LIBCPP_NODISCARD_EXT _LIBCPP_HIDE_FROM_ABI double trunc(double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::trunc(__x);
#else
  return __builtin_trunc(__x);
#endif
}

_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI long double trunc(long double __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::truncl(__x);
#else
  return __builtin_truncl(__x);
#endif
}

template <class _A1, __enable_if_t<is_integral<_A1>::value, int> = 0>
_LIBCPP_NODISCARD_EXT inline _LIBCPP_HIDE_FROM_ABI double trunc(_A1 __x) _NOEXCEPT {
#if defined(__QNX__) && !defined(QNX_LIBM_BUILTINS)
  return ::trunc((double)__x);
#else
  return __builtin_trunc((double)__x);
#endif
}

} // namespace __math

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MATH_ROUNDING_FUNCTIONS_H
