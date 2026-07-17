/*
 * Copyright (c) 2021, 2025-2026, BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _PCI_GIC_ITS_H_
#define _PCI_GIC_ITS_H_

#include <drvr/hwinfo.h>
#include <sys/cache.h>
#include <sys/neutrino.h>

#include <pci/pci.h>
#include "pci/hw_lib.h"


/*
 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

                        GIC support for HW modules

 This file contains types, defines and prototypes for helper functions for ARM
 GIC v3/4 support within HW modules wishing to make use of those features.
 Specifically it includes support for ITS based LPIs

 They are included by adding a line such as the following to the HW modules
 common.mk file
 EXTRA_SRCVPATH+=$(PROJECT_ROOT)/../src/arm_gic_its

 Note also that the HW module must link with libdrvr and libcache in order to
 resolve the hwi_*() and cache APIs used respectively to obtain the relevant
 ITS information from the hwinfo section of the syspage and to manage any cached
 ITS tables. Add the following lines to the HW module common.mk

 LIBS+=drvrS
 LIBS+=cacheS

 The following includes a breakdown of the design and implementation.
 Because the GIC is a global resource it cannot be solely managed by any one
 subsystem including the PCI subsystem. In order to help coordinate this, the
 following approach will be taken

 First, to recap, the following existing interface is defined between startup
 and the PCI subsystem HW modules

 - startup identifies the interrupts to be used for PCI based MSIs by setting
   the INTR_FLAG_MSI_PCI flag in the startup_intrinfo structure
 - as many contiguous blocks of such interrupts can be identified as PCI MSI
   interrupts
 - these blocks can include GIC SPIs, LPIs (either direct or ITS based) or
   inbound address match (ie. non-GIC) based interrupts. While it is typically
   the case that only one such type of MSI interrupts is available on the
   platform, it is possible for there to be multiple types. An example would be
   a combination of GIC SPIs and LPIs
 - it is left to the HW module writer to decide whether or not multiple types
   will be supported

 For GIC SPI and direct LPIs, MSI vector data is the GIC SPI and/or LPI vector
 number and so this is what is placed into the resource pool. For these MSI
 types, the same MSI vector data is also the IRQ that drivers will attach to.
 The MSI vector address is the GICD_SETSPI_NSR and GICR_SETLPIR register for
 SPIs and direct LPIs respectively. The GICR_SETLPIR is (typically) that for
 PE0 (CPU0) by default.

 For non-GIC (ie. address match) implementations, the MSI vector data represents
 a zero based bit index into one or more MSI status registers and so it is these
 values which are placed into the interrupt resource pool. When an allocation is
 made, we obtain the IRQ (constructed from the startup callouts and intrinfo
 information) which corresponds the allocated MSI vector data for use as the IRQ
 to attach to. The MSI vector address will be the match address programmed into
 the address match hardware

 GIC ITS based LPIs
 ------------------

 For GIC ITS based LPI support, the MSI vector data is a zero based index into
 the Interrupt Translation Table (ITT) and this is what is entered into the
 interrupt resource pool. The MSI vector address will typically be the
 GITS_TRANSLATOR register

 The following additional interface requirements are defined between startup and
 a HW module for ITS use

 - the HW module must allocate the Interrupt Translation Table (ITT) for the
   device and associate it with the DeviceID in the Device Table. This is
   accomplished using the ITS command queue
 - the HW module must add the MSI vector data value to ITE mappings to the ITT
   for each allocated MSI interrupt. This is accomplished using the ITS command
   queue
 - startup will allocate a Device Table and Collection Table and program the
   required properties of these tables into the ITS BASER registers. While it is
   possible for there to be more than one ITS, only one will be used for PCI MSI
   based interrupts and startup will decide which that is
 - startup will convey which ITS instance a HW module should use by adding the
   ITS based address and ITS instance information to the 'hwinfo' section of the
   syspage
 - startup will allocate the memory for the ITS command queue and configure the
   associated ITS registers (ex. CBASER)

 Because the registers containing the Device and Collection Tables will be
 read-only to the PCI subsystem (and any other non-PCI subsystem making use of
 the same ITS), there are no synchronization requirements for access to these
 registers

 The PCI subsystem (and any other non-PCI subsystem making use of the same ITS)
 uses the ITS command queue for management of the Device Table and ITT in order
 to create the interrupt translations for a given device. Therefore access to
 the ITS command queue must be synchronized.

 Because of the relatively sporadic and time limited nature of the required
 access to this queue, the synchronization is most efficiently implemented using
 a globally accessible spinlock (ie. an atomic variable and atomic ops). The
 spinlock will be allocated by startup in a cacheable memory region associated
 with the ITS command queue and appropriate for the platform. The information
 on the location of this spinlock will be communicated along with the ITS
 command queue location and ITS instance in the syspage

 Other Implementation notes/thoughts
 -----------------------------------

 When creating the ITT and adding entries to it, the HW module needs to know the
 collection Table ID. We will currently always expect that startup has created
 a Collection Table with a unity mapping between logical CPU number and ICID.
 That is, CPU 0 will be associated with ICID 0, CPU 1 with ICID 1, etc. The
 appropriate RDBase will be obtained from the GICR registers associated with
 the specific CPU based on its 'smp_hwcoreid'

 In cases where the QNX hypervisor is being used and a PCI device will be passed
 through, it is not an ICID that is required but rather a vPEID.

 While this interface has not yet been designed, some possible choices for
 handling this configuration based on the existing QVM support module interfaces
 for pci_msg_e_ALLOC_IRQ and pci_msg_e_FREE_IRQ messages are as follows
 - the 'type' and 'flags' field of the QVM 'pci_msg_alloc_irq_t' correspond to
   the '_pci_irqType_e' and '_pci_irqAttr_e' types respectively of the HW module
   hw_alloc_irq() function.
 - we can add a new '_pci_irqAttr_e', say _pci_irqAttr_e_QVM, which the HW
   can use to skip adding the ITT entries for the allocated vectors (which it
   would do in a non-hypervisor scenario)
 - it would however allocate the ITT and associated it with the DeviceId. It has
   the platform specific DeviceId information already and it would allow the HW
   module to clean up as it does in a non-virtualized scenario
 - since the vINTID is similar to a pINTID which is what will be returned, QVM
   can then use the VMAPTI command to add the vINTIDs to the vPEID it has
   created for the guest
   **QVM has replicated the '_pci_irqmap_t' type as 'struct msi_intr'
 - the only piece of missing information for QVM is the DeviceID which it will
   need in order to do the VMAPTI. This may require a new message in order to
   obtain it


 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

/* this is the name of the ITS 'hwinfo' tag to look for in the syspage */
#define GIC_ITS_HWINFO_TAGNAME	"GIC_ITS"

/*
 ===============================================================================
 arm_gits_cmds_t

 The following define the set of commands which are handled by the ITS
 These definitions were adapted from aarch64/gic_its.h which are (currently)
 only available in 7.0

*/
#define GITS_CMD_CLEAR		0x04u
 __attribute__((packed,aligned(4)))
struct gits_clear
{
	uint8_t cmd;
	uint8_t resv0[3];
	uint32_t DeviceID;
	uint32_t EventID;
	uint32_t resv1;
	uint64_t resv2[2];
};

#define GITS_CMD_DISCARD	0x0fu
__attribute__((packed,aligned(4)))
struct gits_discard
{
	uint8_t cmd;
	uint8_t resv0[3];
	uint32_t DeviceID;
	uint32_t EventID;
	uint32_t resv1;
	uint64_t resv2[2];
};

#define GITS_CMD_INT		0x03u
__attribute__((packed,aligned(4)))
struct gits_int
{
	uint8_t cmd;
	uint8_t resv0[3];
	uint32_t DeviceID;
	uint32_t EventID;
	uint32_t resv1;
	uint64_t resv2[2];
};

#define GITS_CMD_INV		0x0cu
__attribute__((packed,aligned(4)))
struct gits_inv {
	uint8_t cmd;
	uint8_t resv0[3];
	uint32_t DeviceID;
	uint32_t EventID;
	uint32_t resv1;
	uint64_t resv2[2];
};

#define GITS_CMD_INVALL		0x0du
__attribute__((packed,aligned(4)))
struct gits_invall
{
	uint8_t cmd;
	uint8_t resv0[7];
	uint64_t resv1;
	uint16_t ICID;
	uint8_t resv2[6];
	uint64_t resv3;
};

#define GITS_CMD_MAPC		0x09u
__attribute__((packed,aligned(4)))
struct gits_mapc
{
	uint8_t cmd;
	uint8_t resv0[7];
	uint64_t resv1;
	uint64_t RDbase_and_ICID;
	uint64_t resv2;
};

#define GITS_CMD_MAPD		0x08u
__attribute__((packed,aligned(4)))
struct gits_mapd
{
	uint8_t cmd;
	uint8_t resv0[3];
	uint32_t DeviceID;
	uint8_t size;
	uint8_t resv1[7];
	uint64_t ITT_addr;
	uint64_t resv2;
};

#define GITS_CMD_MAPI		0x0bu
__attribute__((packed,aligned(4)))
struct gits_mapi
{
	uint8_t cmd;
	uint8_t resv0[3];
	uint32_t DeviceID;
	uint32_t EventID;
	uint32_t resv1;
	uint16_t ICID;
	uint8_t resv2[6];
	uint64_t resv3;
};

#define GITS_CMD_MAPTI		0x0au
__attribute__((packed,aligned(4)))
struct gits_mapti
{
	uint8_t cmd;
	uint8_t resv0[3];
	uint32_t DeviceID;
	uint32_t EventID;
	uint32_t pINTID;
	uint16_t ICID;
	uint8_t resv2[6];
	uint64_t resv3;
};

#define GITS_CMD_MOVALL		0x0eu
__attribute__((packed,aligned(4)))
struct gits_movall
{
	uint8_t cmd;
	uint8_t resv0[7];
	uint64_t resv1;
	uint64_t RDbase1;
	uint64_t RDbase2;
};

#define GITS_CMD_MOVI		0x01u
__attribute__((packed,aligned(4)))
struct gits_movi
{
	uint8_t cmd;
	uint8_t resv0[3];
	uint32_t DeviceID;
	uint32_t EventID;
	uint32_t resv1;
	uint16_t ICID;
	uint8_t resv2[6];
	uint64_t resv3;
};

#define GITS_CMD_SYNC		0x05u
__attribute__((packed,aligned(4)))
struct gits_sync
{
	uint8_t cmd;
	uint8_t resv0[7];
	uint64_t resv1;
	uint64_t RDbase;
	uint64_t resv2;
};

typedef union __attribute__((packed,aligned(4)))
{
	uint8_t cmd;	/* command is always in the first byte */
	struct gits_clear gclear;
	struct gits_discard gdiscard;
	struct gits_int gint;
	struct gits_inv ginv;
	struct gits_invall ginvall;
	struct gits_mapc gmapc;
	struct gits_mapd gmapd;
	struct gits_mapi gmapi;
	struct gits_mapti gmapti;
	struct gits_movall gmovall;
	struct gits_movi gmovi;
	struct gits_sync gsync;
} arm_gits_cmds_t;

/* ITS command error numbers */
#define GITS_ERR_INV_DEVICE_OOR			0x010C01u
#define GITS_ERR_INV_UNMAPPED_DEVICE	0x010C04u
#define GITS_ERR_INV_ID_OOR				0x010C05u
#define GITS_ERR_INV_UNMAPPED_INTERRUPT	0x010C07u
#define GITS_ERR_INV_ITE_INVALID		0x010C10u
#define GITS_ERR_INVALL_COLLECTION_OOR	0x010D03u
#define GITS_ERR_INT_ID_OOR				0x010305u
#define GITS_ERR_INT_UNMAPPED_INTERRUPT	0x010307u
#define GITS_ERR_INT_ITE_INVALID		0x010310u
#define GITS_ERR_CLEAR_DEVICE_OOR		0x010501u
#define GITS_ERR_CLEAR_ID_OOR			0x010505u
#define GITS_ERR_CLEAR_UNMAPPED_INTERRUPT 0x010507u
#define GITS_ERR_CLEAR_ITE_INVALID		0x010510u
#define GITS_ERR_VMAPP_VCPU_OOR			0x012911u
#define GITS_ERR_VMAPI_ID_OOR			0x012b05u
#define GITS_ERR_VMAPI_PHYSICALID_OOR	0x012b06u
#define GITS_ERR_VMAPTI_ID_OOR			0x012a05u
#define GITS_ERR_VMAPTI_VIRTUALID_OOR	0x012a13u
#define GITS_ERR_VSYNC_VCPU_OOR			0x012511u
#define GITS_ERR_VSYNC_VCPU_INVALID		0x012514u
#define GITS_ERR_VMOVI_ID_OOR			0x012105u
#define GITS_ERR_VMOVI_PHYSICALID_OOR	0x012106u
#define GITS_ERR_VMOVI_ID_IS_PHYSICAL	0x012115u
#define GITS_ERR_VMOVI_ITEVCPU_INVALID	0x012116u
#define GITS_ERR_VMOVI_CMDVCPU_INVALID	0x012117u

/*
 ===============================================================================
 _pci_arm_gic_its_ctrl_reg_t

 This type represents the layout of the ARM GICv3/4 ITS control registers

*/
typedef struct __attribute__((packed,aligned(4)))
{
	volatile uint32_t CTLR;
	volatile uint32_t IIDR;
	volatile uint64_t TYPER;

	PAD_FROM_TO(0x10, 0x20, reserved1);

	volatile uint32_t implementation_defined_1[8];

	PAD_FROM_TO(0x40, 0x80, reserved2);

	volatile uint64_t CBASER;
	volatile uint64_t CWRITER;
	volatile uint64_t CREADR;

	PAD_FROM_TO(0x98, 0x100, reserved3);

	volatile uint64_t BASER[8];

#if 0
	/*
	 * since we don't actually care about these registers right now, don't
	 * map in the extra 15 4KB pages associated with them
	 */
	PAD_FROM_TO(0x140, 0xC000, reserved4);

	volatile uint32_t implementation_defined_2[4084];

	volatile uint32_t ID[12];
#endif

} _pci_arm_gic_its_ctrl_reg_t;

/*
 ===============================================================================
 _pci_arm_gic_its_trans_reg_t

 This type represents the layout of the ARM GICv3/4 ITS translation registers

*/
typedef struct __attribute__((packed,aligned(4)))
{
	PAD_FROM_TO(0x0, 0x40, reserved1);

	volatile uint32_t TRANSLATER;

#if 0
	/*
	 * since we don't actually care about these registers right now, don't
	 * map in the extra 15 4KB pages associated with them
	 */
	PAD_FROM_TO(0x44, 0x10000, reserved2);
#endif

} _pci_arm_gic_its_trans_reg_t;

/*
 ===============================================================================
 arm_gic_its_lock_t

 This type represents the layout of the ARM GICv3/4 ITS translation registers

*/
typedef struct {
	union {
        struct intrspin int_spin;
        uint_t          atomic_spin;
	} lock;
	int version;
} arm_gic_its_lock_t;

/*
 ===============================================================================
 _pci_arm_gic_its_params_t

 This type can be used to cache parameters for implementations that use an ITS
 so that the information does not need to be repeatedly looked up in the ITS
 registers. Only one of these structures is required per ITS instance

*/
typedef struct
{
	paddr_t its_base_paddr;
	_pci_arm_gic_its_ctrl_reg_t *its_reg_p;	/* pointer to the mmap()'d ITS registers */

	/* pointer to the mapped ITS command queue memory */
	struct
	{
		volatile arm_gits_cmds_t *buf;
		size_t size;	/* total size in bytes of the command queue */
		size_t cmd_size;	/* size of a command */
		uint_t num_q_entries;
		arm_gic_its_lock_t *lock;
		struct cache_ctrl *cache_info;	/* NULL if command queue is mapped PROT_NOCACHE */
		paddr_t paddr;	/* set if using a cached command queue */
	} cmd_q;

	uint_t ite_size;
	struct _its_typer_info_s
	{
		uint_t num_bits;
		uint32_t mask;		/* 5 bit field for a maximum of 32 bits */
	} event_id;
	struct _its_typer_info_s device_id;

} _pci_arm_gic_its_params_t;

/*
 ===============================================================================
 _pci_arm_gic_itt_info_t

 For HW modules which support ITS based LPIs, this structure can be used to keep
 track of the ITT information on a per device basis

*/
typedef struct
{
	uint32_t device_id;
	struct	/* this sub-structure holds information about the allocated ITT */
	{
		paddr_t paddr;
		void *vaddr;	/* needed for munmap() */
		size_t size;	/* in bytes for munmap() */
		/*
		 * the following 3 fields provide the HW module with some control over
		 * the pool of memory an ITT is allocated from as well as the protection
		 * and mapping flags that are used in the call to mmap() to obtain that
		 * memory. An ITT is allocated when gic_its_dte_add() is called
		 *
		 * If 'prot_flags' or 'mmap_flags' are 0, they will be ignored otherwise
		 * they will be used so be careful! This also means PROT_NONE is ignored
		 * The ITT is not accessed directly except to ensure it is zeroed after
		 * allocation so the default protection flags are PROT_READ | PROT_WRITE | PROT_NOCACHE
		 * The default mapping and protection flags should almost always be used
		 * and so these fields should normally be left as 0
		 *
		 * 'mem_pool', if non NULL should specify a valid typed memory pool as
		 * reported in the syspage asinfo. For example, to force the ITT allocations
		 * to come from below 4G memory, 'mem_pool' can be set to "sysram&below4G"
		 */
		int_t prot_flags;
		int_t mmap_flags;
		char *mem_pool;
		struct cache_ctrl *cache_info;	/* NULL if ITT mapped PROT_NOCACHE */
	} itt;

} _pci_arm_gic_itt_info_t;


/* prototypes */
/*
 ===============================================================================
 gic_its_get_instance

 If there is an entry in the 'hwinfo' section of the syspage for an ITS, then
 any LPIs will be ITS based and so we will return the ITS instance for PCI HW
 modules to use for them.
 Otherwise return -1 indicating that any LPIs are direct LPIs

*/
int_t gic_its_get_instance(void);

pci_err_t gic_its_dte_add(const uint_t its_num, _pci_arm_gic_itt_info_t * const itt_info, const uint_t nirq);
pci_err_t gic_its_dte_del(const uint_t its_num, _pci_arm_gic_itt_info_t * const itt_info);
pci_err_t gic_its_ite_add(const uint_t its_num, _pci_arm_gic_itt_info_t * const itt_info, const uint_t nirq, const _pci_irqmap_t * const irq_map);

#endif	/* _PCI_GIC_ITS_H_ */
