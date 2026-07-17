/*
 * $QNXLicenseC:
 * Copyright 2019, QNX Software Systems. All Rights Reserved.
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

#ifndef _USBSMMU_H_
#define _USBSMMU_H_

#include <smmu.h>
#include <pci/pci.h>

/* Unless otherwise DEBUG is defined, usb_debug macro produces zero code at compilation time */
#ifdef DEBUG
#define USB_DEBUG(fmt, ...) \
	slog2f( usb_slog2_buf_hdl, _SLOGC_USB_GEN, _SLOG_ERROR, "%s : "fmt, __func__, ##__VA_ARGS__);
#else
#define USB_DEBUG(fmt, ...)
#endif

/* size of hash table to be used */
#define HASH_SIZE			128

#define USB_SMMU_SET_HCD(smmu, self)											\
do {																			\
	smmu.flags |= USB_SMMU_DEV_HCD;												\
	smmu.methods = (void *) self;												\
	if (((usb_hcd_self_t *)self)->usb_smmu_get_flags() & USB_SMMU_ENABLED)		\
		smmu.flags |= USB_SMMU_ENABLED;											\
} while (0)

#define USB_SMMU_SET_DCD(smmu, self)											\
do {																			\
	smmu.flags |= USB_SMMU_DEV_DCD;												\
	smmu.methods = (void *) self;												\
	if (((usb_dcd_self_t *)self)->usb_smmu_get_flags() & USB_SMMU_ENABLED)		\
		smmu.flags |= USB_SMMU_ENABLED;											\
} while (0)

typedef struct _usb_smmu_t usb_smmu_t;

/* used to keep track of hashed data */
typedef struct _node {
	uint64_t paddr;
	uint64_t len;
	volatile unsigned refcnt;		/* reference counter to prevent multiple mapping to the same page */
	struct _node *next;				/* pointer to next item from hash bucket */
	unsigned flags;
#define USB_SMMU_MEM_FROM_STACK		0x00000001
} node;

struct _usb_smmu_t {
	unsigned			enabled;	// obsolete
	unsigned			shared;		// whether to use shared smmu object
	struct smmu_object	*obj;		// smmuman data object
	unsigned			phys;		// physical address for mmio
	unsigned			len;		// length of physical address for mmio
	unsigned			flags;		// flag to store extra information (e.g. pci device)
#define USB_SMMU_DEV_PCI			0x00000001
#define USB_SMMU_DEV_MMIO			0x00000002
#define USB_SMMU_DEV_HCD			0x00000004
#define USB_SMMU_DEV_DCD			0x00000008
#define USB_SMMU_ENABLED			0x80000000
	uint8_t				bus;
	uint8_t				dev;
	uint8_t				func;
	unsigned			pagesize;

	volatile unsigned	map_cnt;
	volatile unsigned	unmap_cnt;

	pthread_mutex_t	mutex;
	node *addr_hash[HASH_SIZE];

	void *methods;					// can be hcd or dcd depending on flags
};

/*
 * SMMUMAN support library functions
 */
int	usb_smmu_stack_init(usb_smmu_t *smmu);
int	usb_smmu_stack_fini(usb_smmu_t *smmu);

int	usb_smmu_init(usb_smmu_t *smmu, uint64_t addr, uint64_t size);
int	usb_smmu_fini(usb_smmu_t *smmu, uint64_t addr, uint64_t size);
int	usb_smmu_map(usb_smmu_t *smmu, uint64_t addr, uint64_t size);
int	usb_smmu_unmap(usb_smmu_t *smmu, uint64_t addr, uint64_t size);
void	usb_smmu_set_dev_type(usb_smmu_t *smmu, pci_bdf_t bdf);
int	usb_smmu_add_mmio(usb_smmu_t *smmu, uint64_t addr, uint64_t size, int map);


/* should be moved to io-usb-otg header file */
int iousb_smmu_get_flags( void );
int iousb_smmu_stack_init(usb_smmu_t *smmu);
int iousb_smmu_stack_fini(usb_smmu_t *smmu);
int iousb_smmu_map(usb_smmu_t *smmu, uint64_t addr, uint64_t size);
int iousb_smmu_unmap(usb_smmu_t *smmu, uint64_t addr, uint64_t size);
int iousb_smmu_init(usb_smmu_t *smmu, uint64_t addr, uint64_t size);
int iousb_smmu_fini(usb_smmu_t *smmu, uint64_t addr, uint64_t size);
int	iousb_smmu_add_mmio(usb_smmu_t *smmu, uint64_t addr, uint64_t size, int map);

#endif /* _USBSMMU_H_ */

#if defined(QNXNTO) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/hardware/trunk/lib/usb/public/sys/usb_smmu.h $ $Rev: 977663 $")
#endif
