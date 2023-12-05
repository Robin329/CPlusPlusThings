#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <getopt.h>
#include "dptx.h"

#define EDP_CSR_MK_VIDEO_CTRL(video_mode, ipi_fmt, den_pol, color_depth) \
	((video_mode) << 0 | (den_pol) << 3 | (ipi_fmt) << 4 |           \
	 (color_depth) << 9)

static bool mst = false;

const struct option long_options[] = {
	{ "help", no_argument, NULL, 'z' },
	{ "config1", required_argument, NULL, 'a' },
	{ "config2", required_argument, NULL, 'b' },
	{ "config3", required_argument, NULL, 'c' },
	{ "config4", required_argument, NULL, 'd' },
	{ "config5", required_argument, NULL, 'e' },
	{ "msa1", required_argument, NULL, 'f' },
	{ "msa2", required_argument, NULL, 'g' },
	{ "msa3", required_argument, NULL, 'h' },
	{ "hinterval", required_argument, NULL, 'i' },
	{ "cctl", required_argument, NULL, 'j' },
	{ "dsc_ctl", required_argument, NULL, 'k' },
	{ "dsc_intsts", required_argument, NULL, 'l' },
	{ "phyif", required_argument, NULL, 'm' },
	{ "sdp_config1", required_argument, NULL, 'n' },
	{ "sdp_config2", required_argument, NULL, 'o' },
	{ "sdp_config3", required_argument, NULL, 'p' },
	{ "vsample", required_argument, NULL, 'q' },
	{ NULL, 0, NULL, 0 } // 结束标记
};

static char *all_opt = "za:b:c:d:e:f:g:h:i:j:k:l:m:n:o:p:q:r:s:t:u:v:w:x:y:";

static void usage(char *argv[])
{
	int i;

	printf(" Usage: %s [opt] <val> ...\n", argv[0]);
	printf(" options:\n");
	for (i = 0; long_options[i].name != 0; i++) {
		printf(" --%-12s", long_options[i].name);
		if (long_options[i].flag != NULL)
			printf(" flag (internal value:%d)\n",
			       *long_options[i].flag);
		else
			printf(" -%c\n", long_options[i].val);
	}
	printf("\n\n");
}

static void parse_dsc(uint32_t val)
{
	printf("================================\n");
	printf("    DSC_CTL(0x234):%#x\n\n", val);
	printf("    PPS_REPEAT_CNT[17:16]:%lu", (val & GENMASK(17, 16)) >> 16);
}

static void parse_video_config(uint8_t num, uint32_t val)
{
	printf("================================\n");
	printf("    VIDEO_CONFIG%d(%#x): %#x\n\n", num, 0x310 + 0x4 * (num - 1),
	       val);
	switch (num) {
	case 1:
		printf("        interlaced[1]:%lu\n",
		       DPTX_VIDEO_CONFIG1_O_IP_EN & val);
		printf("      h_active[31:16]:%lu\n",
		       (val & GENMASK(31, 16)) >> DPTX_VIDEO_H_ACTIVE_SHIFT);
		printf("     h_blanking[15:2]:%lu\n",
		       (val & GENMASK(15, 2)) >> DPTX_VIDEO_H_BLANK_SHIFT);
		break;
	case 2:
		printf("       v_active[15:0]:%lu\n",
		       (val & GENMASK(15, 0)) >> DPTX_VIDEO_V_ACTIVE_SHIFT);
		printf("    v_blanking[31:16]:%lu\n",
		       (val & GENMASK(31, 16)) >> DPTX_VIDEO_V_BLANK_SHIFT);
		break;
	case 3:
		printf("     h_sync_offset(HFP)[15:0]:%lu\n",
		       (val & GENMASK(15, 0)) >> DPTX_VIDEO_H_FRONT_PORCH);
		printf("    h_sync_pulse_width[30:16]:%lu\n",
		       (val & GENMASK(30, 16)) >> DPTX_VIDEO_H_SYNC_WIDTH);
		break;
	case 4:
		printf("     v_sync_offset(HFP)[15:0]:%lu\n",
		       (val & GENMASK(15, 0)) >> DPTX_VIDEO_V_FRONT_PORCH);
		printf("    v_sync_pulse_width[30:16]:%lu\n",
		       (val & GENMASK(30, 16)) >> DPTX_VIDEO_V_SYNC_WIDTH);
		break;
	case 5:
		printf("                 tu[6:0]:%lu\n",
		       (val & GENMASK(6, 0)) >> DPTX_VIDEO_CONFIG5_TU_SHIFT);
		printf("           tu_fac[19:%d]:%lu\n", mst ? 14 : 16,
		       mst ? (((val & DPTX_VIDEO_CONFIG5_TU_FRAC_MASK_MST) >>
			       DPTX_VIDEO_CONFIG5_TU_FRAC_SHIFT_MST)) :
				   ((val & DPTX_VIDEO_CONFIG5_TU_FRAC_MASK_SST) >>
			      DPTX_VIDEO_CONFIG5_TU_FRAC_SHIFT_SST));
		break;
	default:
		break;
	}
	printf("================================\n");
}

static void parse_msa(uint8_t num, uint32_t val)
{
	printf("================================\n");
	printf("    VIDEO_MSA%d(%#x): %#x\n\n", num, 0x324 + (num - 1) * 0x4,
	       val);
	switch (num) {
	case 1:
		printf("        H_START[15:0]:%lu\n",
		       (val & GENMASK(15, 0)) >> DPTX_VIDEO_MSA1_H_START_SHIFT);
		printf("       V_START[31:16]:%lu\n",
		       (val & GENMASK(31, 16)) >>
			       DPTX_VIDEO_MSA1_V_START_SHIFT);
		break;

	default:
		break;
	}
}

static void parse_cctl(uint32_t val)
{
	uint32_t debug_ctl = (val & GENMASK(11, 8)) >> 8;
	char *debug_str[8];

	printf("================================\n");
	printf("       CCTL(0x200):%#x\n\n", val);
	printf(" ENHANCE_FRAMING_WITH_FEC_EN[29]: %d\n",
	       (val & BIT(29) ? 1 : 0));
	printf("        INITIATE_MST_ACT_SEQ[28]: %d\n",
	       (val & BIT(28) ? 1 : 0));
	printf("                  ENABLE_eDP[27]: %d\n",
	       (val & BIT(27) ? 1 : 0));
	printf("                  ENABLE_FEC[26]: %d\n",
	       (val & BIT(26) ? 1 : 0));
	printf("             ENABLE_MST_MODE[25]: %d\n",
	       (val & BIT(25) ? 1 : 0));
	printf("        BS_512_SCALE_DOWN[24:17]: %lu\n",
	       (val & GENMASK(24, 17)) >> 17);
	printf("               SR_SCALE_DOWN[16]: %d\n",
	       (val & BIT(16)) ? 1 : 0);
	if (debug_ctl & BIT(0))
		debug_str[0] = "NO_AUX";
	else
		debug_str[0] = "NO_SIGNAL";
	if (debug_ctl & BIT(1))
		debug_str[1] = "AUDIO";
	if ((debug_ctl & GENMASK(1, 0)) == 0x3)
		debug_str[2] = "VIDIO";
	if (debug_ctl & BIT(2))
		debug_str[3] = "LINK";
	if ((debug_ctl & GENMASK(3, 0)) == 0x5)
		debug_str[4] = "HDCP1.3";
	if ((debug_ctl & GENMASK(3, 0)) == 0x6)
		debug_str[5] = "HDCP2";
	if ((debug_ctl & GENMASK(3, 0)) == 0x7)
		debug_str[5] = "SDP";
	printf("             DEBUG_CONTROL[11:8]: %s %s %s %s %s %s %s\n",
	       debug_str[0], debug_str[1], debug_str[2], debug_str[3],
	       debug_str[4], debug_str[5], debug_str[6], debug_str[7]);
}

static void parse_phyif_ctl(uint32_t val)
{
	uint32_t edp_phy_rate = (val & GENMASK(28, 26)) >> 26;
	char *edp_rate;
	char *phy_powerdown;
	char *tps_sel;
	char *phy_rate;
	uint32_t busy;
	uint32_t xmit_enable;
	uint32_t lanes;
	uint32_t tps;

	printf("================================\n");
	printf("PHYIF_CTL(0xa00):%#x\n\n", val);
	switch (edp_phy_rate) {
	case 0x0:
		edp_rate = "See [5:4]";
		break;
	case 0x1:
		edp_rate = "R216";
		break;
	case 0x2:
		edp_rate = "R243";
		break;
	case 0x3:
		edp_rate = "R324";
		break;
	case 0x4:
		edp_rate = "R432";
		break;
	default:
		edp_rate = "";
		break;
	}
	printf("        EDP_PHY_RATE[28:26]: %s\n", edp_rate);
	printf("                  PHY_WIDTH: %s\n",
	       val & BIT(25) ? "IF_40BIT" : "IF_20BIT");
	switch ((val & GENMASK(20, 17)) >> 17) {
	case 0x0:
		phy_powerdown = "POWER_ON";
		break;
	case 0x2:
		phy_powerdown = "INTER_P2_POWER";
		break;
	case 0x3:
		phy_powerdown = "PHY_POWER_DOWN";
		break;
	case 0xc:
		phy_powerdown = "P4_POWER_STATE";
		break;
	default:
		phy_powerdown = "";
		break;
	}
	printf("               PHY_POWERDOWN: %s\n", phy_powerdown);
	printf("                     SSC_DIS: %s\n",
	       val & BIT(16) ? "Disable" : "Enable");

	busy = (val & GENMASK(15, 12)) >> 12;

	printf("                    PHY_BUSY: Lane %s %s %s %s\n",
	       busy & 0x1 ? "0" : "", busy & 0x2 ? "1" : "",
	       busy & 0x4 ? "2" : "", busy & 0x8 ? "3" : "");

	xmit_enable = (val & GENMASK(11, 8)) >> 8;
	printf("                 XMIT_ENABLE: Lane %s %s %s %s\n",
	       xmit_enable & 0x1 ? "0" : "", xmit_enable & 0x2 ? "1" : "",
	       xmit_enable & 0x4 ? "2" : "", xmit_enable & 0x8 ? "3" : "");
	switch ((val & GENMASK(7, 6)) >> 6) {
	case 0x0:
		lanes = 1;
		break;
	case 0x1:
		lanes = 2;
		break;
	case 0x2:
		lanes = 4;
		break;
	default:
		break;
	}
	printf("                  PHY_LANES: %d Lanes\n", lanes);

	switch ((val & GENMASK(5, 4)) >> 4) {
	case 0x0:
		phy_rate = "RBR 1.62Gps";
		break;
	case 0x1:
		phy_rate = "HBR 2.7Gps";
		break;
	case 0x2:
		phy_rate = "HBR2 5.4Gps";
		break;
	case 0x3:
		phy_rate = "HBR3 8.1Gps";
		break;
	default:
		phy_rate = "RBR 1.62Gps";
		break;
	}
	printf("                   PHYRATE: %s\n", phy_rate);
	tps = val & GENMASK(3, 0);
	switch (tps) {
	case 0x0:
		tps_sel = "NO TRAIN";
		break;
	case 0x1:
		tps_sel = "TPS1, D10.2";
		break;
	case 0x2:
		tps_sel = "TPS2";
		break;
	case 0x3:
		tps_sel = "TPS3";
		break;
	case 0x4:
		tps_sel = "TPS4, CP2520 Pattern 3";
		break;
	case 0x5:
		tps_sel = "SYMBOL_ERR_RATE";
		break;
	case 0x6:
		tps_sel = "PRBS7";
		break;
	case 0x7:
		tps_sel = "CUSTOMPAT";
		break;
	case 0x8:
		tps_sel = "CP2520_PAT_1";
		break;
	case 0x9:
		tps_sel = "CP2520_PAT_2";
		break;
	default:
		tps_sel = "NO TRAIN";
		break;
	}
	printf("                TPS_SEL: %s\n", tps_sel);
}

static void parse_interval(uint32_t val)
{
	printf("================================\n");
	printf("VIDEO_HBLANK_INTERVAL(0x330):%#x\n\n", val);
	printf("                   HBLANK_INTERVAL:%#lx\n",
	       val & GENMASK(15, 0));
}

static void parse_dscint(uint32_t val)
{
	printf("================================\n");
	printf("        DSC_INTSTS(0x238):%#x\n\n", val);
	if (val & BIT(19))
		printf("    CDS_FIFO_UNDERFLOW_STREAM3[19]\n");
	if (val & BIT(18))
		printf("    CDS_FIFO_UNDERFLOW_STREAM2[18]\n");
	if (val & BIT(17))
		printf("    CDS_FIFO_UNDERFLOW_STREAM1[17]\n");
	if (val & BIT(16))
		printf("    CDS_FIFO_UNDERFLOW_STREAM0[16]\n");
	if (val & BIT(15))
		printf("    CDS_FIFO_OVERFLOW_STREAM3[15]\n");
	if (val & BIT(14))
		printf("    CDS_FIFO_OVERFLOW_STREAM2[14]\n");
	if (val & BIT(13))
		printf("    CDS_FIFO_OVERFLOW_STREAM1[13]\n");
	if (val & BIT(12))
		printf("    CDS_FIFO_OVERFLOW_STREAM0[12]\n");
	if (val & BIT(11))
		printf("    DSC_STREAM3_CRC_READY[11]\n");
	if (val & BIT(10))
		printf("    DSC_STREAM2_CRC_READY[10]\n");
	if (val & BIT(9))
		printf("    DSC_STREAM1_CRC_READY[9]\n");
	if (val & BIT(8))
		printf("    DSC_STREAM1_CRC_READY[8]\n");
}
static void parse_vsample(uint32_t val)
{
	char *pix_mode;
	char *video_mapping;

	printf("================================\n");
	printf("   VSAMPLE_CTRL(0x300):%#x\n\n", val);
	printf("      LINK_UPD_PPS[27]:%d\n", (val & BIT(27)) ? 1 : 0);
	printf("       STREAM_TYPE[25]:%d\n", (val & BIT(25)) ? 1 : 0);
	printf(" ENCRYPTION_ENABLE[24]:%d\n", (val & BIT(24)) ? 1 : 0);
	printf("        ENABLE_DSC[23]:%d\n", (val & BIT(23)) ? 1 : 0);
	switch ((val & GENMASK(22, 21)) >> 21) {
	case 0:
		pix_mode = "Single pixel mode (default)";
		break;
	case 1:
		pix_mode = "Dual pixel mode";
		break;
	case 2:
		pix_mode = "Quad pixel mode";
		break;
	case 3:
		pix_mode = "Reserved";
		break;
	default:
		pix_mode = "Single pixel mode (default)";
		break;
	}
	printf("PIXEL_MODE_SELECT[22:21]:%s\n", pix_mode);
	switch ((val & GENMASK(20, 16)) >> 16) {
	case 0x0:
		video_mapping = "RGB 6bits";
		break;
	case 0x1:
		video_mapping = "RGB 8bits";
		break;
	case 0x2:
		video_mapping = "RGB 10bits";
		break;
	case 0x3:
		video_mapping = "RGB 12bits";
		break;
	case 0x4:
		video_mapping = "RGB 16bits";
		break;
	case 0x5:
		video_mapping = "YCbCR4:4:4 8bits";
		break;
	case 0x6:
		video_mapping = "YCbCR4:4:4 10bits";
		break;
	case 0x7:
		video_mapping = "YCbCR4:4:4 12bits";
		break;
	case 0x8:
		video_mapping = "YCbCR4:4:4 16bits";
		break;
	case 0x9:
		video_mapping = "YCbCR4:2:2 8bits";
		break;
	case 0xa:
		video_mapping = "YCbCR4:2:2 10bits";
		break;
	case 0xb:
		video_mapping = "YCbCR4:2:2 12bits";
		break;
	case 0xc:
		video_mapping = "YCbCR4:2:2 16bits";
		break;
	case 0xd:
		video_mapping = "YCbCR4:2:0 8bits";
		break;
	case 0xe:
		video_mapping = "YCbCR4:2:0 10bits";
		break;
	case 0xf:
		video_mapping = "YCbCR4:2:0 12bits";
		break;
	case 0x10:
		video_mapping = "YCbCR4:2:0 16bits";
		break;
	case 0x11:
		video_mapping = "YOnly 8bits";
		break;
	case 0x12:
		video_mapping = "YOnly 10bits";
		break;
	case 0x13:
		video_mapping = "YOnly 12bits";
		break;
	case 0x14:
		video_mapping = "YOnly 16bits";
		break;
	case 0x17:
		video_mapping = "RAW 8bits";
		break;
	case 0x18:
		video_mapping = "RAW 10bits";
		break;
	case 0x19:
		video_mapping = "RAW 12bits";
		break;
	case 0x1b:
		video_mapping = "RAW 16bits";
		break;
	default:
		video_mapping = "RGB 6bits";
		break;
	}
	printf("    VIDEO_MAPPING[20:16]:%s\n", video_mapping);
	printf("VIDEO_MAPPING_IPI_EN[15]:%d\n", val & BIT(15) ? 1 : 0);
	printf("  VIDEO_STREAM_ENABLE[5]:%d\n", val & BIT(5) ? 1 : 0);
}
int main(int argc, char *argv[])
{
	int option;
	int option_index = 0;

	usage(argv);
	// 使用循环获取命令行参数
	while ((option = getopt_long(argc, argv, all_opt, long_options,
				     &option_index)) != -1) {
		switch (option) {
		case 'a':
			parse_video_config(1, strtoul(optarg, NULL, 16));
			break;
		case 'b':
			parse_video_config(2, strtoll(optarg, NULL, 16));
			break;
		case 'c':
			parse_video_config(3, strtoll(optarg, NULL, 16));
			break;
		case 'd':
			parse_video_config(4, strtoll(optarg, NULL, 16));
			break;
		case 'e':
			parse_video_config(5, strtoll(optarg, NULL, 16));
			break;
		case 'f':
			parse_msa(1, strtoll(optarg, NULL, 16));
			break;
		case 'g':
			parse_msa(2, strtoll(optarg, NULL, 16));
			break;
		case 'h':
			parse_msa(3, strtoll(optarg, NULL, 16));
			break;
		case 'm':
			parse_phyif_ctl(strtoll(optarg, NULL, 16));
			break;
		case 'j':
			parse_cctl(strtoll(optarg, NULL, 16));
			break;
		case 'i':
			parse_interval(strtoll(optarg, NULL, 16));
			break;
		case 'k':
			parse_dsc(strtoll(optarg, NULL, 16));
			break;
		case 'l':
			parse_dscint(strtoll(optarg, NULL, 16));
			break;
		case 'q':
			parse_vsample(strtoll(optarg, NULL, 16));
			break;
		case '?':
		case 'z':
		default:
			usage(argv);
			break;
		}
	}

	return 0;
}