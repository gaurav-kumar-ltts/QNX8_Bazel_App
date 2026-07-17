#ifndef _HW_SEG_H_
#define _HW_SEG_H_
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


/*
 ===============================================================================

 This file contains types and definitions related to HW module support for the
 PCI Hierarchy and Segmentation functionality

 ===============================================================================
*/




/* prototypes */
bool_t hw_seg_supported(void);
pci_err_t hw_seg_map_add(const uint_t seg_idx, const struct seg_ctrl_info_s * const seg_map);
pci_err_t hw_seg_map_del(const uint_t seg_idx);
pci_err_t hw_seg_map_deref(const pci_server_id_t server_id);
uint_t hw_seg_num_segments(const pci_server_id_t server_id);
pci_err_t hw_seg_ctrl_info(const uint_t seg_idx, struct seg_ctrl_info_s * const ctrl_info);
int_t hw_seg_idx_get_by_bdf(const pci_bdf_t bdf);
int_t hw_seg_idx_get_by_server_id(const int_t seg_idx_next, const pci_server_id_t server_id);


#endif	/* _HW_SEG_H_ */
