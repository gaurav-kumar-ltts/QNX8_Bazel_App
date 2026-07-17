/*
 * $QNXLicenseC:
 * Copyright 2023, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef __INTERRUPTS_H_INCLUDED
#define __INTERRUPTS_H_INCLUDED

#include <stdint.h>

// InterruptQuery() specifiers. Each specifier determines how the `id` and `aux`
// parameters will be interpreted.
#define _NTO_INTR_QUERY_HANDLER     0x00000000U
#define _NTO_INTR_QUERY_SOURCE      0x00000001U

/**
 * Information that can be retrieved by a call to InterruptQuery().
 */
struct interrupt_query_data {
    /**
     * Indicate what type of data this answer contains. This will be one of the
     * `_NTO_INTR_QUERY_*` values.
     */
    uint32_t type;

    /**
     * The interrupt vector that was queried.
     */
    uint32_t vector;

    /**
     * The timestamp in clock cycles of the last delivery of this interrupt.
     */
    uint64_t deliver_time;

    /**
     *  The total number of occurences of this interrupt.
     */
    uint64_t deliver_count;

    union {
        struct {
            /**
             * The flags provided by startup for this interrupt source.
             */
            uint16_t startup_flags;

            /**
             * The config provided by startup for this interrupt source.
             */
            uint16_t startup_config;

            /**
             * The number of ISTs attached to this interrupt.
             */
            uint32_t num_handlers;

            /**
             * The current mask count of this interrupt source.
             */
            uint32_t mask_count;

            /**
             * Controller-specific flags.
             */
            uint32_t flags;

            /**
             * Controller-specific destination this interrupt is routed to.
             */
            uint64_t route;
        } source;

        struct {
            /**
             * The process ID of the IST.
             */
            pid_t ist_pid;

            /**
             * The thread ID of the IST.
             */
            pthread_t ist_tid;

            /**
             * The runmask of the IST.
             */
            uint64_t ist_runmask;

            /**
             * The ID associated with this handler by its call to
             * InterruptAttach*().
             */
            int32_t attach_id;

            /**
             * The _NTO_INTR_FLAGS_* as recorded by InterruptAttach*().
             */
            uint32_t attach_flags;

            /**
             * The mask count of the handler.
             */
            uint32_t mask_count;

            /**
             * A copy of the sigevent provided to InterruptAttachEvent().
             */
            struct sigevent event;
        } handler;
    } data;
};

#endif /* __INTERRUPTS_H_INCLUDED */
