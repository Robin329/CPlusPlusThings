/*
 * Copyright © 2006 Keith Packard
 * Copyright © 2007-2008 Dave Airlie
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (c) 2007 Jakob Bornecrantz <wallbraker@gmail.com>
 * Copyright (c) 2008 Red Hat Inc.
 * Copyright (c) 2007-2008 Tungsten Graphics, Inc., Cedar Park, TX., USA
 * Copyright © 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@intel.com>
 * Copyright © 2014 Intel Corporation
 *   Daniel Vetter <daniel.vetter@ffwll.ch>
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright © 2019 Christien Rioux
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __INC_VIC_TIMINGS_H
#define __INC_VIC_TIMINGS_H

#include"stdbool.h"
#include"stdint.h"

typedef uint32_t u32;
typedef uint8_t u8;

struct videomode;
struct list_head {
	struct list_head *next;
    struct list_head *prev;
};

/* from linux/hdmi.h */

enum hdmi_picture_aspect {
	HDMI_PICTURE_ASPECT_NONE,
	HDMI_PICTURE_ASPECT_4_3,
	HDMI_PICTURE_ASPECT_16_9,
	HDMI_PICTURE_ASPECT_64_27,
	HDMI_PICTURE_ASPECT_256_135,
	HDMI_PICTURE_ASPECT_RESERVED,
};


/* from drm_mode.h */

#define DRM_DISPLAY_INFO_LEN	32
#define DRM_CONNECTOR_NAME_LEN	32
#define DRM_DISPLAY_MODE_LEN	32
#define DRM_PROP_NAME_LEN	32

#define DRM_MODE_TYPE_BUILTIN	(1<<0) /* deprecated */
#define DRM_MODE_TYPE_CLOCK_C	((1<<1) | DRM_MODE_TYPE_BUILTIN) /* deprecated */
#define DRM_MODE_TYPE_CRTC_C	((1<<2) | DRM_MODE_TYPE_BUILTIN) /* deprecated */
#define DRM_MODE_TYPE_PREFERRED	(1<<3)
#define DRM_MODE_TYPE_DEFAULT	(1<<4) /* deprecated */
#define DRM_MODE_TYPE_USERDEF	(1<<5)
#define DRM_MODE_TYPE_DRIVER	(1<<6)

#define DRM_MODE_TYPE_ALL	(DRM_MODE_TYPE_PREFERRED |	\
				 DRM_MODE_TYPE_USERDEF |	\
				 DRM_MODE_TYPE_DRIVER)

/* Video mode flags */
/* bit compatible with the xrandr RR_ definitions (bits 0-13)
 *
 * ABI warning: Existing userspace really expects
 * the mode flags to match the xrandr definitions. Any
 * changes that don't match the xrandr definitions will
 * likely need a new client cap or some other mechanism
 * to avoid breaking existing userspace. This includes
 * allocating new flags in the previously unused bits!
 */
#define DRM_MODE_FLAG_PHSYNC			(1<<0)
#define DRM_MODE_FLAG_NHSYNC			(1<<1)
#define DRM_MODE_FLAG_PVSYNC			(1<<2)
#define DRM_MODE_FLAG_NVSYNC			(1<<3)
#define DRM_MODE_FLAG_INTERLACE			(1<<4)
#define DRM_MODE_FLAG_DBLSCAN			(1<<5)
#define DRM_MODE_FLAG_CSYNC			(1<<6)
#define DRM_MODE_FLAG_PCSYNC			(1<<7)
#define DRM_MODE_FLAG_NCSYNC			(1<<8)
#define DRM_MODE_FLAG_HSKEW			(1<<9) /* hskew provided */
#define DRM_MODE_FLAG_BCAST			(1<<10) /* deprecated */
#define DRM_MODE_FLAG_PIXMUX			(1<<11) /* deprecated */
#define DRM_MODE_FLAG_DBLCLK			(1<<12)
#define DRM_MODE_FLAG_CLKDIV2			(1<<13)
 /*
  * When adding a new stereo mode don't forget to adjust DRM_MODE_FLAGS_3D_MAX
  * (define not exposed to user space).
  */
#define DRM_MODE_FLAG_3D_MASK			(0x1f<<14)
#define  DRM_MODE_FLAG_3D_NONE		(0<<14)
#define  DRM_MODE_FLAG_3D_FRAME_PACKING		(1<<14)
#define  DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE	(2<<14)
#define  DRM_MODE_FLAG_3D_LINE_ALTERNATIVE	(3<<14)
#define  DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL	(4<<14)
#define  DRM_MODE_FLAG_3D_L_DEPTH		(5<<14)
#define  DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH	(6<<14)
#define  DRM_MODE_FLAG_3D_TOP_AND_BOTTOM	(7<<14)
#define  DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF	(8<<14)

/* Picture aspect ratio options */
#define DRM_MODE_PICTURE_ASPECT_NONE		0
#define DRM_MODE_PICTURE_ASPECT_4_3		1
#define DRM_MODE_PICTURE_ASPECT_16_9		2
#define DRM_MODE_PICTURE_ASPECT_64_27		3
#define DRM_MODE_PICTURE_ASPECT_256_135		4

/* Content type options */
#define DRM_MODE_CONTENT_TYPE_NO_DATA		0
#define DRM_MODE_CONTENT_TYPE_GRAPHICS		1
#define DRM_MODE_CONTENT_TYPE_PHOTO		2
#define DRM_MODE_CONTENT_TYPE_CINEMA		3
#define DRM_MODE_CONTENT_TYPE_GAME		4

/* Aspect ratio flag bitmask (4 bits 22:19) */
#define DRM_MODE_FLAG_PIC_AR_MASK		(0x0F<<19)
#define  DRM_MODE_FLAG_PIC_AR_NONE \
			(DRM_MODE_PICTURE_ASPECT_NONE<<19)
#define  DRM_MODE_FLAG_PIC_AR_4_3 \
			(DRM_MODE_PICTURE_ASPECT_4_3<<19)
#define  DRM_MODE_FLAG_PIC_AR_16_9 \
			(DRM_MODE_PICTURE_ASPECT_16_9<<19)
#define  DRM_MODE_FLAG_PIC_AR_64_27 \
			(DRM_MODE_PICTURE_ASPECT_64_27<<19)
#define  DRM_MODE_FLAG_PIC_AR_256_135 \
			(DRM_MODE_PICTURE_ASPECT_256_135<<19)

#define  DRM_MODE_FLAG_ALL	(DRM_MODE_FLAG_PHSYNC |		\
				 DRM_MODE_FLAG_NHSYNC |		\
				 DRM_MODE_FLAG_PVSYNC |		\
				 DRM_MODE_FLAG_NVSYNC |		\
				 DRM_MODE_FLAG_INTERLACE |	\
				 DRM_MODE_FLAG_DBLSCAN |	\
				 DRM_MODE_FLAG_CSYNC |		\
				 DRM_MODE_FLAG_PCSYNC |		\
				 DRM_MODE_FLAG_NCSYNC |		\
				 DRM_MODE_FLAG_HSKEW |		\
				 DRM_MODE_FLAG_DBLCLK |		\
				 DRM_MODE_FLAG_CLKDIV2 |	\
				 DRM_MODE_FLAG_3D_MASK)

/* DPMS flags */
/* bit compatible with the xorg definitions. */
#define DRM_MODE_DPMS_ON	0
#define DRM_MODE_DPMS_STANDBY	1
#define DRM_MODE_DPMS_SUSPEND	2
#define DRM_MODE_DPMS_OFF	3

/* Scaling mode options */
#define DRM_MODE_SCALE_NONE		0 /* Unmodified timing (display or
					     software can still scale) */
#define DRM_MODE_SCALE_FULLSCREEN	1 /* Full screen, ignore aspect */
#define DRM_MODE_SCALE_CENTER		2 /* Centered, no scaling */
#define DRM_MODE_SCALE_ASPECT		3 /* Full screen, preserve aspect */

/* Dithering mode options */
#define DRM_MODE_DITHERING_OFF	0
#define DRM_MODE_DITHERING_ON	1
#define DRM_MODE_DITHERING_AUTO 2

/* Dirty info options */
#define DRM_MODE_DIRTY_OFF      0
#define DRM_MODE_DIRTY_ON       1
#define DRM_MODE_DIRTY_ANNOTATE 2

/* Link Status options */
#define DRM_MODE_LINK_STATUS_GOOD	0
#define DRM_MODE_LINK_STATUS_BAD	1

/*
 * DRM_MODE_ROTATE_<degrees>
 *
 * Signals that a drm plane is been rotated <degrees> degrees in counter
 * clockwise direction.
 *
 * This define is provided as a convenience, looking up the property id
 * using the name->prop id lookup is the preferred method.
 */
#define DRM_MODE_ROTATE_0       (1<<0)
#define DRM_MODE_ROTATE_90      (1<<1)
#define DRM_MODE_ROTATE_180     (1<<2)
#define DRM_MODE_ROTATE_270     (1<<3)

/*
 * DRM_MODE_ROTATE_MASK
 *
 * Bitmask used to look for drm plane rotations.
 */
#define DRM_MODE_ROTATE_MASK (\
		DRM_MODE_ROTATE_0  | \
		DRM_MODE_ROTATE_90  | \
		DRM_MODE_ROTATE_180 | \
		DRM_MODE_ROTATE_270)

/*
 * DRM_MODE_REFLECT_<axis>
 *
 * Signals that the contents of a drm plane is reflected along the <axis> axis,
 * in the same way as mirroring.
 * See kerneldoc chapter "Plane Composition Properties" for more details.
 *
 * This define is provided as a convenience, looking up the property id
 * using the name->prop id lookup is the preferred method.
 */
#define DRM_MODE_REFLECT_X      (1<<4)
#define DRM_MODE_REFLECT_Y      (1<<5)

/*
 * DRM_MODE_REFLECT_MASK
 *
 * Bitmask used to look for drm plane reflections.
 */
#define DRM_MODE_REFLECT_MASK (\
		DRM_MODE_REFLECT_X | \
		DRM_MODE_REFLECT_Y)

/* Content Protection Flags */
#define DRM_MODE_CONTENT_PROTECTION_UNDESIRED	0
#define DRM_MODE_CONTENT_PROTECTION_DESIRED     1
#define DRM_MODE_CONTENT_PROTECTION_ENABLED     2
/*
 * Note on terminology:  here, for brevity and convenience, we refer to connector
 * control chips as 'CRTCs'.  They can control any type of connector, VGA, LVDS,
 * DVI, etc.  And 'screen' refers to the whole of the visible display, which
 * may span multiple monitors (and therefore multiple CRTC and connector
 * structures).
 */

/**
 * enum drm_mode_status - hardware support status of a mode
 * @MODE_OK: Mode OK
 * @MODE_HSYNC: hsync out of range
 * @MODE_VSYNC: vsync out of range
 * @MODE_H_ILLEGAL: mode has illegal horizontal timings
 * @MODE_V_ILLEGAL: mode has illegal horizontal timings
 * @MODE_BAD_WIDTH: requires an unsupported linepitch
 * @MODE_NOMODE: no mode with a matching name
 * @MODE_NO_INTERLACE: interlaced mode not supported
 * @MODE_NO_DBLESCAN: doublescan mode not supported
 * @MODE_NO_VSCAN: multiscan mode not supported
 * @MODE_MEM: insufficient video memory
 * @MODE_VIRTUAL_X: mode width too large for specified virtual size
 * @MODE_VIRTUAL_Y: mode height too large for specified virtual size
 * @MODE_MEM_VIRT: insufficient video memory given virtual size
 * @MODE_NOCLOCK: no fixed clock available
 * @MODE_CLOCK_HIGH: clock required is too high
 * @MODE_CLOCK_LOW: clock required is too low
 * @MODE_CLOCK_RANGE: clock/mode isn't in a ClockRange
 * @MODE_BAD_HVALUE: horizontal timing was out of range
 * @MODE_BAD_VVALUE: vertical timing was out of range
 * @MODE_BAD_VSCAN: VScan value out of range
 * @MODE_HSYNC_NARROW: horizontal sync too narrow
 * @MODE_HSYNC_WIDE: horizontal sync too wide
 * @MODE_HBLANK_NARROW: horizontal blanking too narrow
 * @MODE_HBLANK_WIDE: horizontal blanking too wide
 * @MODE_VSYNC_NARROW: vertical sync too narrow
 * @MODE_VSYNC_WIDE: vertical sync too wide
 * @MODE_VBLANK_NARROW: vertical blanking too narrow
 * @MODE_VBLANK_WIDE: vertical blanking too wide
 * @MODE_PANEL: exceeds panel dimensions
 * @MODE_INTERLACE_WIDTH: width too large for interlaced mode
 * @MODE_ONE_WIDTH: only one width is supported
 * @MODE_ONE_HEIGHT: only one height is supported
 * @MODE_ONE_SIZE: only one resolution is supported
 * @MODE_NO_REDUCED: monitor doesn't accept reduced blanking
 * @MODE_NO_STEREO: stereo modes not supported
 * @MODE_NO_420: ycbcr 420 modes not supported
 * @MODE_STALE: mode has become stale
 * @MODE_BAD: unspecified reason
 * @MODE_ERROR: error condition
 *
 * This enum is used to filter out modes not supported by the driver/hardware
 * combination.
 */
enum drm_mode_status {
	MODE_OK = 0,
	MODE_HSYNC,
	MODE_VSYNC,
	MODE_H_ILLEGAL,
	MODE_V_ILLEGAL,
	MODE_BAD_WIDTH,
	MODE_NOMODE,
	MODE_NO_INTERLACE,
	MODE_NO_DBLESCAN,
	MODE_NO_VSCAN,
	MODE_MEM,
	MODE_VIRTUAL_X,
	MODE_VIRTUAL_Y,
	MODE_MEM_VIRT,
	MODE_NOCLOCK,
	MODE_CLOCK_HIGH,
	MODE_CLOCK_LOW,
	MODE_CLOCK_RANGE,
	MODE_BAD_HVALUE,
	MODE_BAD_VVALUE,
	MODE_BAD_VSCAN,
	MODE_HSYNC_NARROW,
	MODE_HSYNC_WIDE,
	MODE_HBLANK_NARROW,
	MODE_HBLANK_WIDE,
	MODE_VSYNC_NARROW,
	MODE_VSYNC_WIDE,
	MODE_VBLANK_NARROW,
	MODE_VBLANK_WIDE,
	MODE_PANEL,
	MODE_INTERLACE_WIDTH,
	MODE_ONE_WIDTH,
	MODE_ONE_HEIGHT,
	MODE_ONE_SIZE,
	MODE_NO_REDUCED,
	MODE_NO_STEREO,
	MODE_NO_420,
	MODE_STALE = -3,
	MODE_BAD = -2,
	MODE_ERROR = -1
};

#define DRM_MODE(nm, t, c, hd, hss, hse, ht, hsk, vd, vss, vse, vt, vs, f) \
	.name = nm, .status = 0, .type = (t), .clock = (c), \
	.hdisplay = (hd), .hsync_start = (hss), .hsync_end = (hse), \
	.htotal = (ht), .hskew = (hsk), .vdisplay = (vd), \
	.vsync_start = (vss), .vsync_end = (vse), .vtotal = (vt), \
	.vscan = (vs), .flags = (f)

#define CRTC_INTERLACE_HALVE_V	(1 << 0) /* halve V values for interlacing */
#define CRTC_STEREO_DOUBLE	(1 << 1) /* adjust timings for stereo modes */
#define CRTC_NO_DBLSCAN		(1 << 2) /* don't adjust doublescan */
#define CRTC_NO_VSCAN		(1 << 3) /* don't adjust doublescan */
#define CRTC_STEREO_DOUBLE_ONLY	(CRTC_STEREO_DOUBLE | CRTC_NO_DBLSCAN | CRTC_NO_VSCAN)

#define DRM_MODE_FLAG_3D_MAX	DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF

#define DRM_MODE_MATCH_TIMINGS (1 << 0)
#define DRM_MODE_MATCH_CLOCK (1 << 1)
#define DRM_MODE_MATCH_FLAGS (1 << 2)
#define DRM_MODE_MATCH_3D_FLAGS (1 << 3)
#define DRM_MODE_MATCH_ASPECT_RATIO (1 << 4)

/**
 * struct drm_display_mode - DRM kernel-internal display mode structure
 * @hdisplay: horizontal display size
 * @hsync_start: horizontal sync start
 * @hsync_end: horizontal sync end
 * @htotal: horizontal total size
 * @hskew: horizontal skew?!
 * @vdisplay: vertical display size
 * @vsync_start: vertical sync start
 * @vsync_end: vertical sync end
 * @vtotal: vertical total size
 * @vscan: vertical scan?!
 * @crtc_hdisplay: hardware mode horizontal display size
 * @crtc_hblank_start: hardware mode horizontal blank start
 * @crtc_hblank_end: hardware mode horizontal blank end
 * @crtc_hsync_start: hardware mode horizontal sync start
 * @crtc_hsync_end: hardware mode horizontal sync end
 * @crtc_htotal: hardware mode horizontal total size
 * @crtc_hskew: hardware mode horizontal skew?!
 * @crtc_vdisplay: hardware mode vertical display size
 * @crtc_vblank_start: hardware mode vertical blank start
 * @crtc_vblank_end: hardware mode vertical blank end
 * @crtc_vsync_start: hardware mode vertical sync start
 * @crtc_vsync_end: hardware mode vertical sync end
 * @crtc_vtotal: hardware mode vertical total size
 *
 * The horizontal and vertical timings are defined per the following diagram.
 *
 * ::
 *
 *
 *               Active                 Front           Sync           Back
 *              Region                 Porch                          Porch
 *     <-----------------------><----------------><-------------><-------------->
 *       //////////////////////|
 *      ////////////////////// |
 *     //////////////////////  |..................               ................
 *                                                _______________
 *     <----- [hv]display ----->
 *     <------------- [hv]sync_start ------------>
 *     <--------------------- [hv]sync_end --------------------->
 *     <-------------------------------- [hv]total ----------------------------->*
 *
 * This structure contains two copies of timings. First are the plain timings,
 * which specify the logical mode, as it would be for a progressive 1:1 scanout
 * at the refresh rate userspace can observe through vblank timestamps. Then
 * there's the hardware timings, which are corrected for interlacing,
 * double-clocking and similar things. They are provided as a convenience, and
 * can be appropriately computed using drm_mode_set_crtcinfo().
 *
 * For printing you can use %DRM_MODE_FMT and DRM_MODE_ARG().
 */
struct drm_display_mode {
	/**
	 * @head:
	 *
	 * struct list_head for mode lists.
	 */
	struct list_head head;

	/**
	 * @name:
	 *
	 * Human-readable name of the mode, filled out with drm_mode_set_name().
	 */
	char name[DRM_DISPLAY_MODE_LEN];

	/**
	 * @status:
	 *
	 * Status of the mode, used to filter out modes not supported by the
	 * hardware. See enum &drm_mode_status.
	 */
	enum drm_mode_status status;

	/**
	 * @type:
	 *
	 * A bitmask of flags, mostly about the source of a mode. Possible flags
	 * are:
	 *
	 *  - DRM_MODE_TYPE_PREFERRED: Preferred mode, usually the native
	 *    resolution of an LCD panel. There should only be one preferred
	 *    mode per connector at any given time.
	 *  - DRM_MODE_TYPE_DRIVER: Mode created by the driver, which is all of
	 *    them really. Drivers must set this bit for all modes they create
	 *    and expose to userspace.
	 *  - DRM_MODE_TYPE_USERDEF: Mode defined via kernel command line
	 *
	 * Plus a big list of flags which shouldn't be used at all, but are
	 * still around since these flags are also used in the userspace ABI.
	 * We no longer accept modes with these types though:
	 *
	 *  - DRM_MODE_TYPE_BUILTIN: Meant for hard-coded modes, unused.
	 *    Use DRM_MODE_TYPE_DRIVER instead.
	 *  - DRM_MODE_TYPE_DEFAULT: Again a leftover, use
	 *    DRM_MODE_TYPE_PREFERRED instead.
	 *  - DRM_MODE_TYPE_CLOCK_C and DRM_MODE_TYPE_CRTC_C: Define leftovers
	 *    which are stuck around for hysterical raisins only. No one has an
	 *    idea what they were meant for. Don't use.
	 */
	unsigned int type;

	/**
	 * @clock:
	 *
	 * Pixel clock in kHz.
	 */
	int clock;		/* in kHz */
	int hdisplay;
	int hsync_start;
	int hsync_end;
	int htotal;
	int hskew;
	int vdisplay;
	int vsync_start;
	int vsync_end;
	int vtotal;
	int vscan;
	/**
	 * @flags:
	 *
	 * Sync and timing flags:
	 *
	 *  - DRM_MODE_FLAG_PHSYNC: horizontal sync is active high.
	 *  - DRM_MODE_FLAG_NHSYNC: horizontal sync is active low.
	 *  - DRM_MODE_FLAG_PVSYNC: vertical sync is active high.
	 *  - DRM_MODE_FLAG_NVSYNC: vertical sync is active low.
	 *  - DRM_MODE_FLAG_INTERLACE: mode is interlaced.
	 *  - DRM_MODE_FLAG_DBLSCAN: mode uses doublescan.
	 *  - DRM_MODE_FLAG_CSYNC: mode uses composite sync.
	 *  - DRM_MODE_FLAG_PCSYNC: composite sync is active high.
	 *  - DRM_MODE_FLAG_NCSYNC: composite sync is active low.
	 *  - DRM_MODE_FLAG_HSKEW: hskew provided (not used?).
	 *  - DRM_MODE_FLAG_BCAST: <deprecated>
	 *  - DRM_MODE_FLAG_PIXMUX: <deprecated>
	 *  - DRM_MODE_FLAG_DBLCLK: double-clocked mode.
	 *  - DRM_MODE_FLAG_CLKDIV2: half-clocked mode.
	 *
	 * Additionally there's flags to specify how 3D modes are packed:
	 *
	 *  - DRM_MODE_FLAG_3D_NONE: normal, non-3D mode.
	 *  - DRM_MODE_FLAG_3D_FRAME_PACKING: 2 full frames for left and right.
	 *  - DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE: interleaved like fields.
	 *  - DRM_MODE_FLAG_3D_LINE_ALTERNATIVE: interleaved lines.
	 *  - DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL: side-by-side full frames.
	 *  - DRM_MODE_FLAG_3D_L_DEPTH: ?
	 *  - DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH: ?
	 *  - DRM_MODE_FLAG_3D_TOP_AND_BOTTOM: frame split into top and bottom
	 *    parts.
	 *  - DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF: frame split into left and
	 *    right parts.
	 */
	unsigned int flags;

	/**
	 * @width_mm:
	 *
	 * Addressable size of the output in mm, projectors should set this to
	 * 0.
	 */
	int width_mm;

	/**
	 * @height_mm:
	 *
	 * Addressable size of the output in mm, projectors should set this to
	 * 0.
	 */
	int height_mm;

	/**
	 * @crtc_clock:
	 *
	 * Actual pixel or dot clock in the hardware. This differs from the
	 * logical @clock when e.g. using interlacing, double-clocking, stereo
	 * modes or other fancy stuff that changes the timings and signals
	 * actually sent over the wire.
	 *
	 * This is again in kHz.
	 *
	 * Note that with digital outputs like HDMI or DP there's usually a
	 * massive confusion between the dot clock and the signal clock at the
	 * bit encoding level. Especially when a 8b/10b encoding is used and the
	 * difference is exactly a factor of 10.
	 */
	int crtc_clock;
	int crtc_hdisplay;
	int crtc_hblank_start;
	int crtc_hblank_end;
	int crtc_hsync_start;
	int crtc_hsync_end;
	int crtc_htotal;
	int crtc_hskew;
	int crtc_vdisplay;
	int crtc_vblank_start;
	int crtc_vblank_end;
	int crtc_vsync_start;
	int crtc_vsync_end;
	int crtc_vtotal;

	/**
	 * @private:
	 *
	 * Pointer for driver private data. This can only be used for mode
	 * objects passed to drivers in modeset operations. It shouldn't be used
	 * by atomic drivers since they can store any additional data by
	 * subclassing state structures.
	 */
	int *private;

	/**
	 * @private_flags:
	 *
	 * Similar to @private, but just an integer.
	 */
	int private_flags;

	/**
	 * @vrefresh:
	 *
	 * Vertical refresh rate, for debug output in human readable form. Not
	 * used in a functional way.
	 *
	 * This value is in Hz.
	 */
	int vrefresh;

	/**
	 * @hsync:
	 *
	 * Horizontal refresh rate, for debug output in human readable form. Not
	 * used in a functional way.
	 *
	 * This value is in kHz.
	 */
	int hsync;

	/**
	 * @picture_aspect_ratio:
	 *
	 * Field for setting the HDMI picture aspect ratio of a mode.
	 */
	enum hdmi_picture_aspect picture_aspect_ratio;

	/**
	 * @export_head:
	 *
	 * struct list_head for modes to be exposed to the userspace.
	 * This is to maintain a list of exposed modes while preparing
	 * user-mode's list in drm_mode_getconnector ioctl. The purpose of this
	 * list_head only lies in the ioctl function, and is not expected to be
	 * used outside the function.
	 * Once used, the stale pointers are not reset, but left as it is, to
	 * avoid overhead of protecting it by mode_config.mutex.
	 */
	struct list_head export_head;
};


#define version_greater(edid, maj, min) \
	(((edid)->version > (maj)) || \
	 ((edid)->version == (maj) && (edid)->revision > (min)))

#define EDID_EST_TIMINGS 16
#define EDID_STD_TIMINGS 8
#define EDID_DETAILED_TIMINGS 4

/*
 * EDID blocks out in the wild have a variety of bugs, try to collect
 * them here (note that userspace may work around broken monitors first,
 * but fixes should make their way here so that the kernel "just works"
 * on as many displays as possible).
 */

/* First detailed mode wrong, use largest 60Hz mode */
#define EDID_QUIRK_PREFER_LARGE_60		(1 << 0)
/* Reported 135MHz pixel clock is too high, needs adjustment */
#define EDID_QUIRK_135_CLOCK_TOO_HIGH		(1 << 1)
/* Prefer the largest mode at 75 Hz */
#define EDID_QUIRK_PREFER_LARGE_75		(1 << 2)
/* Detail timing is in cm not mm */
#define EDID_QUIRK_DETAILED_IN_CM		(1 << 3)
/* Detailed timing descriptors have bogus size values, so just take the
 * maximum size and use that.
 */
#define EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE	(1 << 4)
/* use +hsync +vsync for detailed mode */
#define EDID_QUIRK_DETAILED_SYNC_PP		(1 << 6)
/* Force reduced-blanking timings for detailed modes */
#define EDID_QUIRK_FORCE_REDUCED_BLANKING	(1 << 7)
/* Force 8bpc */
#define EDID_QUIRK_FORCE_8BPC			(1 << 8)
/* Force 12bpc */
#define EDID_QUIRK_FORCE_12BPC			(1 << 9)
/* Force 6bpc */
#define EDID_QUIRK_FORCE_6BPC			(1 << 10)
/* Force 10bpc */
#define EDID_QUIRK_FORCE_10BPC			(1 << 11)
/* Non desktop display (i.e. HMD) */
#define EDID_QUIRK_NON_DESKTOP			(1 << 12)

struct detailed_mode_closure {
	struct drm_connector *connector;
	struct edid *edid;
	bool preferred;
	u32 quirks;
	int modes;
};

#define LEVEL_DMT	0
#define LEVEL_GTF	1
#define LEVEL_GTF2	2
#define LEVEL_CVT	3

static const struct edid_quirk {
	char vendor[4];
	int product_id;
	u32 quirks;
} edid_quirk_list[] = {
	/* Acer AL1706 */
	{ "ACR", 44358, EDID_QUIRK_PREFER_LARGE_60 },
	/* Acer F51 */
	{ "API", 0x7602, EDID_QUIRK_PREFER_LARGE_60 },

	/* AEO model 0 reports 8 bpc, but is a 6 bpc panel */
	{ "AEO", 0, EDID_QUIRK_FORCE_6BPC },

	/* BOE model on HP Pavilion 15-n233sl reports 8 bpc, but is a 6 bpc panel */
	{ "BOE", 0x78b, EDID_QUIRK_FORCE_6BPC },

	/* CPT panel of Asus UX303LA reports 8 bpc, but is a 6 bpc panel */
	{ "CPT", 0x17df, EDID_QUIRK_FORCE_6BPC },

	/* SDC panel of Lenovo B50-80 reports 8 bpc, but is a 6 bpc panel */
	{ "SDC", 0x3652, EDID_QUIRK_FORCE_6BPC },

	/* BOE model 0x0771 reports 8 bpc, but is a 6 bpc panel */
	{ "BOE", 0x0771, EDID_QUIRK_FORCE_6BPC },

	/* Belinea 10 15 55 */
	{ "MAX", 1516, EDID_QUIRK_PREFER_LARGE_60 },
	{ "MAX", 0x77e, EDID_QUIRK_PREFER_LARGE_60 },

	/* Envision Peripherals, Inc. EN-7100e */
	{ "EPI", 59264, EDID_QUIRK_135_CLOCK_TOO_HIGH },
	/* Envision EN2028 */
	{ "EPI", 8232, EDID_QUIRK_PREFER_LARGE_60 },

	/* Funai Electronics PM36B */
	{ "FCM", 13600, EDID_QUIRK_PREFER_LARGE_75 |
	  EDID_QUIRK_DETAILED_IN_CM },

	/* LGD panel of HP zBook 17 G2, eDP 10 bpc, but reports unknown bpc */
	{ "LGD", 764, EDID_QUIRK_FORCE_10BPC },

	/* LG Philips LCD LP154W01-A5 */
	{ "LPL", 0, EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE },
	{ "LPL", 0x2a00, EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE },

	/* Samsung SyncMaster 205BW.  Note: irony */
	{ "SAM", 541, EDID_QUIRK_DETAILED_SYNC_PP },
	/* Samsung SyncMaster 22[5-6]BW */
	{ "SAM", 596, EDID_QUIRK_PREFER_LARGE_60 },
	{ "SAM", 638, EDID_QUIRK_PREFER_LARGE_60 },

	/* Sony PVM-2541A does up to 12 bpc, but only reports max 8 bpc */
	{ "SNY", 0x2541, EDID_QUIRK_FORCE_12BPC },

	/* ViewSonic VA2026w */
	{ "VSC", 5020, EDID_QUIRK_FORCE_REDUCED_BLANKING },

	/* Medion MD 30217 PG */
	{ "MED", 0x7b8, EDID_QUIRK_PREFER_LARGE_75 },

	/* Panel in Samsung NP700G7A-S01PL notebook reports 6bpc */
	{ "SEC", 0xd033, EDID_QUIRK_FORCE_8BPC },

	/* Rotel RSX-1058 forwards sink's EDID but only does HDMI 1.1*/
	{ "ETR", 13896, EDID_QUIRK_FORCE_8BPC },

	/* Valve Index Headset */
	{ "VLV", 0x91a8, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b0, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b1, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b2, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b3, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b4, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b5, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b6, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b7, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b8, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91b9, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91ba, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91bb, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91bc, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91bd, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91be, EDID_QUIRK_NON_DESKTOP },
	{ "VLV", 0x91bf, EDID_QUIRK_NON_DESKTOP },

	/* HTC Vive and Vive Pro VR Headsets */
	{ "HVR", 0xaa01, EDID_QUIRK_NON_DESKTOP },
	{ "HVR", 0xaa02, EDID_QUIRK_NON_DESKTOP },

	/* Oculus Rift DK1, DK2, and CV1 VR Headsets */
	{ "OVR", 0x0001, EDID_QUIRK_NON_DESKTOP },
	{ "OVR", 0x0003, EDID_QUIRK_NON_DESKTOP },
	{ "OVR", 0x0004, EDID_QUIRK_NON_DESKTOP },

	/* Windows Mixed Reality Headsets */
	{ "ACR", 0x7fce, EDID_QUIRK_NON_DESKTOP },
	{ "HPN", 0x3515, EDID_QUIRK_NON_DESKTOP },
	{ "LEN", 0x0408, EDID_QUIRK_NON_DESKTOP },
	{ "LEN", 0xb800, EDID_QUIRK_NON_DESKTOP },
	{ "FUJ", 0x1970, EDID_QUIRK_NON_DESKTOP },
	{ "DEL", 0x7fce, EDID_QUIRK_NON_DESKTOP },
	{ "SEC", 0x144a, EDID_QUIRK_NON_DESKTOP },
	{ "AUS", 0xc102, EDID_QUIRK_NON_DESKTOP },

	/* Sony PlayStation VR Headset */
	{ "SNY", 0x0704, EDID_QUIRK_NON_DESKTOP },

	/* Sensics VR Headsets */
	{ "SEN", 0x1019, EDID_QUIRK_NON_DESKTOP },

	/* OSVR HDK and HDK2 VR Headsets */
	{ "SVR", 0x1019, EDID_QUIRK_NON_DESKTOP },
};

/*
 * Autogenerated from the DMT spec.
 * This table is copied from xfree86/modes/xf86EdidModes.c.
 * Reorganized into ID order by hand
 */
static const struct drm_display_mode drm_dmt_modes[] = {
	/* 0 - dummy, DMTs start at 1 */
	{ },
    /* 0x01 - 640x350@85Hz */
	{ DRM_MODE("640x350", DRM_MODE_TYPE_DRIVER, 31500, 640, 672,
		   736, 832, 0, 350, 382, 385, 445, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x02 - 640x400@85Hz */
	{ DRM_MODE("640x400", DRM_MODE_TYPE_DRIVER, 31500, 640, 672,
		   736, 832, 0, 400, 401, 404, 445, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x03 - 720x400@85Hz */
	{ DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 35500, 720, 756,
		   828, 936, 0, 400, 401, 404, 446, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x04 - 640x480@60Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
		   752, 800, 0, 480, 490, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x05 - 640x480@72Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 664,
		   704, 832, 0, 480, 489, 492, 520, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x06 - 640x480@75Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 656,
		   720, 840, 0, 480, 481, 484, 500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x07 - 640x480@85Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 36000, 640, 696,
		   752, 832, 0, 480, 481, 484, 509, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x08 - 800x600@56Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 36000, 800, 824,
		   896, 1024, 0, 600, 601, 603, 625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x09 - 800x600@60Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 40000, 800, 840,
		   968, 1056, 0, 600, 601, 605, 628, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x0a - 800x600@72Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 50000, 800, 856,
		   976, 1040, 0, 600, 637, 643, 666, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x0b - 800x600@75Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 49500, 800, 816,
		   896, 1056, 0, 600, 601, 604, 625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x0c - 800x600@85Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 56250, 800, 832,
		   896, 1048, 0, 600, 601, 604, 631, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x0d - 800x600@120Hz RB */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 73250, 800, 848,
		   880, 960, 0, 600, 603, 607, 636, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x0e - 848x480@60Hz */
	{ DRM_MODE("848x480", DRM_MODE_TYPE_DRIVER, 33750, 848, 864,
		   976, 1088, 0, 480, 486, 494, 517, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x0f - 1024x768@43Hz, interlace */
	{ DRM_MODE("1024x768i", DRM_MODE_TYPE_DRIVER, 44900, 1024, 1032,
		   1208, 1264, 0, 768, 768, 776, 817, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE) },
	/* 0x10 - 1024x768@60Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 65000, 1024, 1048,
		   1184, 1344, 0, 768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x11 - 1024x768@70Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 75000, 1024, 1048,
		   1184, 1328, 0, 768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x12 - 1024x768@75Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 78750, 1024, 1040,
		   1136, 1312, 0, 768, 769, 772, 800, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x13 - 1024x768@85Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 94500, 1024, 1072,
		   1168, 1376, 0, 768, 769, 772, 808, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x14 - 1024x768@120Hz RB */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 115500, 1024, 1072,
		   1104, 1184, 0, 768, 771, 775, 813, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x15 - 1152x864@75Hz */
	{ DRM_MODE("1152x864", DRM_MODE_TYPE_DRIVER, 108000, 1152, 1216,
		   1344, 1600, 0, 864, 865, 868, 900, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x16 - 1280x768@60Hz RB */
	{ DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 68250, 1280, 1328,
		   1360, 1440, 0, 768, 771, 778, 790, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x17 - 1280x768@60Hz */
	{ DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 79500, 1280, 1344,
		   1472, 1664, 0, 768, 771, 778, 798, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x18 - 1280x768@75Hz */
	{ DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 102250, 1280, 1360,
		   1488, 1696, 0, 768, 771, 778, 805, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x19 - 1280x768@85Hz */
	{ DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 117500, 1280, 1360,
		   1496, 1712, 0, 768, 771, 778, 809, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x1a - 1280x768@120Hz RB */
	{ DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 140250, 1280, 1328,
		   1360, 1440, 0, 768, 771, 778, 813, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x1b - 1280x800@60Hz RB */
	{ DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 71000, 1280, 1328,
		   1360, 1440, 0, 800, 803, 809, 823, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x1c - 1280x800@60Hz */
	{ DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 83500, 1280, 1352,
		   1480, 1680, 0, 800, 803, 809, 831, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x1d - 1280x800@75Hz */
	{ DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 106500, 1280, 1360,
		   1488, 1696, 0, 800, 803, 809, 838, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x1e - 1280x800@85Hz */
	{ DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 122500, 1280, 1360,
		   1496, 1712, 0, 800, 803, 809, 843, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x1f - 1280x800@120Hz RB */
	{ DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 146250, 1280, 1328,
		   1360, 1440, 0, 800, 803, 809, 847, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x20 - 1280x960@60Hz */
	{ DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 108000, 1280, 1376,
		   1488, 1800, 0, 960, 961, 964, 1000, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x21 - 1280x960@85Hz */
	{ DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1344,
		   1504, 1728, 0, 960, 961, 964, 1011, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x22 - 1280x960@120Hz RB */
	{ DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 175500, 1280, 1328,
		   1360, 1440, 0, 960, 963, 967, 1017, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x23 - 1280x1024@60Hz */
	{ DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 108000, 1280, 1328,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x24 - 1280x1024@75Hz */
	{ DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 135000, 1280, 1296,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x25 - 1280x1024@85Hz */
	{ DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 157500, 1280, 1344,
		   1504, 1728, 0, 1024, 1025, 1028, 1072, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x26 - 1280x1024@120Hz RB */
	{ DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 187250, 1280, 1328,
		   1360, 1440, 0, 1024, 1027, 1034, 1084, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x27 - 1360x768@60Hz */
	{ DRM_MODE("1360x768", DRM_MODE_TYPE_DRIVER, 85500, 1360, 1424,
		   1536, 1792, 0, 768, 771, 777, 795, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x28 - 1360x768@120Hz RB */
	{ DRM_MODE("1360x768", DRM_MODE_TYPE_DRIVER, 148250, 1360, 1408,
		   1440, 1520, 0, 768, 771, 776, 813, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x29 - 1400x1050@60Hz RB */
	{ DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 101000, 1400, 1448,
		   1480, 1560, 0, 1050, 1053, 1057, 1080, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x2a - 1400x1050@60Hz */
	{ DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 121750, 1400, 1488,
		   1632, 1864, 0, 1050, 1053, 1057, 1089, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x2b - 1400x1050@75Hz */
	{ DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 156000, 1400, 1504,
		   1648, 1896, 0, 1050, 1053, 1057, 1099, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x2c - 1400x1050@85Hz */
	{ DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 179500, 1400, 1504,
		   1656, 1912, 0, 1050, 1053, 1057, 1105, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x2d - 1400x1050@120Hz RB */
	{ DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 208000, 1400, 1448,
		   1480, 1560, 0, 1050, 1053, 1057, 1112, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x2e - 1440x900@60Hz RB */
	{ DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 88750, 1440, 1488,
		   1520, 1600, 0, 900, 903, 909, 926, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x2f - 1440x900@60Hz */
	{ DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 106500, 1440, 1520,
		   1672, 1904, 0, 900, 903, 909, 934, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x30 - 1440x900@75Hz */
	{ DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 136750, 1440, 1536,
		   1688, 1936, 0, 900, 903, 909, 942, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x31 - 1440x900@85Hz */
	{ DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 157000, 1440, 1544,
		   1696, 1952, 0, 900, 903, 909, 948, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x32 - 1440x900@120Hz RB */
	{ DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 182750, 1440, 1488,
		   1520, 1600, 0, 900, 903, 909, 953, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x33 - 1600x1200@60Hz */
	{ DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 162000, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x34 - 1600x1200@65Hz */
	{ DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 175500, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x35 - 1600x1200@70Hz */
	{ DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 189000, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x36 - 1600x1200@75Hz */
	{ DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 202500, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x37 - 1600x1200@85Hz */
	{ DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 229500, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x38 - 1600x1200@120Hz RB */
	{ DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 268250, 1600, 1648,
		   1680, 1760, 0, 1200, 1203, 1207, 1271, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x39 - 1680x1050@60Hz RB */
	{ DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 119000, 1680, 1728,
		   1760, 1840, 0, 1050, 1053, 1059, 1080, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x3a - 1680x1050@60Hz */
	{ DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 146250, 1680, 1784,
		   1960, 2240, 0, 1050, 1053, 1059, 1089, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x3b - 1680x1050@75Hz */
	{ DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 187000, 1680, 1800,
		   1976, 2272, 0, 1050, 1053, 1059, 1099, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x3c - 1680x1050@85Hz */
	{ DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 214750, 1680, 1808,
		   1984, 2288, 0, 1050, 1053, 1059, 1105, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x3d - 1680x1050@120Hz RB */
	{ DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 245500, 1680, 1728,
		   1760, 1840, 0, 1050, 1053, 1059, 1112, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x3e - 1792x1344@60Hz */
	{ DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 204750, 1792, 1920,
		   2120, 2448, 0, 1344, 1345, 1348, 1394, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x3f - 1792x1344@75Hz */
	{ DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 261000, 1792, 1888,
		   2104, 2456, 0, 1344, 1345, 1348, 1417, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x40 - 1792x1344@120Hz RB */
	{ DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 333250, 1792, 1840,
		   1872, 1952, 0, 1344, 1347, 1351, 1423, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x41 - 1856x1392@60Hz */
	{ DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 218250, 1856, 1952,
		   2176, 2528, 0, 1392, 1393, 1396, 1439, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x42 - 1856x1392@75Hz */
	{ DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 288000, 1856, 1984,
		   2208, 2560, 0, 1392, 1393, 1396, 1500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x43 - 1856x1392@120Hz RB */
	{ DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 356500, 1856, 1904,
		   1936, 2016, 0, 1392, 1395, 1399, 1474, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x44 - 1920x1200@60Hz RB */
	{ DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 154000, 1920, 1968,
		   2000, 2080, 0, 1200, 1203, 1209, 1235, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x45 - 1920x1200@60Hz */
	{ DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 193250, 1920, 2056,
		   2256, 2592, 0, 1200, 1203, 1209, 1245, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x46 - 1920x1200@75Hz */
	{ DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 245250, 1920, 2056,
		   2264, 2608, 0, 1200, 1203, 1209, 1255, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x47 - 1920x1200@85Hz */
	{ DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 281250, 1920, 2064,
		   2272, 2624, 0, 1200, 1203, 1209, 1262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x48 - 1920x1200@120Hz RB */
	{ DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 317000, 1920, 1968,
		   2000, 2080, 0, 1200, 1203, 1209, 1271, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x49 - 1920x1440@60Hz */
	{ DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 234000, 1920, 2048,
		   2256, 2600, 0, 1440, 1441, 1444, 1500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x4a - 1920x1440@75Hz */
	{ DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2064,
		   2288, 2640, 0, 1440, 1441, 1444, 1500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x4b - 1920x1440@120Hz RB */
	{ DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 380500, 1920, 1968,
		   2000, 2080, 0, 1440, 1443, 1447, 1525, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x4c - 2560x1600@60Hz RB */
	{ DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 268500, 2560, 2608,
		   2640, 2720, 0, 1600, 1603, 1609, 1646, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x4d - 2560x1600@60Hz */
	{ DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 348500, 2560, 2752,
		   3032, 3504, 0, 1600, 1603, 1609, 1658, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x4e - 2560x1600@75Hz */
	{ DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 443250, 2560, 2768,
		   3048, 3536, 0, 1600, 1603, 1609, 1672, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x4f - 2560x1600@85Hz */
	{ DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 505250, 2560, 2768,
		   3048, 3536, 0, 1600, 1603, 1609, 1682, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x50 - 2560x1600@120Hz RB */
	{ DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 552750, 2560, 2608,
		   2640, 2720, 0, 1600, 1603, 1609, 1694, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x51 - 1366x768@60Hz */
	{ DRM_MODE("1366x768", DRM_MODE_TYPE_DRIVER, 85500, 1366, 1436,
		   1579, 1792, 0, 768, 771, 774, 798, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x52 - 1920x1080@60Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x53 - 1600x900@60Hz */
	{ DRM_MODE("1600x900", DRM_MODE_TYPE_DRIVER, 108000, 1600, 1624,
		   1704, 1800, 0, 900, 901, 904, 1000, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
    /* 0x54 - 2048x1152@60Hz */
	{ DRM_MODE("2048x1152", DRM_MODE_TYPE_DRIVER, 162000, 2048, 2074,
		   2154, 2250, 0, 1152, 1153, 1156, 1200, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x55 - 1280x720@60Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x56 - 1366x768@60Hz */
	{ DRM_MODE("1366x768", DRM_MODE_TYPE_DRIVER, 72000, 1366, 1380,
		   1436, 1500, 0, 768, 769, 772, 800, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) },
	/* 0x57 - 4096x2160@60Hz RB */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 556744, 4096, 4104,
		   4136, 4176, 0, 2160, 2208, 2216, 2222, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
	/* 0x58 - 4096x2160@59.94Hz RB */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 556188, 4096, 4104,
		   4136, 4176, 0, 2160, 2208, 2216, 2222, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) },
};

/*
 * These more or less come from the DMT spec.  The 720x400 modes are
 * inferred from historical 80x25 practice.  The 640x480@67 and 832x624@75
 * modes are old-school Mac modes.  The EDID spec says the 1152x864@75 mode
 * should be 1152x870, again for the Mac, but instead we use the x864 DMT
 * mode.
 *
 * The DMT modes have been fact-checked; the rest are mild guesses.
 */
static const struct drm_display_mode edid_est_modes[] = {
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 40000, 800, 840,
		   968, 1056, 0, 600, 601, 605, 628, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 800x600@60Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 36000, 800, 824,
		   896, 1024, 0, 600, 601, 603,  625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 800x600@56Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 656,
		   720, 840, 0, 480, 481, 484, 500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 640x480@75Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 664,
		   704,  832, 0, 480, 489, 492, 520, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 640x480@72Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 30240, 640, 704,
		   768,  864, 0, 480, 483, 486, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 640x480@67Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
		   752, 800, 0, 480, 490, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 640x480@60Hz */
	{ DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 35500, 720, 738,
		   846, 900, 0, 400, 421, 423,  449, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 720x400@88Hz */
	{ DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 28320, 720, 738,
		   846,  900, 0, 400, 412, 414, 449, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 720x400@70Hz */
	{ DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 135000, 1280, 1296,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 1280x1024@75Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 78750, 1024, 1040,
		   1136, 1312, 0,  768, 769, 772, 800, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 1024x768@75Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 75000, 1024, 1048,
		   1184, 1328, 0,  768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 1024x768@70Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 65000, 1024, 1048,
		   1184, 1344, 0,  768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 1024x768@60Hz */
	{ DRM_MODE("1024x768i", DRM_MODE_TYPE_DRIVER,44900, 1024, 1032,
		   1208, 1264, 0, 768, 768, 776, 817, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC | DRM_MODE_FLAG_INTERLACE) }, /* 1024x768@43Hz */
	{ DRM_MODE("832x624", DRM_MODE_TYPE_DRIVER, 57284, 832, 864,
		   928, 1152, 0, 624, 625, 628, 667, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 832x624@75Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 49500, 800, 816,
		   896, 1056, 0, 600, 601, 604,  625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 800x600@75Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 50000, 800, 856,
		   976, 1040, 0, 600, 637, 643, 666, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 800x600@72Hz */
	{ DRM_MODE("1152x864", DRM_MODE_TYPE_DRIVER, 108000, 1152, 1216,
		   1344, 1600, 0,  864, 865, 868, 900, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 1152x864@75Hz */
};

struct minimode {
	short w;
	short h;
	short r;
	short rb;
};

static const struct minimode est3_modes[] = {
	/* byte 6 */
	{ 640, 350, 85, 0 },
	{ 640, 400, 85, 0 },
	{ 720, 400, 85, 0 },
	{ 640, 480, 85, 0 },
	{ 848, 480, 60, 0 },
	{ 800, 600, 85, 0 },
	{ 1024, 768, 85, 0 },
	{ 1152, 864, 75, 0 },
	/* byte 7 */
	{ 1280, 768, 60, 1 },
	{ 1280, 768, 60, 0 },
	{ 1280, 768, 75, 0 },
	{ 1280, 768, 85, 0 },
	{ 1280, 960, 60, 0 },
	{ 1280, 960, 85, 0 },
	{ 1280, 1024, 60, 0 },
	{ 1280, 1024, 85, 0 },
	/* byte 8 */
	{ 1360, 768, 60, 0 },
	{ 1440, 900, 60, 1 },
	{ 1440, 900, 60, 0 },
	{ 1440, 900, 75, 0 },
	{ 1440, 900, 85, 0 },
	{ 1400, 1050, 60, 1 },
	{ 1400, 1050, 60, 0 },
	{ 1400, 1050, 75, 0 },
	/* byte 9 */
	{ 1400, 1050, 85, 0 },
	{ 1680, 1050, 60, 1 },
	{ 1680, 1050, 60, 0 },
	{ 1680, 1050, 75, 0 },
	{ 1680, 1050, 85, 0 },
	{ 1600, 1200, 60, 0 },
	{ 1600, 1200, 65, 0 },
	{ 1600, 1200, 70, 0 },
	/* byte 10 */
	{ 1600, 1200, 75, 0 },
	{ 1600, 1200, 85, 0 },
	{ 1792, 1344, 60, 0 },
	{ 1792, 1344, 75, 0 },
	{ 1856, 1392, 60, 0 },
	{ 1856, 1392, 75, 0 },
	{ 1920, 1200, 60, 1 },
	{ 1920, 1200, 60, 0 },
	/* byte 11 */
	{ 1920, 1200, 75, 0 },
	{ 1920, 1200, 85, 0 },
	{ 1920, 1440, 60, 0 },
	{ 1920, 1440, 75, 0 },
};

static const struct minimode extra_modes[] = {
	{ 1024, 576,  60, 0 },
	{ 1366, 768,  60, 0 },
	{ 1600, 900,  60, 0 },
	{ 1680, 945,  60, 0 },
	{ 1920, 1080, 60, 0 },
	{ 2048, 1152, 60, 0 },
	{ 2048, 1536, 60, 0 },
};

/*
 * Probably taken from CEA-861 spec.
 * This table is converted from xorg's hw/xfree86/modes/xf86EdidModes.c.
 *
 * Index using the VIC.
 */
static const struct drm_display_mode edid_cea_modes[] = {
	/* 0 - dummy, VICs start at 1 */
	{ },
	/* 1 - 640x480@60Hz 4:3 */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
		   752, 800, 0, 480, 490, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 2 - 720x480@60Hz 4:3 */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 3 - 720x480@60Hz 16:9 */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 4 - 1280x720@60Hz 16:9 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 5 - 1920x1080i@60Hz 16:9 */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 6 - 720(1440)x480i@60Hz 4:3 */
	{ DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 7 - 720(1440)x480i@60Hz 16:9 */
	{ DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 8 - 720(1440)x240@60Hz 4:3 */
	{ DRM_MODE("720x240", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
		   801, 858, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 9 - 720(1440)x240@60Hz 16:9 */
	{ DRM_MODE("720x240", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
		   801, 858, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 10 - 2880x480i@60Hz 4:3 */
	{ DRM_MODE("2880x480i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 11 - 2880x480i@60Hz 16:9 */
	{ DRM_MODE("2880x480i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 12 - 2880x240@60Hz 4:3 */
	{ DRM_MODE("2880x240", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 13 - 2880x240@60Hz 16:9 */
	{ DRM_MODE("2880x240", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 14 - 1440x480@60Hz 4:3 */
	{ DRM_MODE("1440x480", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1472,
		   1596, 1716, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 15 - 1440x480@60Hz 16:9 */
	{ DRM_MODE("1440x480", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1472,
		   1596, 1716, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 16 - 1920x1080@60Hz 16:9 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 17 - 720x576@50Hz 4:3 */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 18 - 720x576@50Hz 16:9 */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 19 - 1280x720@50Hz 16:9 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 20 - 1920x1080i@50Hz 16:9 */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 21 - 720(1440)x576i@50Hz 4:3 */
	{ DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 22 - 720(1440)x576i@50Hz 16:9 */
	{ DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 23 - 720(1440)x288@50Hz 4:3 */
	{ DRM_MODE("720x288", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
		   795, 864, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 24 - 720(1440)x288@50Hz 16:9 */
	{ DRM_MODE("720x288", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
		   795, 864, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 25 - 2880x576i@50Hz 4:3 */
	{ DRM_MODE("2880x576i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 26 - 2880x576i@50Hz 16:9 */
	{ DRM_MODE("2880x576i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 27 - 2880x288@50Hz 4:3 */
	{ DRM_MODE("2880x288", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 28 - 2880x288@50Hz 16:9 */
	{ DRM_MODE("2880x288", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 29 - 1440x576@50Hz 4:3 */
	{ DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
		   1592, 1728, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 30 - 1440x576@50Hz 16:9 */
	{ DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
		   1592, 1728, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 31 - 1920x1080@50Hz 16:9 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 32 - 1920x1080@24Hz 16:9 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 33 - 1920x1080@25Hz 16:9 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 34 - 1920x1080@30Hz 16:9 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 35 - 2880x480@60Hz 4:3 */
	{ DRM_MODE("2880x480", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2944,
		   3192, 3432, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 36 - 2880x480@60Hz 16:9 */
	{ DRM_MODE("2880x480", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2944,
		   3192, 3432, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 37 - 2880x576@50Hz 4:3 */
	{ DRM_MODE("2880x576", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2928,
		   3184, 3456, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 38 - 2880x576@50Hz 16:9 */
	{ DRM_MODE("2880x576", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2928,
		   3184, 3456, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 39 - 1920x1080i@50Hz 16:9 */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 72000, 1920, 1952,
		   2120, 2304, 0, 1080, 1126, 1136, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 40 - 1920x1080i@100Hz 16:9 */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 41 - 1280x720@100Hz 16:9 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 42 - 720x576@100Hz 4:3 */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 43 - 720x576@100Hz 16:9 */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 44 - 720(1440)x576i@100Hz 4:3 */
	{ DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 45 - 720(1440)x576i@100Hz 16:9 */
	{ DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 46 - 1920x1080i@120Hz 16:9 */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 47 - 1280x720@120Hz 16:9 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 48 - 720x480@120Hz 4:3 */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 54000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 49 - 720x480@120Hz 16:9 */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 54000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 50 - 720(1440)x480i@120Hz 4:3 */
	{ DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 27000, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 51 - 720(1440)x480i@120Hz 16:9 */
	{ DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 27000, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 52 - 720x576@200Hz 4:3 */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 108000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 200, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 53 - 720x576@200Hz 16:9 */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 108000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 200, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 54 - 720(1440)x576i@200Hz 4:3 */
	{ DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 200, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 55 - 720(1440)x576i@200Hz 16:9 */
	{ DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 200, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 56 - 720x480@240Hz 4:3 */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 108000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 240, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 57 - 720x480@240Hz 16:9 */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 108000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 240, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 58 - 720(1440)x480i@240Hz 4:3 */
	{ DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 54000, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 240, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, },
	/* 59 - 720(1440)x480i@240Hz 16:9 */
	{ DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 54000, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 240, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 60 - 1280x720@24Hz 16:9 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 59400, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 61 - 1280x720@25Hz 16:9 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3700,
		   3740, 3960, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 62 - 1280x720@30Hz 16:9 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 63 - 1920x1080@120Hz 16:9 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 64 - 1920x1080@100Hz 16:9 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 65 - 1280x720@24Hz 64:27 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 59400, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 66 - 1280x720@25Hz 64:27 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3700,
		   3740, 3960, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 67 - 1280x720@30Hz 64:27 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 68 - 1280x720@50Hz 64:27 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 69 - 1280x720@60Hz 64:27 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 70 - 1280x720@100Hz 64:27 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 71 - 1280x720@120Hz 64:27 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 72 - 1920x1080@24Hz 64:27 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 73 - 1920x1080@25Hz 64:27 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 74 - 1920x1080@30Hz 64:27 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 75 - 1920x1080@50Hz 64:27 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 76 - 1920x1080@60Hz 64:27 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 77 - 1920x1080@100Hz 64:27 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 78 - 1920x1080@120Hz 64:27 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 79 - 1680x720@24Hz 64:27 */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400, 1680, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 80 - 1680x720@25Hz 64:27 */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400, 1680, 2908,
		   2948, 3168, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 81 - 1680x720@30Hz 64:27 */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400, 1680, 2380,
		   2420, 2640, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 82 - 1680x720@50Hz 64:27 */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 82500, 1680, 1940,
		   1980, 2200, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 83 - 1680x720@60Hz 64:27 */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 99000, 1680, 1940,
		   1980, 2200, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 84 - 1680x720@100Hz 64:27 */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 165000, 1680, 1740,
		   1780, 2000, 0, 720, 725, 730, 825, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 85 - 1680x720@120Hz 64:27 */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 198000, 1680, 1740,
		   1780, 2000, 0, 720, 725, 730, 825, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 86 - 2560x1080@24Hz 64:27 */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 99000, 2560, 3558,
		   3602, 3750, 0, 1080, 1084, 1089, 1100, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 87 - 2560x1080@25Hz 64:27 */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 90000, 2560, 3008,
		   3052, 3200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 88 - 2560x1080@30Hz 64:27 */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 118800, 2560, 3328,
		   3372, 3520, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 89 - 2560x1080@50Hz 64:27 */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 185625, 2560, 3108,
		   3152, 3300, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 90 - 2560x1080@60Hz 64:27 */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 198000, 2560, 2808,
		   2852, 3000, 0, 1080, 1084, 1089, 1100, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 91 - 2560x1080@100Hz 64:27 */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 371250, 2560, 2778,
		   2822, 2970, 0, 1080, 1084, 1089, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 92 - 2560x1080@120Hz 64:27 */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 495000, 2560, 3108,
		   3152, 3300, 0, 1080, 1084, 1089, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 93 - 3840x2160@24Hz 16:9 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 94 - 3840x2160@25Hz 16:9 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 95 - 3840x2160@30Hz 16:9 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 96 - 3840x2160@50Hz 16:9 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 97 - 3840x2160@60Hz 16:9 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 98 - 4096x2160@24Hz 256:135 */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000, 4096, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, },
	/* 99 - 4096x2160@25Hz 256:135 */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000, 4096, 5064,
		   5152, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, },
	/* 100 - 4096x2160@30Hz 256:135 */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000, 4096, 4184,
		   4272, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, },
	/* 101 - 4096x2160@50Hz 256:135 */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 594000, 4096, 5064,
		   5152, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, },
	/* 102 - 4096x2160@60Hz 256:135 */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 594000, 4096, 4184,
		   4272, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, },
	/* 103 - 3840x2160@24Hz 64:27 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 104 - 3840x2160@25Hz 64:27 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 105 - 3840x2160@30Hz 64:27 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 106 - 3840x2160@50Hz 64:27 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 107 - 3840x2160@60Hz 64:27 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
    /* 108 - 1280x720@48Hz 16:9 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 90000, 1280, 2240,
		   2280, 2500, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 109 - 1280x720@48Hz 64:27 */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 90000, 1280, 2240,
		   2280, 2500, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 110 - 1680x720@48Hz 64:27 */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 99000, 1680, 2490,
		   2530, 2750, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 111 - 1920x1080@48Hz 16:9 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 112 - 1920x1080@48Hz 64:27 */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 113 - 2560x1080@48Hz 64:27 */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 198000, 2560, 3558,
		   3602, 3750, 0, 1080, 1084, 1089, 1100, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 114 - 3840x2160@48Hz 16:9 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 115 - 4096x2160@48Hz 256:135 */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 594000, 4096, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, },
	/* 116 - 3840x2160@48Hz 64:27 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 117 - 3840x2160@100Hz 16:9 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 1188000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 118 - 3840x2160@120Hz 16:9 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 1188000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 119 - 3840x2160@100Hz 64:27 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 1188000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 120 - 3840x2160@120Hz 64:27 */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 1188000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 121 - 5120x2160@24Hz 64:27 */
	{ DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 396000, 5120, 7116,
		   7204, 7500, 0, 2160, 2168, 2178, 2200, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 122 - 5120x2160@25Hz 64:27 */
	{ DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 396000, 5120, 6816,
		   6904, 7200, 0, 2160, 2168, 2178, 2200, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 123 - 5120x2160@30Hz 64:27 */
	{ DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 396000, 5120, 5784,
		   5872, 6000, 0, 2160, 2168, 2178, 2200, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 124 - 5120x2160@48Hz 64:27 */
	{ DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 742500, 5120, 5866,
		   5954, 6250, 0, 2160, 2168, 2178, 2475, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 125 - 5120x2160@50Hz 64:27 */
	{ DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 742500, 5120, 6216,
		   6304, 6600, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 126 - 5120x2160@60Hz 64:27 */
	{ DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 742500, 5120, 5284,
		   5372, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 127 - 5120x2160@100Hz 64:27 */
	{ DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 1485000, 5120, 6216,
		   6304, 6600, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
};

/*
 * From CEA/CTA-861 spec.
 *
 * Index with VIC-193.
 */
static const struct drm_display_mode edid_cea_modes_193[] = {
	/* 193 - 5120x2160@120Hz 64:27 */
	{ DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 1485000, 5120, 5284,
		   5372, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 194 - 7680x4320@24Hz 16:9 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 10232,
		   10408, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 195 - 7680x4320@25Hz 16:9 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 10032,
		   10208, 10800, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 196 - 7680x4320@30Hz 16:9 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 8232,
		   8408, 9000, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 197 - 7680x4320@48Hz 16:9 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 10232,
		   10408, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 198 - 7680x4320@50Hz 16:9 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 10032,
		   10208, 10800, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 199 - 7680x4320@60Hz 16:9 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 8232,
		   8408, 9000, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 200 - 7680x4320@100Hz 16:9 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 4752000, 7680, 9792,
		   9968, 10560, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 201 - 7680x4320@120Hz 16:9 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 4752000, 7680, 8032,
		   8208, 8800, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
	/* 202 - 7680x4320@24Hz 64:27 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 10232,
		   10408, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 203 - 7680x4320@25Hz 64:27 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 10032,
		   10208, 10800, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 204 - 7680x4320@30Hz 64:27 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 8232,
		   8408, 9000, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 205 - 7680x4320@48Hz 64:27 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 10232,
		   10408, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 206 - 7680x4320@50Hz 64:27 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 10032,
		   10208, 10800, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 207 - 7680x4320@60Hz 64:27 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 8232,
		   8408, 9000, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 208 - 7680x4320@100Hz 64:27 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 4752000, 7680, 9792,
		   9968, 10560, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 209 - 7680x4320@120Hz 64:27 */
	{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 4752000, 7680, 8032,
		   8208, 8800, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 210 - 10240x4320@24Hz 64:27 */
	{ DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 1485000, 10240, 11732,
		   11908, 12500, 0, 4320, 4336, 4356, 4950, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 211 - 10240x4320@25Hz 64:27 */
	{ DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 1485000, 10240, 12732,
		   12908, 13500, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 212 - 10240x4320@30Hz 64:27 */
	{ DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 1485000, 10240, 10528,
		   10704, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 213 - 10240x4320@48Hz 64:27 */
	{ DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 2970000, 10240, 11732,
		   11908, 12500, 0, 4320, 4336, 4356, 4950, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 48, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 214 - 10240x4320@50Hz 64:27 */
	{ DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 2970000, 10240, 12732,
		   12908, 13500, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 215 - 10240x4320@60Hz 64:27 */
	{ DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 2970000, 10240, 10528,
		   10704, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 216 - 10240x4320@100Hz 64:27 */
	{ DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 5940000, 10240, 12432,
		   12608, 13200, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 217 - 10240x4320@120Hz 64:27 */
	{ DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 5940000, 10240, 10528,
		   10704, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, },
	/* 218 - 4096x2160@100Hz 256:135 */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 1188000, 4096, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, },
	/* 219 - 4096x2160@120Hz 256:135 */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 1188000, 4096, 4184,
		   4272, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, },
};

/*
 * HDMI 1.4 4k modes. Index using the VIC.
 */
static const struct drm_display_mode edid_4k_modes[] = {
	/* 0 - dummy, VICs start at 1 */
	{ },
	/* 1 - 3840x2160@30Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
		   3840, 4016, 4104, 4400, 0,
		   2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, },
	/* 2 - 3840x2160@25Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
		   3840, 4896, 4984, 5280, 0,
		   2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, },
	/* 3 - 3840x2160@24Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
		   3840, 5116, 5204, 5500, 0,
		   2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, },
	/* 4 - 4096x2160@24Hz (SMPTE) */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000,
		   4096, 5116, 5204, 5500, 0,
		   2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, },
};

/*** DDC fetch and block validation ***/

static const u8 edid_header[] = {
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
};


#endif

