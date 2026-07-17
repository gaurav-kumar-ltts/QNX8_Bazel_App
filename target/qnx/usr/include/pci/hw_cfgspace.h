#ifndef _HW_CFGSPACE_H_
#define _HW_CFGSPACE_H_
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
#include <pci/hw_lib.h>

 /*
 ===============================================================================
 _pci_device_cfg_rd8
 _pci_device_cfg_rd16
 _pci_device_cfg_rd32
 _pci_device_cfg_rd64
 _pci_device_cfg_rd

 4 convenience functions to read fixed size configuration space entries and 1
 to read an arbitrary number of bytes

 The fixed size functions will perform endian correction
*/
pci_err_t _pci_device_cfg_rd8(const pci_bdf_t bdf, const uint32_t offset, uint8_t * const val);
pci_err_t _pci_device_cfg_rd16(const pci_bdf_t bdf, const uint32_t offset, uint16_t * const val);
pci_err_t _pci_device_cfg_rd32(const pci_bdf_t bdf, const uint32_t offset, uint32_t * const val);
pci_err_t _pci_device_cfg_rd64(const pci_bdf_t bdf, const uint32_t offset, uint64_t * const val);
pci_err_t _pci_device_cfg_rd(const pci_bdf_t bdf, const uint32_t offset, const uint32_t size, uint8_t * const buf);

/*
 ===============================================================================
 _pci_device_cfg_wr8
 _pci_device_cfg_wr16
 _pci_device_cfg_wr32
 _pci_device_cfg_wr64

 4 convenience functions to write fixed size configuration space entries and 1
 to write an arbitrary number of bytes

 The fixed size functions will perform endian correction
*/
pci_err_t _pci_device_cfg_wr8(const pci_bdf_t bdf, const uint32_t offset, const uint8_t val);
pci_err_t _pci_device_cfg_wr16(const pci_bdf_t bdf, const uint32_t offset, const uint16_t val);
pci_err_t _pci_device_cfg_wr32(const pci_bdf_t bdf, const uint32_t offset, const uint32_t val);
pci_err_t _pci_device_cfg_wr64(const pci_bdf_t bdf, const uint32_t offset, const uint64_t val);
pci_err_t _pci_device_cfg_wr(const pci_bdf_t bdf, const uint32_t offset, const uint32_t size, uint8_t * const buf);

/*
 ===============================================================================
 The following are ISR callable versions of the above functions. These are used
 by API's which need to be called from an ISR. Because there is no way to know
 you are being called from an ISR, the API's will be explicitly named with an
 '_isr' suffix and utilize the following to convey that information to the HW
 dependent modules
 ===============================================================================
*/

/*
 ===============================================================================
 _pci_device_cfg_rd8_isr
 _pci_device_cfg_rd16_isr
 _pci_device_cfg_rd32_isr
 _pci_device_cfg_rd64_isr
 _pci_device_cfg_rd_isr

 4 convenience functions to read fixed size configuration space entries and 1
 to read an arbitrary number of bytes

 The fixed size functions will perform endian correction
*/
pci_err_t _pci_device_cfg_rd8_isr(const pci_bdf_t bdf, const uint32_t offset, uint8_t * const val);
pci_err_t _pci_device_cfg_rd16_isr(const pci_bdf_t bdf, const uint32_t offset, uint16_t * const val);
pci_err_t _pci_device_cfg_rd32_isr(const pci_bdf_t bdf, const uint32_t offset, uint32_t * const val);
pci_err_t _pci_device_cfg_rd64_isr(const pci_bdf_t bdf, const uint32_t offset, uint64_t * const val);
pci_err_t _pci_device_cfg_rd_isr(const pci_bdf_t bdf, const uint32_t offset, const uint32_t size, uint8_t * const buf);

/*
 ===============================================================================
 _pci_device_cfg_wr8_isr
 _pci_device_cfg_wr16_isr
 _pci_device_cfg_wr32_isr
 _pci_device_cfg_wr64_isr

 4 convenience functions to write fixed size configuration space entries and 1
 to write an arbitrary number of bytes

 The fixed size functions will perform endian correction

*/
pci_err_t _pci_device_cfg_wr8_isr(const pci_bdf_t bdf, const uint32_t offset, const uint8_t val);
pci_err_t _pci_device_cfg_wr16_isr(const pci_bdf_t bdf, const uint32_t offset, const uint16_t val);
pci_err_t _pci_device_cfg_wr32_isr(const pci_bdf_t bdf, const uint32_t offset, const uint32_t val);
pci_err_t _pci_device_cfg_wr64_isr(const pci_bdf_t bdf, const uint32_t offset, const uint64_t val);
pci_err_t _pci_device_cfg_wr_isr(const pci_bdf_t bdf, const uint32_t offset, const uint32_t size, uint8_t * const buf);

extern pci_err_t cfg_rd(const pci_bdf_t bdf, const uint_t offset, const uint_t size, uint8_t * const buf, const _pci_accessAttr_e accessAttr);
extern pci_err_t cfg_wr(const pci_bdf_t bdf, const uint_t offset, const uint_t size, uint8_t * const buf, const _pci_accessAttr_e accessAttr);

#endif /* _HW_CFGSPACE_H_ */
