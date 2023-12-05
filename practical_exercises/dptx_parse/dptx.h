#ifndef __DPTX_H__
#define __DPTX_H__
#include <stdio.h>

#define BITS_PER_LONG 64
#define BIT(nr)	      (UL(1) << (nr))
#define __AC(X, Y)    (X##Y)
#define _AC(X, Y)     __AC(X, Y)
#define _AT(T, X)     ((T)(X))

#define _UL(x)	(_AC(x, UL))
#define _ULL(x) (_AC(x, ULL))
#define UL(x)	(_UL(x))
#define ULL(x)	(_ULL(x))

#define __GENMASK(h, l)                    \
	(((~UL(0)) - (UL(1) << (l)) + 1) & \
	 (~UL(0) >> (BITS_PER_LONG - 1 - (h))))
#define GENMASK(h, l) __GENMASK(h, l)

/* MST */
#define DPTX_MST_VCP_TABLE_REG_N(n) (0x210 + (n)*4)

/* Video Registers. N=0-3 */
#define DPTX_VSAMPLE_CTRL_N(n)		(0x300 + 0x10000 * (n))
#define DPTX_VSAMPLE_RESERVED1_N(n)	(0x304 + 0x10000 * (n))
#define DPTX_VSAMPLE_RESERVED2_N(n)	(0x308 + 0x10000 * (n))
#define DPTX_VSAMPLE_POLARITY_CTRL_N(n) (0x30C + 0x10000 * (n))
#define DPTX_VIDEO_CONFIG1_N(n)		(0x310 + 0x10000 * (n))
#define DPTX_VIDEO_CONFIG2_N(n)		(0x314 + 0x10000 * (n))
#define DPTX_VIDEO_CONFIG3_N(n)		(0x318 + 0x10000 * (n))
#define DPTX_VIDEO_CONFIG4_N(n)		(0x31c + 0x10000 * (n))
#define DPTX_VIDEO_CONFIG5_N(n)		(0x320 + 0x10000 * (n))
#define DPTX_VIDEO_MSA1_N(n)		(0x324 + 0x10000 * (n))
#define DPTX_VIDEO_MSA2_N(n)		(0x328 + 0x10000 * (n))
#define DPTX_VIDEO_MSA3_N(n)		(0x32C + 0x10000 * (n))
#define DPTX_VG_CONFIG1_N(n)		(0x3804 + 0x10000 * (n))
#define DPTX_VG_CONFIG2_N(n)		(0x3808 + 0x10000 * (n))
#define DPTX_VG_CONFIG3_N(n)		(0x380C + 0x10000 * (n))
#define DPTX_VG_CONFIG4_N(n)		(0x3810 + 0x10000 * (n))
#define DPTX_VG_CONFIG5_N(n)		(0x3814 + 0x10000 * (n))
#define DPTX_VG_SWRST_N(n)		(0x3800 + 0x10000 * (n))

#define DPTX_VSAMPLE_CTRL_VMAP_BPC_SHIFT	16
#define DPTX_VSAMPLE_CTRL_VMAP_BPC_MASK		GENMASK(20, 16)
#define DPTX_VSAMPLE_CTRL_MULTI_PIXEL_SHIFT	21
#define DPTX_VSAMPLE_CTRL_MULTI_PIXEL_MASK	GENMASK(22, 21)
#define DPTX_VIDEO_VMSA2_BPC_SHIFT		29
#define DPTX_VIDEO_VMSA2_BPC_MASK		GENMASK(31, 29)
#define DPTX_VIDEO_VMSA2_COL_SHIFT		25
#define DPTX_VIDEO_VMSA2_COL_MASK		GENMASK(28, 25)
#define DPTX_VIDEO_VMSA3_PIX_ENC_SHIFT		31
#define DPTX_VIDEO_VMSA3_PIX_ENC_YCBCR420_SHIFT 30 /* ignore MSA */
#define DPTX_VIDEO_VMSA3_PIX_ENC_MASK		GENMASK(31, 30)
#define DPTX_POL_CTRL_V_SYNC_POL_EN		BIT(0)
#define DPTX_POL_CTRL_H_SYNC_POL_EN		BIT(1)
#define DPTX_VIDEO_CONFIG1_IN_OSC_EN		BIT(0)
#define DPTX_VIDEO_CONFIG1_O_IP_EN		BIT(1)
#define DPTX_VIDEO_H_BLANK_SHIFT		2
#define DPTX_VIDEO_H_ACTIVE_SHIFT		16
#define DPTX_VIDEO_V_BLANK_SHIFT		16
#define DPTX_VIDEO_V_ACTIVE_SHIFT		0
#define DPTX_VIDEO_H_FRONT_PORCH		0
#define DPTX_VIDEO_H_SYNC_WIDTH			16
#define DPTX_VIDEO_V_FRONT_PORCH		0
#define DPTX_VIDEO_V_SYNC_WIDTH			16
#define DPTX_VIDEO_MSA1_H_START_SHIFT		0
#define DPTX_VIDEO_MSA1_V_START_SHIFT		16
#define DPTX_VIDEO_CONFIG5_TU_SHIFT		0
#define DPTX_VIDEO_CONFIG5_TU_MASK		GENMASK(6, 0)
#define DPTX_VIDEO_CONFIG5_TU_FRAC_SHIFT_MST	14
#define DPTX_VIDEO_CONFIG5_TU_FRAC_MASK_MST	GENMASK(19, 14)
#define DPTX_VIDEO_CONFIG5_TU_FRAC_SHIFT_SST	16
#define DPTX_VIDEO_CONFIG5_TU_FRAC_MASK_SST	GENMASK(19, 16)
#define DPTX_VIDEO_CONFIG5_INIT_THRESHOLD_SHIFT 7
#define DPTX_VIDEO_CONFIG5_INIT_THRESHOLD_MASK	GENMASK(13, 7)

#define DP_REG_BASE	 (void *)0x64400000 /* size - 0x10000 */
#define DP_CSR_BASE	 (void *)0x64450000 /* size - 0x10000 */
#define DP_TCA_BASE	 (void *)0x64460000 /* size - 0x10000 */
#define DP_TRNG_BASE	 (void *)0x64470000 /* size - 0x10000 */
#define DP_HPI_BASE	 (void *)0x64440000 /* size - 0x10000 */
#define DP_DISP_MUX_BASE (void *)0x33000000
#define DP_VPG_BASE	 (void *)0x64400000
#define DP_APG_BASE	 (void *)0x64400000

#endif /* __DPTX_H__ */