/*
 * $QNXLicenseC:
 * Copyright 2007-2020, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

/*
 *  The only symbols made visible by this header are
 *  OS/compiler reserved symbols.
 */
#ifndef __COMPILER_GNU_H_INCLUDED
#define __COMPILER_GNU_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#error sys/compiler_gnu.h should not be included directly.
#endif

#undef mips

#ifdef __CHAR_UNSIGNED__
# undef __CHAR_SIGNED__
#else
# ifndef __CHAR_SIGNED__
#  define __CHAR_SIGNED__
# endif
#endif

#ifdef __GNUG__
# undef _NULL
# define _NULL __null
#endif

#if !defined (__cplusplus) && defined(__WCHAR_TYPE__)
# undef __WCHAR_T
# define __WCHAR_T __WCHAR_TYPE__
#endif

#ifdef __WCHAR_MAX__
# undef _WCMAX
# define _WCMAX __WCHAR_MAX__
#endif

#ifdef __WCHAR_MIN__
# undef _WCMIN
# define _WCMIN __WCHAR_MIN__
#endif

#if !defined(__BIGENDIAN__) && !defined(__LITTLEENDIAN__)
# error Endian not defined
#endif

#ifndef	__CDEFS_H_INCLUDED
# include _NTO_HDR_(sys/cdefs.h)
#endif

#if defined(__CHAR_BIT__) && defined(__SIZEOF_INT__)
# define __INT_BITS__	(__CHAR_BIT__*__SIZEOF_INT__)
#else
# define __INT_BITS__	32
#endif

#if defined(__CHAR_BIT__) && defined(__SIZEOF_POINTER__)
# define __PTR_BITS__	(__CHAR_BIT__*__SIZEOF_POINTER__)
#else
# define __PTR_BITS__	32
#endif

#if defined(__CHAR_BIT__) && defined(__SIZEOF_LONG__)
# define __LONG_BITS__	(__CHAR_BIT__*__SIZEOF_LONG__)
#else
# define __LONG_BITS__	32
#endif

#if defined(__X86_64__)
# define __LONGDOUBLE_BITS__		80
#elif defined(__CHAR_BIT__) && defined(__SIZEOF_LONG_DOUBLE__)
# define __LONGDOUBLE_BITS__		(__CHAR_BIT__*__SIZEOF_LONG_DOUBLE__)
#else
# error not configured for CPU
#endif

#if defined(__CHAR_BIT__) && defined(__SIZEOF_SIZE_T__)
# define __SIZE_BITS__		(__CHAR_BIT__*__SIZEOF_SIZE_T__)
#else
# define __SIZE_BITS__		__INT_BITS__
#endif

#define __INT64_ALIGN

typedef int							_GCC_ATTR_ALIGN_64t __attribute__((__mode__(__DI__)));
typedef unsigned int				_GCC_ATTR_ALIGN_u64t __attribute__((__mode__(__DI__)));
typedef _GCC_ATTR_ALIGN_64t			_Int64t __INT64_ALIGN;
typedef _GCC_ATTR_ALIGN_u64t		_Uint64t __INT64_ALIGN;

#if __INT_BITS__ == 32
typedef unsigned					_GCC_ATTR_ALIGN_u32t;
typedef int							_GCC_ATTR_ALIGN_32t;
typedef _GCC_ATTR_ALIGN_u32t		_Uint32t;
typedef _GCC_ATTR_ALIGN_32t			_Int32t;
#else
#error __INT_BITS not 32
#endif

typedef int							_GCC_ATTR_ALIGN_16t __attribute__((__mode__(__HI__)));
typedef unsigned int				_GCC_ATTR_ALIGN_u16t __attribute__((__mode__(__HI__)));
typedef _GCC_ATTR_ALIGN_16t			_Int16t;
typedef _GCC_ATTR_ALIGN_u16t		_Uint16t;

typedef int							_GCC_ATTR_ALIGN_8t __attribute__((__mode__(__QI__)));
typedef unsigned int				_GCC_ATTR_ALIGN_u8t __attribute__((__mode__(__QI__)));
typedef _GCC_ATTR_ALIGN_8t			_Int8t;
typedef _GCC_ATTR_ALIGN_u8t			_Uint8t;

#if __PTR_BITS__ == 64
typedef _Uint64t					_Uintptrt;
typedef _Int64t						_Intptrt;
#else
#error Unable to declare integral pointer type
#endif

typedef _Uint32t					_Size32t;
typedef _Uint64t					_Size64t;
typedef _Int32t						_Ssize32t;
typedef _Int64t						_Ssize64t;
#if __SIZEOF_SIZE_T__+0 == 8
typedef _Uint64t					_Sizet;
typedef _Int64t						_Ssizet;
#else
#error Unable to declare size_t type
#endif

#if defined(__PTRDIFF_TYPE__)
typedef __PTRDIFF_TYPE__				_Ptrdifft;
#else
typedef _Intptrt					_Ptrdifft;
#endif

__extension__ typedef long long				_Longlong;
__extension__ typedef unsigned long long	_ULonglong;

/* alignment of struct is the maximum alignment of any standard type */
typedef struct {
	long long __ll __attribute__((__aligned__(__alignof__(long long))));
	long double __ld __attribute__((__aligned__(__alignof__(long double))));
} _Maxalignt;

/*
 * This is to override the gcc local include files to use
 * our definition of the following types
 */
#define _GCC_PTRDIFF_T
#define _GCC_SIZE_T
#define _GCC_WCHAR_T

/*
 * -ansi			defines __STRICT_ANSI__
 * -traditional		undefines __STDC__ and __STDC_VERSION__
 */

#if defined(__STDC__) && !defined(__STRICT_ANSI__)
# define __EXT
#endif

/*
  For __GNUC__ < 3, we have platform specific implementations of var args
  in the CPU/platform.h headers.  For gcc-3 or newer, we use the builtins
  for the stdarg.h mechanisms, and leave the varargs.h as it is since the
  varargs.h stuff is deprecated in gcc-3.X.
*/

#if (__GNUC__ >= 3)

#ifndef __GNUC_VA_LIST
# define __GNUC_VA_LIST
typedef __builtin_va_list __gnuc_va_list;
#endif

typedef __gnuc_va_list                __NTO_va_list;
#define __NTO_va_start_stdarg(__p1,__p2)  __builtin_va_start(__p1,__p2)
#define __NTO_va_arg(__p1, __p2)          __builtin_va_arg(__p1,__p2)
#define __NTO_va_end(__p1)                __builtin_va_end(__p1)
#define __NTO_va_copy(__d,__s)            __builtin_va_copy(__d,__s)
#endif

#endif

#define __ALIAS_ATTRIBUTE(n)	__asm(n)

#ifndef __ALIAS
#define __ALIAS(name, args, func) name args __ALIAS_ATTRIBUTE(func)
#endif

#if defined(_FORTIFY_SOURCE) && ( _FORTIFY_SOURCE > 0 ) && defined(__QNXNTO__)
# if ( ( __GNUC__ > 4 ) || ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ >= 1 ) ) ) && defined(__OPTIMIZE__) && ( __OPTIMIZE__ > 0 )
#  if _FORTIFY_SOURCE > 1
#   if _FORTIFY_SOURCE > 2
#    warning _FORTIFY_SOURCE > 2 not supported; applying 2 instead
#   endif /* if _FORTIFY_SOURCE > 2 */
#   define __NTO_FORTIFY_LEVEL 2
#  else
#   define __NTO_FORTIFY_LEVEL 1
#  endif /* if _FORTIFY_SOURCE > 1 */
# else
#  warning _FORTIFY_SOURCE > 0 requires compiling with optimization enabled (-O); applying 0 instead
#  define __NTO_FORTIFY_LEVEL 0
# endif /* if ... ( __OPTIMIZE__ > 0 ) */
#else
# define __NTO_FORTIFY_LEVEL 0
#endif /* if ... ( _FORTIFY_SOURCE > 0 ) && defined(__QNXNTO__) */

#define __bconst(n) __builtin_constant_p(n)

#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))

/*
 * Different types of object size calculation. Specify one of these constants as the type argument to
 * __builtin_object_size(ptr, type):
 *
 *     __BOS_TYPE_OUTER:    Return the number of bytes remaining in the outermost object (whole variable) that ptr references.
 *     __BOS_TYPE_INNER:    Return the number of bytes remaining in the innermost object (struct member) that ptr references.
 *     __BOS_TYPE_DEFAULT:  Defined as __BOS_TYPE_OUTER when the _FORTIFY_SOURCE feature is enabled at level 1. Defined as
 *                          __BOS_TYPE_INNER when the _FORTIFY_SOURCE feature is enabled at level 2 or greater.
 */
# define __BOS_TYPE_OUTER  0
# define __BOS_TYPE_INNER  1
# if __NTO_FORTIFY_LEVEL > 1
#  define __BOS_TYPE_DEFAULT  __BOS_TYPE_INNER
# else
#  define __BOS_TYPE_DEFAULT  __BOS_TYPE_OUTER
# endif

/* Value returned by __builtin_object_size when an object's size can't be determined */
# define __BOS_UNKNOWN     ((_Sizet)-1)

# define __bos_default(ptr)  __builtin_object_size((ptr), __BOS_TYPE_DEFAULT)
# define __bos_outer(ptr)    __builtin_object_size((ptr), __BOS_TYPE_OUTER)
/* Define __bos and __bos0 for backwards compatibility */
# if defined(__QNXNTO__)
#  define __bos(ptr)          __bos_default(ptr)
#  define __bos0(ptr)         __bos_outer(ptr)
# endif
#endif

#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
# define __bvap __builtin_va_arg_pack()
# define __bvap_len __builtin_va_arg_pack_len()
# define __ERROR_ATTRIBUTE(msg)  __attribute__((__error__(msg)))
# define __WARNING_ATTRIBUTE(msg)  __attribute__((__warning__(msg)))
# define __ERRORDECL(name, msg)  extern void name(void) __ERROR_ATTRIBUTE(msg)
#else
# define __ERROR_ATTRIBUTE(msg)
# define __WARNING_ATTRIBUTE(msg)
# define __ERRORDECL(name, msg)  extern void name(void)
#endif

#ifndef __ARTIFICIAL
#if !defined(__clang__)
# define  __ARTIFICIAL __attribute__((__artificial__))
#else
# define  __ARTIFICIAL
#endif
#endif

#ifndef __ALWAYS_INLINE
# if defined __GNUC_STDC_INLINE__
# define __ALWAYS_INLINE __inline  __attribute__((__gnu_inline__,always_inline))
#else
# define __ALWAYS_INLINE __inline  __attribute__((always_inline))
#endif
#endif

#ifndef __FORTIFY_FUNCTION
# define __FORTIFY_FUNCTION __ALWAYS_INLINE __ARTIFICIAL
#endif

#ifndef __LINKER_WARNING
# define __LINKER_WARNING(__symbol, __string) \
__asm__(".section .gnu.warning." #__symbol ";.asciz \"" __string "\";.previous");
#endif

#define __likely(x)    __builtin_expect(!!(x), 1)
#define __unlikely(x)  __builtin_expect(!!(x), 0)

/* <STAN_MACRO5> */
/**
 * Evaluates to a pointer to the specified member of an object. This pointer has same type and value as the expression
 * <tt>&(obj)->member</tt>, but for the purposes of object size determination (e.g. @c __builtin_object_size) the compiler
 * associates it with the same object bounds as the @c obj pointer. This macro provides a means of working around false-positive
 * buffer overflow failures that may arise when enabling the @c _FORTIFY_SOURCE feature at level 2. The intermediate cast to
 * <tt>void *</tt> in the replacement expression is necessary to avoid a <tt>-Wcast-align</tt> diagnostic message.
 *
 * @param[in]  obj     Pointer to an object of a structure or union type which defines the member specified via the @c member
 *                     parameter.
 * @param[in]  member  Designator of the member to obtain a pointer to, in the same format as the second parameter of @c offsetof
 *                     macro. This member may be defined within one or more sub-structures and/or sub-unions within the referenced
 *                     type of @c obj.
 *
 * @return  A pointer with the same type and value as the expression <tt>&(obj)->member</tt>.
 */
#define __OBJ_BOUNDED_MEMBER_PTR(obj, member)  \
        ((__typeof__(&((obj)->member)))((void *)((char *)(obj) + __builtin_offsetof(__typeof__(*(obj)), member))))
/* </STAN_MACRO5> */
