/*
 * Copyright (c) 2024, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef PTP_H
#define PTP_H

#include <stdint.h>

/**
 * @defgroup ptp_ioctls PTP driver ioctls
 *
 * @brief @c ioctl() commands for use with @c SIOCGDRVSPEC and @c SIOCSDRVSPEC
 * @{
*/
#define PTP_GET_TIME		0x102
#define PTP_SET_TIME		0x103
#define PTP_SET_COMPENSATION	0x104
#define PTP_GET_COMPENSATION	0x105
/** @}*/

/**
 * @brief Structure used with the @c PTP_[G/S]ET_TIME commands,
 * as well as to represent the time in the ptp clock.
 */
struct ptp_time {
	/** The number of seconds in ptp time */
	int64_t	sec;
	/** The number of nanoseconds in ptp time. Cannot exceed or equal 1E9 */
	int32_t	nsec;
};

/**
 * @brief Represents a packet's TX/RX timestamp. Used on packet receive
 */
struct ptp_tstmp {
	/** Time the timestamp was taken */
	struct ptp_time	time;
	/** Per-driver unique id to differentiate timestamps */
	uint32_t	uid;
};

/**
 * @brief Structure used with the @c PTP_[G/S]ET_COMPENSATION commands.
 */
struct ptp_comp {
	/** compensation addend value in nanoseconds */
	uint32_t	comp;
	/** positive or negative compensation. 1 is positive, 0 is negative */
	unsigned char	positive;
};


/**
 * @defgroup ptp_specification PTP specification definitions
 *
 * @brief For more information on these structures,
 * please read IEEE Std 1588-2019.
 */

/**
 * @ingroup ptp_specification
 *
 * @brief UDP port for PTP event messages
 */
#define PTP_PORT_EVENT		319

/**
 * @ingroup ptp_ports
 *
 * @brief UDP port for PTP general messages
 */
#define PTP_PORT_GENERAL	320

/**
 * @ingroup ptp_specification
 *
 * @brief PTP header message types
 *
 * @details Table 36 from IEEE Std 1588-2019
 */
enum PTP_MSG {
	PTP_SYNC = 0x0,
	PTP_DELAY_REQ,
	PTP_PDELAY_REQ,
	PTP_PDELAY_RESP,
	/* 0x4 - 0x7 reserved */
	PTP_FOLLOW_UP = 0x8,
	PTP_DELAY_RESP,
	PTP_PDELAY_RESP_FOLLOW_UP,
	PTP_ANNOUNCE,
	PTP_SIGNALING,
	PTP_MANAGEMENT
	/* 0xE - 0xF reserved */
};

/**
 * @ingroup ptp_specification
 *
 * @brief Number of octets in @c ClockIdentity
 *
 * @details 5.3.4 from IEEE Std 1588-2019
 */
#define PTP_CLOCKID_LEN	8U

/**
 * @ingroup ptp_specification
 *
 * @brief PortIdentity struct
 *
 * @details 5.3.5 from IEEE Std 1588-2019
 */
struct PortIdentity {
	uint8_t  clockIdentity[PTP_CLOCKID_LEN];
	uint16_t portNumber;
} __attribute((packed));

/**
 * @ingroup ptp_specification
 *
 * @brief PTP message header struct
 *
 * @details 13.3.1 from IEEE Std 1588-2019
*/
struct ptp_hdr {
	uint8_t  messageType : 4;
	uint8_t  majorSdoId : 4;
	uint8_t  versionPTP : 4;
	uint8_t  minorVersionPTP : 4;
	uint16_t messageLength;
	uint8_t  domainNumber;
	uint8_t  minorSdoId;
	uint16_t flagField;
	int64_t  correctionField;
	uint32_t messageTypeSpecific;
	struct PortIdentity
	    sourcePortIdentity;
	uint16_t sequenceId;
	uint8_t  controlField;
	uint8_t  logMessageInterval;
} __attribute((packed));

#endif /* PTP_H */
