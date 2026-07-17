#ifndef _HW_CFG_H_
#define _HW_CFG_H_
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

#include <pthread.h>
#include <atomic.h>
#include <sys/mman.h>
#include <assert.h>

#include <pci/pci.h>
#include <pci/hw_lib.h>

typedef enum
{
pcie_ctrl_type_e_first = 0,

	pcie_ctrl_type_e_NONE = pcie_ctrl_type_e_first,
	pcie_ctrl_type_e_RC,
	pcie_ctrl_type_e_EP,

pcie_ctrl_type_e_last = pcie_ctrl_type_e_EP
} pcie_ctrl_type_e;

typedef struct pin_to_irq_map_s
{
	struct pin_to_irq_map_s *next;
	pci_bdf_t bdf;
	char intpin;		// A, B, C or D
	pci_irq_t irq;
} pin_to_irq_map_t;

typedef struct csd_assignment_s
{
	struct csd_assignment_s *next;
	pci_vid_t vid;
	pci_did_t did;
	uint_t idx;
	pci_csd_t csd;
} csd_assignment_t;

typedef struct aspace_filter_s
{
	struct aspace_filter_s *next;
	_pci_asmap_t asmap;
} aspace_filter_t;

typedef struct rbar_override_s
{
	struct rbar_override_s *next;
	pci_vid_t vid;
	pci_did_t did;
	uint_t idx;
	struct rbar_info_s
	{
		int_t num;	// -1 indicates no entry
		pci_ba_val_t size;
	} bar[6];
} rbar_override_t;

typedef struct ecam_info_s
{
	uint64_t base;
	uint64_t size;
} ecam_info_t;

typedef struct segment_map_s
{
	struct segment_map_s *next;
	const char *hw_specific_id;	/* strdup()'d */
	pci_server_id_t server_id;
	struct
	{
		uint8_t first;
		uint8_t last;
	} bus;
} segment_map_t;

typedef struct
{
	pin_to_irq_map_t *irq_list;
	csd_assignment_t *csd_list;
	aspace_filter_t *aspace_filter_list;
	rbar_override_t *rbar_override_list;
	ecam_info_t *ecam_info;
	segment_map_t *segment_map_list;
} hw_cfg_t;


void force_load_hwcfg_file(void);
void parse_hw_config_file(const char * const fname, hw_cfg_t * const cfg);

/* function to call to use HW config file interrupt mapping overrides */
pci_irq_t extcfg_intpin_to_irq(const pci_bdf_t bdf, const char _pci_intpin_c);
pci_csd_t extcfg_find_csd_assignment(const pci_csd_t csd, const pci_vid_t vid, const pci_did_t did, const uint_t idx);
pci_err_t extcfg_check_rbar_override(const pci_bdf_t bdf, const uint_t bar_num, pci_ba_val_t * const size, uintptr_t extra);
const segment_map_t *extcfg_get_segment_info(void);
const ecam_info_t *extcfg_get_ecam_info(void);


#endif	/* _HW_CFG_H_ */
