/*
 * Copyright (c) 2024, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

/**
 * @file ptp_mod.h
 *
 * @brief These PTP module functions are implemented by the PTP module.
 *
 * Networking drivers use them to handle actions such as transmit (Tx) and
 * receive (Rx) timestamping and handing off PTP I/O-control (@e ioctl())
 * command processing.
 *
 */

#ifndef PTP_MOD_H
#define PTP_MOD_H

#include <io-sock/ptp.h>

/* forward decl. for ptp_if.h */
struct ptp_uhdr;

#include "ptp_if.h"

/**
 * @defgroup mtag_macros Memory buffer tag (m_tag) macros
 *
 * @brief Memory buffer (@c mbuf) tag macros, for use with @e ptp_tstmp_locate().
 * @{
 */
#define MTAG_PTP		1710436530
#define MTAG_PTP_TX_TSTMP	0
#define MTAG_PTP_RX_TSTMP	1
#define MTAG_PTP_TYPE_MIN	MTAG_PTP_TX_TSTMP
#define MTAG_PTP_TYPE_MAX	MTAG_PTP_RX_TSTMP

/** @internal m_tag_alloc allocates space for m_tag and the passed size */
#define MTAG_PTP_SIZE	(sizeof(struct ptp_tstmp_tag) - sizeof(struct m_tag))
/** @} */

/**
 * @brief Comparison macro to check if Tx timestamp initialization
 *        is needed.
 */
#define PTP_TX_TIMESTAMP(_m)	(((_m)->m_flags & M_TSTMP) && \
    (m_tag_locate(_m, MTAG_PTP, MTAG_PTP_TX_TSTMP, NULL) != NULL))

/**
 * @defgroup uhdr_comparisons PTP header comparison macros
 *
 * @brief A set of macros to compare two @c ptp_uhdr structures
 *
 * @details Use these macros if the driver defines a function
 *          for the @e PTP_COMPARE_HEADER() call.
 *
 * @{
 */
#define PTP_UHDR_CMP(_cmp)		{if (!(_cmp)) { return (false); }}
#define PTP_UHDR_CMP_EQ(_member, _u1, _u0)	\
    (PTP_UHDR_CMP((_u1)->_member == (_u0)->_member))

#define PTP_UHDR_PORTNO(_u1, _u0)	\
    PTP_UHDR_CMP_EQ(sourcePortId.portNumber, _u1, _u0)
#define PTP_UHDR_SEQID(_u1, _u0)	\
    PTP_UHDR_CMP_EQ(sequenceId, _u1, _u0)
#define PTP_UHDR_MSGTYPE(_u1, _u0)	\
    PTP_UHDR_CMP_EQ(messageType, _u1, _u0)
#define PTP_UHDR_DOMAIN(_u1, _u0)	\
    PTP_UHDR_CMP_EQ(domain, _u1, _u0)
#define PTP_UHDR_CLOCKID(_u1, _u0)	\
    (PTP_UHDR_CMP(memcmp(&(_u1)->sourcePortId.clockIdentity,\
        &(_u0)->sourcePortId.clockIdentity, PTP_CLOCKID_LEN) == 0))
/** @} */

/** @internal forward decl. for ptp_*() calls */
struct ptp_ctx;
struct mbuf;
struct ifdrv;
struct inpcb;
struct bpf_d;

/**
 * @brief A structure to hold fields that identify a PTP packet
 *
 * @details Derived from the @c ptp_hdr structure in @c ptp.h. These are the
 *          fields used to uniquely identify a PTP packet. Requires no padding
 *          to allow for quick comparison.
 *
 *          For detailed information about the fields, see the IEEE 1588-2019
 *          documentation.
 */
struct ptp_uhdr {
	struct PortIdentity sourcePortId;
	uint16_t sequenceId;
	uint8_t  messageType;
	uint8_t  domain;
};

/* Control functions */

/**
 * @brief Attach device to use @e ptp_*() functions and allocate the context
 *        structure.
 *
 * @details Stores a pointer to @c dev and allocates the PTP context. It also
 * sets up the taskqueue, and mutexes.
 *
 * @param[in]  dev  A driver's @c device_t structure, obtained via @e device_attach().
 * @param[out] ctx  Pointer to return a pointer to the PTP context.
 * @param[in]  name A string that describes the device. Copies up to @c IFNAMSIZ bytes.
 * @param[in]  max  The maximum number of seconds the clock can hold before
 *                  wrapping.
 *
@return EOK on success; otherwise, one of the following:
 *      - @b ENOMEM - Unable to allocate memory for the specified @e ctx.
 */
int ptp_attach(device_t dev, struct ptp_ctx **ctx, const char *name, uint64_t max);

/**
 * @brief Detach and disable the device's PTP context.
 *
 * @details Drain all queues, free mutexes, and free the specified @e ctx. You
 *          cannot use the @e ctx pointer after this.
 *
 * @param[in] ctx A pointer to the PTP context. Cannot be NULL.
 */
void ptp_detach(struct ptp_ctx *ctx);

/**
 * @brief Process @c SIOCGDRVSPEC and @c SIOCSDRVSPEC I/O-control commands
          to service @e ptp_()* commands.
 *
 * @details Handles the copy to or from the @c ifdrv command. Calls
 * to @e PTP_READ_TIME() and @e PTP_WRITE_TIME() are locked with a mutex;
 * calls to @e PTP_WRITE_COMP() and @e PTP_READ_COMP() are not.
 *
 * @param[in]     ctx The driver's PTP context.
 * @param[in,out] ifd The @c ifdrv command structure for @c SIOCGDRVSPEC
 *                    or @c SIOCSDRVSPEC.
 *
 * @return EOK on success; otherwise, one of the following:
 *         - @b EINVAL - For @e PTP_SET_TIME(), the members of the @c
 *                       ptp_time structure are not within the bounds:
 *                       @e nsec value >= 1E9 or @e sec < 0.
 *         - @b EOPNOTSUPP - Unknown command received.
 */
int ptp_ioctl(struct ptp_ctx *ctx, struct ifdrv *ifd);


/* Layer-independent operations */

/**
 * @brief Read the current time from driver and PTP module information
 *
 * @details Use to get the current time as calculated from the driver and
 * the upper seconds bits stored in the PTP module. Calls @e PTP_READ_TIME().
 *
 * @param[in]  ctx      The driver's PTP context.
 * @param[out] ptp_time The current time in the PTP module.
 *
 * @return EOK on success; otherwise, a @e PTP_READ_TIME() error.
 *
 */
int ptp_read_time(struct ptp_ctx *ctx, struct ptp_time *ptp_time);

/**
 * @brief Calculate the current time from the PTP time counter and the driver time
 *
 * @details Gets the current time from the provided driver time. Does
 * not call @e PTP_READ_TIME().
 *
 * @param[in]     ctx      The driver's PTP context.
 * @param[in,out] ptp_time Driver's time on input and PTP time on output.
 */
void ptp_counter_to_realtime(struct ptp_ctx *ctx, struct ptp_time *ptp_time);

/**
 * @brief Return a packet's Tx timestamp
 *
 * @details Used to return a Tx timestamp to the requestor through its associated 
 * @c mbuf, which contains the packet that was timestamped. This @c mbuf @b MUST
 * be the packet header, and contain @c MTAG_PTP_TX_TSTMP in its tags.
 *
 * @param[in] ctx      The driver's PTP context.
 * @param[in] m        The @c mbuf containing the packet.
 * @param[in] ptp_time The timestamp returned by the driver.
 *
 * @return EOK on success, !EOK otherwise.
 */
int ptp_txfinish(struct ptp_ctx *ctx, struct mbuf *m, struct ptp_time *ptp_time);

/**
 * @brief Return a packet's receive (Rx) timestamp
 *
 * @details Used to return an Rx timestamp to the stack. It adds the timestamp
 * to the memory buffer's @e rcv_tstmp field, and a @c MTAG_PTP_RX_TSTMP tag
 * to the packet's tags.
 *
 * @param[in] ctx      The driver's PTP context.
 * @param[in] m        The @c mbuf containing the packet.
 * @param[in] ptp_time The timestamp returned by the driver.
 *
 * @return EOK on success; otherwise, one of the following:
 *         - @b ENOMEM - Unable to allocate memory for the @c MTAG_PTP_RX_TSTMP tag.
 */
int ptp_rx(struct ptp_ctx *ctx, struct mbuf *m, struct ptp_time *ptp_time);

/**
 * @brief Return a pointer to a memory buffer tag's @c ptp_tstmp structure
 *
 * @details Searches the memory buffer's tags for the given tag type, and returns a
 * pointer to its @c ptp_tstmp structure.
 *
 * @param[in] m    The @c mbuf containing the packet.
 * @param[in] type One of the @c MTAG_PTP_*_TSTMP memory buffer tag types
                   (for values, go to @ref mtag_macros).
 *
 * @return Pointer to a @c ptp_tstmp on success; otherwise, one of the following:
 * *       - @b NULL - Unable to find a tag of the given type in the @c mbuf.
 */
struct ptp_tstmp *ptp_tstmp_locate(struct mbuf *m, uint16_t type);

/**
 * @brief Return a packet's Tx timestamp without associating it with
 *        a memory buffer (@c mbuf)
 *
 * @details The @e ptp_txintr() function unlinks the @c MTAG_PTP_TX_TSTMP tag
 * from the @c mbuf and adds it to a queue. It also copies the @c ptp_uhdr attributes
 * from the PTP packet header @c ptp_hdr to allow the @c m_tag to be found later.
 * These attributes are compared later using a call to @e PTP_COMPARE_HDR(), if
 * @e ptp_txintr_finish() is used.
 *
 * @param[in] ctx  The driver's PTP context.
 * @param[in] m    The @c mbuf containing the packet.
 *
 * @return EOK on success; otherwise, one of the following:
 *         - @b EINVAL - The @c mbuf provided does not contain a PTP packet.
 *         - @b ENOMEM - Unable to allocate space for the header.
 */
int ptp_txintr(struct ptp_ctx *ctx, struct mbuf *m);

/**
 * @brief Return a packet's Tx timestamp when the timestamp has been received
 *
 * @details The @e ptp_txintr_finish() function loops through the queue of tags and
 * compares the header for each to the given header. When it finds a match, it takes
 * the same action as @e ptp_txfinish().
 *
 * @param[in] ctx      The driver's PTP context.
 * @param[in] hdr      The @c ptp_uhdr filled with the data to compare.
 * @param[in] ptp_time The timestamp returned by the driver.
 *
 * @return EOK on success; otherwise, one of the following:
 *         - @b ENOENT - No matching tag found.
 *         - @b ETIMEDOUT - The matching tag has expired.
 */
int ptp_txintr_finish(struct ptp_ctx *ctx, struct ptp_uhdr *hdr,
    struct ptp_time *ptp_time);


/**
 * @brief Return a packet's Tx timestamp when the timestamp has been received
 *
 * @details The @e ptp_txintr_finish_head() function takes the same action as
 * @e ptp_txintr_finish(), except instead of comparing the header, it associates
 * the timestamp with the first available tag.
 *
 * @param[in] ctx      The driver's PTP context.
 * @param[in] ptp_time The timestamp returned by the driver.
 *
 * @return EOK on success; otherwise, one of the following:
 *         - @b ENOENT - No available tag found.
 */
int ptp_txintr_finish_head(struct ptp_ctx *ctx, struct ptp_time *ptp_time);


/* Utility functions */

/**
 * @brief Returns a pointer to a PTP header in a memory buffer
 *
 * @details Currently supports IPv4 and L2. Packet is assumed to be in one
 * @c mbuf (i.e., no @c m_next).
 *
 * @param[in] m The @c mbuf containing the packet. The M_PKTHDR flag must be set.
 *
 * @return If successful, returns a pointer to the PTP header in an @c mbuf;
 *         otherwise, one of the following:
 *         - @b NULL - Invalid type or length in the provided @c mbuf.
 */
struct ptp_hdr *ptp_mbuf2hdr(struct mbuf *m);

/**
 * @brief Copy header information retrieved from the memory buffer to a PTP header
 *
 * @details The information copied from the header is converted to the host byte order.
 *
 * @param[in]  hdr  Header returned from @e ptp_mbuf2hdr().
 * @param[out] uhdr Structure to fill with information from @c hdr.
 */
void ptp_hdr2uhdr(struct ptp_hdr *hdr, struct ptp_uhdr *uhdr);


/* Layer-specific operations */

/* These functions are used solely by io-sock */
int ptp_udp_tx(struct inpcb *, struct mbuf *, uint32_t *);
int ptp_ether_tx(struct bpf_d *, struct mbuf *, uint32_t *);

#endif /* PTP_MOD_H */
