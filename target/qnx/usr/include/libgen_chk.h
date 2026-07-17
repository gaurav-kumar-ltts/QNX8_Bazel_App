/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _LIBGEN_H_INCLUDED
#error <libgen_chk.h> should not be included directly.
#endif

#ifndef _LIBGEN_CHK_H_INCLUDED
#define _LIBGEN_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

#if defined(__EXT_QNX)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_pathfind_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'pathfind_r' is greater than the size of the object "
                "referenced by argument 4");
extern char *__pathfind_r_alias(
        char __const *__path,
        char __const *__name,
        char __const *__mode,
        char         *__buff,
        size_t        __buff_size)
        __ALIASATTR("pathfind_r");
#endif /* #if defined(__EXT_QNX) */


#if __NTO_FORTIFY_LEVEL > 0

#if defined(__EXT_QNX)
extern __FORTIFY_FUNCTION char *pathfind_r(
        char __const   * __const __path,
        char __const   * __const __name,
        char __const   * __const __mode,
        char           * __const __buff,
        size_t __const           __buff_size)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __buff,
            __buff_size,
            1,
            __fortify_fail_overflow_dst_diag_pathfind_r);
    return __pathfind_r_alias(__path, __name, __mode, __buff, __buff_size);
}
#endif /* #if defined(__EXT_QNX) */

#endif /* __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _LIBGEN_CHK_H_INCLUDED */
