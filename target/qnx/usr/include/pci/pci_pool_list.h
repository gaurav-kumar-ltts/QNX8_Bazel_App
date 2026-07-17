#ifndef __PCI_POOL_LIST_H_
#define __PCI_POOL_LIST_H_
/*
 * Copyright (c) 2012, 2021, 2025, BlackBerry Limited.
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
#include <pci/pci.h>
#include "pci/hw_lib.h"
#include "pci/pci_gic_its.h"


/*
 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

                        Pool Management support for HW modules

 This file contains types, defines and prototypes of helper functions for HW
 modules that manage multiple resource pools. It is optional

 They are included by adding a line such as the following to the HW modules
 common.mk file
 EXTRA_SRCVPATH+=$(PROJECT_ROOT)/../src/pool_list_mgmt

 Note that the functions in this directory are separate from those in the rsrcdb
 directory which are used to create resource pools and add them to the resource
 database. Instead, these APIs are for those HW modules which wish to associate
 additional information with resource pool identifiers (ie. rsrcdb_pool_id_t)
 or that make use of multiple pools necessitating a list

 There are 2 main APIs defined
 - pool_list_entry_add() to add a new entry to the list
 - pool_list_info_get() to retrieve the information for a previously added
   'rsrcdb_pool_id_t'

 Currently, all entries are held in a single list regardless of pool type

 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

#define PCI_LIST_FIRST(_q)		(_q).head
#define PCI_LIST_LAST(_q)		(_q).tail
#define PCI_LIST_COUNT(_q)		(_q).count
#define PCI_LIST_ADD(_q, _n)	LINK_END((_q), &(_n)->hdr, typeof(_n))
#define PCI_LIST_DEL(_q, _n)	LINK_REM((_q), &(_n)->hdr, typeof(_n))
#define PCI_LIST_NEXT(_n)		((_n)->hdr.next)
#define PCI_LIST_PREV(_n)		((node_t *)((((uintptr_t)((_n)->hdr.prev))) - offsetof(node_t, next)))

/*
 ===============================================================================
 _pci_pool_info_t

 This structure is used to record additional information a HW module wishes to
 associate with a 'rsrcdb_pool_id_t' it has created

*/
typedef struct
{
	node_t hdr;

	rsrcdb_pool_id_t pool_id;
	rsrcdb_pool_type_e type;

	/* specific information related to the pool 'type' */
	union _pool_info_extra_s
	{
		struct
		{
			/* Future */
		} aspace;
		union
		{
			struct
			{
				_pci_irqSubType_e irq_subtype;
				int_t its_num;	/* if 'gic_irq_type' is LPI, the ITS instance, -1 means direct */
			} arm;
		} interrupt;
	} u;

	void *extra;	/* optional and HW module defined */

} _pci_pool_info_t;

/*
 ===============================================================================
 _pci_bdf_irq_info_t

 This type is used in the management of per BDF interrupt resource pools which
 this HW module supports.

 Normally, there is a single interrupt resource pool which is used for all
 allocations of interrupts to requesting devices. This use case presupposes the
 equality of all such interrupt types and normally this is the case. However,
 there are use cases in which different interrupt types are not equal.
 An example would be ARM GIC SPIs vs ITS based LPIs. The later requires the GIC
 ITS implementation to traverse memory based tables and so resolution to the PE
 which handles the interrupt source incurs a higher latency. If both are made
 available to the HW module by startup, it is possible, and likely desirable to
 segment them into separate pools

 It is also possible that for a given configuration, the system architect may
 wish to partition a subset of the globally available interrupt vectors for use
 by a group of devices associated with (ie. rooted by) a specific controller or
 more precisely, to one or more specific devices. It may also desirable to
 ensure that one or more devices use only a specific interrupt type (ex. SPI or
 LPI as noted above). This partitioning and assignment could be accomplished
 using parameters within a section of a HW config file or by other means

 Default behaviour for this HW module
 ------------------------------------
 The default behaviour will be as follows

 If only one type of interrupt is made available by startup, that type will be
 added to the default pool. The default pool is always used if no assignment
 override has been made as described above

 If more than one type of interrupt is made available by startup (this hardware
 currently supports only 2 types, SPI or LPI either direct or ITS), the LPI
 interrupts will be added to the default pool and the SPI interrupts will be
 added to a separate pool. This means that the use of the SPI interrupts is
 restricted to those devices which have an override entry in a HW config file
 as described above. The LPI and SPI pools can be further segmented with a HW
 config file if desired however this is not currently supported

 If 'pool_id' is for ITS based LPIs, the 'extra' field will be used by the IRQ
 handling code in mod_irq.c to point to the ITS information

 This structure (one per device) is maintained in a linked list by access
 functions in init_controller_info.c.
 It is important to understand that one of these structures is always allocated
 and never released for every device in the system. This occurs either at
 initialization time when overrides are found within a HW config file or via
 hw_alloc_irq() when the driver for the device first requests interrupts

 **Implementation Notes**
 If support for partitioning a subset of interrupt vectors for a specific BDF
 into its own pool is added, that BDF will always use the same interrupt type
 if more than one type exists. In other words, a device (BDF) can only use one
 pool however that pool can be established based on type and/or quantity using
 the HW config file

 There is currently no per '_pci_bdf_irq_info_t' locking required. The list lock
 protects list traversal (add/find) and currently any '_pci_bdf_irq_info_t'
 modifications are protected by the functions doing those modifications. This
 structure is pci-server context only

*/
typedef struct
{
	node_t hdr;

	pthread_mutex_t lock;
	pci_bdf_t bdf;
	rsrcdb_pool_id_t pool_id;

	uint_t nirq;
	_pci_irqType_e irq_type;
#ifdef TRACK_IRQ_ATTR
	_pci_irqAttr_e irq_attr;
#endif
	_pci_irqmap_t *irq_map;

	_pci_arm_gic_itt_info_t *itt_info;	/* NULL if pool is not associated with ITS LPIs */

} _pci_bdf_irq_info_t;

/* prototypes */
pci_err_t pool_list_entry_add(const rsrcdb_pool_id_t id, const rsrcdb_pool_type_e type, const union _pool_info_extra_s * const extra);
_pci_pool_info_t *pool_list_info_get(const rsrcdb_pool_id_t pool_id);
void pci_list_init(list_hdr_t *queue, const pthread_mutexattr_t* attr);
void pci_list_add(list_hdr_t *queue, _pci_bdf_irq_info_t * const entry);
void pci_lock(pthread_mutex_t *lock);
void pci_unlock(pthread_mutex_t *lock);


#endif	/* __PCI_POOL_LIST_H_ */
