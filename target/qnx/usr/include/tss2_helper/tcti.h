/*
 * Copyright (c) 2019-2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef QNX_TSS2_HELPER_TCTI_H_INCLUDED
#define QNX_TSS2_HELPER_TCTI_H_INCLUDED

/**
 * @file tcti.h
 *
 * Header file for TCTI helpers.
 */

/* sorted headers from this project */

/* sorted library headers */
#include <tss2/tss2_tcti.h>

/* sorted system headers */
#include <sys/cdefs.h>

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * Allocate and initialize a TCTI context from a given init function.
 *
 * TCG's TCTI standard provides a mechanism to create TCTI contexts, but not one where the TCTI
 * library is responsible for the memory allocation / deallocation, thus pushing the context buffer
 * lifecycle responsibility to the client.  Though this does not represent a tremendous amount of
 * code, it has to be done in all clients, and one has to remember to free the memory once the context
 * is no longer used.  In order to simplify this, this function takes on the responsibility of
 * managing the lifecycle of the context buffer, simplifying the client code.  It allocates the
 * context buffer, and frees it right after the context's finalize function is called.  This is
 * achieved by modifying the TCTI context from the TCTI library, where the finalize function is
 * swapped with a tss2_helper fini function, and where the original finalize function pointer is
 * stored right before the context pointer in memory.  When the swapped finalize function is called,
 * the original finalize function is retrieved and called, and then the buffer is freed.
 *
 * @param[in] init_func  A pointer to the TCTI init function the client wants to use for
 *                       initializing the context.
 * @param[out] context   A pointer to a location where the newly created and initialized context
 *                       will be stored.
 * @param[in] config     The configuration string to be used when initializing the TCTI context. As
 *                       per the TCTI standard, this can be NULL if the default configuration is to
 *                       be used.
 *
 * @return TSS2_RC_SUCCESS on success, and a tss2 return code (TSS2_RC) on failure.
 */
TSS2_RC tss2_helper_tcti_init_alloc(const TSS2_TCTI_INIT_FCN __init_func, TSS2_TCTI_CONTEXT **__context, const char *__config);

/**
 * Allocate and initialize a TCTI context from a given TCTI library name.
 *
 * TCG's TCTI standard provides a mechanism to create TCTI contexts, but not one where the TCTI
 * library is responsible for the memory allocation / deallocation, thus pushing the context buffer
 * lifecycle responsibility to the client.  Furthermore, when dealing with TCTI libraries loaded at
 * runtime, the client also has to deal with the details of opening the library, getting the proper
 * entry point, etc.  Though this does not represent a tremendous amount of code, it has to be done
 * in many clients, and one has to remember to close the library and free the memory once the
 * context is no longer used.  In order to simplify this, this function takes on the responsibility
 * of managing the lifecycle of the context buffer and the library, simplifying the client code.  It
 * loads the library, gets the proper init function, allocates the context buffer, and closes the
 * library and frees the context right after the context's finalize function is called.  This is
 * achieved by modifying the TCTI context from the TCTI library, where the finalize function is
 * swapped with a tss2_helper fini function, and where the original finalize function pointer is
 * stored right before the context pointer in memory.  When the swapped finalize function is called,
 * the original finalize function is retrieved and called, the library is closed, and then the
 * buffer is freed.
 *
 * @param[in] lib_path The path to the tcti library to be used for initializing the tcti context.
 * @param[out] context A pointer to a location where the newly created and initialized context will
 *                     be stored.
 * @param[in] config   The configuration string to be used when initializing the TCTI context. As
 *                     per the TCTI standard, this can be NULL if the default configuration is to be
 *                     used.
 *
 * @return TSS2_RC_SUCCESS on success, and a tss2 return code (TSS2_RC) on failure.
 */
#ifdef __QNXNTO__
TSS2_RC tss2_helper_tcti_lib_init_alloc(const char *__lib_path, TSS2_TCTI_CONTEXT **__context, const char *__config);
#endif /* __QNXNTO__ */

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_TSS2_HELPER_TCTI_H_INCLUDED */
