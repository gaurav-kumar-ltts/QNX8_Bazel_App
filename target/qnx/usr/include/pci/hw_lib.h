#ifndef _HW_LIB_H_
#define _HW_LIB_H_
/*
 * Copyright (c) 2012, 2021, 2025-2026, BlackBerry Limited.
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

#include <pthread.h>
#include <sys/mman.h>
#include <assert.h>

#include <pci/pci.h>
#include <pci/pci_event.h>
#include <pci/rsrcdb.h>

/*
 * INTR_FLAG_MSI_PCI and INTR_FLAG_MSI_IS_PCI() were defined and added to
 * sys/syspage.h after the 7.1 release to replace INT_FLAG_MSI. Neither of these
 * values will be defined for any environment prior to that. The PCI subsystem
 * has now been updated to make use of these 2 defines in all environments and
 * so when compiling against older sys/syspage.h files, make it all look the same
*/
#ifndef INTR_FLAG_MSI_IS_PCI
#ifndef INTR_FLAG_MSI_PCI
#define INTR_FLAG_MSI_PCI		0x0400U		/* same as previous INTR_FLAG_MSI */
#endif
/*
 * MSI type determination macro for PCI ('struct intrinfo_entry *' is the arg)
*/
#define INTR_FLAG_MSI_IS_PCI(_e_)	((((unsigned int)(_e_)->flags) & 0x0700) == INTR_FLAG_MSI_PCI)
#endif	/* INTR_FLAG_MSI_IS_PCI */

#if !defined(ROUND_UP) && !defined(ROUND_DN)
/* we use typeof() to ensure that 64bit rounding works properly */
#define ROUND_UP(x, a) ((typeof(x))(((x) + ((typeof(x))(a)-1)) & ~((typeof(x))(a)-1)))
#define ROUND_DN(x, a) ((typeof(x))((x) & ~((typeof(x))(a)-1)))
#endif	/* !defined(ROUND_UP) && !defined(ROUND_DN) */

#define PAD_FROM_TO(_off_from_, _off_to_, _pad_name_) \
		volatile uint32_t _pad_name_[((_off_to_) - (_off_from_)) / sizeof(uint32_t)]

#define KiB(_x_)	((uint64_t)(_x_) * 1024)
#define MiB(_x_)	((uint64_t)KiB(_x_) * 1024)
#define GiB(_x_)	((uint64_t)MiB(_x_) * 1024)

/*
 ===============================================================================
 HW_USEC_DELAY
 HW_MSEC_DELAY

 micro and milli second delay macros

*/
#define HW_USEC_DELAY(_d_)		hw_usec_delay((_d_))
#define HW_MSEC_DELAY(_d_)		hw_usec_delay((_d_) * 1000)

/*
 ===============================================================================
 CLIENT_ISR_ACCESS_REQ

 This macro can be used to test for ISR accesses within the HW module hw_rd()
 and hw_wr() functions

*/
#define CLIENT_ISR_ACCESS_REQ(__attr__) \
		( \
			((get_pci_runtime_flags() & pci_runtime_flags_e_SERVER) == 0) && \
			(((__attr__) & _pci_accessAttr_e_ISR) != 0) \
		)

/*
 * convert the RID portion of the 'bdf' into a value suitable for use as an
 * index into a 'bdf_hw_array'. This macro assumes that each array element holds
 * a 32KB mapping of all 8 functions for a given device on a given bus segment
*/
#define PCI_BD_IDX(_bdf_)		(PCI_BDF_RID((_bdf_)) >> 3)

/* All GIC interrupt vectors >= 8192 are considered LPIs. Below are SPIs */
#define ARM_GIC_LPI_FIRST	8192


/*
 ===============================================================================
 _pci_link_state_e

 This is an internal type used by software to record and determine the state of
 a PCI bus/PCIe link. It is not meant to map to any of the LTSSM states as
 defined in the PCI Express specification for example. Instead it defines "macro"
 states which are of use in managing accesses to devices downstream of those
 links

 Note that this type will be limited to 8 bits and the '_pci_link_state_t' type
 will be used to store the '_pci_link_state_e' within the HW module shared
 memory segment

 When checking whether or not a link is UP or not, it will be sufficient to test
 that the return value from get_link_state() is equal to _pci_link_state_UP. If
 not, then the link is down and additional information may be present as to why
 so for example, the relative permanence could be determined and used to wait

*/
typedef enum
{
	/* bit 0 of this type identifies 2 main states, UP = 0b0 and DOWN = 0b1 */
	_pci_link_state_UP = 0,
	_pci_link_state_DN = 1,

	pci_link_state_mask = 0x1,

	/*
	 * when the link is DOWN, additional values may identify the reason as follows
	 *
	 * INIT       - this will be the state after HW module initialization prior to
	 *				enumeration
	 * OFFLINE    - the link is not usable
	 * RESETTING  - link is in the process of resetting
	 * RETRAINING - the link is in the process of retraining
	 * NOT_ACTIVE - the link failed to come up after transitioning to the down
	 *				state as a result of a reset, retraining, etc
	 */
	_pci_link_state_INIT = (_pci_link_state_DN | (1u << 1)),
	_pci_link_state_OFFLINE = (_pci_link_state_DN | (2u << 1)),
	_pci_link_state_RESETTING = (_pci_link_state_DN | (3u << 1)),
	_pci_link_state_RETRAINING = (_pci_link_state_DN | (4u << 1)),
	_pci_link_state_NOT_ACTIVE = (_pci_link_state_DN | (5u << 1)),

} _pci_link_state_e;
typedef uint8_t _pci_link_state_t;

/*
 ===============================================================================
 _pci_accessAttr_e

*/

typedef enum
{
	_pci_accessAttr_e_NORMAL = 0,

	_pci_accessAttr_e_CHECK = (1u << 0),		// just do an access check
	_pci_accessAttr_e_ISR = (1u << 1),		// the access is from an ISR

	/* the access is to normally protected offset 0x34 */
	_pci_accessAttr_e_OFFSET_34 = (1u << 2),

} _pci_accessAttr_e;

/*
 ===============================================================================
 _pci_irqType_e
 _pci_irqAttr_e

 IRQ types and attributes

*/
typedef enum
{
	/* types are specified as one of the following values */
	_pci_irqType_e_MSG,		// message based interrupts (like MSI/MSI-X or others)
	_pci_irqType_e_PIN,		// pin based interrupts

	_pci_irqType_e_DIRECT,	// interrupt sources directly connected to an interrupt controller

	_pci_irqType_e_NONE = -1,

} _pci_irqType_e;

typedef enum
{
	/* attributes are specified as a bitwise inclusive OR of the following values */
	_pci_irqAttr_e_NONE = 0,

	_pci_irqAttr_e_CONTIG = (1u << 0),		// interrupts must be a contiguous series (ie. 1,2,3,..)

} _pci_irqAttr_e;

/*
 ===============================================================================
 irq_pin_t

 This structure defines the information required by the '_pci_irqType_e_PIN'
 interrupt type

*/
typedef struct
{
	uint32_t val;
} irq_pin_t;

/*
 ===============================================================================
 irq_msg_t

 This structure defines the information required by the '_pci_irqType_e_MSG'
 interrupt type

*/
typedef struct
{
	uint64_t addr;
	uint32_t data;
} irq_msg_t;

/*
 ===============================================================================
 _pci_irqmap_t

 This structure defines the mapping between an internal, hardware dependent
 system interrupt vector and the IRQ used in calls to InterruptAttach()

*/
typedef struct
{
	pci_irq_t irq;	// system IRQ to InterruptAttach() to
	union
	{
		irq_pin_t pin;
		irq_msg_t msg;
	} vector;
} _pci_irqmap_t;

/*
 ===============================================================================
 _pci_irqSubType_e

 This type is used to further qualify the '_pci_irqType_e' and is meant only for
 use in HW modules since code external to HW modules (currently) only needs to
 differentiate the '_pci_irqType_e'
 A change to consolidate the type and subtype could/should occur in the future
 however managing that change is not warranted or justified at this point

*/
typedef enum
{
	_pci_irqSubType_e_INVALID = -1,

_pci_irqSubType_e_first = 1,

	/* ARM GIC vector types */
arm_gic_vector_type_e_first = _pci_irqSubType_e_first,
	_pci_irqSubType_e_ARM_GIC_SPI = arm_gic_vector_type_e_first,
	_pci_irqSubType_e_ARM_GIC_LPI,
arm_gic_vector_type_e_end,
arm_gic_vector_type_e_last = arm_gic_vector_type_e_end - 1,

	/* vector type for inbound address match logic */
	_pci_irqSubType_e_ADDR_MATCH,

	/* other future types */


_pci_irqSubType_e_end,
_pci_irqSubType_e_last = _pci_irqSubType_e_end - 1,

} _pci_irqSubType_e;

/*
 ===============================================================================
 _pci_asmap_t

*/
typedef struct
{
	node_t hdr;		// used for the free list when devices are live inserted/removed
	pci_ba_t ba;
} _pci_asmap_t;

/*
 ===============================================================================
 _pci_evt_irqmap_t

 This type is used by the 'hwmod_api_t.map_event_irq' callin to allow the HW
 module to provide non-standard and/or non specification defined event to IRQ
 mappings/overrides for things such as link, slot, power management, error
 reporting or other types of events. It is also used to provide information
 on the specification defined interrupt mechanisms as well

 See 'hwmod_api_t.map_event_irq' callin description below for details

*/
typedef struct
{
	pci_event_type_e event;
	struct
	{
		_pci_irqmap_t map;
		_pci_irqType_e type;
		_pci_irqSubType_e subtype;
		_pci_irqAttr_e attr;
	} intsrc;
	struct _pci_evt_irqmap_extra_s
	{
		pci_version_t version;
		union
		{
			void *data;
		} u;
	} *extra;	/* just in case */

} _pci_evt_irqmap_t;

#define _PCI_EVT_IRQMAP_T_INITIALIZER(_evt_, _extra_) \
		{ \
			.event = (_evt_), \
			.intsrc.type = _pci_irqType_e_NONE, \
			.intsrc.subtype = _pci_irqSubType_e_INVALID, \
			.intsrc.attr = _pci_irqAttr_e_NONE, \
			.intsrc.map.irq = -1, \
			.extra = (_extra_), \
		}

/*
 ===============================================================================
 hw_shm_t

 A single shared memory page is created that is used by the HW dependent module
 to maintain shared process data. This includes the configuration space access
 lock as well as data structures for allowing device accesses to be blocked in
 the case of the server dealing with device removals of power state changes.

 A single variable 'hw_shm' exists in the context of all processes using the
 PCI server

 This structure overlays a shared memory object at offset 0 and is therefore
 page aligned

 Based on a typical 32 byte cache line, we force the 'cfg_reg_lock' and the
 'cfg_access_sem' into separate lines. The reason is to try and avoid the
 invalidation of one because of the other in an SMP environment
*/
typedef struct
{
	/* 32 byte alignment (implied) (32 bytes total) */
	volatile uint32_t cfg_reg_lock;
	volatile uint32_t cfg_reg_lock_contention_cnt_lo;
	volatile uint32_t cfg_reg_lock_contention_cnt_hi;
	uint32_t reserved1[3];
	volatile uint32_t init_complete_signature;
	bool_t off_34;
	uint8_t reserved2[3];
#define HW_INIT_COMPLETE_SIGNATURE		((uint32_t)0x4C535351)

	/* 32 byte alignment (32 bytes total) */
	volatile uint32_t cfg_access_sem;
	/* the number of times hw_initiate_hold_off() has been called */
	volatile uint32_t cfg_nested_holdoff_count;
	uint32_t reserved3[6];

	/*
	 * server_info_s
	 * When a pci-server instance successfully registers, its 'pid_t' will be
	 * recorded in the 'pid[]' array. Similarly, when it de-registers, its
	 * 'pid_t' will be removed. This array is indexed by 'server_id' and because
	 * server IDs range from 1 thru 255, for simplicity, pid[0] will be set
	 * invalid
	 * 32 byte alignment (4 + 4 + (256 * 4) = 1032 bytes total)
	 */
	__attribute__((aligned(32)))
	struct server_info_s
	{
		volatile uint32_t rdwr_lock;
		uint8_t num_entries;	/* can be no more than the max permitted by pci_server_id_t */
		uint8_t reserved[3];
		pid_t pid[PCI_SERVER_ID_MAX + 1];
	} server_info;

	/* link state (256 * 1 = 256 bytes total) */
	volatile _pci_link_state_t link_state[PCI_MAX_BUSES / sizeof(_pci_link_state_t)];

	/* 16 bytes */
	struct
	{
		pthread_mutex_t mutex;
		pthread_cond_t cond;
	} hold_off;
	/* (32 + 1024 = 1056 bytes total) */
	uint32_t bus_hold_off[PCI_MAX_BUSES / (sizeof(uint32_t) * 8)];
	uint32_t dev_hold_off[PCI_MAX_BUSES];

	/*
	 * segment_info_s
	 * For each segment supported by the HW module (there can be a maximum of
	 * PCI_MAX_BUSES), we record which 'server_ID' is managing that segment. The
	 * 'server_id' is an index into the 'server_info_s.pid[]' array. It is HW
	 * module dependent how the 'segment_info.ctrl[]' array is indexed wrt how
	 * the BDF space within a partition is distributed among the supported
	 * controllers
	 * 32 byte alignment (4 + 4 + (256 * 3) =  776 bytes total)
	 */
	__attribute__((aligned(32)))
	struct segment_info_s
	{
		volatile uint32_t rdwr_lock;
		uint32_t num_entries;
		struct seg_ctrl_info_s
		{
			pci_server_id_t server_id;
			struct
			{
				/*
				 * these next 2 values record how the BDF space is distributed
				 * across the number of controllers within a partition. While
				 * 'first' is the same as the Root Port 'primary bus number',
				 * 'last' is not necessarily the same as the Root Port
				 * 'subordinate bus number' but rather is 1 less than the next
				 * segments 'first', should it exist
				 * An invalid/empty entry is denoted by first > last
				 */
				uint8_t first;
				uint8_t last;
			} bus;
		} ctrl[PCI_MAX_BUSES];
	} segment_info;
	/*
	 * this lock can be used to ensure that the 'segment_info' is fully
	 * initialized by only one pci-server instance for all segments. It is
	 * different than the 'rdwr_lock' above which is used to ensure atomicity of
	 * access to the 'segment_info' across a single function call. Since it will
	 * only be used once at initialization time, we won't worry about cache
	 * alignment. Use the hw_wrlock()/hw_wr_unlock() functions
	 */
	volatile uint32_t seg_info_init_lock;

	/* this counter is used to provide a partition unique pci_err_record_id_t' */
	volatile uint32_t pci_err_record_id;

	uint64_t last[0];

	/* from 'last' to the end of the shared memory segment can be used by HW modules */

} hw_shm_t;

/*
 ===============================================================================
 bdf_hw_map_t

 This structure is used to map a BDF to a pointer which will allow memory
 mapped accesses to the configuration region. A value of BDF_HW_MAP_IO indicates
 that there is no memory mapped access to the configuration space. A value of
 BDF_HW_MAP_UNKNOWN indicates that it has not yet been determined whether the
 region is accessible by memory mapped accesses

 If a particular hardware implementation does not (or will not) support memory
 mapped configuration space accesses, an array of this type is not required

 Typical use is to declare an array (ex. bdf_hw_array[]) of 'bdf_hw_map_t'
 structures to hold the mappings on a per BD (ie Bus/Device) basis and each
 mapping will be for all 8 functions, so 32KB in size. The PCI_BD_INDX macro
 below can then be used to generate the index in the 'bdf_hw_array[]'

*/
#define BDF_HW_MAP_UNKNOWN	NULL	/* allows 'bdf_hw_array' to be a .bss variable */
#define BDF_HW_MAP_MMAP
#define BDF_HW_MAP_IO		((void *)-1)

typedef struct
{
	void *cfgmem_base;
} bdf_hw_map_t;

/*
 ===============================================================================
 pci_pmType_e

 For the Low Power support.

*/
typedef enum
{
	pci_pmType_e_OFF = 1,
	pci_pmType_e_SUSPEND_PHASE_1,
	pci_pmType_e_SUSPEND_PHASE_2,
	pci_pmType_e_RESUME_PHASE_1,
	pci_pmType_e_RESUME_PHASE_2,
	pci_pmType_e_ON,

pci_pmType_e_end,
pci_pmType_e_last = pci_pmType_e_end - 1,
} pci_pmType_e;

/*
 ===============================================================================
 intrinfo_entry_type_e

 Used with find_vec_entry() to allow for an intrinfo entry to be found based on
 whether its a match with the 'vector_base', the 'cpu_intr_base' or the
 'cascade_vector' field respectively
 The *_RANGE selections match if <vector> is within the first and last of the
 specified range

*/
typedef enum
{
	intrinfo_entry_type_e_BASE,
	intrinfo_entry_type_e_BASE_RANGE,
	intrinfo_entry_type_e_CPU,
	intrinfo_entry_type_e_CPU_RANGE,
	intrinfo_entry_type_e_CASCADE,
} intrinfo_entry_type_e;

/*
 ===============================================================================
 pci_server_callbackType_e

 A list of callback functions to support

*/
typedef enum
{
	pci_server_callbackType_e_SET_POWER_MODE = 1,
	pci_server_callbackType_e_GET_DO_BUS_CFG = 2,

pci_server_callbackType_e_end,
pci_server_callbackType_e_last = pci_server_callbackType_e_end - 1,
} pci_server_callbackType_e;

/*
 ===============================================================================
 pci_hwmod_vm_context_e

 This type defines the different Virtual Machine contexts which a HW module can
 use to check its execution environment with the in_guest_vm_context().
 One or more contexts can be checked by OR'ing in the various values

*/
typedef enum
{
	pci_hwmod_vm_context_QNX = (1u << 0),
	pci_hwmod_vm_context_KVM = (1u << 1),
	pci_hwmod_vm_context_QEMU = (1u << 2),
	pci_hwmod_vm_context_RTS = (1u << 3),

	pci_hwmod_vm_context_ANY =
	(
		pci_hwmod_vm_context_QNX |
		pci_hwmod_vm_context_KVM |
		pci_hwmod_vm_context_QEMU |
		pci_hwmod_vm_context_RTS
	),
} pci_hwmod_vm_context_e;

/*
 ===============================================================================
 _pci_bar_t

 Type to hold a base address register value

*/
typedef uint32_t	pci_bar_t;

/*
 ===============================================================================
 pci_csd_t

 This type is used by the find_csd_assignment() API to return the chassis, slot
 and device number information for a chassis slot record

 It is encoded into a 32 bit unsigned integer as follows

	 xxxx xxxx xxxd dddd cccs ssss ssss ssss
	                    {_____ pci_cs_t ____}

*/
typedef uint32_t	pci_csd_t;

/*
 ===============================================================================
 hwmod_api_t

 This is the structure which provides the access API's for the HW dependent
 modules of the PCI server

 In order to allow future extensions and retain backwards compatibility, this
 structure can only ever be extended. Fields can never be removed or reordered.
 The 'struct_size' field ensures this compatibility with the PCI library as
 follows.
	 - If this structure is extended and used with an existing libpci.so, the
	   new fields will not be known to libpci.so and hence not used but the
	   interface will continue to function properly since libpci.so idea of
	   sizeof(hwmod_api_t) will be <= 'struct_size' of the new structure
	 - If this structure is extended and a new libpci.so delivered but that
	   library is used with an older HW dependent module, libpci.so's idea of
	   sizeof(hwmod_api_t) will be > 'struct_size' of the old HW dependent
	   module and hence will be rejected

 So, if the API's for a new HW dependent module are extended, that new module
 can be used with an existing libpci.so, however none of the new features of
 that HW dependent module will be utilized. If the API's for a new HW dependent
 module are extended and a new libpci.so provided which utilizes those new
 API's, the new libpci.so can only be used with a new HW dependent module, which
 is exactly what one would expect.

*/
typedef struct
{
	uint_t struct_size;
	pci_version_t (*mod_version)(void);
	bool_t (*mod_compat)(const version_typecheck_e check_type, const pci_version_t version);
	/*
	 * server_register() is used by pci-server instances to register and
	 * de-register information about them. This will be an atomic operation
	 * (wrt other pci-server instances) in order to ensure 'pci_server_id_t'
	 * uniqueness. This callin is called during the HW module load process just
	 * before HW_MODULE_INITFN and gives the HW module the opportunity to
	 * implement or reject support for the segmentation portion of the PCI
	 * Hierarchy and Segmentation functionality. It can also be used to
	 * de-register itself and remove the entry in 'hw_shm' in server atexit()
	 * processing
	 */
	pci_err_t (*server_register)(const _pci_server_info_t * const server_info);

	/*
	 * server_info_get() is used to obtain information on the currently registered
	 * pci-server instances. If <nsi> is non NULL and <server_info> is NULL, this
	 * function will return the number of pci-server instances currently registered.
	 * Otherwise <nsi> should point to a value which represents the size of the
	 * <server_info> array to be filled in. If more server instances exist than
	 * there is space in <server_info>, the 2's complement of the number that
	 * remain will be returned in the location pointed to by <nsi>. In all of
	 * the above, the <req_type> should be 'pci_reqType_e_UNSPECIFIED'. This
	 * function can also be used to obtain the '_pci_server_info_t' for specific
	 * server ID's. In this case, the <server_info> array should be initialized
	 * with the 'pci_server_id_t' of interest and <req_type> should be set to
	 * 'pci_reqType_e_MANDATORY'. More generically, this function operates similar
	 * to pci_device_read_ba|irq()
	 */
	pci_err_t (*server_info_get)(int_t * const nsi, _pci_server_info_t * const server_info, const pci_reqType_t req_type);

	/*
	 * server_id_get() will return the 'pci_server_id_t' for the server instance
	 * which handles the segment hierarchy which contains the device <bdf> or
	 * pci_server_id_INVALID
	 */
	pci_server_id_t (*server_id_get)(const pci_bdf_t bdf);

	pci_err_t (*cfg_rd)(const pci_bdf_t bdf, const uint_t offset, const uint_t size, uint8_t * const buf, const _pci_accessAttr_e accessAttr);
	pci_err_t (*cfg_wr)(const pci_bdf_t bdf, const uint_t offset, const uint_t size, uint8_t * const buf, const _pci_accessAttr_e accessAttr);
	pci_err_t (*alloc_irq)(const pci_bdf_t bdf, const _pci_irqType_e irq_type, const _pci_irqAttr_e irq_attr, uint_t * const nirq, _pci_irqmap_t * const irq_map);
	pci_err_t (*free_irq)(const pci_bdf_t bdf, const _pci_irqType_e irq_type, const uint_t nirq, _pci_irqmap_t * const irq_map);
	pci_err_t (*alloc_as)(const pci_bdf_t bdf, const pci_asType_e as_type, const pci_asAttr_e as_attr, const uint64_t as_size, _pci_asmap_t * const as_map);
	pci_err_t (*resv_as)(const pci_bdf_t bdf, _pci_asmap_t * const as_map);
	pci_err_t (*free_as)(const pci_bdf_t bdf, _pci_asmap_t * const as_map);
	pci_err_t (*map_as)(const pci_bdf_t bdf, const pci_ba_t * const as, pci_ba_t * const as_xlate);

	pci_err_t (*add_device_hold_off)(const pci_bdf_t bdf);
	pci_err_t (*remove_device_hold_off)(const pci_bdf_t bdf);
	pci_err_t (*initiate_hold_off)(void);
	pci_err_t (*release_hold_off)(void);

	pci_csd_t (*find_csd_assignment)(const pci_csd_t csd, pci_vid_t const vid, pci_did_t const did, uint_t const idx);

	/*
	 * reset callout processing (see also msg_device_reset() comments)
	 *
	 * If this callout is implemented, it will be called on every phase of reset
	 * processing so that the HW dependent module can manage any HW specific
	 * requirements. The 'pci_err_t' returned from this function will effect the
	 * reset processing sequence as follows
	 *
	 * - if PCI_ERR_OK is returned, reset processing will continue
	 * - if PCI_ERR_ENOTSUP is returned from any phase other than
	 *   _pci_resetPhase_e_CHECK_SUPPORTED, reset processing will continue as
	 *   if PCI_ERR_OK had been returned
	 * - if any error other than those mentioned above is returned from any
	 *   phase other than _pci_resetPhase_e_CHECK_SUPPORTED, reset processing
	 *   will be terminated
	 *
	 * Therefore, if a HW dependent module does not support any HW module
	 * specific reset types and is not required to perform any HW specific
	 * processing during any phase of reset processing, PCI_ERR_OK should be
	 * returned for every phase except _pci_resetPhase_e_CHECK_SUPPORTED and
	 * PCI_ERR_ENOTSUP should be returned for _pci_resetPhase_e_CHECK_SUPPORTED.
	 * Or better yet, leave this callout entry NULL to obtain this default
	 * behaviour
	 *
	 * If HW specific reset processing is required, but the HW module does not
	 * support any HW specific reset types, then the result of that processing
	 * should be returned. Any return other than PCI_ERR_OK and PCI_ERR_ENOTSUP
	 * will terminate the reset processing. PCI_ERR_ENOTSUP should be returned
	 * for _pci_resetPhase_e_CHECK_SUPPORTED for non HW specific reset types
	 *
	 * If a HW dependent module does support HW specific reset types then the
	 * result of that processing should be returned. When called for a HW
	 * specific reset type, the first call will be with phase
	 * _pci_resetPhase_e_CHECK_SUPPORTED to allow this callout to identify
	 * whether or not the specific reset type is supported. If it is (PCI_ERR_OK
	 * returned) then all remaining calls will be with phase
	 * _pci_resetPhase_e_UNSPECIFIED
	 *
	 * HW modules are free to define what the reset processing will do for any
	 * reset type of 'pci_resetType_e_hw_specific_first' and above. In addition,
	 * HW modules may want to consider supporting pre-defined HW reset types
	 *
	 * Pre-defined, non-specification reset types
	 * ------------------------------------------
	 *
	 * pci_resetType_e_SEGMENT
	 *
	 * This pre-defined reset type is defined in order to assist with the reset
	 * of the segment hierarchy originating from and including the Root Port
	 * and not just the devices below the Root Port (as would be the case for
	 * a normal BUS reset)
	 *
	 * Here is the flow as seen by the HW module 'reset' callin for a segment
	 * reset issued as pci_device_reset(<hdl for RP>, pci_resetType_e_SEGMENT)
	 *
	 * 1. the HW module 'reset' callin will first be called with phase
	 *	  '_pci_resetPhase_e_CHECK_SUPPORTED', reset type 'pci_resetType_e_SEGMENT'
	 *	  and the RP bdf. PCI_ERR_OK should be returned to indicate support,
	 *	  otherwise PCI_ERR_ENOTSUP to terminate the reset sequence
	 * 2. the HW module 'reset' callin will then be called with phase
	 *	  '_pci_resetPhase_e_UNSPECIFIED', reset type 'pci_resetType_e_SEGMENT'
	 *	  and the RP bdf. The HW module may choose to initiate a reset of the
	 *	  Root Port at this time or it may defer until phase 1 of step 3. If
	 *	  any server modules are being used in the system that need to save
	 *	  registers in the downstream devices prior to the actual reset AND the
	 *	  reset of the Root Port will cause those downstream devices to also be
	 *	  reset or otherwise become inaccessible, then the reset of the Root
	 *	  Port should be deferred until phase 1 of step 3. Ultimately it is the
	 *	  responsibility of the HW module to ensure proper functionality in all
	 *	  reset scenarios if supporting non-specification defined or HW specific
	 *	  resets
	 * 3. the HW module 'reset' callin will then be called for all phases for
	 *	  reset type pci_resetType_e_BUS and RP bdf. This is almost identical
	 *	  to the case of a BUS reset of the downstream devices with the
	 *	  exception that the <bdf> parameter to the 'reset' callin will be for
	 *	  the RP instead of the immediate downstream device. The RP bdf and/or
	 *	  the occurrence of step #2 will allow the HW module to differentiate
	 *	  between an actual BUS reset of downstream devices and the full segment
	 *	  reset (including the RP)
	 *
	 * See also pci/pci.h
	 *
	 */
	pci_err_t (*reset)(const pci_resetType_e reset_type, const _pci_resetPhase_e phase, const pci_bdf_t bdf, uintptr_t extra);

	/* for processing of [rbar] section settings in a HW config file */
	pci_err_t (*check_rbar_override)(const pci_bdf_t bdf, const uint_t bar_num, pci_ba_val_t * const size, uintptr_t extra);

	/*
	 * set_link_state
	 * get_link_state
	 *
	 * These functions will be used throughout the PCI server and modules to
	 * globally manage the state of the PCI bus/PCIe link. Currently, each HW
	 * module implements this using a process global variable however this state
	 * is system global and therefore the state information needs to be stored
	 * globally in HW shared memory segment
	 *
	 * Implementation Details
	 * ----------------------
	 * Typically all that is required by HW modules is to know whether or not
	 * the link is up or down in order to allow or prevent an access.
	 * For non HW modules, all we really need to be able to do is to set the
	 * link state to up or down during things like device removal, reset, link
	 * state change events, etc however in order to try and help future proof
	 * these API's, they will allow for specifying an actual link state instead
	 * of just a boolean value indicating whether or not the link is up
	 * When setting or retrieving the link state, the 'link_num' should be the
	 * secondary bus number of the bridge or the PCI_BUS() of the device BDF
	 *
	 * When updating the link state, set_link_state() will return PCI_ERR_OK if
	 * the update is the current link state otherwise PCI_ERR_EAGAIN will be
	 * returned. It is the callers responsibility to determine, what if any
	 * actions are required when PCI_ERR_OK is not returned. In general, the
	 * actual link state should not be assumed
	 *
	 */
	pci_err_t (*set_link_state)(const uint_t link_num, const _pci_link_state_e state);
	_pci_link_state_e (*get_link_state)(const uint_t link_num);

	/*
	 * map_event_irq
	 *
	 * Background and Purpose of this callin
	 * -------------------------------------
	 * PCI specification defined events such as link, slot, power management,
	 * hotplug error reporting (ex. AER), etc all report events using a
	 * specification defined mechanism.
	 * For example, all link events (up, down, bandwidth change) are reported
	 * with the same IRQ used to report any status register change. The same
	 * IRQ is also used for slot, power management and hotplug events if they
	 * are supported. Similarly, PCIe error events (correctable, uncorrectable,
	 * fatal) are all reported with a single interrupt defined in the AER
	 * capability register set
	 *
	 * Some platforms do not make use of these specification defined mechanisms
	 * and instead use a proprietary and/or platform specific mechanism which
	 * may also map each event type to a separate and platform specific interrupt
	 * vector instead of using 1 interrupt vector for one or more class of
	 * interrupts
	 *
	 * This callin is provided to accommodate such configurations by allowing
	 * event handling modules to obtain the platform specific mapping of events
	 * which can be reported to the platform specific interrupt vectors actually
	 * used for reporting those events in a generic fashion
	 *
	 * Calling Context
	 * ---------------
	 * This callin is currently executed in the context of the PCI server
	 * process when one of the server modules used for handling events is loaded.
	 * The server module loading is done as part of the final stages of PCI server
	 * initialization and the callin is used to allow the HW module to provide
	 * interrupt vector overrides for those vectors that would have otherwise
	 * been determined using the specification defined mechanisms. If implemented,
	 * and once the overrides have been determined, there is typically no need
	 * for this callin to be executed again however the interface is designed
	 * such that it can be called at any time. This callin API is analogous to
	 * the pci_device_read_irq() function which device drivers use to determine
	 * which IRQs they should attach too for device specific events
	 *
	 * API Usage
	 * ---------
	 * [NOTE]
	 *		this section is specifically concerned with the callin API, the
	 *		expected input and output parameter values and the interpretation
	 *		of returned error codes and information. Of equivalent importance is
	 *		the following section regarding interrupt behaviour (ie. startup
	 *		callouts) and other expectations of the platform hardware
	 *
	 * The caller allocates an 'evt_irq_map[]' array sized for the number of
	 * events that should be checked by the HW module. For each element, the
	 * caller will set the '_pci_evt_irqmap_t.event' field to the event which
	 * should be checked. The HW module will fill in the '_pci_evt_irqmap_t.intsrc'
	 * for <nevts> elements of the 'evt_irq_map[]' array
	 *
	 * If the event uses an alternate interrupt vector or the specification
	 * defined mechanism is implemented, the '_pci_evt_irqmap_t.intsrc.map' will
	 * contain the mapping information and '_pci_evt_irqmap_t.intsrc.type' will
	 * be set to the appropriate type based on what type of interrupt it is.
	 * This will usually be _pci_irqType_e_DIRECT but could also be
	 * _pci_irqType_e_MSG/PIN for information about events which do actually use
	 * the specification defined mechanisms
	 *
	 * ** IMPORTANT **
	 * The interrupt type returned should always be the same. That is, the
	 * device for which the events apply will report the occurrence of those
	 * events using the specification defined mechanism (which can either be
	 * message based or INTPIN based) or they can be reported using a platform
	 * specific mechanism using the _pci_irqType_e_DIRECT type but can never be
	 * a mix
	 *
	 * If the type returned is _pci_irqType_e_MSG, the 'intsrc.map.irq' field
	 * should contain the MSI/MSI-X interrupt index for the interrupt and not
	 * a specific IRQ. The IRQ will be determined when the capability is enabled
	 *
	 * If the type returned is _pci_irqType_e_PIN, the 'intsrc.map.irq' field
	 * should contain the INTPIN value 1 thru 4 inclusive and not a specific
	 * IRQ. It is typical that an event reporting agent usually supports only
	 * a single INTPIN interrupt and so the same value (usually 0) should be
	 * returned for all events since they all report on the same INTPIN interrupt
	 *
	 * The '_pci_evt_irqmap_t.intsrc.subtype' and '_pci_evt_irqmap_t.intsrc.attr'
	 * fields may optionally provide additional qualification information
	 *
	 * If there is no alternate interrupt vector or the specification defined
	 * mechanism is not implemented, the '_pci_evt_irqmap_t.intsrc.type' will be
	 * set to _pci_irqType_e_NONE and all '_pci_evt_irqmap_t.intsrc' information
	 * must be ignored by the caller
	 *
	 * The <bdf> parameter depends on the type of event(s) provided in the call
	 * For error events, <bdf> identifies the event reporting agent for the
	 * event(s)
	 *
	 * For example, for link and power management events, <bdf> identifies the
	 * device of interest. For slot events, <bdf> identifies the Root or switch
	 * port the slot is connected too. For other types of events, the <bdf> is
	 * event specific
	 *
	 * A 'pci_err_t' will be returned as follows
	 * See also the description of _pci_map_event_irq() in lib/private/pci_hw.h
	 *
	 *	PCI_ERR_ENOTSUP - the HW module does not implement the callin or all of
	 *					  the necessary information (ex. startup intrinfo
	 *					  information) is not available/implemented
	 *
	 *					  Important note for HW modules
	 *					  -----------------------------
	 *					  If the callin is not implemented by the HW module,
	 *					  this error will be automatically returned. If the
	 *					  callin is implemented, the HW module implementation
	 *					  needs to be careful about returning this error code
	 *					  since it can and will in most cases be interpreted by
	 *					  the caller as "the HW module has no overrides for the
	 *					  events provided" and it will therefore assume that the
	 *					  specification defined mechanism is supported. If this
	 *					  is not actually the case, it is probable that no event
	 *					  notifications will be received and this will be
	 *					  interpreted by the user as failed behaviour. Instead
	 *					  of returning this error code, the HW module should
	 *					  instead return the information for the specification
	 *					  defined mechanism if it is in fact supported for some
	 *					  or all of the events for which a mapping is requested
	 *
	 *	PCI_ERR_EINVAL - will be returned if there are any parameter errors such
	 *					 as the following
	 *					 - <evt_irq_map> is NULL
	 *					 - <nevts> is zero
	 *					 - one or more of the 'evt_irq_map[].event' entries
	 *					   contains invalid information
	 *					 - the 'evt_irq_map[].extra.size' field is non-zero and
	 *					   the HW module cannot properly interpret the
	 *					   'evt_irq_map[].extra.data' field
	 *
	 *	PCI_ERR_ENODEV - the <bdf> is not valid
	 *
	 *	PCI_ERR_IRQ_NOT_AVAIL - the HW module does not have any valid mappings
	 *							for any of the events specified in the
	 *							<evt_irq_map> array or the information is
	 *							otherwise not available
	 *
	 *	PCI_ERR_IRQ_CFG - at least one of the <nevts> entries in <evt_irq_map>
	 *					  array does have a valid mapping but one or more others
	 *					  do not. The ones which do not should be identified
	 *					  with an entry as follows
	 *						<evt_irq_map>.intsrc.map.irq == -1
	 *						<evt_irq_map>.intsrc.type == _pci_irqType_e_NONE
	 *					  and must be ignored by the caller. This error should
	 *					  only be returned if <nevts> > 1. For <nevts> == 1
	 *					  PCI_ERR_IRQ_NOT_AVAIL will be returned if there is no
	 *					  valid mapping
	 *					  This return value can be considered to be a partially
	 *					  successful return by the caller
	 *
	 *	PCI_ERR_OK - all of the <nevts> entries in the <evt_irq_map> array have
	 *				 a valid mapping
	 *
	 * While in some cases it is possible for the caller to attempt to obtain
	 * all mappings in a single call it will usually be much simpler for the
	 * caller to make multiple calls based on the class of event being checked
	 * This will certainly be required if a different <bdf> parameter is
	 * required depending on the event type
	 *
	 * On a successful return, it is possible that more than one event will
	 * share the same interrupt vector. The caller will usually want to coalesce
	 * such entries such that the interrupt is only attached too once and all
	 * events triggering that interrupt are checked by a single ISR when the
	 * interrupt triggers. An example of this behaviour is for PCIe specification
	 * defined AER events which indicate correctable, Uncorrectable and Fatal
	 * error events using a single interrupt vector
	 *
	 * Interrupt Behaviour and Other platform requirements
	 * ---------------------------------------------------
	 *
	 * While the purpose of this callout is to accommodate platform specific
	 * event reporting mechanisms in as flexible a fashion as possible, there
	 * are still some expectations of the platform hardware in order for the
	 * generic event handling modules to be used
	 *
	 *	Link Events
	 *		For each of the specification defined and supported link events ...
	 *		 - Data Link Layer Link Active
	 *		 - Link Bandwidth Management Status
	 *		 - Link Autonomous Bandwidth Status
	 *		the status of the specific event must be reported in the Link Status
	 *		register of the PCIe capability regardless of whether or not each
	 *		event reports using the same or a different interrupt vector
	 *	Slot Events
	 *		For each of the specification defined and supported slot events,
	 *		the status of the specific event must be reported in the Slot Status
	 *		register of the PCIe capability regardless of whether or not each
	 *		event reports using the same or a different interrupt vector
	 *	Power Management Events
	 *		If supported, power management events must be reported in the status
	 *		register of the Power Management (PMI) capability regardless of
	 *		whether or not power management events are reported through the PCI
	 *		specification defined interrupt mechanism or a platform specific
	 *		mechanism
	 *	Error Events (specifically AER)
	 *		For each of the specification defined and supported error events ...
	 *		 - Correctable Error Events
	 *		 - Uncorrectable Error Events
	 *		 - Fatal Error Events
	 *		the status of the specific events must be reported in the respective
	 *		status register of the AER extended PCIe capability regardless of
	 *		whether or not each	specific event or event class reports using the
	 *		same or a different interrupt vector
	 *
	 * Regarding the implementation of startup callouts which are involved in
	 * the reporting of each event type, there are a few choices
	 *	1. de-multiplex each event to a unique vector
	 *	2. partially de-multiplex such that each event class reports on a single
	 *	   interrupt vector similar to the specification defined mechanisms
	 *
	 * The current event handling modules are implemented in a generic fashion
	 * based on the PCI specification defined mechanisms. This means that all
	 * events of the same class (ex. Link Events) will always be checked for
	 * occurrence whenever one of the events of the class occurs and therefore
	 * there is no advantage to having a separate vector for each event of the
	 * class and while this will work it will result in the same ISR being
	 * attached to multiple interrupt vectors
	 *
	 * If the startup callouts are implemented such that any event of a given
	 * class (ex. Link Events) report using the same interrupt vector, this will
	 * mimic the PCI specification defined mechanism and although the same vector
	 * will be returned multiple times for each event of the class, the event
	 * handling modules will detect this and only attach the event handling ISR
	 * once. This partial de-multiplex however requires that all such events of
	 * the class are eoi'd/masked/unmasked as a group
	 *
	 */
	pci_err_t (*map_event_irq)(const pci_bdf_t bdf, const uint_t nevts, _pci_evt_irqmap_t * const evt_irq_map);

	/*
	 * alloc_err_record_id
	 *
	 * This callin is used to allocate a partition unique value which can be
	 * used as a 'pci_err_record_id_t' in support of the error event handler
	 * server module
	 *
	 */
	uint32_t (*alloc_err_record_id)(void);

	/*
	 * register_server_callback
	 *
	 * This callin is to register callbacks to the server
	 *
	 */
	pci_err_t (*register_server_callback)(const pci_server_callbackType_e callback_type, void (*funcptr)(void));

	/*
	 * set_power_mode
	 *
	 * This callin is to set the power mode when pci-server is the one that
	 * is registered to a power management framework
	 *
	 */
	pci_err_t (*set_power_mode)(const pci_pmType_e pm_type);

	/*
	 * pad out 'hwmod_api_t' so we can avoid an immediate version bump on
	 * specific HW modules if a new API is not required for a specific module
	 * This allows the sizeof(hwmod_api_t) > struct_size check to pass in the
	 * libc loading of a HW dependent module as long as an API specific
	 * existence check (offsetof() and NULL) is done (as with the 'reset' API
	 * above)
	 */
	void (*reserved5)(void);
	void (*reserved4)(void);
	void (*reserved3)(void);
	void (*reserved2)(void);
	void (*reserved1)(void);
	void (*reserved0)(void);

} hwmod_api_t;

/*
 ===============================================================================
 hwmod_server_callback_t

 This is the structure which provides the access for the HW dependent modules
 of the PCI server to call back into functions in the PCI server.  Callback
 functions typically will first have be registered with register_server_callback

 In order to allow future extensions and retain backwards compatibility, this
 structure can only ever be extended. Fields can never be removed or reordered.
 The 'struct_size' field ensures this compatibility with the PCI library as
 follows.
	 - If this structure is extended and used with an existing libpci.so, the
	   new fields will not be known to libpci.so and hence not used but the
	   interface will continue to function properly since libpci.so idea of
	   sizeof(hwmod_api_t) will be <= 'struct_size' of the new structure
	 - If this structure is extended and a new libpci.so delivered but that
	   library is used with an older HW dependent module, libpci.so's idea of
	   sizeof(hwmod_api_t) will be > 'struct_size' of the old HW dependent
	   module and hence will be rejected

 So, if the API's for a new HW dependent module are extended, that new module
 can be used with an existing libpci.so, however none of the new features of
 that HW dependent module will be utilized. If the API's for a new HW dependent
 module are extended and a new libpci.so provided which utilizes those new
 API's, the new libpci.so can only be used with a new HW dependent module, which
 is exactly what one would expect.

*/
typedef struct
{
	uint_t struct_size;
	pci_version_t (*mod_version)(void);
	bool_t (*mod_compat)(const version_typecheck_e check_type, const pci_version_t version);

	pci_err_t (*server_set_power_mode)(const pci_pmType_e pm_type);
	bool_t (*get_do_bus_config)(void);
	/*
	 * pad out 'hwmod_server_callback_t' so we can avoid an immediate version bump on
	 * specific HW modules if a new API is not required for a specific module
	 * This allows the sizeof(hwmod_api_t) > struct_size check to pass in the
	 * libc loading of a HW dependent module as long as an API specific
	 * existence check (offsetof() and NULL) is done (as with the 'reset' API
	 * above)
	 */

	void (*reserved8)(void);
	void (*reserved7)(void);
	void (*reserved6)(void);
	void (*reserved5)(void);
	void (*reserved4)(void);
	void (*reserved3)(void);
	void (*reserved2)(void);
	void (*reserved1)(void);
	void (*reserved0)(void);
} hwmod_server_callback_t;

/* prototypes for required HW dependent module functions */

pci_err_t hw_rd(const pci_bdf_t bdf, const uint32_t offset, const uint32_t size, uint8_t * const buf, const _pci_accessAttr_e accessAttr);
pci_err_t hw_wr(const pci_bdf_t bdf, const uint32_t offset, const uint32_t size, uint8_t * const buf, const _pci_accessAttr_e accessAttr);
pci_err_t hw_alloc_irq(const pci_bdf_t bdf, const _pci_irqType_e irq_type, const _pci_irqAttr_e irq_attr, uint32_t * const nirq, _pci_irqmap_t * const irq_map);
pci_err_t hw_free_irq(const pci_bdf_t bdf, const _pci_irqType_e irq_type, const uint32_t nirq, _pci_irqmap_t * const irq_map);
pci_err_t hw_map_event_irq(const pci_bdf_t bdf, const uint32_t nevts, _pci_evt_irqmap_t * const evt_irq_map);
pci_err_t hw_alloc_as(const pci_bdf_t bdf, const pci_asType_e as_type, const pci_asAttr_e as_attr, const uint64_t as_size, _pci_asmap_t * const as_map);
pci_err_t hw_resv_as(const pci_bdf_t bdf, _pci_asmap_t * const as_map);
pci_err_t hw_free_as(const pci_bdf_t bdf, _pci_asmap_t * const as_map);
pci_err_t hw_map_as(const pci_bdf_t bdf, const pci_ba_t * const as, pci_ba_t * const as_xlate);
pci_err_t hw_add_device_hold_off(pci_bdf_t bdf);
pci_err_t hw_remove_device_hold_off(pci_bdf_t bdf);
pci_err_t hw_initiate_hold_off(void);
pci_err_t hw_release_hold_off(void);
pci_err_t hw_reset(const pci_resetType_e reset_type, const _pci_resetPhase_e phase, const pci_bdf_t bdf, uintptr_t extra);
pci_err_t hw_set_link_state(const uint32_t link_num, const _pci_link_state_e state);
_pci_link_state_e hw_get_link_state(const uint32_t link_num);
pci_err_t hw_server_register(const _pci_server_info_t * const server_info);
pci_err_t hw_server_info_get(int_t * const nsi, _pci_server_info_t * const server_info, const pci_reqType_t req_type);
pci_server_id_t hw_server_id_get(const pci_bdf_t bdf);
pci_server_id_t get_my_server_id(void);
uint32_t hw_alloc_err_record_id(void);
pci_err_t hw_set_power_mode(const pci_pmType_e pm_type);
pci_err_t hw_register_server_callback(const pci_server_callbackType_e callback_type, void (*funcptr)(void));
const char * hw_get_mod_version(void);

pci_err_t syspage_get_sysram_info(_pci_asmap_t * const sysram);
pci_err_t syspage_calc_aspace_range(const char * const asinfo_name, _pci_asmap_t * const asinfo);
void syspage_load_asinfo(void);
void syspage_load_intrinfo(const intrinfo_entry_type_e type, const rsrcdb_pool_id_t pool_id);
int find_vector(const uint32_t vector, const _pci_irqType_e irq_type);
struct intrinfo_entry *find_vec_entry(struct intrinfo_entry * const start, const uint32_t vector, const intrinfo_entry_type_e type);

void mmap_cfg_reg_lock(void);

pci_err_t rsrcdb_as_add(const _pci_asmap_t * const as_map, const uint32_t req_flags, const rsrcdb_pool_id_t pool_id);
pci_err_t rsrcdb_as_del(const _pci_asmap_t * const as_map, const rsrcdb_pool_id_t pool_id);
pci_err_t rsrcdb_as_resv(_pci_asmap_t * const as_map, const uint32_t req_flags, const rsrcdb_pool_id_t pool_id);
pci_err_t rsrcdb_as_free(_pci_asmap_t * const as_map, const rsrcdb_pool_id_t pool_id);
pci_err_t rsrcdb_irq_resv(const _pci_irqType_e irq_type, const _pci_irqAttr_e irq_attr, const uint32_t nirq, pci_irq_t * const irq_list, const uint32_t req_flags, const rsrcdb_pool_id_t pool_id);
pci_err_t rsrcdb_irq_free(const _pci_irqType_e irq_type, const uint32_t nirq, pci_irq_t * const irq_list, const rsrcdb_pool_id_t pool_id);
pci_err_t rsrcdb_irq_add(const struct intrinfo_entry * const entry, const intrinfo_entry_type_e type, const uint32_t req_flags, const rsrcdb_pool_id_t pool_id);
rsrcdb_pool_id_t rsrcdb_pool_create(const rsrcdb_pool_type_e pool_type, const uint32_t tag, pci_err_t *err);
const char * rsrcdb_pool_get_name(const rsrcdb_pool_id_t pool_id, const rsrcdb_pool_type_e pool_type);

pci_irq_t bdf_irq(const pci_bdf_t bdf);
char bridge_intpin_route(const pci_bdf_t root_bdf, const pci_bdf_t device_bdf, const char intpin_c);

pci_err_t get_pciecap_link_state(const pci_bdf_t bdf, _pci_link_state_e * const link_state);
pci_err_t get_pci_bus_state(const pci_bdf_t bdf, _pci_link_state_e * const bus_state);

void hw_usec_delay(const uint32_t usec);

pci_err_t init_hw_shm(void);

void init_link_states(void);

pci_version_t hw_mod_version(void);

/*
 ===============================================================================
 config_reg_lock
 config_reg_unlock

 Because the PCI configuration space accesses are performed by accessing 2
 separate registers (an address register and a data register) we must make sure
 that their use is performed atomically.

 PCI server only handles write operations and so read operations are
 performed in the context of the reading process. Additionally, even if this
 were not the case, we desire to run the PCI server multi-threaded, hence the
 need for a global (system wide) lock.

 Note
 There may be a need to have the calling process sleep after 'n' attempts to
 acquire the lock so that long hold offs for say bus segment reconfiguration do
 not impact overall system performance. This is TBD and a counter has been added
 alongside the lock to collect the number of lock contentions that occur

*/
void config_reg_unlock(void *dummy);
void config_reg_lock(void);

/*
 ===============================================================================
 get_link_state
 set_link_state

 Functions to get and set entries in the link state array. These in-line
 functions are also used by the corresponding functions in hw_shm.c which can be
 installed into the HW modules 'hwmod_api_t'

 When changing the link state with set_link_state(), the caller should also
 check the return value and not assume that the link state is <state> since it
 is possible that the state has changed again since the callers update.
 In general, set_link_state() should really be used as part of the
 check_link_trained() operation described in the template HW module and
 is_link_up() function below

 CAUTION:
 Can be called from ISR context

*/
_pci_link_state_e get_link_state(const uint32_t link_num);
_pci_link_state_e set_link_state(const uint32_t link_num, const _pci_link_state_e state);

/*
 ===============================================================================
 is_link_up

 This function can be used to quickly determine whether or not the link
 for <bdf> is marked as up or not according to the hw_shm->link_state[] array.

 If it is not marked up, the rd/wr functions must take further action to
 determine the actual state of the link and update the link state array

 It is expected to be used within the hw_rd()/hw_wr() functions in a test
 similar to the following

	if (!is_link_up(bdf) && !check_link_trained(bdf)) {
		return PCI_ERR_PCIe_LINK_NOT_ACTIVE;
	}
	else
		... carry on with rd/wr operation ...

 The check_link_trained() function must be implemented by the HW module to
 consult any hardware resources available to determine the actual state of the
 link and to update the link state array. The example above is only meant to
 illustrate a possible implementation. Arguments and return values are
 implementation specific

 CAUTION:
 Can be called from ISR context

*/
bool_t is_link_up(const pci_bdf_t bdf);

/*
 ===============================================================================
 hw_rdlock
 hw_wrlock
 hw_rd_unlock
 hw_wr_unlock

 These functions implement read/write spinlocks and operate on a volatile
 uint32_t memory objects using atomic_*() operations

 They are useful for guarding very short sequences that are mostly read-only
 with uncorrelated temporal access patterns between execution streams and
 which therefore don't need scheduling support to make forward progress

*/
void hw_rdlock(volatile uint32_t *lock);
void hw_wrlock(volatile uint32_t *lock);
void hw_rd_unlock(volatile uint32_t *lock);
void hw_wr_unlock(volatile uint32_t *lock);

/*
 ===============================================================================
 DEBUG API's

 The following API is used to log various output points.
*/
#ifndef slog_debug
void slog_debug(int32_t verbosity_level, const char *fmt, ...);
#endif

/*
 ===============================================================================
 SLOG API's

 The following API's are used to log various output points.
 There are 3 functions based on the severity of the information.
 The global variable 'pci_verbosity' is also used to control the amount of
 output

 The 'verbosity_level' is used to control the amount of output for a given
 log type (INFO, WARNING, ERROR, etc). It represents a delta from the base
 verbosity level for the logging type.
 For example,
*/
#ifndef slog_info
void slog_info(int32_t verbosity_level, const char *fmt, ...);
#endif

#ifndef slog_warn
void slog_warn(int32_t verbosity_level, const char *fmt, ...);
#endif

#ifndef slog_error
void slog_error(int32_t verbosity_level, const char *fmt, ...);
#endif

/*
 ===============================================================================
 get_pci_runtime_flags

 This API allows the HW modules to retrued the server runtime flags.

*/
pci_runtime_flags_e get_pci_runtime_flags(void);

/*
 ===============================================================================
 in_guest_vm_context

 This optional function can be implemented by HW modules which have the need to
 determine whether they are executing in a any or a particular VM context

*/
bool_t in_guest_vm_context(const pci_hwmod_vm_context_e vm_check);

bool_t mod_compat(version_typecheck_e check_type, pci_version_t version);

const char *pci_hw_getenv(const char * const envvar_name);

/*
 ===============================================================================
 Capability API's
 */
uint32_t pcie_ecam_bdf(uint32_t b, uint32_t d, uint32_t f, uint32_t offset);

/*
 ===============================================================================
 get_hw_shm

 This functions returns a pointer to the hw_shm_t object

*/
hw_shm_t * get_hw_shm(void);

bool_t pci_isr_context(void);

/*
 ===============================================================================
 The HW dependent module provides an initialized function pointer table of type
 'hwmod_api_t' and named HW_MODULE_ACCESS. The symbol can be found by the
 PCI library using the search string HW_MODULE_ACCESS_SYM.

 Additionally, this module must also provide an initialization function named
 HW_MODULE_INITFN which can be found by the PCI library using the search
 string HW_MODULE_INITFN_SYM.

 The PCI server module_load() function will first lookup HW_MODULE_ACCESS_SYM
 such that a version and compatibility check can be performed. If those checks
 fail, the module will not be loaded, otherwise if the process loading the
 module is a server process, then the server ID will be registered.

 Next, HW_MODULE_INITFN_SYM will be searched for. If not found module loading
 will fail otherwise the function will be called to perform the required module
 and hardware initialization. If the initialization is successful and PCI_ERR_OK
 returned, the caller expects the 'hwmod_api_t **' parameter passed in to be
 set to &HW_MODULE_ACCESS otherwise the parameter should not be set and an
 appropriate error code returned

 IMPORTANT: These symbol names can never change if backward compatibility is to
			be maintained
*/
#define STRINGX(s)	STRING(s)
#define STRING(s)	#s

#define HW_MODULE_ACCESS		hwmod_access
#define HW_MODULE_INITFN		hwmod_init

#define HW_MODULE_ACCESS_SYM	STRINGX(HW_MODULE_ACCESS)
#define HW_MODULE_INITFN_SYM	STRINGX(HW_MODULE_INITFN)

extern pci_err_t HW_MODULE_INITFN(volatile const hwmod_api_t **hw_p);
extern const hwmod_api_t HW_MODULE_ACCESS;

#endif	/* _HW_LIB_H_ */
