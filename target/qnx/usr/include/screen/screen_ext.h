/*
 * $QNXLicenseC:
 * Copyright 2020-2025, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */
/**
*   @file screen_ext.h
*   @brief Extended functions for the Screen library
*
*   This file defines extended Screen API functions that are supported by
*   the Screen library. The Screen API facilitates the communication
*   between applications and Screen services.
*/

#ifndef _SCREEN_SCREEN_EXT_H_
#define _SCREEN_SCREEN_EXT_H_

#include <screen/screen.h>

/** @brief Qualcomm supported pixel formats.
*   @details Qualcomm's Venus NV12 10-bit UBWC is a compressed macro-tile format for NV12.
*   For more information, refer to the COLOR_FMT_NV12_UBWC section in your Qualcomm documentation.
*
*   Make sure that the pixel format definitions match those in @c wfdext.h.
*   @anonenum QCOM_Screen_Pixel_Format Qualcomm Screen Pixel Format
*/
enum {
	SCREEN_FORMAT_QC_TP10 = (3 << 16) | SCREEN_FORMAT_NV12,
};

/** @brief The feature preprocessor definition that indicates the definition of the following RGX
 *  formats are supported.
 */
#define SCREEN_FORMAT_RG16_RGX SCREEN_FORMAT_RG16_RGX
#define SCREEN_FORMAT_RG16UI_RGX SCREEN_FORMAT_RG16UI_RGX
#define SCREEN_FORMAT_RGBA16_RGX SCREEN_FORMAT_RGBA16_RGX
#define SCREEN_FORMAT_RGBA16UI_RGX SCREEN_FORMAT_RGBA16UI_RGX

/** Formats supported by RGX DDK. Can be used as the source for samplers and as
*   render targets. The use of these formats does not imply displaying, they
*   can be used mostly for storage of data in a specific format. Endianness of
*   all multibyte components is native to the host.
*/
enum {
	/** OpenGL: n/a, Vulkan: VK_FORMAT_R16G16_UNORM
	*   Specifies a two-component, 32-bit unsigned normalized format that has a 16-bit R
	*   component in bytes 0..1, and a 16-bit G component in bytes 2..3.
	*/
	SCREEN_FORMAT_RG16_RGX = (('i' << 24) | (7 << 16) | SCREEN_FORMAT_BYTE),

	/** OpenGL: GL_RG16UI, Vulkan: VK_FORMAT_R16G16_UINT
	*   Specifies a two-component, 32-bit unsigned integer format that has a 16-bit R
	*   component in bytes 0..1, and a 16-bit G component in bytes 2..3.
	*/
	SCREEN_FORMAT_RG16UI_RGX = (('i' << 24) | (8 << 16) | SCREEN_FORMAT_BYTE),

	/** OpenGL: n/a, Vulkan: VK_FORMAT_R16G16B16A16_UNORM
	*   specifies a four-component, 64-bit unsigned normalized format that has a 16-bit R
	*   component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component
	*   in bytes 4..5, and a 16-bit A component in bytes 6..7.
	*/
	SCREEN_FORMAT_RGBA16_RGX = (('i' << 24) | (15 << 16) | SCREEN_FORMAT_BYTE),

	/** OpenGL: GL_RGBA16UI, Vulkan: VK_FORMAT_R16G16B16A16_UINT
	*   Specifies a four-component, 64-bit unsigned integer format that has a 16-bit R
	*   component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component
	*   in bytes 4..5, and a 16-bit A component in bytes 6..7.
	*/
	SCREEN_FORMAT_RGBA16UI_RGX = (('i' << 24) | (16 << 16) | SCREEN_FORMAT_BYTE),
};

/** Common supported pixel formats for DRM-based drivers.
*
*   Make sure that the pixel format definitions match those in @c wfdext.h.
*/
enum {
	/** YU16 format. Similar to YU12 (YUV420), but the U and V planes use 2:1 horizontal
	* subsampling. Also referred to as 422H in VA-API and YUV422 in DRM. The FOURCC
	* code is ('Y', 'U', '1', '6').
	*/
	SCREEN_FORMAT_DRM_YU16 = ((1 << 20) | SCREEN_FORMAT_BYTE),
	/** YU24 format. Similar to YU12 (YUV420), but the U and V planes have no
	* subsampling (1:1). Also referred to as 444P in VA-API and YUV444 in DRM.
	* The FOURCC code is ('Y', 'U', '2', '4').
	*/
	SCREEN_FORMAT_DRM_YU24 = ((2 << 20) | SCREEN_FORMAT_BYTE),
};

#endif /* _SCREEN_SCREEN_EXT_H_ */
