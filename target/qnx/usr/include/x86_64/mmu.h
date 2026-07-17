/*
 * $QNXLicenseC:
 * Copyright 2020, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/*
 * x86_64 MMU support
 */

#ifndef __X86_64_MMU_H_INCLUDED
#define __X86_64_MMU_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

// Included for X86_64_PTE_* definitions
#include <x86_64/cpu.h>

/**
 * Mapping of PTE bits to PAT entries
 *
 * PAT_Entry_Num = 4*PAT + 2*PCD + PWT
 *
 * The following table summaries the mapping of PTE bits to PAT entries.
 *
 * | PAT | PCD | PWT | Entry | Arch | QNX |
 * | --- | --- | --- | ----- | ---- | --- |
 * | 0   | 0   | 0   | PAT0  | WB   | WB  |
 * | 0   | 0   | 1   | PAT1  | WT   | WT  |
 * | 0   | 1   | 0   | PAT2  | UC-  | WC  |
 * | 0   | 1   | 1   | PAT3  | UC   | UC  |
 * | 1   | 0   | 0   | PAT4  | WB   | WB  |
 * | 1   | 0   | 1   | PAT5  | WT   | WT  |
 * | 1   | 1   | 0   | PAT6  | UC-  | UC- |
 * | 1   | 1   | 1   | PAT7  | UC   | UC  |
 *
 * The last two columns of the above table show the default mappings of PAT entry to memory
 * attribute. Values in the Arch column are the arcitecural defaults, those under QNX are the
 * default upon entry to procnto. The QNX defaults are set by startup (see `cpu_one_startup()` in
 * `hardware/startup/lib/common_x86/cpu_startup.c`).
 *
 * The memory attributes are defined as follows.
 *
 * - Strong Uncacheable (UC)
 * - Uncacheable (UC-)
 * - Write Combining (WC)
 * - Write Back (WB)
 * - Write Through (WT)
 * - Write Protect (WP)
 *
 * NOTE: The primary difference between Strong Uncacheable (UC) and Uncacheable (UC-) is that the
 *       Uncacheable (UC-) memory type may be overidden by programming the MTRRs for Write Combining.
 *
 * For architecture details see:
 * 
 * - Intel SDM, Vol 3, 4,9.2: Paging and Memorty Type when PAT is supported
 * - Intel SDM, Vol 3, 11.3: Methods of Caching Available
 * - Intel SDM, Vol 3, 11.12: Page Attribute Table
 */

#define X86_64_PAT_ENTRY_0      (0ull)
#define X86_64_PAT_ENTRY_1      (X86_64_PTE_WT)
#define X86_64_PAT_ENTRY_2      (X86_64_PTE_CD)
#define X86_64_PAT_ENTRY_3      (X86_64_PTE_CD | X86_64_PTE_WT)
#define X86_64_PAT_ENTRY_4      (X86_64_PTE_PAT)
#define X86_64_PAT_ENTRY_5      (X86_64_PTE_PAT | X86_64_PTE_WT)
#define X86_64_PAT_ENTRY_6      (X86_64_PTE_PAT | X86_64_PTE_CD)
#define X86_64_PAT_ENTRY_7      (X86_64_PTE_PAT | X86_64_PTE_CD | X86_64_PTE_WT)

/**
 * Definitions for use with shm_clt_special()
 */

#define X86_64_PTE_MTYPE_WB     (X86_64_PAT_ENTRY_0)     // Write Back
#define X86_64_PTE_MTYPE_WT     (X86_64_PAT_ENTRY_1)     // Write Through
#define X86_64_PTE_MTYPE_WC     (X86_64_PAT_ENTRY_2)     // Write Combine
#define X86_64_PTE_MTYPE_UC     (X86_64_PAT_ENTRY_3)     // Strong Uncacheable
#define X86_64_PTE_MTYPE_UCM    (X86_64_PAT_ENTRY_6)     // Uncacheable

#endif /* __X86_64_MMU_H_INCLUDED */
