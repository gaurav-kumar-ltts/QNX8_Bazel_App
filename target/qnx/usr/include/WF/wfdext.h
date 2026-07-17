#ifndef _WFD_H_
# error include <WF/wfd.h> before including <WF/wfdext.h>
#endif
#ifndef __wfdext_h_
#define __wfdext_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <WF/wfdplatform.h>

/*************************************************************/

#define WFD_WFDEXT_VERSION 1

#ifndef WFD_QNX_cbabc
#define WFD_QNX_cbabc 1
#define WFD_EXTNAME_WFD_QNX_cbabc "WFD_QNX_cbabc"
#define WFD_PORT_CBABC_MODE_QNX 0x7670
typedef enum
{   WFD_PORT_CBABC_MODE_NONE_QNX   = 0x7671,
	WFD_PORT_CBABC_MODE_VIDEO_QNX  = 0x7672,
	WFD_PORT_CBABC_MODE_UI_QNX     = 0x7673,
	WFD_PORT_CBABC_MODE_PHOTO_QNX  = 0x7674,
	WFD_PORT_CBABC_MODE_32BIT_QNX  = 0x7FFFFFFF
} WFDPortCBABCModeQNX;

#endif

#ifndef WFD_QNX_bchs_filter
/**
 * This extension provides attributes for controlling the brightness,
 * contrast, hue, and saturation to be applied to a pipeline's image.
 *
 * The values are applied before layer blending.  Normally, they're applied
 * during YCbCr-to-RGB conversion, and therefore don't affect buffers already
 * in an RGB format.
 */
#define WFD_QNX_bchs_filter 1
#define WFD_EXTNAME_WFD_QNX_bchs_filter "WFD_QNX_bchs_filter"
/**
 * This pipeline attribute specifies the brightness to apply.
 *
 * Storage type: @c WFDint; read/write
 * Range: [-255, 255] from darkest to brightest
 * Default: 0
 * Accessors: @c wfdGetPipelineAttribi(), @c wfdSetPipelineAttribi()
 */
#define WFD_PIPELINE_BRIGHTNESS_QNX		0x7750
/**
 * This pipeline attribute specifies the contrast to apply.
 *
 * Storage type: @c WFDint; read/write
 * Range: [-128, 127] from least to most contrast
 * Default: 0
 * Accessors: @c wfdGetPipelineAttribi(), @c wfdSetPipelineAttribi()
 */
#define WFD_PIPELINE_CONTRAST_QNX		0x7751
/**
 * This pipeline attribute specifies the hue to apply.
 *
 * Storage type: @c WFDint; read/write
 * Range: [-128, 127]
 * Default: 0
 * Accessors: @c wfdGetPipelineAttribi(), @c wfdSetPipelineAttribi()
 */
#define WFD_PIPELINE_HUE_QNX			0x7752
/**
 * This pipeline attribute specifies the saturation to apply.
 *
 * Storage type: @c WFDint; read/write
 * Range: [-128, 127] from least to most saturation
 * Default: 0
 * Accessors: @c wfdGetPipelineAttribi(), @c wfdSetPipelineAttribi()
 */
#define WFD_PIPELINE_SATURATION_QNX		0x7753
#endif

#ifndef WFD_QNX_pipeline_color_space
/**
 * This extension allows setting of pipeline's color space.
 */
#define WFD_QNX_pipeline_color_space 1
#define WFD_EXTNAME_WFD_QNX_pipeline_color_space "WFD_QNX_pipeline_color_space"
/**
 * This pipeline attribute specifies the color space to apply.
 *
 * Storage type: @c WFDint; read/write
 * Range: Values defined below
 * Default: WFD_COLOR_SPACE_UNCORRECTED_QNX
 * Accessors: @c wfdGetPipelineAttribi(), @c wfdSetPipelineAttribi()
 */
#define WFD_PIPELINE_COLOR_SPACE_QNX        0x77A0

/* Those defines needs to match with screen.h */
#define WFD_COLOR_SPACE_UNCORRECTED_QNX     0x0
#define WFD_COLOR_SPACE_SRGB_QNX            0x1
#define WFD_COLOR_SPACE_LRGB_QNX            0x2
#define WFD_COLOR_SPACE_BT601_QNX           0x3
#define WFD_COLOR_SPACE_BT601_FULL_QNX      0x4
#define WFD_COLOR_SPACE_BT709_QNX           0x5
#define WFD_COLOR_SPACE_BT709_FULL_QNX      0x6
#endif

#ifndef WFD_QNX_pipeline_alpha_blend_mode
#define WFD_QNX_pipeline_alpha_blend_mode 1
#define WFD_EXTNAME_WFD_QNX_pipeline_alpha_blend_mode "WFD_QNX_pipeline_alpha_blend_mode"
/**
 * This pipeline attribute specifies the alpha blending mode
 *
 * Storage type: @c WFDint; write
 * Range: Possible values are non-premultiplied alpha blending and pre-multiplied alpha blending
 * Default: WFD_NON_PRE_MULTIPLIED_ALPHA_QNX
 * Accessors: @c wfdSetPipelineAttribi()
 */
#define WFD_PIPELINE_ALPHA_BLEND_MODE_QNX   0x77A1

/* Those defines needs to match with screen.h */
#define WFD_NON_PRE_MULTIPLIED_ALPHA_QNX    0x0
#define WFD_PRE_MULTIPLIED_ALPHA_QNX        0x1
#endif

#ifndef WFD_QNX_port_mode_info
/**
 * @brief Indicates that two extra port mode attributes are available:
 * @c WFD_PORT_MODE_PREFERRED_QNX and @c WFD_PORT_MODE_ASPECT_RATIO_QNX.
 */
#define WFD_QNX_port_mode_info 1
#define WFD_EXTNAME_WFD_QNX_port_mode_info "WFD_QNX_port_mode_info"
/**
 * This port mode attribute specifies the aspect ratio the display will have
 * when the mode is used.
 *
 * Storage type: @c WFDfloat; read-only
 * Accessors: @c wfdGetPortModeAttribf()
 */
#define WFD_PORT_MODE_ASPECT_RATIO_QNX  0x7606
/**
 * This port mode attribute specifies whether the mode is "preferred".  A WFD client
 * should select a preferred mode if the user has not configured another.
 *
 * Storage type: @c WFDboolean; read-only
 * Accessors: @c wfdGetPortModeAttribi()
 */
#define WFD_PORT_MODE_PREFERRED_QNX     0x7607
#endif

#ifndef WFD_QNX_avoid_unconfigured_ports
/**
 * @brief Indicates that the client should avoid creating ports unnecessarily.
 *
 * If the driver lists this extension as supported, wfdCreatePort() shouldn't
 * be called for ports the user didn't explicitly configure/enable.
 */
#define WFD_QNX_avoid_unconfigured_ports 1
#define WFD_EXTNAME_WFD_QNX_avoid_unconfigured_ports "WFD_QNX_avoid_unconfigured_ports"
#endif

#ifndef WFD_QNX_vsync
#define WFD_QNX_vsync 1
#define WFD_EXTNAME_WFD_QNX_vsync "WFD_QNX_vsync"
#ifdef WFD_WFDEXT_PROTOTYPES
/**
 * @brief Wait for a vertical synchronization (VSync) on the specified port.
 *
 * For this function, VSync is an instantaneous event that occurs
 * once in each vertical blanking interval, at an unspecified time.
 *
 * @param device  A WFD device handle.
 * @param port    A port handle associated with @c device.
 *
 * @retval WFD_ERROR_NONE           Success.
 * @retval WFD_ERROR_BAD_DEVICE     @c device was not a valid handle.
 * @retval WFD_ERROR_BAD_HANDLE     @c port was not a valid handle
 *                                  for @c device.
 * @retval WFD_ERROR_INCONSISTENCY  The port has no active signal.
 * @retval WFD_ERROR_NOT_SUPPORTED  The port does not support this event.
 *
 * This function does not affect values returned by @c wfdGetError().
 */
WFD_API_CALL WFDErrorCode WFD_APIENTRY
    wfdWaitForVSyncQNX(WFDDevice device, WFDPort port) WFD_APIEXIT;
#endif /* WFD_WFDEXT_PROTOTYPES */
typedef WFDErrorCode (WFD_APIENTRY PFNWFDWAITFORVSYNCQNX) (WFDDevice device, WFDPort port);
#endif

#ifndef WFD_QNX_egl_images
/**
 * This extension provides a way to allocate and deallocate memory for graphics buffers.
 */
#define WFD_QNX_egl_images 1
#define WFD_EXTNAME_WFD_QNX_egl_images "WFD_QNX_egl_images"
#define WFD_USAGE_DISPLAY_QNX      (1 << 0)
#define WFD_USAGE_READ_QNX         (1 << 1)
#define WFD_USAGE_WRITE_QNX        (1 << 2)
#define WFD_USAGE_NATIVE_QNX       (1 << 3)
//#define WFD_USAGE_OPENGL_ES1_QNX   (1 << 4) /*Deprecated*/
#define WFD_USAGE_OPENGL_ES2_QNX   (1 << 5)
#define WFD_USAGE_OPENGL_ES3_QNX   (1 << 11)
#define WFD_USAGE_OPENVG_QNX       (1 << 6)
#define WFD_USAGE_VIDEO_QNX        (1 << 7)
#define WFD_USAGE_CAPTURE_QNX      (1 << 8)
#define WFD_USAGE_ROTATION_QNX     (1 << 9)
#define WFD_USAGE_OVERLAY_QNX      (1 << 10)
#define WFD_USAGE_COMPRESSION_QNX  (1 << 12)
        /**  Flag to indicate that the buffer should be physically contiguous
         * and the physical address should be provided.
         * This is only a hint; read SCREEN_PROPERTY_PHYSICALLY_CONTIGUOUS
         * from a buffer to check whether it's contiguous.
         */
#define WFD_USAGE_PHYSICAL_QNX     (1 << 13)
        /** Flag to indicate that the buffer should be in sync with Vulkan
         * driver for this hardware platform for the buffer restrictions.
         * Vulkan driver could handle new formats and do not handle old
         * and some additional restrictions could be applied to the buffer
         * properties.
         */
#define WFD_USAGE_VULKAN_QNX       (1 << 14)
        /** Flag to indicate that buffers must be allocated as protected by OS.
         */
#define WFD_USAGE_PROTECTION_QNX   (1 << 15)
        /** This is a special flag to perform unsynchronized to CPU
         * mappings of allocated surfaces. User takes full responsibility
         * to invalidate and flush CPU caches in a mixed usage of surface
         * between CPU and GPU. Currently supported by i915/DRM driver.
         */
#define WFD_USAGE_UNSYNC_QNX       (1 << 28)
        /** Deprecated, could be re-used again */
#define WFD_USAGE_WRITEBACK_QNX    (1 << 31)

#define WFD_FORMAT_BYTE_QNX                  1
#define WFD_FORMAT_RGBA4444_QNX              2
#define WFD_FORMAT_RGBX4444_QNX              3
#define WFD_FORMAT_RGBA5551_QNX              4
#define WFD_FORMAT_RGBX5551_QNX              5
#define WFD_FORMAT_RGB565_QNX                6
#define WFD_FORMAT_RGB888_QNX                7
#define WFD_FORMAT_RGBA8888_QNX              8
#define WFD_FORMAT_RGBX8888_QNX              9
#define WFD_FORMAT_YVU9_QNX                 10
#define WFD_FORMAT_YUV420_QNX               11
#define WFD_FORMAT_NV12_QNX                 12
#define WFD_FORMAT_YV12_QNX                 13
#define WFD_FORMAT_UYVY_QNX                 14
#define WFD_FORMAT_YUY2_QNX                 15
#define WFD_FORMAT_YVYU_QNX                 16
#define WFD_FORMAT_V422_QNX                 17
#define WFD_FORMAT_AYUV_QNX                 18
#define WFD_FORMAT_NV16_QNX                 19
#define WFD_FORMAT_P010_QNX                 20
#define WFD_FORMAT_BGRA8888_QNX             21
#define WFD_FORMAT_BGRX8888_QNX             22
#define WFD_FORMAT_RGBA1010102_QNX          23
#define WFD_FORMAT_RGBX1010102_QNX          24
#define WFD_FORMAT_BGRA1010102_QNX          25
#define WFD_FORMAT_BGRX1010102_QNX          26
#define WFD_BASE_FORMAT_MASK                (WFDint)0xffff
#define WFD_BASE_FORMAT(x)                  ((WFDint)(x) & WFD_BASE_FORMAT_MASK)

#define WFD_FORMAT_NV12_QC_SUPERTILE        ((1 << 16) | WFD_FORMAT_NV12_QNX)
#define WFD_FORMAT_NV12_QC_32M4KA           ((2 << 16) | WFD_FORMAT_NV12_QNX)

#define WFD_FORMAT_RCAR3_ADD_ALPHA_PLANE    (1 << 19)

#define WFD_FORMAT_IMX8X_TILING_MODE_SHIFT  (16)
#define WFD_FORMAT_IMX8X_TILING_MODE_MASK   (0x0FU << WFD_FORMAT_IMX8X_TILING_MODE_SHIFT)
#define WFD_FORMAT_IMX8X_TILING_MODE(x)     (int)((unsigned)(x) & WFD_FORMAT_IMX8X_TILING_MODE_MASK)

    /** Storage formats below are handled by RGX DDK 1.15 */

    /** OpenGL: n/a, Vulkan: VK_FORMAT_R16G16_UNORM
     * Specifies a two-component, 32-bit unsigned normalized format that has a 16-bit R
     * component in bytes 0..1, and a 16-bit G component in bytes 2..3.
     */
#define WFD_FORMAT_RG16_RGX                 (('i' << 24) |  (7 << 16) | WFD_FORMAT_BYTE_QNX)

    /** OpenGL: GL_RG16UI, Vulkan: VK_FORMAT_R16G16_UINT
     * Specifies a two-component, 32-bit unsigned integer format that has a 16-bit R
     * component in bytes 0..1, and a 16-bit G component in bytes 2..3.
     */
#define WFD_FORMAT_RG16UI_RGX               (('i' << 24) |  (8 << 16) | WFD_FORMAT_BYTE_QNX)

    /** OpenGL: n/a, Vulkan: VK_FORMAT_R16G16B16A16_UNORM
     * specifies a four-component, 64-bit unsigned normalized format that has a 16-bit R
     * component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component
     * in bytes 4..5, and a 16-bit A component in bytes 6..7.
     */
#define WFD_FORMAT_RGBA16_RGX               (('i' << 24) | (15 << 16) | WFD_FORMAT_BYTE_QNX)

    /**  OpenGL: GL_RGBA16UI, Vulkan: VK_FORMAT_R16G16B16A16_UINT
     * Specifies a four-component, 64-bit unsigned integer format that has a 16-bit R
     * component in bytes 0..1, a 16-bit G component in bytes 2..3, a 16-bit B component
     * in bytes 4..5, and a 16-bit A component in bytes 6..7.
     */
#define WFD_FORMAT_RGBA16UI_RGX             (('i' << 24) | (16 << 16) | WFD_FORMAT_BYTE_QNX)

    /** DRM 6.x definitions of tiled format modifiers.
     * The actual tiling format is hidden from the user and functions as a hint. The
     * allocator selects the optimal tiled format based on the given usage, resolution,
     * bpp, stride, and other parameters.
     */
#define WFD_FORMAT_MOD_DRM_SHIFT            (16)
#define WFD_FORMAT_MOD_DRM_MASK             (0x0F << WFD_FORMAT_MOD_DRM_SHIFT)
#define WFD_FORMAT_MOD_DRM_TILING_AUTO      (0 << WFD_FORMAT_MOD_DRM_SHIFT)
#define WFD_FORMAT_MOD_DRM_TILING_NONE      (1 << WFD_FORMAT_MOD_DRM_SHIFT)
#define WFD_FORMAT_MOD_DRM_TILING_OPTIMAL   (2 << WFD_FORMAT_MOD_DRM_SHIFT)
#define WFD_FORMAT_MOD_DRM(x)               (int)((unsigned)(x) & WFD_FORMAT_MOD_DRM_MASK)
#define WFD_FORMAT_DRM_SHIFT                (20)
#define WFD_FORMAT_DRM_MASK                 (0x0FU << WFD_FORMAT_DRM_SHIFT)
#define WFD_FORMAT_DRM(x)                   (int)((unsigned)(x) & WFD_FORMAT_DRM_MASK)
    /* YU16 format. Similar to YU12 (YUV420), but the U and V planes use 2:1 horizontal
     * subsampling. Also referred to as 422H in VA-API and YUV422 in DRM. The FOURCC
     * code is ('Y', 'U', '1', '6').
     */
#define WFD_FORMAT_YU16_DRM                 ((1 << WFD_FORMAT_DRM_SHIFT) | WFD_FORMAT_BYTE_QNX)
    /* YU24 format. Similar to YU12 (YUV420), but the U and V planes have no
     * subsampling (1:1). Also referred to as 444P in VA-API and YUV444 in DRM.
     * The FOURCC code is ('Y', 'U', '2', '4').
     */
#define WFD_FORMAT_YU24_DRM                 ((2 << WFD_FORMAT_DRM_SHIFT) | WFD_FORMAT_BYTE_QNX)

/** i.MX8x Tiling Modes */
enum wfd_imx8_tiling_mode {
	/** Linear Layout */
	WFD_FORMAT_IMX8X_TILING_MODE_LINEAR = (0x0 << WFD_FORMAT_IMX8X_TILING_MODE_SHIFT),

	/** Vivante 4x4 tiling layout -
	 * This is a simple tiled layout using tiles of 4x4 pixels in a row-major
	 * layout. */
	WFD_FORMAT_IMX8X_TILING_MODE_VIVANTE_TILED = (0x1 << WFD_FORMAT_IMX8X_TILING_MODE_SHIFT),

	/** Vivante 64x64 super-tiling layout -
	 * This is a tiled layout using 64x64 pixel super-tiles, where each super-tile
	 * contains 8x4 groups of 2x4 tiles of 4x4 pixels (like above) each, all in row-
	 * major layout. */
	WFD_FORMAT_IMX8X_TILING_MODE_VIVANTE_SUPER_TILED = (0x2 << WFD_FORMAT_IMX8X_TILING_MODE_SHIFT),

	/** Amphion 8x128 tiling layout -
	 * This is a tiled layout using 8x128 pixel vertical strips, where each strip
	 * contains 1x16 groups of 8x8 pixels in a row-major layout. */
	WFD_FORMAT_IMX8X_TILING_MODE_AMPHION_TILED = (0x3 << WFD_FORMAT_IMX8X_TILING_MODE_SHIFT),

	WFD_FORMAT_IMX8X_TILING_MODE_AMPHION_INTERLACED = (0x4 << WFD_FORMAT_IMX8X_TILING_MODE_SHIFT),

	/** Vivante 64x64 super-tiling layout + tile status
	 * This is the same tiled layout as WFD_FORMAT_IMX8X_TILING_MODE_VIVANTE_SUPER_TILED, however
	 * there is another buffer allocated to be used as a status buffer for each tile. Using the tile status
	 * allows to use compressed buffer. This saves gpu cycles and memory bandwidth when passing the image data
	 * to gles compositor. */
	WFD_FORMAT_IMX8X_TILING_MODE_VIVANTE_SUPER_TILED_TILE_STATUS = (0x5 << WFD_FORMAT_IMX8X_TILING_MODE_SHIFT),
};

#define WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT  (24)
#define WFD_FORMAT_IMX8X_COLOR_SPACE_MASK   (0xF << WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT)
#define WFD_FORMAT_IMX8X_COLOR_SPACE(x)     (int)((unsigned)(x) & WFD_FORMAT_IMX8X_COLOR_SPACE_MASK)

/** i.MX8X Color Space Types */
enum wfd_imx8_color_space {
	WFD_FORMAT_IMX8X_COLOR_SPACE_UNCORRECTED = (0x0 << WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT),  /**< Default */
	WFD_FORMAT_IMX8X_COLOR_SPACE_SRGB        = (0x1 << WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT),  /**< Standard RGB */
	WFD_FORMAT_IMX8X_COLOR_SPACE_LRGB        = (0x2 << WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT),  /**< Linear RGB */
	WFD_FORMAT_IMX8X_COLOR_SPACE_BT601       = (0x3 << WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT),  /**< Refer to BT.601 standards */
	WFD_FORMAT_IMX8X_COLOR_SPACE_BT601_FULL  = (0x4 << WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT),  /**< Refer to BT.601 standards */
	WFD_FORMAT_IMX8X_COLOR_SPACE_BT709       = (0x5 << WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT),  /**< Refer to BT.709 standards */
	WFD_FORMAT_IMX8X_COLOR_SPACE_BT709_FULL  = (0x6 << WFD_FORMAT_IMX8X_COLOR_SPACE_SHIFT),  /**< Refer to BT.709 standards */
};

#ifdef WFD_WFDEXT_PROTOTYPES
/**
 * @brief Allocate memory for graphics buffers.
 *
 * @param device  A WFD device handle.
 * @param width   The desired width in pixels.
 * @param height  The desired height in pixels.
 * @param format  The desired storage format.  A WFD_FORMAT_* value is
 *                expected (these being the same as SCREEN_FORMAT_*).
 *                If @c usage does not request CPU access, the
 *                returned images may use a variant of the format.
 * @param usage   A set of WFD_USAGE_* bits (which are the same as
 *                SCREEN_USAGE_*) to indicate how the buffer will be used.
 *                See @c SCREEN_PROPERTY_USAGE.  The allocated images may
 *                have additional usage bits sets.
 * @param count   The number of buffers to allocate.
 * @param images  A pointer to an array where this function will,
 *                on success, write @c count @c WFDEGLImage objects
 *                (each being a pointer to image metadata).
 * @return @c WFD_ERROR_NONE on success (the @c images array was filled);
 *         or an OpenWFD error code on failure.
 *         This function does not affect values returned by @c wfdGetError().
 */
WFD_API_CALL WFDErrorCode WFD_APIENTRY
    wfdCreateWFDEGLImagesQNX(WFDDevice device, WFDint width, WFDint height, WFDint format, WFDint usage, WFDint count, WFDEGLImage *images);

/**
 * @brief Deallocate memory that came from @c wfdCreateWFDEGLImagesQNX().
 *
 * @param device  The WFD device handle from which the images were allocated.
 * @param count   The number of buffers to deallocate.
 * @param images  A pointer to an array containing the @c WFDEGLImage
 *                objects to free.  Each object must be a pointer that came
 *                from @c wfdCreateWFDEGLImagesQNX(), not a pointer to an
 *                equivalent object.  Objects that were allocated together
 *                do not have to be freed together.
 * @return @c WFD_ERROR_NONE on success, or an OpenWFD error code on failure.
 *         This function does not affect values returned by @c wfdGetError().
 */
WFD_API_CALL WFDErrorCode WFD_APIENTRY
    wfdDestroyWFDEGLImagesQNX(WFDDevice device, WFDint count, WFDEGLImage *images);
#endif /* WFD_WFDEXT_PROTOTYPES */
typedef WFDErrorCode (WFD_APIENTRY PFNWFDCREATEWFDEGLIMAGESQNX) (WFDDevice device, WFDint width, WFDint height, WFDint usage, WFDint count, WFDEGLImage *images);
typedef WFDErrorCode (WFD_APIENTRY PFNWFDDESTROYWFDEGLIMAGESQNX) (WFDDevice device, WFDint count, WFDEGLImage *images);
#endif


#ifndef WFD_QNX_port_brightness
/**
 * This extension provides a way of changing the perceived brightness of a port.
 *
 * @note The use of 'brightness' in this extension is inconsistent with the
 *       'brightness' in the bchs extension, where brightness affects the
 *       color, not the way the color is displayed. In other words, pipeline
 *       brightness changes the color in the WFDDestinationQNX when writeback
 *       is enabled, whereas the port brightness doesn't.
 */
#define WFD_QNX_port_brightness 1
#define WFD_EXTNAME_WFD_QNX_port_brightness "WFD_QNX_port_brightness"
/**
 * This port attribute returns the current port brightness as a normalized value between
 * 0.0 and 1.0.
 *
 * Storage type: @c WFDfloat; read-only
 * Range: [0.0, 1.0]
 * Default: None
 * Accessors: @c wfdGetPortAttribf()
 */
#define WFD_PORT_CURRENT_BRIGHTNESS_QNX		0x7650
/**
 * This port attribute that is used to set the current brightness. Values can be:
 *   -1.0       Indicates that the system has automatic control over
 *              the brightness
 *   [0.0,1.0]  An absolute brightness ranging from off to maximum.
 *
 * Storage type: @c WFDfloat; read/write
 * Range: [-1.0, 0.0-1.0]
 * Accessors: @c wfdGetPortAttribf(), @c wfdSetPortAttribf()
 */
#define WFD_PORT_BRIGHTNESS_QNX			0x7651
#endif

#ifndef WFD_QNX_port_color_profile
/**
 * This extension provides a way of querying a port's current color profile.
 *
 * WFD_PORT_COLOR_POINT_####_QNX is a read-only property that returns the
 * requested x,y,Y values after any transformations by a HW CMU block (if present)
 *
 */
#define WFD_QNX_port_color_profile 1
#define WFD_EXTNAME_WFD_QNX_port_color_profile "WFD_QNX_port_color_profile"
#define WFD_PORT_COLOR_POINT_RED_QNX    0x7652
#define WFD_PORT_COLOR_POINT_GREEN_QNX  0x7653
#define WFD_PORT_COLOR_POINT_BLUE_QNX   0x7654
#define WFD_PORT_COLOR_POINT_WHITE_QNX  0x7655
#define WFD_PORT_COLOR_POINT_RED        0x7652
#define WFD_PORT_COLOR_POINT_GREEN      0x7653
#define WFD_PORT_COLOR_POINT_BLUE       0x7654
#define WFD_PORT_COLOR_POINT_WHITE      0x7655
#endif

#ifndef WFD_QNX_port_gamma_curve
/**
 * WFD_PORT_###_GAMMA_CURVE is a port property for getting/setting gamma curve
 * values. Each R/G/B gamma curve is defined as an array of 256 elements of
 * integers, ranging from 0 to 65535.
 */
#define WFD_QNX_port_gamma_curve 1
#define WFD_EXTNAME_WFD_QNX_port_gamma_curve "WFD_QNX_port_gamma_curve"
/**
 * This port attribute that is used to get/set red gamma curve.
 * Each R/G/B gamma curve is defined as an array of 256 elements of
 * integers, ranging from 0 to 65535.
 *
 * Storage type: @c WFDint; read/write
 * Range: [0-65535]
 * Accessors: @c wfdGetPortAttribi(), @c wfdSetPortAttribi()
 */
#define WFD_PORT_RED_GAMMA_CURVE_QNX   0x7690
/**
 * This port attribute that is used to get/set green gamma curve.
 * Each R/G/B gamma curve is defined as an array of 256 elements of
 * integers, ranging from 0 to 65535.
 *
 * Storage type: @c WFDint; read/write
 * Range: [0-65535]
 * Accessors: @c wfdGetPortAttribi(), @c wfdSetPortAttribi()
 */
#define WFD_PORT_GREEN_GAMMA_CURVE_QNX 0x7691
/**
 * This port attribute that is used to get/set blue gamma curve.
 * Each R/G/B gamma curve is defined as an array of 256 elements of
 * integers, ranging from 0 to 65535.
 *
 * Storage type: @c WFDint; read/write
 * Range: [0-65535]
 * Accessors: @c wfdGetPortAttribi(), @c wfdSetPortAttribi()
 */
#define WFD_PORT_BLUE_GAMMA_CURVE_QNX  0x7692
#endif

#ifndef WFD_QNX_read_source_pixels
/**
 * This extension provides a way of querying a source's color values. This
 * may be useful when the format of image data is not known to the caller,
 * such as when special internal formats are used.
 *
 * The format argument specifies one of the formats defined in the
 * WFD_QNX_egl_images extension and correspond to the format in which the
 * color values will be written out to data. The implementation may not
 * support all formats. It may only support reading back content in non-
 * special format equivalents of the source.
 *
 * Implementations of this extension must also accept WFD_INVALID_HANDLE as
 * the pipeline argument to wfdCreateSourceFromImage.  The resulting WFDSource
 * is only required to be usable with wfdReadPixelsFromSourceQNX() and wfdDestroySource().
 */
#define WFD_QNX_read_source_pixels 1
#define WFD_EXTNAME_WFD_QNX_read_source_pixels "WFD_QNX_read_source_pixels"
#ifdef WFD_WFDEXT_PROTOTYPES
/**
 * @brief Read color values for the image from specified source.
 *
 *
 * @param device       A WFD device handle
 * @param source       A WFD handle for source
 * @param x            Starting x position
 * @param y            Starting y position
 * @param width        Width of the image to read
 * @param height       Height of the image to read
 * @param format       The format that corresponds to the color values written. Check WFD pixel formats for a list of supported formats.
 * @param data         Destination buffer for the read color values
 *
 * @return @c WFD_ERROR_NONE on success, or an OpenWFD error code on failure.
 *         This function does not affect values returned by @c wfdGetError().
 */
WFD_API_CALL WFDErrorCode WFD_APIENTRY
    wfdReadPixelsFromSourceQNX(WFDDevice device, WFDSource source, WFDint x, WFDint y, WFDint width, WFDint height, WFDint format, void *data) WFD_APIEXIT;
#endif
typedef WFDErrorCode (WFD_APIENTRY PFNWFDREADPIXELSFROMSOURCEQNX) (WFDDevice device, WFDSource source, WFDint x, WFDint y, WFDint width, WFDint height, WFDint format, void *data);
#endif


#ifndef WFD_QNX_port_types
/**
 * This extension defines new port type that can be queried using WFD_PORT_TYPE attribute.
 *
 */
#define WFD_QNX_port_types 1
#define WFD_EXTNAME_WFD_QNX_port_types "WFD_QNX_port_types"
/**
 * New port type, extension to WFDPortType enum which is queired using WFD_PORT_TYPE attribute
 * The WFD_PORT_TYPE_DSI_QNX value denotes a DSI (Display Serial Interface) port.
 */
#define WFD_PORT_TYPE_DSI_QNX 0x7675
#define WFD_PORT_TYPE_VIRTUAL_QNX 0x7676
#endif /* WFD_QNX_port_types */


#ifndef WFD_QNX_egl_image_attrib
#define WFD_QNX_egl_image_attrib 1
#define WFD_EXTNAME_WFD_QNX_egl_image_attrib "WFD_QNX_egl_image_attrib"

typedef enum WFDEGLImageAttrib {
	/** For numbering we use 0x42557000 plus the number of
	 *  the equivalent screen.h property.
	 */

	/** 2 ints: (width, height) */
	WFD_EGL_IMAGE_SIZE_QNX = 0x42557000 + 5,

	/** 1 int */
	WFD_EGL_IMAGE_FORMAT_QNX = 0x42557000 + 14,

	/** 1 int */
	WFD_EGL_IMAGE_USAGE_QNX = 0x42557000 + 48,

	/** 1 int */
	WFD_EGL_IMAGE_FD_QNX = 0x42557000 + 174,

	/** 1 int */
	WFD_EGL_IMAGE_STRIDE_QNX = 0x42557000 + 44,

	/** 1 pointer */
	WFD_EGL_IMAGE_POINTER_QNX = 0x42557000 + 34,

	/** int array; size depends on format */
	WFD_EGL_IMAGE_PLANAR_OFFSETS_QNX = 0x42557000 + 33,


	/** The following have no Screen equivalents. **/

	/* 1 int */
	WFD_EGL_IMAGE_PADDING_QNX = 0x42557100,

	WFD_EGL_IMAGE_FORCE_32BIT_QNX = 0x7FFFFFFF
} WFDEGLImageAttrib;

#ifdef WFD_WFDEXT_PROTOTYPES
/**
*   @brief Retrieve the current value of the specified EGLImage attribute of type WFDint
*
*   This function retrieves the value(s) of an eglimage attribute and stores them in a user-provided buffer.
*   The values of the following attributes can be queried using this function:
*   - @c #WFD_EGL_IMAGE_SIZE_QNX
*        count has to be 2.
*        The width and height in pixel are returned in value[0] and value[1] respectively.
*   - @c #WFD_EGL_IMAGE_FORMAT_QNX
*        count has to be 1.
*        The desired storage format. WFD_FORMAT_* value is expected (these being the same as SCREEN_FORMAT_*).
*        If usage does not request CPU access, the returned images may use a variant of the format.
*   - @c #WFD_EGL_IMAGE_USAGE_QNX
*        count has to be 1.
*        A set of WFD_USAGE_* bits (which are the same as SCREEN_USAGE_*) to indicate how the buffer will be used.
*        See SCREEN_PROPERTY_USAGE in the Screen Developer's Guide.
*        The allocated images may have additional usage bits sets.
*   - @c #WFD_EGL_IMAGE_FD_QNX
*        count has to be 1,and the fd is returned.
*   - @c #WFD_EGL_IMAGE_STRIDE_QNX
*        count has to be 2. The horizontal stride in bytes and vertical stride in lines are returned
*        in value[0] and value[1] respectively.
*   - @c #WFD_EGL_IMAGE_PLANAR_OFFSETS_QNX
*        count can to be 2 or 3 depending on the planar YUV fromats.
*        The offset between y-plane and uv-plane are returned in value[0], value[1] respectively.
*        Or the y-plane, u-plane and v-plane in bytes are returned in value[0], value[1], value[2] respectively.
*   - @c #WFD_EGL_IMAGE_PADDING_QNX
*        count has to be 1. The padding in bytes is returned in value[0].
*
*   @param  image The handle of the eglimage whose attribute is being queried.
*   @param  attrib The name of the attribute whose value is being queried. The
*                 attributes available for querying are of type WFDEGLImageAttrib
*   @param  count The maximum number of WFDint that wfd-server can write to @c param.
*   @param  value A pointer to a buffer where this function stores the retrieved value(s). This
*                 buffer must be of type @c WFDint. The buffer may be a single WFDint or
*                 an array of WFDints, depending on the attribute being retrieved.
*
*   @return @c WFD_ERROR_NONE if successful, or @c other WFDErrorCode if an error occurred
*              The error possible codes are listed below:
*              WFD_ERROR_ILLEGAL_ARGUMENT
*              WFD_ERROR_BAD_ATTRIBUTE
*/
WFD_API_CALL WFDErrorCode WFD_APIENTRY
    wfdGetEGLImageAttribivQNX(WFDEGLImage image,
                              WFDEGLImageAttrib attrib,
                              WFDint count,
                              WFDint *value) WFD_APIEXIT;

/**
*   @brief Retrieve the current value of the specified EGLImage attributes of type void pointer
*
*   This function retrieves the value(s) of an eglimage attribute and stores them in a user-provided buffer.
*   The value of the following attribute can be queried using this function:
*   - @c #WFD_EGL_IMAGE_POINTER_QNX
*        count has to be one and the virtual address of the data buffer associated with the specified EGLImage is returned.
*
*   @param  image The handle of the eglimage whose attribute is being queried.
*   @param  attrib The name of the attribute whose value is being queried. The
*                 attributes available for querying are of type WFDEGLImageAttrib
*   @param  count The maximum number of WFDint that wfd-server can write to @c param.
*                 Currently, the count has to be one. Otherwise, the call fails.
*   @param  value A pointer to a buffer where this function stores the retrieved value(s). This
*                 buffer must be of type @c void pointer.
*
*   @return @c WFD_ERROR_NONE if successful, or @c other WFDErrorCode if an error occurred
*              The error possible codes are listed below:
*              WFD_ERROR_ILLEGAL_ARGUMENT
*              WFD_ERROR_BAD_ATTRIBUTE
*/
WFD_API_CALL WFDErrorCode WFD_APIENTRY
    wfdGetEGLImageAttribpvQNX(WFDEGLImage image,
                              WFDEGLImageAttrib attrib,
                              WFDint count,
                              void* *value) WFD_APIEXIT;
#endif
typedef WFDErrorCode (WFD_APIENTRY PFNWFDWFDGETEGLIMAGEATTRIBIVQNX) (WFDEGLImage, WFDEGLImageAttrib, WFDint, WFDint*);
typedef WFDErrorCode (WFD_APIENTRY PFNWFDWFDGETEGLIMAGEATTRIBPVQNX) (WFDEGLImage, WFDEGLImageAttrib, WFDint, void**);
#endif

#ifndef WFD_QNX_tls_error_mode
/**
* This extension allows per-thread error values to be accessed.
*
* A new device attribute to access per-thread error values.
*
* If it has a non-zero value, @c wfdGetError() will read and clear an error code
* set by the calling thread.  Errors set by other threads will not be
* returned.
*
* The new property value takes effect immediately (without being committed).
*
* Storage type: @c WFDint; read/write
* Accessors: @c wfdGetDeviceAttribi(), @c wfdSetDeviceAttribi()
*/
#define WFD_QNX_tls_error_mode 1
#define WFD_EXTNAME_WFD_QNX_tls_error_mode "WFD_QNX_tls_error_mode"
#define WFD_DEVICE_GETERROR_USE_TLS_QNX 0x42557560
#endif


#ifndef WFD_QNX_destination
/**
 * This extension defines @ WFDHandle and @c WFDDestinationQNX object type,
 * which is used for writeback support.
 */
#define WFD_QNX_destination 1
#define WFD_EXTNAME_WFD_QNX_destination "WFD_QNX_destination"
typedef WFDHandle WFDDestinationQNX;
#ifdef WFD_WFDEXT_PROTOTYPES
/**
 * @brief Destroy a @c WFDDestinationQNX object.
 *
 * If an invalid handle is specified, an error will be made accessible via
 * @c wfdGetError().  Otherwise, any outstanding uses of the destination
 * will be cancelled and the destination will be deleted as soon as possible.
 *
 * @param device       A WFD device handle.
 * @param destination  A destination handle associated with @c device.
 */
WFD_API_CALL void WFD_APIENTRY
    wfdDestroyDestinationQNX(WFDDevice device, WFDDestinationQNX destination) WFD_APIEXIT;
#endif
typedef void (WFD_APIENTRY PFNWFDDESTROYDESTINATIONQNX) (WFDDevice device, WFDDestinationQNX destination);
#endif


#ifndef WFD_QNX_destination_create_from_images
/**
 * This extension defines the preferred way to create @c WFDDestinationQNX
 * objects.  It depends on @c WFD_QNX_destination.
 */
#define WFD_QNX_destination_create_from_images 1
#define WFD_EXTNAME_WFD_QNX_destination_create_from_images "WFD_QNX_destination_create_from_images"
#ifdef WFD_WFDEXT_PROTOTYPES
/**
 * @brief Allocate a destination from a set of image buffers.
 *
 * To enable writeback, bind the returned destination to a port that
 * advertises @c WFD_PORT_WRITEBACK_SUPPORT_QNX.
 *
 * @param device           A WFD device handle.
 * @param count            The number of image buffers the destination may use.
 * @param images           The set of image buffers the destination may use.
 *                         The destination will retain references to the memory
 *                         described by the these structures, but the driver
 *                         will not access the structures themselves after this
 *                         call returns.
 * @param attribList       Reserved; pass NULL.
 * @param destination_out  A pointer to a location where this function will,
 *                         on success, store the created destination handle.
 *
 * @retval EOK      Success; @c *destination_out was filled.
 * @retval EACCES   The images couldn't be opened for write access.
 * @retval EBADF    An image contained an invalid file descriptor.
 * @retval EBUSY    An image is already being used by the driver.
 * @retval EINVAL   An invalid parameter value was specified.
 * @retval EMFILE   No file descriptors are available in this process.
 * @retval ENFILE   No file descriptors are available in the system.
 * @retval ENOENT   A bad handle was specified.
 * @retval ENOMEM   There was not enough memory or address space.
 * @retval ENOTSUP  An unsupported attribute was provided, or 'count' was
 *                  too low.
 *
 * This function does not affect values returned by @c wfdGetError().
 *
 * @warning It is not recommended to pass image buffers that are part of a
 *          different destination; drivers may fail with @c EBUSY.
 * @note{All image buffers should have been allocated with the same parameters
 *       (width, height, format) and with @c WFD_USAGE_WRITEBACK_QNX.}
 * @note{A driver may return @c ENOTSUP if there are too few image buffers.
 *       Typically 3 are recommended and 2 is the minimum.}
 */
WFD_API_CALL __errno_t WFD_APIENTRY
    wfdCreateDestinationFromImagesQNX(WFDDevice device, WFDint count, const WFDEGLImage *images,
                                      const _Intptrt *attribList, WFDDestinationQNX *destination_out) WFD_APIEXIT;
#endif
#endif


#ifndef WFD_QNX_port_writeback
/**
 * This extension defines attributes and functions needed to configure
 * writeback support on a port.  It depends on @c WFD_QNX_destination.
 */
#define WFD_QNX_port_writeback 1
#define WFD_EXTNAME_WFD_QNX_port_writeback "WFD_QNX_port_writeback"
/**
 * This port attribute indicates whether a port supports writeback.
 *
 * Storage type: @c WFDboolean; read-only
 * Accessors: @c wfdGetPortAttribi()
 */
#define WFD_PORT_WRITEBACK_SUPPORT_QNX               0x7640
/**
 * This port attribute gives the minimum and maximum scaling factors supported
 * for writeback, using the same calculations as @c WFD_PIPELINE_SCALE_RANGE.
 *
 * Storage type: @c WFDfloat[2]; read-only
 * Accessors: @c wfdGetPortAttribfv()
 */
#define WFD_PORT_WRITEBACK_SCALE_RANGE_QNX           0x7641
/**
 * This attribute specifies the portion of the port output image to be
 * captured during writeback.  The image is captured after the final stage
 * of the OpenWFD 1.0 display control pipeline (i.e. #7, layer & blend);
 * the width and height of the active port mode define the maximum source
 * image size.
 *
 * Storage type: @c WFDint[4] as (offsetX,offsetY,width,height); read/write
 * Default: (0,0,0,0), an invalid setting
 * Accessors: @c wfdGetPortAttribiv(), @c wfdSetPortAttribiv()
 */
#define WFD_PORT_WRITEBACK_SOURCE_RECTANGLE_QNX      0x7642
/**
 * This attribute defines the sub-rectangle of each destination buffer
 * where the data captured during writeback will be written.
 *
 * Storage type: @c WFDint[4] as (offsetX,offsetY,width,height); read/write
 * Default: (0,0,0,0), an invalid setting
 * Accessors: @c wfdGetPortAttribiv(), @c wfdSetPortAttribiv()
 */
#define WFD_PORT_WRITEBACK_DESTINATION_RECTANGLE_QNX 0x7643
/** Reserved for future use. */
#define WFD_EVENT_PORT_BIND_DESTINATION_COMPLETE_QNX 0x7587
/** Reserved for future use. */
#define WFD_EVENT_PORT_BIND_PORT_ID_QNX              0x75C9
/** Reserved for future use. */
#define WFD_EVENT_PORT_BIND_DESTINATION_QNX          0x75CA
/** Reserved for future use. */
#define WFD_EVENT_PORT_BIND_QUEUE_OVERFLOW_QNX       0x75CB
#ifdef WFD_WFDEXT_PROTOTYPES
/**
 * @brief Set the writeback destination for a port.
 *
 * When the new binding takes effect, any other destination bound to the
 * specified port will be released.
 *
 * @param device       A WFD device handle.
 * @param port         A port handle associated with @c device.
 * @param destination  A destination handle associated with @c device;
 *                     or WFD_INVALID_HANDLE to disable writeback.
 * @param transition   Indicates when the new binding should take effect.
 *                     Pass @c WFD_TRANSITION_AT_VSYNC to switch after the
 *                     current frame, or @c WFD_TRANSITION_IMMEDIATE to
 *                     switch as soon as possible (which may cause the
 *                     current frame to be dropped).
 *
 * @return @c WFD_ERROR_NONE on success, or an OpenWFD error code on failure.
 *         This function does not affect values returned by @c wfdGetError().
 */
WFD_API_CALL WFDErrorCode WFD_APIENTRY
    wfdBindDestinationToPortQNX(WFDDevice device, WFDPort port, WFDDestinationQNX destination, WFDTransition transition) WFD_APIEXIT;
#endif
typedef WFDErrorCode (WFD_APIENTRY PFNWFDBINDDESTINATIONTOPORTQNX) (WFDDevice device, WFDPort port, WFDDestinationQNX destination, WFDTransition transition);
#endif


#ifndef WFD_QNX_write_back
/**
 * This is the deprecated writeback extension.
 * @c WFD_QNX_destination_acquire_image is the replacement.
 *
 * The presence of this extension implies support for:
 *  - @c WFD_QNX_destination
 *  - @c WFD_QNX_port_writeback
 */
#define WFD_QNX_write_back 1
#ifdef WFD_WFDEXT_PROTOTYPES
WFD_API_CALL WFDDestinationQNX WFD_APIENTRY
    wfdCreateDestinationFromImageQNX(WFDDevice device, WFDPort port, WFDEGLImage image, const WFDint *attribList) WFD_APIEXIT;
WFD_API_CALL WFDDestinationQNX WFD_APIENTRY
    wfdCreateDestinationFromStreamQNX(WFDDevice device, WFDPort port, WFDNativeStreamType stream, const WFDint *attribList) WFD_APIEXIT;
#endif
typedef WFDDestinationQNX (WFD_APIENTRY PFNWFDCREATEDESTINATIONFROMIMAGEQNX) (WFDDevice device, WFDPort port, WFDEGLImage image, const WFDint *attribList);
typedef WFDDestinationQNX (WFD_APIENTRY PFNWFDCREATEDESTINATIONFROMSTREAMQNX) (WFDDevice device, WFDPort port, WFDNativeStreamType stream, const WFDint *attribList);
#endif


#ifndef WFD_QNX_port_writeback_reserved_buffers
/**
 * This extension indicates that every writeback-capable port will provide
 * a value for the @c WFD_PORT_WRITEBACK_RESERVED_BUFFERS_QNX attribute,
 * specifying the number of buffers each Destination may reserve.
 */
#define WFD_QNX_port_writeback_reserved_buffers 1
#define WFD_EXTNAME_WFD_QNX_port_writeback_reserved_buffers "WFD_QNX_port_writeback_reserved_buffers"
/**
 * This port attribute defines the number of buffers that a @c WFDDestinationQNX
 * created for this @c WFDPort may reserve for its own use.
 *
 * When creating a destination, the client should provide at least this number
 * of buffers, plus however many buffers it intends to own (i.e. have acquired
 * but not released) at any given time.  @c wfdAcquireDestinationImageQNX()
 * shall block until @c wfdReleaseDestinationImageQNX() releases a buffer, if
 * the client attempts to acquire too many.
 *
 * If the extension is not present, clients may assume the value would be 0
 * (i.e., that they can own all buffers simultaneously).
 *
 * Storage type: @c WFDboolean; read-only
 * Accessors: @c wfdGetPortAttribi()
 */
#define WFD_PORT_WRITEBACK_RESERVED_BUFFERS_QNX 0x42557644
#endif


#ifndef WFD_QNX_destination_acquire_image
/**
 * This is the preferred way to get data generated by port writeback.
 *
 * It depends on the following extensions:
 *  - @c WFD_QNX_destination
 *  - @c WFD_QNX_port_writeback
 *
 * The following code shows how writeback could be configured:
 * @anchor sample_writeback @code{.c}
	#define WFD_WFDEXT_PROTOTYPES
	#include <WF/wfd.h>
	#include <WF/wfdext.h>
	#include <assert.h>
	#include <stddef.h>
	#include <stdio.h>
	#include <time.h>

	struct wb_arg {
		WFDDevice devhdl;
		WFDPort porthdl;
		WFDint width, height;
		WFDEGLImage images[3];
	};

	void *writeback_thread(void *arg)
	{
		struct wb_arg *wb = arg;
		WFDDestinationQNX desthdl;
		__errno_t err;
		WFDErrorCode wfderr;

		//TODO:
		//	check for necessary extensions:
		//		- WFD_QNX_destination_create_from_images
		//		- WFD_QNX_port_writeback
		//		- WFD_QNX_destination
		//		- WFD_QNX_destination_acquire_image
		// verify that the writeback is enabled on the port:
		//		- eg. wfdGetPortAttribi(device, port,WFD_PORT_WRITEBACK_SUPPORT_QNX)
		// allocate image buffers
		// fill the 'images' array

		err = wfdCreateDestinationFromImagesQNX(wb->devhdl, 3, &wb->images[0], NULL, &desthdl);
		if (err) { goto fail; }

		wfderr = wfdBindDestinationToPortQNX(wb->devhdl, wb->porthdl, desthdl, WFD_TRANSITION_AT_VSYNC);
		if (wfderr) { goto fail; }

		wfdSetPortAttribiv(wb->devhdl, wb->porthdl, WFD_PORT_WRITEBACK_SOURCE_RECTANGLE_QNX,
				4, (const WFDint[]){0, 0, wb->width, wb->height});
		wfdSetPortAttribiv(wb->devhdl, wb->porthdl, WFD_PORT_WRITEBACK_DESTINATION_RECTANGLE_QNX,
				4, (const WFDint[]){0, 0, wb->width, wb->height});

		wfdDeviceCommit(wb->devhdl, WFD_COMMIT_ENTIRE_PORT, wb->porthdl);
		wfderr = wfdGetError(wb->devhdl);
		if (wfderr) { goto fail; }

		for(;;) {
			WFDint image_idx;
			struct timespec endtime;
			unsigned seqno;

			if (0 != clock_gettime(CLOCK_MONOTONIC, &endtime)) { goto fail; }
			endtime.tv_sec += 1;

			// wait for the driver to write an image buffer
			err = wfdAcquireDestinationImageQNX(wb->devhdl, desthdl, (const intptr_t[]){
				WFD_TIMEOUT_ABS_MONOTONIC_QNX, (intptr_t)&endtime,
				WFD_WRITEBACK_SEQUENCE_NUMBER_QNX, (intptr_t)&seqno,
				WFD_NONE
			}, &image_idx);

			if (err) {
				goto fail;
			}

			printf("got frame #%u from writeback\n", seqno);
			//TODO: look for sequence number gaps, to detect missed frames
			//TODO: use images[image_idx], possibly via WFD_QNX_egl_image_attrib

			// release the buffer back to the driver, so it can write new
			// data there if necessary
			err = wfdReleaseDestinationImageQNX(wb->devhdl, desthdl, image_idx);
			assert(!err);
		}

		// unbind the destination
		wfderr = wfdBindDestinationToPortQNX(wb->devhdl, wb->porthdl, WFD_INVALID_HANDLE, WFD_TRANSITION_AT_VSYNC);
		if (wfderr) { goto fail; }

		wfdDeviceCommit(wb->devhdl, WFD_COMMIT_ENTIRE_PORT, wb->porthdl);
		wfderr = wfdGetError(wb->devhdl);
		if (wfderr) { goto fail; }

		wfdDestroyDestinationQNX(wb->devhdl, desthdl);
		return NULL;
	fail:
		; //TODO
	}
 * @endcode
 */
#define WFD_QNX_destination_acquire_image 1
#define WFD_EXTNAME_WFD_QNX_destination_acquire_image "WFD_QNX_destination_acquire_image"

/**
 * When used in a pointer-sized attribute list, its value is a pointer
 * (cast to @c intptr_t) to a <tt>const struct timespec</tt> declaring the
 * @c CLOCK_MONOTONIC time at which the blocking call should stop waiting.
 * Alternately, one of the following special integer values can be specified:
 *   0 means the call should not block;
 *   -1 or @c (intptr_t)WFD_FOREVER indicates it should not time out.
 *
 * Currently supported by @c wfdAcquireDestinationImageQNX().
 */
#define WFD_TIMEOUT_ABS_MONOTONIC_QNX 0x42557200

/**
 * When used in a pointer-sized attribute list, its value is a pointer
 * (cast to @c intptr_t) to an <tt>unsigned int</tt> where the driver
 * shall write the sequence number of any returned frame.
 *
 * Currently supported by @c wfdAcquireDestinationImageQNX().
 */
#define WFD_WRITEBACK_SEQUENCE_NUMBER_QNX 0x42557201

#ifdef WFD_WFDEXT_PROTOTYPES
/**
 * @brief Acquire an image from a destination.
 *
 * By default, the function will block while writeback is active until an
 * image is emitted by the driver.  A timeout can be given to override this.
 * Deactivating writeback, e.g. by detaching the destination from the port,
 * will wake up any blocked clients.
 *
 * The returned image shall not be used by the driver in connection with the
 * specified destination, until @c wfdReleaseDestinationImageQNX() is called
 * for it.
 *
 * This might not work with destinations from the old @c WFD_QNX_write_back
 * extension.  Use @c WFD_QNX_destination_create_from_images instead.
 *
 * @param device       A WFD device handle.
 * @param destination  A destination handle associated with @c device.
 * @param attribList   NULL; or a pointer to an attribute list as defined by
 *                     OpenWFD 1.0 section 2.9, but with pointer-sized values.
 *                     Supported attributes (see the definitions for details):
 *                      * @c WFD_TIMEOUT_ABS_MONOTONIC_QNX
 *                      * @c WFD_WRITEBACK_SEQUENCE_NUMBER_QNX
 * @param index_out    A pointer to a location where this function will,
 *                     on success, store the index of the acquired image.
 *                     This is the 0-based index within the array used
 *                     to create the destination.
 *
 * @retval EOK        Success; @c *index_out was filled.
 * @retval EBUSY      Too many buffers are in use by the client.
 * @retval ECANCELED  Writeback is disabled.
 * @retval EINVAL     An invalid parameter value was specified.
 * @retval ENOENT     A bad handle was specified.
 * @retval ENOTSUP    An unsupported attribute was provided.
 * @retval ETIMEDOUT  The timeout was reached.
 *
 * This function does not affect values returned by @c wfdGetError().
 *
 * @note{Drivers may need to hold onto one or more buffers while writeback is
 *       active, and so may return @c EBUSY if the client tries to
 *       acquire too many without releasing them.}
 */
WFD_API_CALL __errno_t WFD_APIENTRY
    wfdAcquireDestinationImageQNX(WFDDevice device, WFDDestinationQNX destination,
                                  const _Intptrt *attribList, WFDint *index_out) WFD_APIEXIT;
/**
 * @brief Release an image that was acquired from a destination.
 *
 * This returns ownership to the driver.
 *
 * @param device       A WFD device handle.
 * @param destination  A destination handle associated with @c device.
 * @param index        The index of the image to release.
 *
 * @retval EOK        Success.
 * @retval EINVAL     The index was out of range or referred to a buffer
 *                    that was already owned by the driver.
 * @retval ENOENT     A bad handle was specified.
 *
 * This function does not affect values returned by @c wfdGetError().
 */
WFD_API_CALL __errno_t WFD_APIENTRY
    wfdReleaseDestinationImageQNX(WFDDevice device, WFDDestinationQNX destination,
                                  WFDint index) WFD_APIEXIT;
#endif
#endif


#ifdef __cplusplus
}
#endif

#endif
