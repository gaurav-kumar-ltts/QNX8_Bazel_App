// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
/*
 * Copyright 2019-2023,2025 BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _LIBCPP_SUPPORT_NTO_XLOCALE_H
#define _LIBCPP_SUPPORT_NTO_XLOCALE_H

#if defined(__QNX__)

#include <locale.h>
#include <string.h>
#include <wchar.h>

extern "C" {

struct locale_s;
typedef struct locale_s* locale_t;

// Forward-declare certain non-C-standard libc functions so `<locale>` will compile
// successfully with `-std=...`
extern int vasprintf(char **__strp, const char *__fmt, __NTO_va_list __arg) __attribute__((__format__(__printf__, 2, 0)));
extern int isascii(int);

#define LC_COLLATE_MASK  _M_COLLATE
#define LC_CTYPE_MASK    _M_CTYPE
#define LC_MONETARY_MASK _M_MONETARY
#define LC_NUMERIC_MASK  _M_NUMERIC
#define LC_TIME_MASK     _M_TIME
#define LC_MESSAGES_MASK _M_MESSAGES
#define LC_ALL_MASK      _M_ALL

extern const locale_t LC_GLOBAL_LOCALE;

_LIBCPP_WEAK locale_t _QNX_newlocale(int, const char *name, locale_t);
_LIBCPP_WEAK locale_t _QNX_uselocale(locale_t loc);
_LIBCPP_WEAK void     _QNX_freelocale(locale_t);

static inline locale_t newlocale(int __i, const char *__name, locale_t __loc) {
    if (_QNX_newlocale)
        return _QNX_newlocale(__i, __name, __loc);
    return NULL;
}

static inline locale_t uselocale(locale_t __loc) {
    if (_QNX_uselocale)
        return _QNX_uselocale(__loc);
    return NULL;
}

static inline void freelocale(locale_t __loc) {
    if (_QNX_freelocale)
        _QNX_freelocale(__loc);
}

_LIBCPP_HIDDEN size_t mbsnrtowcs(wchar_t *dst, const char **src, size_t nmc, size_t nwc, mbstate_t *ps);
_LIBCPP_HIDDEN size_t wcsnrtombs(char *dst, const wchar_t **src, size_t nwc, size_t nmc, mbstate_t *ps);
}

#include <__support/xlocale/__posix_l_fallback.h>
#include <__support/xlocale/__strtonum_fallback.h>

#endif // defined(__QNX__)
#endif // _LIBCPP_SUPPORT_NTO_XLOCALE_H

