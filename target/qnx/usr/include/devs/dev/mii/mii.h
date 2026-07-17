/*	$NetBSD: mii.h,v 1.18 2014/06/16 14:43:22 msaitoh Exp $	*/

/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 1997 Manuel Bouyer.  All rights reserved.
 *
 * Modification to match BSD/OS 3.0 MII interface by Jason R. Thorpe,
 * Numerical Aerospace Simulation Facility, NASA Ames Research Center.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _DEV_MII_MII_H_
#define	_DEV_MII_MII_H_

/*
 * Registers common to all PHYs.
 */

#define	MII_NPHY	32	/* max # of PHYs per MII */

/*
 * MII commands, used if a device must drive the MII lines
 * manually.
 */
#define	MII_COMMAND_START	0x01
#define	MII_COMMAND_READ	0x02
#define	MII_COMMAND_WRITE	0x01
#define	MII_COMMAND_ACK		0x02

#define	MII_BMCR	0x00	/* Basic mode control register (rw) */
#define	BMCR_RESET	0x8000	/* reset */
#define	BMCR_LOOP	0x4000	/* loopback */
#define	BMCR_SPEED0	0x2000	/* speed selection (LSB) */
#define	BMCR_AUTOEN	0x1000	/* autonegotiation enable */
#define	BMCR_PDOWN	0x0800	/* power down */
#define	BMCR_ISO	0x0400	/* isolate */
#define	BMCR_STARTNEG	0x0200	/* restart autonegotiation */
#define	BMCR_FDX	0x0100	/* Set duplex mode */
#define	BMCR_CTEST	0x0080	/* collision test */
#define	BMCR_SPEED1	0x0040	/* speed selection (MSB) */

#define	BMCR_S10	0x0000		/* 10 Mb/s */
#define	BMCR_S100	BMCR_SPEED0	/* 100 Mb/s */
#define	BMCR_S1000	BMCR_SPEED1	/* 1000 Mb/s */

#define	BMCR_SPEED(x)	((x) & (BMCR_SPEED0|BMCR_SPEED1))

#define	MII_BMSR	0x01	/* Basic mode status register (ro) */
#define	BMSR_100T4	0x8000	/* 100 base T4 capable */
#define	BMSR_100TXFDX	0x4000	/* 100 base Tx full duplex capable */
#define	BMSR_100TXHDX	0x2000	/* 100 base Tx half duplex capable */
#define	BMSR_10TFDX	0x1000	/* 10 base T full duplex capable */
#define	BMSR_10THDX	0x0800	/* 10 base T half duplex capable */
#define	BMSR_100T2FDX	0x0400	/* 100 base T2 full duplex capable */
#define	BMSR_100T2HDX	0x0200	/* 100 base T2 half duplex capable */
#define	BMSR_EXTSTAT	0x0100	/* Extended status in register 15 */
#define	BMSR_MFPS	0x0040	/* MII Frame Preamble Suppression */
#define	BMSR_ACOMP	0x0020	/* Autonegotiation complete */
#define	BMSR_RFAULT	0x0010	/* Link partner fault */
#define	BMSR_ANEG	0x0008	/* Autonegotiation capable */
#define	BMSR_LINK	0x0004	/* Link status */
#define	BMSR_JABBER	0x0002	/* Jabber detected */
#define	BMSR_EXTCAP	0x0001	/* Extended capability */

#define	BMSR_DEFCAPMASK	0xffffffff

/*
 * Note that the EXTSTAT bit indicates that there is extended status
 * info available in register 15, but 802.3 section 22.2.4.3 also
 * states that all 1000 Mb/s capable PHYs will set this bit to 1.
 */

#define	BMSR_MEDIAMASK	(BMSR_100T4|BMSR_100TXFDX|BMSR_100TXHDX| \
		BMSR_10TFDX|BMSR_10THDX|BMSR_100T2FDX|BMSR_100T2HDX)

/*
 * Convert BMSR media capabilities to ANAR bits for autonegotiation.
 * Note the shift chopps off the BMSR_ANEG bit.
 */
#define	BMSR_MEDIA_TO_ANAR(x)	(((x) & BMSR_MEDIAMASK) >> 6)

#define	MII_PHYIDR1	0x02	/* ID register 1 (ro) */

#define	MII_PHYIDR2	0x03	/* ID register 2 (ro) */
#define	IDR2_OUILSB	0xfc00	/* OUI LSB */
#define	IDR2_MODEL	0x03f0	/* vendor model */
#define	IDR2_REV	0x000f	/* vendor revision */

#define	MII_ANAR	0x04	/* Autonegotiation advertisement (rw) */
		/* section 28.2.4.1 and 37.2.6.1 */
#define ANAR_NP		0x8000	/* Next page (ro) */
#define	ANAR_ACK	0x4000	/* link partner abilities acknowledged (ro) */
#define ANAR_RF		0x2000	/* remote fault (ro) */
		/* Annex 28B.2 */
#define	ANAR_FC		0x0400	/* local device supports PAUSE */
#define ANAR_T4		0x0200	/* local device supports 100bT4 */
#define ANAR_TX_FD	0x0100	/* local device supports 100bTx FD */
#define ANAR_TX		0x0080	/* local device supports 100bTx */
#define ANAR_10_FD	0x0040	/* local device supports 10bT FD */
#define ANAR_10		0x0020	/* local device supports 10bT */
#define	ANAR_CSMA	0x0001	/* protocol selector CSMA/CD */
#define	ANAR_PAUSE_NONE		(0 << 10)
#define	ANAR_PAUSE_SYM		(1 << 10)
#define	ANAR_PAUSE_ASYM		(2 << 10)
#define	ANAR_PAUSE_TOWARDS	(3 << 10)

		/* Annex 28D */
#define	ANAR_X_FD	0x0020	/* local device supports 1000BASE-X FD */
#define	ANAR_X_HD	0x0040	/* local device supports 1000BASE-X HD */
#define	ANAR_X_PAUSE_NONE	(0 << 7)
#define	ANAR_X_PAUSE_SYM	(1 << 7)
#define	ANAR_X_PAUSE_ASYM	(2 << 7)
#define	ANAR_X_PAUSE_TOWARDS	(3 << 7)

#define	MII_ANLPAR	0x05	/* Autonegotiation lnk partner abilities (rw) */
		/* section 28.2.4.1 and 37.2.6.1 */
#define ANLPAR_NP	0x8000	/* Next page (ro) */
#define	ANLPAR_ACK	0x4000	/* link partner accepted ACK (ro) */
#define ANLPAR_RF	0x2000	/* remote fault (ro) */
#define	ANLPAR_FC	0x0400	/* link partner supports PAUSE */
#define ANLPAR_T4	0x0200	/* link partner supports 100bT4 */
#define ANLPAR_TX_FD	0x0100	/* link partner supports 100bTx FD */
#define ANLPAR_TX	0x0080	/* link partner supports 100bTx */
#define ANLPAR_10_FD	0x0040	/* link partner supports 10bT FD */
#define ANLPAR_10	0x0020	/* link partner supports 10bT */
#define	ANLPAR_CSMA	0x0001	/* protocol selector CSMA/CD */
#define	ANLPAR_PAUSE_MASK	(3 << 10)
#define	ANLPAR_PAUSE_NONE	(0 << 10)
#define	ANLPAR_PAUSE_SYM	(1 << 10)
#define	ANLPAR_PAUSE_ASYM	(2 << 10)
#define	ANLPAR_PAUSE_TOWARDS	(3 << 10)

#define	ANLPAR_X_FD	0x0020	/* local device supports 1000BASE-X FD */
#define	ANLPAR_X_HD	0x0040	/* local device supports 1000BASE-X HD */
#define	ANLPAR_X_PAUSE_MASK	(3 << 7)
#define	ANLPAR_X_PAUSE_NONE	(0 << 7)
#define	ANLPAR_X_PAUSE_SYM	(1 << 7)
#define	ANLPAR_X_PAUSE_ASYM	(2 << 7)
#define	ANLPAR_X_PAUSE_TOWARDS	(3 << 7)

#define	MII_ANER	0x06	/* Autonegotiation expansion (ro) */
		/* section 28.2.4.1 and 37.2.6.1 */
#define ANER_MLF	0x0010	/* multiple link detection fault */
#define ANER_LPNP	0x0008	/* link parter next page-able */
#define ANER_NP		0x0004	/* next page-able */
#define ANER_PAGE_RX	0x0002	/* Page received */
#define ANER_LPAN	0x0001	/* link parter autoneg-able */

#define	MII_ANNP	0x07	/* Autonegotiation next page */
		/* section 28.2.4.1 and 37.2.6.1 */

#define	MII_ANLPRNP	0x08	/* Autonegotiation link partner rx next page */
		/* section 32.5.1 and 37.2.6.1 */

			/* This is also the 1000baseT control register */
#define	MII_100T2CR	0x09	/* 100base-T2 control register */
#define	GTCR_TEST_MASK	0xe000	/* see 802.3ab ss. 40.6.1.1.2 */
#define	GTCR_MAN_MS	0x1000	/* enable manual master/slave control */
#define	GTCR_ADV_MS	0x0800	/* 1 = adv. master, 0 = adv. slave */
#define	GTCR_PORT_TYPE	0x0400	/* 1 = DCE, 0 = DTE (NIC) */
#define	GTCR_ADV_1000TFDX 0x0200 /* adv. 1000baseT FDX */
#define	GTCR_ADV_1000THDX 0x0100 /* adv. 1000baseT HDX */

			/* This is also the 1000baseT status register */
#define	MII_100T2SR	0x0a	/* 100base-T2 status register */
#define	GTSR_MAN_MS_FLT	0x8000	/* master/slave config fault */
#define	GTSR_MS_RES	0x4000	/* result: 1 = master, 0 = slave */
#define	GTSR_LRS	0x2000	/* local rx status, 1 = ok */
#define	GTSR_RRS	0x1000	/* remote rx status, 1 = ok */
#define	GTSR_LP_1000TFDX 0x0800	/* link partner 1000baseT FDX capable */
#define	GTSR_LP_1000THDX 0x0400	/* link partner 1000baseT HDX capable */
#define	GTSR_LP_ASM_DIR	0x0200	/* link partner asym. pause dir. capable */
#define	GTSR_IDLE_ERR	0x00ff	/* IDLE error count */

#define	MII_PSECR	0x0b	/* PSE control register */
#define	PSECR_PACTLMASK	0x000c	/* pair control mask */
#define	PSECR_PSEENMASK	0x0003	/* PSE enable mask */
#define	PSECR_PINOUTB	0x0008	/* PSE pinout Alternative B */
#define	PSECR_PINOUTA	0x0004	/* PSE pinout Alternative A */
#define	PSECR_FOPOWTST	0x0002	/* Force Power Test Mode */
#define	PSECR_PSEEN	0x0001	/* PSE Enabled */
#define	PSECR_PSEDIS	0x0000	/* PSE Disabled */

#define	MII_PSESR	0x0c	/* PSE status register */
#define	PSESR_PWRDENIED	0x1000	/* Power Denied */
#define	PSESR_VALSIG	0x0800	/* Valid PD signature detected */
#define	PSESR_INVALSIG	0x0400	/* Invalid PD signature detected */
#define	PSESR_SHORTCIRC	0x0200	/* Short circuit condition detected */
#define	PSESR_OVERLOAD	0x0100	/* Overload condition detected */
#define	PSESR_MPSABSENT	0x0080	/* MPS absent condition detected */
#define	PSESR_PDCLMASK	0x0070	/* PD Class mask */
#define	PSESR_STATMASK	0x000e	/* PSE Status mask */
#define	PSESR_PAIRCTABL	0x0001	/* PAIR Control Ability */
#define	PSESR_PDCL_4		(4 << 4)	/* Class 4 */
#define	PSESR_PDCL_3		(3 << 4)	/* Class 3 */
#define	PSESR_PDCL_2		(2 << 4)	/* Class 2 */
#define	PSESR_PDCL_1		(1 << 4)	/* Class 1 */
#define	PSESR_PDCL_0		(0 << 4)	/* Class 0 */

#define	MII_MMDACR	0x0d	/* MMD access control register */
#define	MMDACR_FUNCMASK	0xc000	/* function */
#define	MMDACR_DADDRMASK 0x001f	/* device address */
#define	MMDACR_FN_ADDRESS	(0 << 14) /* address */
#define	MMDACR_FN_DATANPI	(1 << 14) /* data, no post increment */
#define	MMDACR_FN_DATAPIRW	(2 << 14) /* data, post increment on r/w */
#define	MMDACR_FN_DATAPIW	(3 << 14) /* data, post increment on wr only */

#define	MII_MMDAADR	0x0e	/* MMD access address data register */

#define	MII_EXTSR	0x0f	/* Extended status register */
#define	EXTSR_1000XFDX	0x8000	/* 1000X full-duplex capable */
#define	EXTSR_1000XHDX	0x4000	/* 1000X half-duplex capable */
#define	EXTSR_1000TFDX	0x2000	/* 1000T full-duplex capable */
#define	EXTSR_1000THDX	0x1000	/* 1000T half-duplex capable */

#define	EXTSR_MEDIAMASK	(EXTSR_1000XFDX|EXTSR_1000XHDX| \
		EXTSR_1000TFDX|EXTSR_1000THDX)

#ifdef __QNXNTO__
#define	MII_DEVADDR_NONE	-1

/*
 * MDIO Manageable Device Addresses (MMD)
 * Table 45-1 - Section 45.2
 */
#define CL45_MMD_RESERVED	0	/* Reserved */
#define CL45_MMD_PMAPMD		1	/* Physical Medium Attachment */
					/* Physical Medium Dependent */
#define CL45_MMD_WIS		2	/* WAN Interface Sublayer */
#define CL45_MMD_PCS		3	/* Physical Coding Sublayer */
#define CL45_MMD_PHYXS		4	/* PHY Extender Sublayer */
#define CL45_MMD_DTEXS		5	/* DTE Extender Sublayer */
#define CL45_MMD_TC		6	/* Transmission Convergence */
#define CL45_MMD_AN		7	/* Auto-Negotiation */
#define CL45_MMD_SEP_PMA1	8	/* Separated PMA (1) */
#define CL45_MMD_SEP_PMA2	9	/* Separated PMA (2) */
#define CL45_MMD_SEP_PMA3	10	/* Separated PMA (3) */
#define CL45_MMD_SEP_PMA4	11	/* Separated PMA (4) */
#define CL45_MMD_OFDM		12	/* OFDM Sublayer */
#define CL45_MMD_PWRUNIT	13	/* Power Management Unit */
/* 14 through 28 are reserved */
#define CL45_MMD_C22EXT		29	/* Clause 22 extension */
#define CL45_MMD_VEND1		30	/* Vendor specific 1 */
#define CL45_MMD_VEND2		31	/* Vendor specific 2 */

/*
 * Generic MDIO registers shared across MMDs
 * Table 45-3
 */
#define CL45_CTRL1		MII_BMCR /* Control 1 */
#define CL45_STAT1		MII_BMSR /* Status 1 */
#define CL45_DEVID1		MII_PHYIDR1 /* Device identifier 1 */
#define CL45_DEVID2		MII_PHYIDR2 /* Device identifier 2 */
#define CL45_SPEED		4	/* Speed ability */
#define CL45_DEVS1		5	/* Devices in package 1 */
#define CL45_DEVS2		6	/* Devices in package 2 */
#define CL45_CTRL2		7	/* Control 2 */
#define CL45_STAT2		8	/* Status 2 */
#define CL45_PMA_TXDIS		9	/* Transmit disable */
#define CL45_PMA_RXDET		10	/* Receive signal detect */
#define CL45_PMA_EXTABLE	11	/* Extended ability */
#define CL45_PKGID1		14	/* Package identifier1 */
#define CL45_PKGID2		15	/* Package identifier2 */
#define CL45_AN_ADVERTISE	16	/* AN advertising (base page) */
#define CL45_AN_ADVERTISE2	17	/* AN advertisement register 2 */
#define CL45_AN_ADVERTISE3	18	/* AN advertisement register 3 */
#define CL45_AN_LPA		19	/* AN LP abilities (base page) */
#define CL45_AN_LPA2		20	/* AN LP abilities register 2 */
#define CL45_AN_LPA3		21	/* AN LP abilities register 3 */
#define CL45_PHYXS_LNSTAT	24	/* PHY XGXS lane state */

/*
 * PMA/PMD Extended Ability Register Sets
 */
#define CL45_PMA_EXTREG_10GEPON		12	/* 10G EPON extended ability */
#define CL45_PMA_EXTREG_40G100G		13	/* 40G/100G extended ability */
#define CL45_PMA_EXTREG_BASET1		18	/* BASE-T1 extended ability */
#define CL45_PMA_EXTREG_25G		19	/* 25G extended ability */
#define CL45_PMA_EXTREG_50G		20	/* 50G extended ability */
#define CL45_PMA_EXTREG_2P5G5G		21	/* 2.5G/5G extended ability */
#define CL45_PMA_EXTREG_BASEH		22	/* BASE-H extended ability */
#define CL45_PMA_EXTREG_200G		23	/* 200G extended ability */
#define CL45_PMA_EXTREG_400G		24	/* 400G extended ability */
#define CL45_PMA_EXTREG2_40G100G	26	/* 40G/100G extended ability 2 */

/* Media-dependent registers. */
#define CL45_PMA_10GBT_SWAPPOL	130	/* 10GBASE-T pair swap & polarity */
#define CL45_PMA_10GBT_TXPWR	131	/* 10GBASE-T TX power control */
#define CL45_PMA_10GBT_SNR	133	/* 10GBASE-T SNR margin, lane A.
				* Lanes B-D are numbered 134-136. */
#define CL45_PMA_10GBR_FECABLE	170	/* 10GBASE-R FEC ability */
#define CL45_PCS_10GBX_STAT1	24	/* 10GBASE-X PCS status 1 */
#define CL45_PCS_10GBRT_STAT1	32	/* 10GBASE-R/-T PCS status 1 */
#define CL45_PCS_10GBRT_STAT2	33	/* 10GBASE-R/-T PCS status 2 */
#define CL45_AN_10GBT_CTRL	32	/* 10GBASE-T auto-negotiation control */
#define CL45_AN_10GBT_STAT	33	/* 10GBASE-T auto-negotiation status */
#define CL45_AN_EEE_ADV		60	/* EEE advertisement */

/* LASI (Link Alarm Status Interrupt) registers, defined by XENPAK MSA. */
#define CL45_PMA_LASI_RXCTRL	0x9000	/* RX_ALARM control */
#define CL45_PMA_LASI_TXCTRL	0x9001	/* TX_ALARM control */
#define CL45_PMA_LASI_CTRL	0x9002	/* LASI control */
#define CL45_PMA_LASI_RXSTAT	0x9003	/* RX_ALARM status */
#define CL45_PMA_LASI_TXSTAT	0x9004	/* TX_ALARM status */
#define CL45_PMA_LASI_STAT	0x9005	/* LASI status */

/*
 * Control Register 1
 * Table 45-4
 * b2-5: Speed selection
 * b6: Speed Selection MSB
 * b13: Speed Selection LSB
 */
#define CL45_PMA_CTRL1_LOOPBACK			0x0000 /* Loopback */
#define CL45_PMA_CTRL1_REMLOOPBACK		0x0001 /* Remote loopback */
#define CL45_PMA_CTRL1_SPEEDSEL_MASK		0x003c /* Speed selection mask for multigig speeds */
#define CL45_PMA_CTRL1_SPEEDSEL_MSB		0x0040 /* Speed selection MSB */
/* b7-10: Reserved */
#define CL45_PMA_CTRL1_LPOWER			0x0800 /* Low power mode - BMCR_PDOWN*/
/* b12: Reserved */
#define CL45_PMA_CTRL1_SPEEDSEL_LSB		0x2000 /* Speed selection LSB */
/* b14: Reserved */
#define CL45_PMA_CTRL1_RESET			0x8000 /* Reset */

/* Control Register 1 Speed Selection */
#define CL45_PMA_CTRL1_10			0x0000 /* 10 Mbps */
#define CL45_PMA_CTRL1_100			CL45_PMA_CTRL1_SPEEDSEL_LSB /* 100 Mbps */
#define CL45_PMA_CTRL1_1000			CL45_PMA_CTRL1_SPEEDSEL_MSB /* 1000 Mbps */
/* When b6 and b13 = 1, then refer to b2-5 */
#define CL45_PMA_CTRL1_SPEEDSELEXT		(CL45_PMA_CTRL1_100 | CL45_PMA_CTRL1_1000)

#define CL45_PMA_CTRL1_SPEED_10G		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x0000) /* 10G */
#define CL45_PMA_CTRL1_SPEED_10P2B		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x0004) /* 10PASS-TS/2BASE-TL */
#define CL45_PMA_CTRL1_SPEED_40G		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x0008) /* 40G */
#define CL45_PMA_CTRL1_SPEED_100G		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x000c) /* 100G */
#define CL45_PMA_CTRL1_SPEED_25G		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x0010) /* 25G */
#define CL45_PMA_CTRL1_SPEED_50G		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x0014) /* 50G */
#define CL45_PMA_CTRL1_SPEED_2P5G		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x0018) /* 2.5G */
#define CL45_PMA_CTRL1_SPEED_5G			(CL45_PMA_CTRL1_SPEEDSELEXT | 0x001c) /* 5G */
#define CL45_PMA_CTRL1_SPEED_200G		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x0020) /* 200G */
#define CL45_PMA_CTRL1_SPEED_400G		(CL45_PMA_CTRL1_SPEEDSELEXT | 0x0024) /* 400G */
/* Reserved */

/*
 * Status register 1
 * Table 45-5
 */
#define CL45_STAT1_LPOWERABLE		0x0002	/* Low-power ability */
#define CL45_STAT1_LSTATUS		BMSR_LINK
#define CL45_STAT1_FAULT		0x0080	/* Fault */

/*
 * AN Status Register 1
 * Table 45 - 380
 */
/* b15:10: Reserved */
#define CL45_AN_STAT1_PARALLEL_FLT	0x0200	/* Parallel detection fault */
/* b8: Reserved */
#define CL45_AN_STAT1_EXTNP		0x0080
#define CL45_AN_STAT1_PGRX		0x0040	/* Page received */
#define CL45_AN_STAT1_COMPLETE		0x0020	/* Auto-negotiation complete */
#define CL45_AN_STAT1_RFAULT		0x0010 /* Remote fault */
#define CL45_AN_STAT1_ABLE		0x0008	/* Auto-negotiation ability */
#define CL45_AN_STAT1_LSTATUS		0x0004	/* Link status */
/* b1: Reserved */
#define CL45_AN_STAT1_LPABLE		0x0001	/* Link partner auto-negotiation ability */

/*
 * PMA/PMD Speed Ability Registers
 * Table 45-6
 */
#define CL45_PMA_SPEED_10G		0x0001	/* 10G capable */
#define CL45_PMA_SPEED_2B		0x0002	/* 2BASE-TL capable */
#define CL45_PMA_SPEED_10P		0x0004	/* 10PASS-TS capable */
#define CL45_PMA_SPEED_50G		0x0008	/* 50G capable */
#define CL45_PMA_SPEED_1000		0x0010	/* 1000M capable */
#define CL45_PMA_SPEED_100		0x0020	/* 100M capable */
#define CL45_PMA_SPEED_10		0x0040	/* 10M capable */
#define CL45_PMA_SPEED_10G_1GU		0x0080	/* 10G capable, 1G Upstream */
#define CL45_PMA_SPEED_40G		0x0100	/* 40G capable */
#define CL45_PMA_SPEED_100G		0x0200	/* 100G capable */
#define CL45_PMA_SPEED_10GPXR		0x0400	/* 10G capable, 10G PHY XAUI */
#define CL45_PMA_SPEED_25G		0x0800	/* 25G capable */
#define CL45_PMA_SPEED_200G		0x1000	/* 200G capable */
#define CL45_PMA_SPEED_2P5G		0x2000	/* 2.5G capable */
#define CL45_PMA_SPEED_5G		0x4000	/* 5G capable */
#define CL45_PMA_SPEED_400G		0x8000	/* 400G capable */

/*
 * PCS Speed Ability Register
 * Table 45-236
 */
#define CL45_PCS_SPEED_10G		0x0001	/* 10G capable */
#define CL45_PCS_SPEED_10P2B		0x0002	/* 10PASS-TS/2BASE-TL capable */
#define CL45_PCS_SPEED_40G		0x0004	/* 40G capable */
#define CL45_PCS_SPEED_100G		0x0008	/* 100G capable */
#define CL45_PCS_SPEED_25G		0x0010	/* 25G capable */
#define CL45_PCS_SPEED_50G		0x0020	/* 50G capable */
#define CL45_PCS_SPEED_2P5G		0x0040	/* 2.5G capable */
#define CL45_PCS_SPEED_5G		0x0080	/* 5G capable */
#define CL45_PCS_SPEED_200G		0x0100	/* 200G capable */
#define CL45_PCS_SPEED_400G		0x0200	/* 400G capable */
/* b10-b15: Reserved */

/*
 * Devices in Package Registers (5,6)
 * Table 45-2
 * DEVS2 and DEVS1 have the following register definitions:
 * Table 45-2 Devices in Package Registers
 * DEVS2.15: Vendor Specific Device 2 Present
 * DEVS2.14: Vendor Specific Device 1 Present
 * DEVS2.13: Clause 22 Extension Present
 * DEVS2.12-0: Reserved (always 0)
 * DEVS1.15-14: Reserved (always 0)
 * DEVS1.13: Power Unit Present
 * DEVS1.12: OFDM Present
 * DEVS1.11: Separated PMA (4) Present
 * DEVS1.10: Separated PMA (3) Present
 * DEVS1.9: Separated PMA (2) Present
 * DEVS1.8: Separated PMA (1) Present
 * DEVS1.7: Auto-Negotiation Present
 * DEVS1.6: TC Present
 * DEVS1.5: DTE XS Present
 * DEVS1.4: PHY XS Present
 * DEVS1.3: PCS Present
 * DEVS1.2: WIS Present
 * DEVS1.1: PMA/PMD Present
 * DEVS1.0: Clause 22 Registers Present
 */
#define CL45_DEVS_PRESENT_INT32(devad)	(1 << (devad))
#define CL45_DEVS_C22			CL45_DEVS_PRESENT_INT32(0)
#define CL45_DEVS_PMAPMD		CL45_DEVS_PRESENT_INT32(CL45_MMD_PMAPMD)
#define CL45_DEVS_WIS			CL45_DEVS_PRESENT_INT32(CL45_MMD_WIS)
#define CL45_DEVS_PCS			CL45_DEVS_PRESENT_INT32(CL45_MMD_PCS)
#define CL45_DEVS_PHYXS			CL45_DEVS_PRESENT_INT32(CL45_MMD_PHYXS)
#define CL45_DEVS_DTEXS			CL45_DEVS_PRESENT_INT32(CL45_MMD_DTEXS)
#define CL45_DEVS_TC			CL45_DEVS_PRESENT_INT32(CL45_MMD_TC)
#define CL45_DEVS_AN			CL45_DEVS_PRESENT_INT32(CL45_MMD_AN)
#define CL45_DEVS_SEP_PMA1		CL45_DEVS_PRESENT_INT32(CL45_MMD_SEP_PMA1)
#define CL45_DEVS_SEP_PMA2		CL45_DEVS_PRESENT_INT32(CL45_MMD_SEP_PMA2)
#define CL45_DEVS_SEP_PMA3		CL45_DEVS_PRESENT_INT32(CL45_MMD_SEP_PMA3)
#define CL45_DEVS_SEP_PMA4		CL45_DEVS_PRESENT_INT32(CL45_MMD_SEP_PMA4)
#define CL45_DEVS_OFDM			CL45_DEVS_PRESENT_INT32(CL45_MMD_OFDM)
#define CL45_DEVS_PWRUNIT		CL45_DEVS_PRESENT_INT32(CL45_MMD_PWRUNIT)
#define CL45_DEVS_C22EXT		CL45_DEVS_PRESENT_INT32(CL45_MMD_C22EXT)
#define CL45_DEVS_VEND1			CL45_DEVS_PRESENT_INT32(CL45_MMD_VEND1)
#define CL45_DEVS_VEND2			CL45_DEVS_PRESENT_INT32(CL45_MMD_VEND2)

/* Control register 2. */
#define CL45_PMA_CTRL2_TYPE		0x000f	/* PMA/PMD type selection */
#define CL45_PMA_CTRL2_10GBCX4		0x0000	/* 10GBASE-CX4 type */
#define CL45_PMA_CTRL2_10GBEW		0x0001	/* 10GBASE-EW type */
#define CL45_PMA_CTRL2_10GBLW		0x0002	/* 10GBASE-LW type */
#define CL45_PMA_CTRL2_10GBSW		0x0003	/* 10GBASE-SW type */
#define CL45_PMA_CTRL2_10GBLX4		0x0004	/* 10GBASE-LX4 type */
#define CL45_PMA_CTRL2_10GBER		0x0005	/* 10GBASE-ER type */
#define CL45_PMA_CTRL2_10GBLR		0x0006	/* 10GBASE-LR type */
#define CL45_PMA_CTRL2_10GBSR		0x0007	/* 10GBASE-SR type */
#define CL45_PMA_CTRL2_10GBLRM		0x0008	/* 10GBASE-LRM type */
#define CL45_PMA_CTRL2_10GBT		0x0009	/* 10GBASE-T type */
#define CL45_PMA_CTRL2_10GBKX4		0x000a	/* 10GBASE-KX4 type */
#define CL45_PMA_CTRL2_10GBKR		0x000b	/* 10GBASE-KR type */
#define CL45_PMA_CTRL2_1000BT		0x000c	/* 1000BASE-T type */
#define CL45_PMA_CTRL2_1000BKX		0x000d	/* 1000BASE-KX type */
#define CL45_PMA_CTRL2_100BTX		0x000e	/* 100BASE-TX type */
#define CL45_PMA_CTRL2_10BT		0x000f	/* 10BASE-T type */
#define CL45_PMA_CTRL2_2_5GBT		0x0030	/* 2.5GBaseT type */
#define CL45_PMA_CTRL2_5GBT		0x0031	/* 5GBaseT type */
#define CL45_PMA_CTRL2_BASET1		0x003D	/* BASE-T1 type */
#define CL45_PCS_CTRL2_TYPE		0x0003	/* PCS type selection */
#define CL45_PCS_CTRL2_10GBR		0x0000	/* 10GBASE-R type */
#define CL45_PCS_CTRL2_10GBX		0x0001	/* 10GBASE-X type */
#define CL45_PCS_CTRL2_10GBW		0x0002	/* 10GBASE-W type */
#define CL45_PCS_CTRL2_10GBT		0x0003	/* 10GBASE-T type */

/* Status register 2. */
#define CL45_STAT2_RXFAULT		0x0400	/* Receive fault */
#define CL45_STAT2_TXFAULT		0x0800	/* Transmit fault */
#define CL45_STAT2_DEVPRST		0xc000	/* Device present */
#define CL45_STAT2_DEVPRST_VAL		0x8000	/* Device present value */
#define CL45_PMA_STAT2_LBABLE		0x0001	/* PMA loopback ability */
#define CL45_PMA_STAT2_10GBEW		0x0002	/* 10GBASE-EW ability */
#define CL45_PMA_STAT2_10GBLW		0x0004	/* 10GBASE-LW ability */
#define CL45_PMA_STAT2_10GBSW		0x0008	/* 10GBASE-SW ability */
#define CL45_PMA_STAT2_10GBLX4		0x0010	/* 10GBASE-LX4 ability */
#define CL45_PMA_STAT2_10GBER		0x0020	/* 10GBASE-ER ability */
#define CL45_PMA_STAT2_10GBLR		0x0040	/* 10GBASE-LR ability */
#define CL45_PMA_STAT2_10GBSR		0x0080	/* 10GBASE-SR ability */
#define CL45_PMD_STAT2_TXDISAB		0x0100	/* PMD TX disable ability */
#define CL45_PMA_STAT2_EXTABLE		0x0200	/* Extended abilities */
#define CL45_PMA_STAT2_RXFLTABLE	0x1000	/* Receive fault ability */
#define CL45_PMA_STAT2_TXFLTABLE	0x2000	/* Transmit fault ability */
#define CL45_PCS_STAT2_10GBR		0x0001	/* 10GBASE-R capable */
#define CL45_PCS_STAT2_10GBX		0x0002	/* 10GBASE-X capable */
#define CL45_PCS_STAT2_10GBW		0x0004	/* 10GBASE-W capable */
#define CL45_PCS_STAT2_RXFLTABLE	0x1000	/* Receive fault ability */
#define CL45_PCS_STAT2_TXFLTABLE	0x2000	/* Transmit fault ability */

#define CL45_MEDIAMASK	(CL45_PMA_STAT2_10GBEW|CL45_PMA_STAT2_10GBLW| \
		CL45_PMA_STAT2_10GBSW|CL45_PMA_STAT2_10GBLX4| \
		CL45_PMA_STAT2_10GBER|CL45_PMA_STAT2_10GBLR| \
		CL45_PMA_STAT2_10GBSR)

/* Transmit disable register. */
#define CL45_PMD_TXDIS_GLOBAL		0x0001	/* Global PMD TX disable */
#define CL45_PMD_TXDIS_0		0x0002	/* PMD TX disable 0 */
#define CL45_PMD_TXDIS_1		0x0004	/* PMD TX disable 1 */
#define CL45_PMD_TXDIS_2		0x0008	/* PMD TX disable 2 */
#define CL45_PMD_TXDIS_3		0x0010	/* PMD TX disable 3 */

/* Receive signal detect register. */
#define CL45_PMD_RXDET_GLOBAL		0x0001	/* Global PMD RX signal detect */
#define CL45_PMD_RXDET_0		0x0002	/* PMD RX signal detect 0 */
#define CL45_PMD_RXDET_1		0x0004	/* PMD RX signal detect 1 */
#define CL45_PMD_RXDET_2		0x0008	/* PMD RX signal detect 2 */
#define CL45_PMD_RXDET_3		0x0010	/* PMD RX signal detect 3 */

/* Extended abilities register. */
#define CL45_PMA_EXTABLE_10GCX4		0x0001	/* 10GBASE-CX4 ability */
#define CL45_PMA_EXTABLE_10GBLRM	0x0002	/* 10GBASE-LRM ability */
#define CL45_PMA_EXTABLE_10GBT		0x0004	/* 10GBASE-T ability */
#define CL45_PMA_EXTABLE_10GBKX4	0x0008	/* 10GBASE-KX4 ability */
#define CL45_PMA_EXTABLE_10GBKR		0x0010	/* 10GBASE-KR ability */
#define CL45_PMA_EXTABLE_1000BT		0x0020	/* 1000BASE-T ability */
#define CL45_PMA_EXTABLE_1000BKX	0x0040	/* 1000BASE-KX ability */
#define CL45_PMA_EXTABLE_100BTX		0x0080	/* 100BASE-TX ability */
#define CL45_PMA_EXTABLE_10BT		0x0100	/* 10BASE-T ability */
#define CL45_PMA_EXTABLE_P2MP		0x0200	/* P2MP ability */
#define CL45_PMA_EXTABLE_40G100GEXT	0x0400	/* 40G/100G extended ability */
#define CL45_PMA_EXTABLE_BASET1EXT	0x0800	/* BASE-T1 extended ability */
#define CL45_PMA_EXTABLE_25GEXT		0x1000	/* 25G extended ability */
#define CL45_PMA_EXTABLE_200G400GEXT	0x2000	/* 200G/400G extended ability */
#define CL45_PMA_EXTABLE_2P5G5GEXT	0x4000	/* 2.5G/5G extended ability */
#define CL45_PMA_EXTABLE_BASEHEXT	0x8000	/* BASE-HE extended ability */

#define CL45_EXTABLE_MEDIAMASK (CL45_PMA_EXTABLE_10GCX4| \
				CL45_PMA_EXTABLE_10GBLRM| \
				CL45_PMA_EXTABLE_10GBT| \
				CL45_PMA_EXTABLE_10GBKX4| \
				CL45_PMA_EXTABLE_10GBKR| \
				CL45_PMA_EXTABLE_1000BT| \
				CL45_PMA_EXTABLE_1000BKX| \
				CL45_PMA_EXTABLE_100BTX| \
				CL45_PMA_EXTABLE_10BT| \
				CL45_PMA_EXTABLE_P2MP| \
				CL45_PMA_EXTABLE_40G100GEXT| \
				CL45_PMA_EXTABLE_BASET1EXT| \
				CL45_PMA_EXTABLE_25GEXT| \
				CL45_PMA_EXTABLE_200G400GEXT| \
				CL45_PMA_EXTABLE_2P5G5GEXT| \
				CL45_PMA_EXTABLE_BASEHEXT)

/* Masking the bits that support extended register bits. */
#define CL45_EXTABLE_MEDIAMASKEXT (CL45_PMA_EXTABLE_40G100GEXT| \
			   CL45_PMA_EXTABLE_BASET1EXT| \
			   CL45_PMA_EXTABLE_25GEXT| \
			   CL45_PMA_EXTABLE_200G400GEXT| \
			   CL45_PMA_EXTABLE_2P5G5GEXT| \
			   CL45_PMA_EXTABLE_BASEHEXT)

/* PMA/PMD Extended Ability Register Sets */
#define CL45_PMA_EXTREG_2P5G5G_5GBKR	0x0008	/* 5GBASE-KR ability */
#define CL45_PMA_EXTREG_2P5G5G_2P5GBKX	0x0004	/* 2.5GBASE-KX ability */
#define CL45_PMA_EXTREG_2P5G5G_5GBT	0x0002	/* 5GBASE-T ability */
#define CL45_PMA_EXTREG_2P5G5G_2P5GBT	0x0001	/* 2.5GBASE-T ability */

#define CL45_PMA_EXTREG_2P5G5G_MEDIAMASK (CL45_PMA_EXTREG_2P5G5G_5GBKR| \
				 CL45_PMA_EXTREG_2P5G5G_2P5GBKX| \
				 CL45_PMA_EXTREG_2P5G5G_5GBT| \
				 CL45_PMA_EXTREG_2P5G5G_2P5GBT)

/* PHY XGXS lane state register. */
#define CL45_PHYXS_LNSTAT_SYNC0		0x0001
#define CL45_PHYXS_LNSTAT_SYNC1		0x0002
#define CL45_PHYXS_LNSTAT_SYNC2		0x0004
#define CL45_PHYXS_LNSTAT_SYNC3		0x0008
#define CL45_PHYXS_LNSTAT_ALIGN		0x1000

/* PMA 10GBASE-T pair swap & polarity */
#define CL45_PMA_10GBT_SWAPPOL_ABNX	0x0001	/* Pair A/B uncrossed */
#define CL45_PMA_10GBT_SWAPPOL_CDNX	0x0002	/* Pair C/D uncrossed */
#define CL45_PMA_10GBT_SWAPPOL_AREV	0x0100	/* Pair A polarity reversed */
#define CL45_PMA_10GBT_SWAPPOL_BREV	0x0200	/* Pair B polarity reversed */
#define CL45_PMA_10GBT_SWAPPOL_CREV	0x0400	/* Pair C polarity reversed */
#define CL45_PMA_10GBT_SWAPPOL_DREV	0x0800	/* Pair D polarity reversed */

/* PMA 10GBASE-T TX power register. */
#define CL45_PMA_10GBT_TXPWR_SHORT	0x0001	/* Short-reach mode */

/* PMA 10GBASE-T SNR registers. */
/* Value is SNR margin in dB, clamped to range [-127, 127], plus 0x8000. */
#define CL45_PMA_10GBT_SNR_BIAS		0x8000
#define CL45_PMA_10GBT_SNR_MAX		127

/* PMA 10GBASE-R FEC ability register. */
#define CL45_PMA_10GBR_FECABLE_ABLE	0x0001	/* FEC ability */
#define CL45_PMA_10GBR_FECABLE_ERRABLE	0x0002	/* FEC error indic. ability */

/* PCS 10GBASE-R/-T status register 1. */
#define CL45_PCS_10GBRT_STAT1_BLKLK	0x0001	/* Block lock attained */

/* PCS 10GBASE-R/-T status register 2. */
#define CL45_PCS_10GBRT_STAT2_ERR	0x00ff
#define CL45_PCS_10GBRT_STAT2_BER	0x3f00

/* AN 10GBASE-T control register. */
#define CL45_AN_10GBT_CTRL_ADVFSRT2_5G	0x0020	/* Advertise 2.5GBASE-T fast retrain */
#define CL45_AN_10GBT_CTRL_ADV2_5G	0x0080	/* Advertise 2.5GBASE-T */
#define CL45_AN_10GBT_CTRL_ADV5G	0x0100	/* Advertise 5GBASE-T */
#define CL45_AN_10GBT_CTRL_ADV10G	0x1000	/* Advertise 10GBASE-T */

/* AN 10GBASE-T status register. */
#define CL45_AN_10GBT_STAT_LPTRR	0x0200	/* LP training reset req. */
#define CL45_AN_10GBT_STAT_LPLTABLE	0x0400	/* LP loop timing ability */
#define CL45_AN_10GBT_STAT_LP10G	0x0800	/* LP is 10GBT capable */
#define CL45_AN_10GBT_STAT_REMOK	0x1000	/* Remote OK */
#define CL45_AN_10GBT_STAT_LOCOK	0x2000	/* Local OK */
#define CL45_AN_10GBT_STAT_MS		0x4000	/* Master/slave config */
#define CL45_AN_10GBT_STAT_MSFLT	0x8000	/* Master/slave config fault */

/* AN EEE Advertisement register. */
#define CL45_AN_EEE_ADV_100TX		0x0002	/* Advertise 100TX EEE cap */
#define CL45_AN_EEE_ADV_1000T		0x0004	/* Advertise 1000T EEE cap */

/* AN Advertisement Register bits */
#define CL45_AN_ADVERTISE_NPABLE	0x8000	/* Next page ability */
#define CL45_AN_ADVERTISE_ACK		0x4000	/* Acknowledge */
#define CL45_AN_ADVERTISE_REMFAULT	0x2000	/* Remote fault */
/* Data select for bits D5 to D12 */
#define CL45_AN_ADVERTISE_D(x)		((1) << (x)) /* Data select */
#define CL45_AN_ADVERTISE_D5		CL45_AN_ADVERTISE_D(5)
#define CL45_AN_ADVERTISE_D6		CL45_AN_ADVERTISE_D(6)
#define CL45_AN_ADVERTISE_D7		CL45_AN_ADVERTISE_D(7)
#define CL45_AN_ADVERTISE_D8		CL45_AN_ADVERTISE_D(8)
#define CL45_AN_ADVERTISE_D9		CL45_AN_ADVERTISE_D(9)
#define CL45_AN_ADVERTISE_D10		CL45_AN_ADVERTISE_D(10)
#define CL45_AN_ADVERTISE_D11		CL45_AN_ADVERTISE_D(11)
#define CL45_AN_ADVERTISE_D12		CL45_AN_ADVERTISE_D(12)
#define CL45_AN_ADVERTISE_DMASK		0x1f80	/* Data mask */
#define CL45_AN_ADVERTISE_SELECTOR	0x001f	/* Selector field */

/* AN Advertisement Register bits D16 to D31 */
#define CL45_AN_ADVERTISE2_D(x)		((1) << ((x) - 16)) /* Data select */
#define CL45_AN_ADVERTISE2_D16		CL45_AN_ADVERTISE2_D(16)
#define CL45_AN_ADVERTISE2_D17		CL45_AN_ADVERTISE2_D(17)
#define CL45_AN_ADVERTISE2_D18		CL45_AN_ADVERTISE2_D(18)
#define CL45_AN_ADVERTISE2_D19		CL45_AN_ADVERTISE2_D(19)
#define CL45_AN_ADVERTISE2_D20		CL45_AN_ADVERTISE2_D(20)
#define CL45_AN_ADVERTISE2_D21		CL45_AN_ADVERTISE2_D(21)
#define CL45_AN_ADVERTISE2_D22		CL45_AN_ADVERTISE2_D(22)
#define CL45_AN_ADVERTISE2_D23		CL45_AN_ADVERTISE2_D(23)
#define CL45_AN_ADVERTISE2_D24		CL45_AN_ADVERTISE2_D(24)
#define CL45_AN_ADVERTISE2_D25		CL45_AN_ADVERTISE2_D(25)
#define CL45_AN_ADVERTISE2_D26		CL45_AN_ADVERTISE2_D(26)
#define CL45_AN_ADVERTISE2_D27		CL45_AN_ADVERTISE2_D(27)
#define CL45_AN_ADVERTISE2_D28		CL45_AN_ADVERTISE2_D(28)
#define CL45_AN_ADVERTISE2_D29		CL45_AN_ADVERTISE2_D(29)
#define CL45_AN_ADVERTISE2_D30		CL45_AN_ADVERTISE2_D(30)
#define CL45_AN_ADVERTISE2_D31		CL45_AN_ADVERTISE2_D(31)
#define CL45_AN_ADVERTISE2_DMASK	0xffff0000 /* Data mask */

/* AN Advertisement Register bits D32 to D47 */
#define CL45_AN_ADVERTISE3_D(x)		((1) << ((x) - 32)) /* Data select */
#define CL45_AN_ADVERTISE3_D32		CL45_AN_ADVERTISE3_D(32)
#define CL45_AN_ADVERTISE3_D33		CL45_AN_ADVERTISE3_D(33)
#define CL45_AN_ADVERTISE3_D34		CL45_AN_ADVERTISE3_D(34)
#define CL45_AN_ADVERTISE3_D35		CL45_AN_ADVERTISE3_D(35)
#define CL45_AN_ADVERTISE3_D36		CL45_AN_ADVERTISE3_D(36)
#define CL45_AN_ADVERTISE3_D37		CL45_AN_ADVERTISE3_D(37)
#define CL45_AN_ADVERTISE3_D38		CL45_AN_ADVERTISE3_D(38)
#define CL45_AN_ADVERTISE3_D39		CL45_AN_ADVERTISE3_D(39)
#define CL45_AN_ADVERTISE3_D40		CL45_AN_ADVERTISE3_D(40)
#define CL45_AN_ADVERTISE3_D41		CL45_AN_ADVERTISE3_D(41)
#define CL45_AN_ADVERTISE3_D42		CL45_AN_ADVERTISE3_D(42)
#define CL45_AN_ADVERTISE3_D43		CL45_AN_ADVERTISE3_D(43)
#define CL45_AN_ADVERTISE3_D44		CL45_AN_ADVERTISE3_D(44)
#define CL45_AN_ADVERTISE3_D45		CL45_AN_ADVERTISE3_D(45)
#define CL45_AN_ADVERTISE3_D46		CL45_AN_ADVERTISE3_D(46)
#define CL45_AN_ADVERTISE3_D47		CL45_AN_ADVERTISE3_D(47)

/* AN Link Partner Ability Register bits */
/* Data select fields D0-D15*/
#define CL45_AN_LPA_D(x)		((1) << (x)) /* Data select */
#define CL45_AN_LPA_D0			CL45_AN_LPA_D(0)
#define CL45_AN_LPA_D1			CL45_AN_LPA_D(1)
#define CL45_AN_LPA_D2			CL45_AN_LPA_D(2)
#define CL45_AN_LPA_D3			CL45_AN_LPA_D(3)
#define CL45_AN_LPA_D4			CL45_AN_LPA_D(4)
#define CL45_AN_LPA_D5			CL45_AN_LPA_D(5)
#define CL45_AN_LPA_D6			CL45_AN_LPA_D(6)
#define CL45_AN_LPA_D7			CL45_AN_LPA_D(7)
#define CL45_AN_LPA_D8			CL45_AN_LPA_D(8)
#define CL45_AN_LPA_D9			CL45_AN_LPA_D(9)
#define CL45_AN_LPA_D10			CL45_AN_LPA_D(10)
#define CL45_AN_LPA_D11			CL45_AN_LPA_D(11)
#define CL45_AN_LPA_D12			CL45_AN_LPA_D(12)
#define CL45_AN_LPA_D13			CL45_AN_LPA_D(13)
#define CL45_AN_LPA_D14			CL45_AN_LPA_D(14)
#define CL45_AN_LPA_D15			CL45_AN_LPA_D(15)

/* Data select fields D16-D31 */
#define CL45_AN_LPA2_D(x)		((1) << ((x) - 16)) /* Data select */
#define CL45_AN_LPA2_D16		CL45_AN_LPA2_D(16)
#define CL45_AN_LPA2_D17		CL45_AN_LPA2_D(17)
#define CL45_AN_LPA2_D18		CL45_AN_LPA2_D(18)
#define CL45_AN_LPA2_D19		CL45_AN_LPA2_D(19)
#define CL45_AN_LPA2_D20		CL45_AN_LPA2_D(20)
#define CL45_AN_LPA2_D21		CL45_AN_LPA2_D(21)
#define CL45_AN_LPA2_D22		CL45_AN_LPA2_D(22)
#define CL45_AN_LPA2_D23		CL45_AN_LPA2_D(23)
#define CL45_AN_LPA2_D24		CL45_AN_LPA2_D(24)
#define CL45_AN_LPA2_D25		CL45_AN_LPA2_D(25)
#define CL45_AN_LPA2_D26		CL45_AN_LPA2_D(26)
#define CL45_AN_LPA2_D27		CL45_AN_LPA2_D(27)
#define CL45_AN_LPA2_D28		CL45_AN_LPA2_D(28)
#define CL45_AN_LPA2_D29		CL45_AN_LPA2_D(29)
#define CL45_AN_LPA2_D30		CL45_AN_LPA2_D(30)
#define CL45_AN_LPA2_D31		CL45_AN_LPA2_D(31)

/* Data select fields D32-D47 */
#define CL45_AN_LPA3_D(x)		((1) << ((x) - 32)) /* Data select */
#define CL45_AN_LPA3_D32		CL45_AN_LPA3_D(32)
#define CL45_AN_LPA3_D33		CL45_AN_LPA3_D(33)
#define CL45_AN_LPA3_D34		CL45_AN_LPA3_D(34)
#define CL45_AN_LPA3_D35		CL45_AN_LPA3_D(35)
#define CL45_AN_LPA3_D36		CL45_AN_LPA3_D(36)
#define CL45_AN_LPA3_D37		CL45_AN_LPA3_D(37)
#define CL45_AN_LPA3_D38		CL45_AN_LPA3_D(38)
#define CL45_AN_LPA3_D39		CL45_AN_LPA3_D(39)
#define CL45_AN_LPA3_D40		CL45_AN_LPA3_D(40)
#define CL45_AN_LPA3_D41		CL45_AN_LPA3_D(41)
#define CL45_AN_LPA3_D42		CL45_AN_LPA3_D(42)
#define CL45_AN_LPA3_D43		CL45_AN_LPA3_D(43)
#define CL45_AN_LPA3_D44		CL45_AN_LPA3_D(44)
#define CL45_AN_LPA3_D45		CL45_AN_LPA3_D(45)
#define CL45_AN_LPA3_D46		CL45_AN_LPA3_D(46)
#define CL45_AN_LPA3_D47		CL45_AN_LPA3_D(47)

/* LASI RX_ALARM control/status registers. */
#define CL45_PMA_LASI_RX_PHYXSLFLT	0x0001	/* PHY XS RX local fault */
#define CL45_PMA_LASI_RX_PCSLFLT	0x0008	/* PCS RX local fault */
#define CL45_PMA_LASI_RX_PMALFLT	0x0010	/* PMA/PMD RX local fault */
#define CL45_PMA_LASI_RX_OPTICPOWERFLT	0x0020	/* RX optical power fault */
#define CL45_PMA_LASI_RX_WISLFLT	0x0200	/* WIS local fault */

/* LASI TX_ALARM control/status registers. */
#define CL45_PMA_LASI_TX_PHYXSLFLT	0x0001	/* PHY XS TX local fault */
#define CL45_PMA_LASI_TX_PCSLFLT	0x0008	/* PCS TX local fault */
#define CL45_PMA_LASI_TX_PMALFLT	0x0010	/* PMA/PMD TX local fault */
#define CL45_PMA_LASI_TX_LASERPOWERFLT	0x0080	/* Laser output power fault */
#define CL45_PMA_LASI_TX_LASERTEMPFLT	0x0100	/* Laser temperature fault */
#define CL45_PMA_LASI_TX_LASERBICURRFLT	0x0200	/* Laser bias current fault */

/* LASI control/status registers. */
#define CL45_PMA_LASI_LSALARM		0x0001	/* LS_ALARM enable/status */
#define CL45_PMA_LASI_TXALARM		0x0002	/* TX_ALARM enable/status */
#define CL45_PMA_LASI_RXALARM		0x0004	/* RX_ALARM enable/status */

/*
 * Auto-Negotiation Control Register.
 * Table 45-379
 */
#define CL45_AN_CTRL1_RESET		0x8000	/* Restart autonegotiation */
#define CL45_AN_CTRL1_EXTNPAGE		0x2000	/* Enable extended next page */
#define CL45_AN_CTRL1_ENABLE		0x1000	/* Enable autonegotiation */
#define CL45_AN_CTRL1_RESTART		0x0200	/* Restart autonegotiation */

#endif /* __QNXNTO__ */
#endif /* _DEV_MII_MII_H_ */
