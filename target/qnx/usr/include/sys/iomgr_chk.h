/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef __IOMGR_H_INCLUDED
#error <sys/iomgr_chk.h> should not be included directly.
#endif

#ifndef __IOMGR_CHK_H_INCLUDED
#define __IOMGR_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_iofdinfo,
        __fortify_fail_overflow_dst,
        "argument 5 of 'iofdinfo' is greater than the size of the object "
                "referenced by argument 4");
extern int __iofdinfo_alias(
        int             __fd,
        unsigned        __flags,
        struct _fdinfo *__info,
        char           *__path,
        int             __maxlen) __ALIASATTR("iofdinfo");


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION int iofdinfo(
        int const              __fd,
        unsigned const         __flags,
        struct _fdinfo * const __info,
        char           * const __path,
        int const              __maxlen)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __path,
            (unsigned int)__maxlen,
            1,
            __fortify_fail_overflow_dst_diag_iofdinfo);
    return __iofdinfo_alias(__fd, __flags, __info, __path, __maxlen);
}

#endif /* __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef __IOMGR_CHK_H_INCLUDED */
