/*
 * Copyright (c) 2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _QNX_SMMU_H_INCLUDED
#define _QNX_SMMU_H_INCLUDED

void init_smmu(void);
void fini_smmu(void);
void add_mem_smmu(off64_t addr, size_t len);
void del_mem_smmu(off64_t addr, size_t len);
void add_pci_smmu(uint8_t bus, uint8_t dev, uint8_t func);
void del_pci_smmu(uint8_t bus, uint8_t dev, uint8_t func);
void add_mmio_smmu(off64_t addr, size_t len);
void del_mmio_smmu(off64_t addr, size_t len);

#endif /* _QNX_SMMU_H_INCLUDED */
