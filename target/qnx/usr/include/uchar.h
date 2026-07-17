/*
 * Some modifications Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

/* uchar.h added header for TR 19769 */
#ifndef _UCHAR_H_INCLUDED
#define _UCHAR_H_INCLUDED
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

		/* macros */
#ifndef NULL
 #define NULL	_NULL
#endif /* NULL */

__BEGIN_DECLS

		/* TYPE DEFINITIONS */

typedef _Mbstatet mbstate_t;

 #if !defined(_SIZE_T) && !defined(_SIZET) && !defined(_SIZE_T_DEFINED) \
	&& !defined(_BSD_SIZE_T_DEFINED_)
  #define _SIZE_T
  #define _SIZET
  #define _BSD_SIZE_T_DEFINED_
  #define _SIZE_T_DEFINED
  #define _STD_USING_SIZE_T
typedef _Sizet size_t;
 #endif /* !defined(_SIZE_T) etc. */

		/* declarations */
size_t mbrtoc16(char16_t *_Restrict, const char *_Restrict,
	size_t, mbstate_t *_Restrict);
size_t c16rtomb(char *_Restrict, char16_t,
	mbstate_t *_Restrict);

size_t mbrtoc32(char32_t *_Restrict, const char *_Restrict,
	size_t, mbstate_t *_Restrict);
size_t c32rtomb(char *_Restrict, char32_t,
	mbstate_t *_Restrict);

__END_DECLS

#if __NTO_FORTIFY_LEVEL > 0
 #include <uchar_chk.h>
#endif

#endif /* _UCHAR_H_INCLUDED */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */
