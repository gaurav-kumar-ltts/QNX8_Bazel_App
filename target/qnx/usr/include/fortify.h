/*
 * Copyright (c) 2019-2021, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */

#ifndef _FORTIFY_H_INCLUDED
#define _FORTIFY_H_INCLUDED

#include <sys/cdefs.h>


__BEGIN_DECLS


extern void __fortify_fail_extra_arg(void) __attribute__((__noreturn__));
extern void __fortify_fail_fmt_n(void) __attribute__((__noreturn__));
extern void __fortify_fail_missing_arg(void) __attribute__((__noreturn__));
extern void __fortify_fail_overflow_dst(void) __attribute__((__noreturn__));

#define __FORTIFY_DIAG_PREFIX                    "_FORTIFY_SOURCE: "

#define __FORTIFY_ERROR_ATTRIBUTE(msg)           __ERROR_ATTRIBUTE(__FORTIFY_DIAG_PREFIX msg)
#define __FORTIFY_WARNING_ATTRIBUTE(msg)         __WARNING_ATTRIBUTE(__FORTIFY_DIAG_PREFIX msg)

/* If _FORTIFY_SOURCE_WARNINGS_ONLY is defined as a nonzero value, emit warnings in place of errors for function calls that are
 * known at compile time to always be unsafe/incorrect. Such function calls will each be replaced with an unconditional call to the
 * appropriate __fortify_fail_* function. This feature can be used to obtain a complete list of _FORTIFY_SOURCE compile-time
 * diagnostics for a given codebase. When _FORTIFY_SOURCE_WARNINGS_ONLY is enabled, the -Wsystem-headers compiler option should also
 * be specified to prevent the compiler from silencing warnings that originate from the expansion of macros defined in system
 * headers (e.g. memcpy_isr, SETIOV, etc.). */
#if defined(_FORTIFY_SOURCE_WARNINGS_ONLY) && ( _FORTIFY_SOURCE_WARNINGS_ONLY != 0 )
#define __FORTIFY_FAIL_DIAG_ATTRIBUTE(msg)       __FORTIFY_WARNING_ATTRIBUTE(msg)
#else
#define __FORTIFY_FAIL_DIAG_ATTRIBUTE(msg)       __FORTIFY_ERROR_ATTRIBUTE(msg)
#endif

/* Macro that declares an alias of one of the __fortify_fail_* functions with an associated compile-time diagnostic message. When
 * the compiler encounters a call to the declared function that can't be optimized away, it emits the diagnostic message. */
#define __FORTIFY_FAIL_ALIAS_DECL(func_name, aliased_func_name, diag_msg)  \
        extern void func_name(void) __ALIASATTR(#aliased_func_name) \
                __attribute__((__noreturn__)) \
                __FORTIFY_FAIL_DIAG_ATTRIBUTE(diag_msg)

/* Results for parameter validation */
enum __fortify_result_e {
    __FORTIFY_RESULT_OK = 0,
    __FORTIFY_RESULT_OVERFLOW_DST,
};

/* <STAN_MACRO1> */
/**
 * Evaluates the specified failure condition. If it is @c true, calls one of two specified failure functions depending on how many
 * different values are possible for a specified expression. This macro implements a conditional construct that forms the basis of
 * the majority of the compile-time and run-time checks performed by the _FORTIFY_SOURCE feature.
 *
 * @param[in]  expr             Variable/expression validated by the failure condition.
 * @param[in]  fail_condition   Boolean expression used to validate the specified variable/expression. If @c true, one of the two
 *                              specified failure functions is called. @c expr should be the only term in this expression that
 *                              potentially varies at run time.
 * @param[in]  const_fail_func  Function to call when @c fail_condition evaluates to @c true and only one value is possible for
 *                              @c expr. Typically this is an alias of @c fail_func, but with a diagnostic message attributed to it.
 * @param[in]  fail_func        Function to call when @c fail_condition evaluates to @c true and multiple values are possible for
 *                              @c expr.
 *
 * @par Implementation notes:
 * - @c __builtin_constant_p(expr) is purposefully evaluated before @c fail_condition to prevent @c const_fail_func from being
 *   incorrectly called in scenarios where multiple values possible for @c expr, but only a single value leads to @c fail_condition
 *   evaluating to @c true.
 * - @c __unlikely(fail_condition) encourages the compiler to optimize for the case where @c fail_condition evaluates to @c false.
 *   Use of @c __unlikely is unnecessary when <tt>__builtin_constant_p(expr) == 1</tt> as @c fail_condition should in that case be a
 *   constant expression.
 */
#define __FORTIFY_CHK(expr, fail_condition, const_fail_func, fail_func)  \
        do { \
            if ( __builtin_constant_p(expr) ) { \
                if ( fail_condition ) { \
                    (const_fail_func)(); \
                } \
            } else { \
                if ( __unlikely(fail_condition) ) { \
                    (fail_func)(); \
                } \
            } \
        } while ( 0 )
/* <STAN_MACRO1> */

/* <STAN_MACRO1> */
/**
 * Calls either @c __fortify_fail_overflow_dst or the specified failure function when there are fewer than the specified number of
 * elements remaining in the specified object.
 *
 * @param[in]  bos_type         Type of object size calculation to use. @c __BOS_TYPE_DEFAULT should be specified unless it results
 *                              in too many false positives, in which case @c __BOS_TYPE_OUTER may be more appropriate.
 * @param[in]  dst              Pointer to destination object. Note that @c sizeof((dst)[0]) is used to determine the size of each
 *                              element that the function being fortified will potentially write to the destination object, so be
 *                              sure this pointer has an appropriate type.
 * @param[in]  num_elems        Number of elements the function being fortified will potentially write into the destination object.
 *                              Expected to be an unsigned value of integer type.
 * @param[in]  precondition     Precondition to check before validating @c num_elems against the size of the destination object (or
 *                              @c 1 if there is no precondition to check). @c num_elems should be the only term in the precondition
 *                              that potentially varies at run time. E.g.: <tt>num_elems > 0</tt> would be an appropriate
 *                              precondition when the function being fortified already gracefully handles negative values of
 *                              @c num_elems.
 * @param[in]  const_fail_func  Function to call instead of @c __fortify_fail_overflow_dst when only one value is possible for
 *                              @c num_elems. Expected to be an alias of @c __fortify_fail_overflow_dst, but with a diagnostic
 *                              message attributed to it.
 */
#define __FORTIFY_CHK_OVERFLOW_DST(bos_type, dst, num_elems, precondition, const_fail_func)  \
        do { \
            if ( __builtin_object_size((dst), (bos_type)) != __BOS_UNKNOWN ) { \
                __FORTIFY_CHK( \
                        (num_elems), \
                        ( precondition ) && ( (num_elems) > (__builtin_object_size((dst), (bos_type)) / sizeof((dst)[0])) ), \
                        (const_fail_func), \
                        __fortify_fail_overflow_dst); \
            } \
        } while ( 0 )
/* </STAN_MACRO1> */

/* <STAN_MACRO1> */
/**
 * Calls either @c __fortify_fail_overflow_dst or the specified failure function when there are fewer than the specified number of
 * elements remaining in the specified object, starting at the specified byte offset.
 *
 * @param[in]  bos_type         Type of object size calculation to use. @c __BOS_TYPE_DEFAULT should be specified unless it results
 *                              in too many false positives, in which case @c __BOS_TYPE_OUTER may be more appropriate.
 * @param[in]  dst              Pointer to destination object.
 * @param[in]  offset           Constant integer expression indicating the byte offset into the destination object where the
 *                              function being fortified will start writing data. E.g.: @c __builtin_offsetof(dst, member)
 * @param[in]  elem_size        Constant integer expression indicating the size of each element that the function being fortified
 *                              will potentially write into the destination object. E.g.: @c sizeof(dst->member[0])
 * @param[in]  num_elems        Number of elements the function being fortified will potentially write into the destination object
 *                              starting at the specified byte offset. Expected to be an unsigned value of integer type.
 * @param[in]  precondition     Precondition to check before validating @c num_elems against the size of the destination object (or
 *                              @c 1 if there is no precondition to check). @c num_elems should be the only term in the precondition
 *                              that potentially varies at run time. E.g.: <tt>num_elems > 0</tt> would be an appropriate
 *                              precondition when the function being fortified already gracefully handles negative values of
 *                              @c num_elems.
 * @param[in]  const_fail_func  Function to call instead of @c __fortify_fail_overflow_dst when only one value is possible for
 *                              @c num_elems. Expected to be an alias of @c __fortify_fail_overflow_dst, but with a diagnostic
 *                              message attributed to it.
 */
#define __FORTIFY_CHK_OVERFLOW_DST_OFFSET(bos_type, dst, offset, elem_size, num_elems, precondition, const_fail_func)  \
        do { \
            if ( __builtin_object_size((dst), (bos_type)) != __BOS_UNKNOWN ) { \
                if ( __builtin_object_size((dst), (bos_type)) < (offset) ) { \
                    (const_fail_func)(); \
                } else { \
                    __FORTIFY_CHK( \
                            (num_elems), \
                            ( precondition ) && \
                                    ( (num_elems) > ((__builtin_object_size((dst), (bos_type)) - (offset)) / (elem_size)) ), \
                            (const_fail_func), \
                            __fortify_fail_overflow_dst); \
                } \
            } \
        } while ( 0 )
/* </STAN_MACRO1> */

/* <STAN_MACRO5> */
/**
 * Calls either @c __fortify_fail_overflow_dst or the specified failure function when there are fewer than the specified number of
 * elements remaining in the specified object, starting at the specified member.
 *
 * @param[in]  bos_type           Type of object size calculation to use. @c __BOS_TYPE_DEFAULT should be specified unless it
 *                                results in too many false positives, in which case @c __BOS_TYPE_OUTER may be more appropriate.
 * @param[in]  dst                Pointer to destination object.
 * @param[in]  first_member_elem  Member designator for the first member element of the destination object that the function being
 *                                fortified will potentially write. E.g., @c member_array[0], if @c member_array is an array member
 *                                of @c dst.
 * @param[in]  num_elems          Number of elements the function being fortified will potentially write into the destination object
 *                                starting with the member element indicated by @c first_member_element. Expected to be an unsigned
 *                                value of integer type.
 * @param[in]  precondition       Precondition to check before validating @c num_elems against the size of the destination object
 *                                (or @c 1 if there is no precondition to check). @c num_elems should be the only term in the
 *                                precondition that potentially varies at run time. E.g.: <tt>num_elems > 0</tt> would be an
 *                                appropriate precondition when the function being fortified already gracefully handles negative
 *                                values of @c num_elems.
 * @param[in]  const_fail_func    Function to call instead of @c __fortify_fail_overflow_dst when only one value is possible for
 *                                @c num_elems. Expected to be an alias of @c __fortify_fail_overflow_dst, but with a diagnostic
 *                                message attributed to it.
 */
#define __FORTIFY_CHK_OVERFLOW_DST_MEMBER(bos_type, dst, first_member_elem, num_elems, precondition, const_fail_func)  \
        __FORTIFY_CHK_OVERFLOW_DST_OFFSET( \
                (bos_type), \
                (dst), \
                __builtin_offsetof(__typeof__(*(dst)), first_member_elem), \
                sizeof((dst)->first_member_elem), \
                (num_elems), \
                (precondition), \
                (const_fail_func))
/* </STAN_MACRO5> */


__END_DECLS

#endif
