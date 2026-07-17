/*
 * $QNXLicenseC:
 * Copyright 2018, QNX Software Systems. All Rights Reserved.
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

/* $FreeBSD$ */
/*-
 * Copyright (c) 2008 Hans Petter Selasky. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Including this file is mandatory for all USB related c-files in the kernel.
 */

#ifndef _USB_QNX_H_
#define	_USB_QNX_H_

/* Default USB configuration */
#define	USB_HAVE_DEVCTL 1
#define	USB_HAVE_COMPAT_LINUX 1
#define	USB_HAVE_USER_IO 0
#define	USB_HAVE_MBUF 1
#define	USB_HAVE_PF 1
#define	USB_HAVE_ID_SECTION 1
#define	USB_HAVE_PER_BUS_PROCESS 1
#define	USB_HAVE_FIXED_CONFIG 0
#define	USB_HAVE_FIXED_PORT 0
#define	USB_HAVE_DISABLE_ENUM 1

/* define zero ticks callout value */
#define	USB_CALLOUT_ZERO_TICKS 1

#define	USB_TD_GET_PROC(td) (td)->td_proc
#define	USB_PROC_GET_GID(td) (td)->p_pgid

#if (!defined(USB_HOST_ALIGN)) || (USB_HOST_ALIGN <= 0)
/* Use default value. */
#undef USB_HOST_ALIGN
#if defined(__arm__) || defined(__mips__) || defined(__powerpc__)
#define USB_HOST_ALIGN	32		/* Arm and MIPS need at least this much, if not more */
#else
#define	USB_HOST_ALIGN    8		/* bytes, must be power of two */
#endif
#endif
/* Sanity check for USB_HOST_ALIGN: Verify power of two. */
#if ((-USB_HOST_ALIGN) & USB_HOST_ALIGN) != USB_HOST_ALIGN
#error "USB_HOST_ALIGN is not power of two."
#endif
#define	USB_FS_ISOC_UFRAME_MAX 4	/* exclusive unit */
#define	USB_BUS_MAX 256			/* units */
#define	USB_CONFIG_MAX 65535		/* bytes */
#define	USB_IFACE_MAX 32		/* units */
#define	USB_FIFO_MAX 128		/* units */
#define	USB_MAX_EP_STREAMS 8		/* units */
#define	USB_MAX_EP_UNITS 32		/* units */
#define	USB_MAX_PORTS 255		/* units */

#define	USB_MAX_FS_ISOC_FRAMES_PER_XFER (120)	/* units */
#define	USB_MAX_HS_ISOC_FRAMES_PER_XFER (8*120)	/* units */

#define	USB_HUB_MAX_DEPTH	5
#define	USB_EP0_BUFSIZE		1024	/* bytes */
#define	USB_CS_RESET_LIMIT	20	/* failures = 20 * 50 ms = 1sec */

#define	USB_MAX_AUTO_QUIRK	8	/* maximum number of dynamic quirks */

#define	USB_IN_POLLING_MODE_FUNC() usbd_in_polling_mode()
#define	USB_IN_POLLING_MODE_VALUE() (SCHEDULER_STOPPED())

typedef uint32_t usb_timeout_t;		/* milliseconds */
typedef uint32_t usb_frlength_t;	/* bytes */
typedef uint32_t usb_frcount_t;		/* units */
typedef uint32_t usb_size_t;		/* bytes */
typedef uint32_t usb_ticks_t;		/* system defined */
typedef uint16_t usb_stream_t;		/* stream ID */

#endif	/* _USB_QNX_H_ */
