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

#ifndef _CFGSPACE_MAP_H_
#define _CFGSPACE_MAP_H_

#include <pci/pci.h>
#include "pci/hw_lib.h"

/*
 ===============================================================================
 cfgspace_map_t

 This type holds the configuration space mapping for a single device (ie. BDF)

 The size of the area required to provide access to the 4K configuration space
 of any single device in the global BDF space is 256MB. We do not want each
 non-server process which loads the HW module to have such a large mapping.
 Instead, mappings to the 4KB configuration space of each device accessed (which
 generally will be limited to only 1 or 2) will be created on-the-fly and as
 required.

 The structure provides for both a read-only (the default) and an optional
 read-write mapping. Clients (ie. non-server processes) always get a read-only
 configuration space mapping because all configuration writes go through the
 server. However, there are certain write APIs which allow for example,
 interrupts to be masked and unmasked and since these calls can be made from
 an ISR if used, we optionally (at the discretion of the HW module writer)
 implement a read/write mapping to the configuration space of the device. This
 mapping is typically provided when there are additional outbound ATUs available
 for the purpose hence why this is optional

 The 'CFGSPACE_MAP_EXTRA' allows HW modules to extend the 'cfgspace_map_t' with
 additional fields if necessary. If defined, the HW module should provide a
 cfgspace_map_extra.h file which defines the macro _CFGSPACE_MAP_EXTRA_T_ as a
 type and field suitable for inclusion within the base structure

 For example

	typedef struct __attribute__((aligned(8)))
	{
		void *field_1;
		uint_t field_2;
		uint8_t field_3;
	} my_extra_fields_t;
	#define _CFGSPACE_MAP_EXTRA_T_	my_extra_fields_t my_fields;

 Depending on the size of the type that '_CFGSPACE_MAP_EXTRA_T_' represents, it
 may be desirable to have the 'cfgspace_map_t' allocated per function instead
 of 8 copies of the 'cfgspace_map_t' being allocated when the 'func_list_t' is
 allocated. If this is desired, then 'ALLOCATE_CFG_MAP_T' should be defined
 before including cfgspace_map.h. Note that 'ALLOCATE_CFG_MAP_T' call also be
 defined independent of '_CFGSPACE_MAP_EXTRA_T_' however there should be no
 compelling case to do this as it results in more allocation requests. See also
 cfgspace_map.c

*/
#ifdef CFGSPACE_MAP_EXTRA
#include "cfgspace_map_extra.h"
#else
#define _CFGSPACE_MAP_EXTRA_T_
#endif
typedef struct __attribute__((packed,aligned(8)))
{
	const void *ro;
	const void *rw;
	uint32_t ro_size;
	uint32_t rw_size;
	_CFGSPACE_MAP_EXTRA_T_
} cfgspace_map_t;

#define CFGSPACE_MAP_UNKNOWN		BDF_HW_MAP_UNKNOWN
/* use BDF_HW_MAP_IO to flag a non existent device */
#define CFGSPACE_MAP_DOESNT_EXIST	BDF_HW_MAP_IO


void cfgspace_map_set_range(const uint8_t first_bus, const uint8_t last_bus);
const cfgspace_map_t *cfgspace_map_get(const pci_bdf_t bdf);
pci_err_t cfgspace_map_add(const pci_bdf_t bdf, const cfgspace_map_t * const bdf_cfg_map);
pci_err_t cfgspace_map_del(const pci_bdf_t bdf);

#ifndef NDEBUG
void cfgspace_map_dump(void);
size_t get_total_bytes_allocated(void);
#endif	/* NDEBUG */


#endif	/* _CFGSPACE_MAP_H_ */
