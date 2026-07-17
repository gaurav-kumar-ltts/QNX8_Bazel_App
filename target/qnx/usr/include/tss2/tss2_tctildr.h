/*
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright 2018-2019 Intel Corporation
 */
#ifndef TSS2_TCTILDR_H
#define TSS2_TCTILDR_H

#include <inttypes.h>
#include <stdlib.h>

#include "tss2_tpm2_types.h"
#include "tss2_tcti.h"

#ifdef __cplusplus
extern "C" {
#endif

void
Tss2_TctiLdr_Finalize (TSS2_TCTI_CONTEXT **context);
TSS2_RC
Tss2_TctiLdr_Initialize_Ex (const char *name,
                            const char *conf,
                            TSS2_TCTI_CONTEXT **context);
TSS2_RC
Tss2_TctiLdr_Initialize (const char *nameConf,
                         TSS2_TCTI_CONTEXT **context);
TSS2_RC
Tss2_TctiLdr_GetInfo (const char *name,
                      TSS2_TCTI_INFO **info);
void
Tss2_TctiLdr_FreeInfo (TSS2_TCTI_INFO **info);

#ifdef __cplusplus
}
#endif

#endif /* TSS2_TCTILDR_H */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://f27svn.qnx.com/svn/repos/osr/trunk/tcg/intel_tpm2-tss/dist/include/tss2/tss2_tctildr.h $ $Rev: 3432 $")
#endif
