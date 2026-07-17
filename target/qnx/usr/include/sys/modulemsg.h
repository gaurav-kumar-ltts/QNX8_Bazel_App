/*
 * Copyright (c) 2025, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef __MODULEMSG_H_INCLUDED
#define __MODULEMSG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __SYSMSG_H_INCLUDED
#include _NTO_HDR_(sys/sysmsg.h)
#endif

#include <stdbool.h>
#include <module/errata.h>

typedef enum {
    MODULEMSG_ERRATA = _MODULEMSG_BASE,

    _MODULEMSG_END
} modulemsg_types_t;
_Static_assert((_MODULEMSG_END - 1) <= _MODULEMSG_MAX, "Module message types exceed allowed range");

typedef enum {
    MODULEMSG_ERRATA_CPUINFO
} modulemsg_errata_subtypes_t;

typedef struct {
    _Uint16t type;
    _Uint16t subtype;
} modulemsg_header_t;

typedef struct {
    modulemsg_header_t header;
    _Uint32t cpu_num;
    module_errata_identifier_t errata_id;
} modulemsg_errata_cpuinfo_t;

#endif /* __MODULEMSG_H_INCLUDED */
