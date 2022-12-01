#include <iostream>

#define LVDS_LANE_BIT 7

enum pixel_format {
    VESA_FORMAT,
    JEIDA_FORMAT,
    NEW_JEIDA_FORMAT,
    LINEAR_STEP,
};
enum pixel_bpps {
    RGB12_FORMAT,
    RGB18_FORMAT,
    RGB24_FORMAT,
    RGB24_FORMAT_3,
    RGB30_FORMAT,
};

enum lvds_lanes {
    RGB12_LANES = 3,
    RGB18_LANES = 3,
    RGB24_LANES = 4,
    RGB30_LANES = 5,
};

enum rgb12_format_type { NON_LINEAR_STEP_SIZE, LINEAR_STEP_SIZE };

/**
 *  lvds_formats - LVDS RGB arrangement according to different protocols
 *  @r[10]:      R component(6bit)
 *  @g[10]:      G component(6bit)
 *  @b[10]:      B component(6bit)
 *  @data_en:    data_en component(6bit)
 *  @vsync:      vsync component(6bit)
 *  @hsync:      hsync component(6bit)
 *  @res0:       res component(6bit)
 *  @res1:       res component(6bit)
 *  @defaults:    defaults component(6bit)
 */
struct lvds_formats {
    unsigned char r[10];
    unsigned char g[10];
    unsigned char b[10];
    unsigned char data_en;
    unsigned char vsync;
    unsigned char hsync;
    unsigned char res0;
    unsigned char res1;
    unsigned char defaults;
};

struct lvds_formats  lvds_fmt;
static unsigned int highBit = 0;
static unsigned char lvds_arrary[RGB30_LANES][LVDS_LANE_BIT];

std::string get_rgb_string(const unsigned char rgb);

// Channel 1
#define CH1_A0_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][6] | lvds_arrary[1][6] << 6 | lvds_arrary[2][6] << 12 | lvds_arrary[3][6] << 18 | \
     lvds_arrary[4][6] << 24)
#define PRINT(lvds_arrary, col)                                                                         \
    printf("%-3d %-3d %-3d %-3d %-3d\n", lvds_arrary[0][col], lvds_arrary[1][col], lvds_arrary[2][col], \
           lvds_arrary[3][col], lvds_arrary[4][col]);

#define PRINT_ASSIGNMENT(lvds_arrary, col)                                                           \
    printf("%-8s %-8s %-8s %-8s %-8s\n", get_rgb_string(lvds_arrary[0][col]).c_str(),                \
           get_rgb_string(lvds_arrary[1][col]).c_str(), get_rgb_string(lvds_arrary[2][col]).c_str(), \
           get_rgb_string(lvds_arrary[3][col]).c_str(), get_rgb_string(lvds_arrary[4][col]).c_str());

#define CH1_A1_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][5] | lvds_arrary[1][5] << 6 | lvds_arrary[2][5] << 12 | lvds_arrary[3][5] << 18 | \
     lvds_arrary[4][5] << 24)
#define CH1_A2_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][4] | lvds_arrary[1][4] << 6 | lvds_arrary[2][4] << 12 | lvds_arrary[3][4] << 18 | \
     lvds_arrary[4][4] << 24)
#define CH1_A3_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][3] | lvds_arrary[1][3] << 6 | lvds_arrary[2][3] << 12 | lvds_arrary[3][3] << 18 | \
     lvds_arrary[4][3] << 24)
#define CH1_A4_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][2] | lvds_arrary[1][2] << 6 | lvds_arrary[2][2] << 12 | lvds_arrary[3][2] << 18 | \
     lvds_arrary[4][2] << 24)
#define CH1_A5_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][1] | lvds_arrary[1][1] << 6 | lvds_arrary[2][1] << 12 | lvds_arrary[3][1] << 18 | \
     lvds_arrary[4][1] << 24)
#define CH1_A6_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][0] | lvds_arrary[1][0] << 6 | lvds_arrary[2][0] << 12 | lvds_arrary[3][0] << 18 | \
     lvds_arrary[4][0] << 24)
// Channel 2
#define CH2_A0_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][6] | lvds_arrary[1][6] << 6 | lvds_arrary[2][6] << 12 | lvds_arrary[3][6] << 18 | \
     lvds_arrary[4][6] << 24)
#define CH2_A1_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][5] | lvds_arrary[1][5] << 6 | lvds_arrary[2][5] << 12 | lvds_arrary[3][5] << 18 | \
     lvds_arrary[4][5] << 24)
#define CH2_A2_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][4] | lvds_arrary[1][4] << 6 | lvds_arrary[2][4] << 12 | lvds_arrary[3][4] << 18 | \
     lvds_arrary[4][4] << 24)
#define CH2_A3_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][3] | lvds_arrary[1][3] << 6 | lvds_arrary[2][3] << 12 | lvds_arrary[3][3] << 18 | \
     lvds_arrary[4][3] << 24)
#define CH2_A4_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][2] | lvds_arrary[1][2] << 6 | lvds_arrary[2][2] << 12 | lvds_arrary[3][2] << 18 | \
     lvds_arrary[4][2] << 24)
#define CH2_A5_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][1] | lvds_arrary[1][1] << 6 | lvds_arrary[2][1] << 12 | lvds_arrary[3][1] << 18 | \
     lvds_arrary[4][1] << 24)
#define CH2_A6_SEL_CFG(lvds_arrary)                                                                   \
    (lvds_arrary[0][0] | lvds_arrary[1][0] << 6 | lvds_arrary[2][0] << 12 | lvds_arrary[3][0] << 18 | \
     lvds_arrary[4][0] << 24)





unsigned char get_lvds_lanes(pixel_bpps format, const char bpps) {
    int val = format << 4 | bpps;

    switch (val) {
    case 0x21:
    case 0x20: // rgb 12bit
        return RGB12_LANES;
    case 0x01: // rgb 18bit
    case 0x11:
        return RGB18_LANES;
    case 0x02: // rgb 24bit
    case 0x12:
        return RGB24_LANES;
    case 0x03: // rgb 30bit
    case 0x13:
        return RGB30_LANES;
    default:
        break;
    }
    return RGB30_LANES;
}

int combine_rgb(pixel_bpps bpps, const char format) {
    switch (bpps) {
    case RGB12_FORMAT:
        if (format == NON_LINEAR_STEP_SIZE) {
            // Non Linear step size
            lvds_arrary[0][0] = lvds_fmt.g[2+highBit];
            lvds_arrary[0][1] = lvds_fmt.r[3+highBit];
            lvds_arrary[0][2] = lvds_fmt.r[2+highBit];
            lvds_arrary[0][3] = lvds_fmt.r[1+highBit];
            lvds_arrary[0][4] = lvds_fmt.r[0+highBit];
            lvds_arrary[0][5] = lvds_fmt.r[3+highBit];
            lvds_arrary[0][6] = lvds_fmt.r[2+highBit];

            lvds_arrary[1][0] = lvds_fmt.b[3+highBit];
            lvds_arrary[1][1] = lvds_fmt.b[2+highBit];
            lvds_arrary[1][2] = lvds_fmt.r[3+highBit];
            lvds_arrary[1][3] = lvds_fmt.r[2+highBit];
            lvds_arrary[1][4] = lvds_fmt.r[1+highBit];
            lvds_arrary[1][5] = lvds_fmt.r[0+highBit];
            lvds_arrary[1][6] = lvds_fmt.r[3+highBit];

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[3+highBit];
            lvds_arrary[2][4] = lvds_fmt.b[2+highBit];
            lvds_arrary[2][5] = lvds_fmt.b[1+highBit];
            lvds_arrary[2][6] = lvds_fmt.b[0+highBit];

            lvds_arrary[2][0] = lvds_fmt.res0;
        }
        else {
            // Linear step size
            lvds_arrary[0][0] = lvds_fmt.res1;
            lvds_arrary[0][1] = lvds_fmt.r[3+highBit];
            lvds_arrary[0][2] = lvds_fmt.r[2+highBit];
            lvds_arrary[0][3] = lvds_fmt.r[1+highBit];
            lvds_arrary[0][4] = lvds_fmt.r[0+highBit];
            lvds_arrary[0][5] = lvds_fmt.res0;
            lvds_arrary[0][6] = lvds_fmt.res1;

            lvds_arrary[1][0] = lvds_fmt.res0;
            lvds_arrary[1][1] = lvds_fmt.res1;
            lvds_arrary[1][2] = lvds_fmt.g[3+highBit];
            lvds_arrary[1][3] = lvds_fmt.g[2+highBit];
            lvds_arrary[1][4] = lvds_fmt.g[1+highBit];
            lvds_arrary[1][5] = lvds_fmt.g[0+highBit];
            lvds_arrary[1][6] = lvds_fmt.res0;

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[3+highBit];
            lvds_arrary[2][4] = lvds_fmt.b[2+highBit];
            lvds_arrary[2][5] = lvds_fmt.b[1+highBit];
            lvds_arrary[2][6] = lvds_fmt.b[0+highBit];

            lvds_arrary[3][0] = lvds_fmt.res0;
        }
        break;
    case RGB18_FORMAT:
        if (format == JEIDA_FORMAT) {
            lvds_arrary[0][0] = lvds_fmt.g[2+highBit];
            lvds_arrary[0][1] = lvds_fmt.r[7+highBit];
            lvds_arrary[0][2] = lvds_fmt.r[6+highBit];
            lvds_arrary[0][3] = lvds_fmt.r[5+highBit];
            lvds_arrary[0][4] = lvds_fmt.r[4+highBit];
            lvds_arrary[0][5] = lvds_fmt.r[3+highBit];
            lvds_arrary[0][6] = lvds_fmt.r[2+highBit];

            lvds_arrary[1][0] = lvds_fmt.b[3+highBit];
            lvds_arrary[1][1] = lvds_fmt.b[2+highBit];
            lvds_arrary[1][2] = lvds_fmt.g[7+highBit];
            lvds_arrary[1][3] = lvds_fmt.g[6+highBit];
            lvds_arrary[1][4] = lvds_fmt.g[5+highBit];
            lvds_arrary[1][5] = lvds_fmt.g[4+highBit];
            lvds_arrary[1][6] = lvds_fmt.g[3+highBit];

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[7+highBit];
            lvds_arrary[2][4] = lvds_fmt.b[6+highBit];
            lvds_arrary[2][5] = lvds_fmt.b[5+highBit];
            lvds_arrary[2][6] = lvds_fmt.b[4+highBit];

            lvds_arrary[3][0] = lvds_fmt.res0;
        }
        else {
            lvds_arrary[0][0] = lvds_fmt.g[0+highBit];
            lvds_arrary[0][1] = lvds_fmt.r[5+highBit];
            lvds_arrary[0][2] = lvds_fmt.r[4+highBit];
            lvds_arrary[0][3] = lvds_fmt.r[3+highBit];
            lvds_arrary[0][4] = lvds_fmt.r[2+highBit];
            lvds_arrary[0][5] = lvds_fmt.r[1+highBit];
            lvds_arrary[0][6] = lvds_fmt.r[0+highBit];

            lvds_arrary[1][0] = lvds_fmt.b[1+highBit];
            lvds_arrary[1][1] = lvds_fmt.b[0+highBit];
            lvds_arrary[1][2] = lvds_fmt.g[5+highBit];
            lvds_arrary[1][3] = lvds_fmt.g[4+highBit];
            lvds_arrary[1][4] = lvds_fmt.g[3+highBit];
            lvds_arrary[1][5] = lvds_fmt.g[2+highBit];
            lvds_arrary[1][6] = lvds_fmt.g[1+highBit];

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[5+highBit];
            lvds_arrary[2][4] = lvds_fmt.b[4+highBit];
            lvds_arrary[2][5] = lvds_fmt.b[3+highBit];
            lvds_arrary[2][6] = lvds_fmt.b[2+highBit];

            lvds_arrary[3][0] = { lvds_fmt.res0 };
        }
        break;
    case RGB24_FORMAT:
        if (format == JEIDA_FORMAT) {
            lvds_arrary[0][0] = lvds_fmt.g[2+highBit];
            lvds_arrary[0][1] = lvds_fmt.r[7+highBit];
            lvds_arrary[0][2] = lvds_fmt.r[6+highBit];
            lvds_arrary[0][3] = lvds_fmt.r[5+highBit];
            lvds_arrary[0][4] = lvds_fmt.r[4+highBit];
            lvds_arrary[0][5] = lvds_fmt.r[3+highBit];
            lvds_arrary[0][6] = lvds_fmt.r[2+highBit];

            lvds_arrary[1][0] = lvds_fmt.b[3+highBit];
            lvds_arrary[1][1] = lvds_fmt.b[2+highBit];
            lvds_arrary[1][2] = lvds_fmt.g[7+highBit];
            lvds_arrary[1][3] = lvds_fmt.g[6+highBit];
            lvds_arrary[1][4] = lvds_fmt.g[5+highBit];
            lvds_arrary[1][5] = lvds_fmt.g[4+highBit];
            lvds_arrary[1][6] = lvds_fmt.g[3+highBit];

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[7+highBit];
            lvds_arrary[2][4] = lvds_fmt.b[6+highBit];
            lvds_arrary[2][5] = lvds_fmt.b[5+highBit];
            lvds_arrary[2][6] = lvds_fmt.b[4+highBit];

            lvds_arrary[3][0] = lvds_fmt.defaults;
            lvds_arrary[3][1] = lvds_fmt.b[1+highBit];
            lvds_arrary[3][2] = lvds_fmt.b[0+highBit];
            lvds_arrary[3][3] = lvds_fmt.g[1+highBit];
            lvds_arrary[3][4] = lvds_fmt.g[0+highBit];
            lvds_arrary[3][5] = lvds_fmt.r[1+highBit];
            lvds_arrary[3][6] = lvds_fmt.r[0+highBit];

        }
        else {
            lvds_arrary[0][0] = lvds_fmt.g[0+highBit];
            lvds_arrary[0][1] = lvds_fmt.r[5+highBit];
            lvds_arrary[0][2] = lvds_fmt.r[4+highBit];
            lvds_arrary[0][3] = lvds_fmt.r[3+highBit];
            lvds_arrary[0][4] = lvds_fmt.r[2+highBit];
            lvds_arrary[0][5] = lvds_fmt.r[1+highBit];
            lvds_arrary[0][6] = lvds_fmt.r[0+highBit];

            lvds_arrary[1][0] = lvds_fmt.b[1+highBit];
            lvds_arrary[1][1] = lvds_fmt.b[0+highBit];
            lvds_arrary[1][2] = lvds_fmt.g[5+highBit];
            lvds_arrary[1][3] = lvds_fmt.g[4+highBit];
            lvds_arrary[1][4] = lvds_fmt.g[3+highBit];
            lvds_arrary[1][5] = lvds_fmt.g[2+highBit];
            lvds_arrary[1][6] = lvds_fmt.g[1+highBit];

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[5+highBit];
            lvds_arrary[2][4] = lvds_fmt.b[4+highBit];
            lvds_arrary[2][5] = lvds_fmt.b[3+highBit];
            lvds_arrary[2][6] = lvds_fmt.b[2+highBit];

            lvds_arrary[3][0] = lvds_fmt.defaults;
            lvds_arrary[3][1] = lvds_fmt.b[7+highBit];
            lvds_arrary[3][2] = lvds_fmt.b[6+highBit];
            lvds_arrary[3][3] = lvds_fmt.g[7+highBit];
            lvds_arrary[3][4] = lvds_fmt.g[6+highBit];
            lvds_arrary[3][5] = lvds_fmt.r[7+highBit];
            lvds_arrary[3][6] = lvds_fmt.r[6+highBit];
        }
        break;
    case RGB24_FORMAT_3:

        lvds_arrary[0][0] = lvds_fmt.g[2+highBit];
        lvds_arrary[0][1] = lvds_fmt.r[7+highBit];
        lvds_arrary[0][2] = lvds_fmt.r[6+highBit];
        lvds_arrary[0][3] = lvds_fmt.r[5+highBit];
        lvds_arrary[0][4] = lvds_fmt.r[4+highBit];
        lvds_arrary[0][5] = lvds_fmt.r[3+highBit];
        lvds_arrary[0][6] = lvds_fmt.r[2+highBit];

        lvds_arrary[1][0] = lvds_fmt.b[3+highBit];
        lvds_arrary[1][1] = lvds_fmt.b[2+highBit];
        lvds_arrary[1][2] = lvds_fmt.g[7+highBit];
        lvds_arrary[1][3] = lvds_fmt.g[6+highBit];
        lvds_arrary[1][4] = lvds_fmt.g[5+highBit];
        lvds_arrary[1][5] = lvds_fmt.g[4+highBit];
        lvds_arrary[1][6] = lvds_fmt.g[3+highBit];

        lvds_arrary[2][0] = lvds_fmt.data_en;
        lvds_arrary[2][1] = lvds_fmt.vsync;
        lvds_arrary[2][2] = lvds_fmt.hsync;
        lvds_arrary[2][3] = lvds_fmt.b[7+highBit];
        lvds_arrary[2][4] = lvds_fmt.b[6+highBit];
        lvds_arrary[2][5] = lvds_fmt.b[5+highBit];
        lvds_arrary[2][6] = lvds_fmt.b[4+highBit];

        lvds_arrary[3][0] = lvds_fmt.res0;

        break;
    case RGB30_FORMAT:
        if (format == JEIDA_FORMAT) {
            lvds_arrary[0][0] = lvds_fmt.g[4];
            lvds_arrary[0][1] = lvds_fmt.r[9];
            lvds_arrary[0][2] = lvds_fmt.r[8];
            lvds_arrary[0][3] = lvds_fmt.r[7];
            lvds_arrary[0][4] = lvds_fmt.r[6];
            lvds_arrary[0][5] = lvds_fmt.r[5];
            lvds_arrary[0][6] = lvds_fmt.r[4];

            lvds_arrary[1][0] = lvds_fmt.b[5];
            lvds_arrary[1][1] = lvds_fmt.b[4];
            lvds_arrary[1][2] = lvds_fmt.g[9];
            lvds_arrary[1][3] = lvds_fmt.g[8];
            lvds_arrary[1][4] = lvds_fmt.g[7];
            lvds_arrary[1][5] = lvds_fmt.g[6];
            lvds_arrary[1][6] = lvds_fmt.g[5];

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[9];
            lvds_arrary[2][4] = lvds_fmt.b[8];
            lvds_arrary[2][5] = lvds_fmt.b[7];
            lvds_arrary[2][6] = lvds_fmt.b[6];

            lvds_arrary[3][0] = lvds_fmt.res0;
            lvds_arrary[3][1] = lvds_fmt.b[3];
            lvds_arrary[3][2] = lvds_fmt.b[2];
            lvds_arrary[3][3] = lvds_fmt.g[3];
            lvds_arrary[3][4] = lvds_fmt.g[2];
            lvds_arrary[3][5] = lvds_fmt.r[3];
            lvds_arrary[3][6] = lvds_fmt.r[2];

            lvds_arrary[4][0] = lvds_fmt.res0;
            lvds_arrary[4][1] = lvds_fmt.b[1];
            lvds_arrary[4][2] = lvds_fmt.b[0];
            lvds_arrary[4][3] = lvds_fmt.g[1];
            lvds_arrary[4][4] = lvds_fmt.g[0];
            lvds_arrary[4][5] = lvds_fmt.r[1];
            lvds_arrary[4][6] = lvds_fmt.r[0];

        }
        else if (format == VESA_FORMAT) {
            lvds_arrary[0][0] = lvds_fmt.g[0];
            lvds_arrary[0][1] = lvds_fmt.r[5];
            lvds_arrary[0][2] = lvds_fmt.r[4];
            lvds_arrary[0][3] = lvds_fmt.r[3];
            lvds_arrary[0][4] = lvds_fmt.r[2];
            lvds_arrary[0][5] = lvds_fmt.r[1];
            lvds_arrary[0][6] = lvds_fmt.r[0];

            lvds_arrary[1][0] = lvds_fmt.b[1];
            lvds_arrary[1][1] = lvds_fmt.b[0];
            lvds_arrary[1][2] = lvds_fmt.g[5];
            lvds_arrary[1][3] = lvds_fmt.g[4];
            lvds_arrary[1][4] = lvds_fmt.g[3];
            lvds_arrary[1][5] = lvds_fmt.g[2];
            lvds_arrary[1][6] = lvds_fmt.g[1];

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[5];
            lvds_arrary[2][4] = lvds_fmt.b[4];
            lvds_arrary[2][5] = lvds_fmt.b[3];
            lvds_arrary[2][6] = lvds_fmt.b[2];

            lvds_arrary[3][0] = lvds_fmt.res0;
            lvds_arrary[3][1] = lvds_fmt.b[7];
            lvds_arrary[3][2] = lvds_fmt.b[6];
            lvds_arrary[3][3] = lvds_fmt.g[7];
            lvds_arrary[3][4] = lvds_fmt.g[6];
            lvds_arrary[3][5] = lvds_fmt.r[7];
            lvds_arrary[3][6] = lvds_fmt.r[6];

            lvds_arrary[4][0] = lvds_fmt.res0;
            lvds_arrary[4][1] = lvds_fmt.b[9];
            lvds_arrary[4][2] = lvds_fmt.b[8];
            lvds_arrary[4][3] = lvds_fmt.g[9];
            lvds_arrary[4][4] = lvds_fmt.g[8];
            lvds_arrary[4][5] = lvds_fmt.r[9];
            lvds_arrary[4][6] = lvds_fmt.r[8];
        }
        else {
            lvds_arrary[0][0] = lvds_fmt.g[2];
            lvds_arrary[0][1] = lvds_fmt.r[7];
            lvds_arrary[0][2] = lvds_fmt.r[6];
            lvds_arrary[0][3] = lvds_fmt.r[5];
            lvds_arrary[0][4] = lvds_fmt.r[4];
            lvds_arrary[0][5] = lvds_fmt.r[3];
            lvds_arrary[0][6] = lvds_fmt.r[2];

            lvds_arrary[1][0] = lvds_fmt.b[3];
            lvds_arrary[1][1] = lvds_fmt.b[2];
            lvds_arrary[1][2] = lvds_fmt.g[7];
            lvds_arrary[1][3] = lvds_fmt.g[6];
            lvds_arrary[1][4] = lvds_fmt.g[5];
            lvds_arrary[1][5] = lvds_fmt.g[4];
            lvds_arrary[1][6] = lvds_fmt.g[3];

            lvds_arrary[2][0] = lvds_fmt.data_en;
            lvds_arrary[2][1] = lvds_fmt.vsync;
            lvds_arrary[2][2] = lvds_fmt.hsync;
            lvds_arrary[2][3] = lvds_fmt.b[7];
            lvds_arrary[2][4] = lvds_fmt.b[6];
            lvds_arrary[2][5] = lvds_fmt.b[5];
            lvds_arrary[2][6] = lvds_fmt.b[4];

            lvds_arrary[3][0] = lvds_fmt.res0;
            lvds_arrary[3][1] = lvds_fmt.b[9];
            lvds_arrary[3][2] = lvds_fmt.b[8];
            lvds_arrary[3][3] = lvds_fmt.g[9];
            lvds_arrary[3][4] = lvds_fmt.g[8];
            lvds_arrary[3][5] = lvds_fmt.r[9];
            lvds_arrary[3][6] = lvds_fmt.r[8];

            lvds_arrary[4][0] = lvds_fmt.res0;
            lvds_arrary[4][1] = lvds_fmt.b[1];
            lvds_arrary[4][2] = lvds_fmt.b[0];
            lvds_arrary[4][3] = lvds_fmt.g[1];
            lvds_arrary[4][4] = lvds_fmt.g[0];
            lvds_arrary[4][5] = lvds_fmt.r[1];
            lvds_arrary[4][6] = lvds_fmt.r[0];
        }
        break;
    default:
        std::cout << "Error Input!!!" << std::endl;
        break;
    }
    return 0;
}

std::string get_rgb_string(const unsigned char rgb) {
    switch (rgb) {
    case 0x00:
        return "r[0]";
    case 0x01:
        return "r[1]";
    case 0x02:
        return "r[2]";
    case 0x03:
        return "r[3]";
    case 0x04:
        return "r[4]";
    case 0x05:
        return "r[5]";
    case 0x06:
        return "r[6]";
    case 0x07:
        return "r[7]";
    case 0x08:
        return "r[8]";
    case 0x09:
        return "r[9]";

    case 0x0a:
        return "g[0]";
    case 0x0b:
        return "g[1]";
    case 0x0c:
        return "g[2]";
    case 0x0d:
        return "g[3]";
    case 0x0e:
        return "g[4]";
    case 0x0f:
        return "g[5]";
    case 0x10:
        return "g[6]";
    case 0x11:
        return "g[7]";
    case 0x12:
        return "g[8]";
    case 0x13:
        return "g[9]";

    case 0x14:
        return "b[0]";
    case 0x15:
        return "b[1]";
    case 0x16:
        return "b[2]";
    case 0x17:
        return "b[3]";
    case 0x18:
        return "b[4]";
    case 0x19:
        return "b[5]";
    case 0x1a:
        return "b[6]";
    case 0x1b:
        return "b[7]";
    case 0x1c:
        return "b[8]";
    case 0x1d:
        return "b[9]";

    case 0x1e:
        return "vsync";
    case 0x1f:
        return "hsync";
    case 0x20:
        return "data_en";
    case 0x21:
        return "res0";
    case 0x22:
        return "res1";
    case 0x23:
        return "defaults";
    default:
        break;
    }
    return "Invalid";
}

static inline int lvds_formats_init(void) {
    // R
    lvds_fmt.r[0] = 0x00;
    lvds_fmt.r[1] = 0x01;
    lvds_fmt.r[2] = 0x02;
    lvds_fmt.r[3] = 0x03;
    lvds_fmt.r[4] = 0x04;
    lvds_fmt.r[5] = 0x05;
    lvds_fmt.r[6] = 0x06;
    lvds_fmt.r[7] = 0x07;
    lvds_fmt.r[8] = 0x08;
    lvds_fmt.r[9] = 0x09;
    // G
    lvds_fmt.g[0] = 0x0a;
    lvds_fmt.g[1] = 0x0b;
    lvds_fmt.g[2] = 0x0c;
    lvds_fmt.g[3] = 0x0d;
    lvds_fmt.g[4] = 0x0e;
    lvds_fmt.g[5] = 0x0f;
    lvds_fmt.g[6] = 0x10;
    lvds_fmt.g[7] = 0x11;
    lvds_fmt.g[8] = 0x12;
    lvds_fmt.g[9] = 0x13;
    // B
    lvds_fmt.b[0] = 0x14;
    lvds_fmt.b[1] = 0x15;
    lvds_fmt.b[2] = 0x16;
    lvds_fmt.b[3] = 0x17;
    lvds_fmt.b[4] = 0x18;
    lvds_fmt.b[5] = 0x19;
    lvds_fmt.b[6] = 0x1a;
    lvds_fmt.b[7] = 0x1b;
    lvds_fmt.b[8] = 0x1c;
    lvds_fmt.b[9] = 0x1d;
    // data_en
    lvds_fmt.vsync = 0x1e;
    lvds_fmt.hsync = 0x1f;
    lvds_fmt.data_en = 0x20;
    lvds_fmt.res0 = 0x21;
    lvds_fmt.res1 = 0x22;
    lvds_fmt.defaults = 0x23;
    return 0;
}

int main(int argc, char** argv) {
    lvds_formats_init();
    int format, bpps;
    std::cout << "sizeof:" << sizeof(lvds_lanes) << std::endl;
    std::cout << "\nPlease input select rgb format:\n";
    std::cout << "       [0] : RGB - 12bit\n";
    std::cout << "       [1] : RGB - 18bit\n";
    std::cout << "       [2] : RGB - 24bit\n";
    std::cout << "       [3] : RGB format 3 - 24bit\n";
    std::cout << "       [4] : RGB - 30bit\n";
    std::cout << ">";
    while (std::cin >> bpps) {
        if (bpps >= RGB12_FORMAT && bpps <= sizeof(pixel_bpps))
            break;
        else {
            std::cout << "Invalid bpps input!!!\n";
            std::cout << ">";
        }
    }
    if (bpps != RGB24_FORMAT_3 && bpps != RGB12_FORMAT) {
        std::cout << "\nPlease select format:\n";
        std::cout << "       [0] - VESA\n";
        std::cout << "       [1] - JEIDA\n";
        if (bpps == RGB30_FORMAT) {
            std::cout << "       [2] - New JEIDA\n";
        }
        std::cout << ">";
        while (std::cin >> format) {
            if (format >= VESA_FORMAT && format <= sizeof(pixel_format))
                break;
            else {
                std::cout << "Invalid formats input!!!\n";
                std::cout << ">";
            }
        }
    }
    if (bpps == RGB24_FORMAT_3) {
        format = LINEAR_STEP;
    }
    if (bpps == RGB12_FORMAT) {
        std::cout << "\nPlease input select rgb12 format:\n";
        std::cout << "       [0] : Non Linear step size\n";
        std::cout << "       [1] : Linear step size\n";
        std::cout << ">";
        while (std::cin >> format) {
            if (format == LINEAR_STEP_SIZE || format == NON_LINEAR_STEP_SIZE)
                break;
            else {
                std::cout << "Invalid input!!!\n";
                std::cout << ">";
            }
        }
    }
    bool is_high = false;
    if (bpps != RGB30_FORMAT)
    {
        std::cout << "\nIs High 8 BIT?\n";
        std::cout << "       [0] : Low 8 bit;\n";
        std::cout << "       [1] : High 8 bit;\n";
        while (std::cin >> is_high) {
            std::cout << "Select " << (is_high ? "BIT - [2]-[9]" : "BIT - [0]-[7]") << std::endl;
            break;
        }
    }
    if (is_high)
        highBit = 2;
    std::cout << "bpps:" << bpps << ", format:" << format << std::endl;
    combine_rgb((pixel_bpps)bpps, format);
    std::cout << "--------------------------------\n";
    PRINT(lvds_arrary, 6);
    PRINT(lvds_arrary, 5);
    PRINT(lvds_arrary, 4);
    PRINT(lvds_arrary, 3);
    PRINT(lvds_arrary, 2);
    PRINT(lvds_arrary, 1);
    PRINT(lvds_arrary, 0);
    std::cout << "--------------------------------\n";

        PRINT_ASSIGNMENT(lvds_arrary, 6);
        PRINT_ASSIGNMENT(lvds_arrary, 5);
        PRINT_ASSIGNMENT(lvds_arrary, 4);
        PRINT_ASSIGNMENT(lvds_arrary, 3);
        PRINT_ASSIGNMENT(lvds_arrary, 2);
        PRINT_ASSIGNMENT(lvds_arrary, 1);
        PRINT_ASSIGNMENT(lvds_arrary, 0);

    std::cout << "--------------------------------\n";
    std::cout << std::hex << "CH1_A0_SEL_CFG: 0x" << CH1_A0_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH1_A1_SEL_CFG: 0x" << CH1_A1_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH1_A2_SEL_CFG: 0x" << CH1_A2_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH1_A3_SEL_CFG: 0x" << CH1_A3_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH1_A4_SEL_CFG: 0x" << CH1_A4_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH1_A5_SEL_CFG: 0x" << CH1_A5_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH1_A6_SEL_CFG: 0x" << CH1_A6_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << "--------------------------------\n";
    std::cout << std::hex << "CH2_A0_SEL_CFG: 0x" << CH2_A0_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH2_A1_SEL_CFG: 0x" << CH2_A1_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH2_A2_SEL_CFG: 0x" << CH2_A2_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH2_A3_SEL_CFG: 0x" << CH2_A3_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH2_A4_SEL_CFG: 0x" << CH2_A4_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH2_A5_SEL_CFG: 0x" << CH2_A5_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << std::hex << "CH2_A6_SEL_CFG: 0x" << CH2_A6_SEL_CFG(lvds_arrary) << std::endl;
    std::cout << "--------------------------------\n\n";
    system("pause");
    getchar();
    return 0;
}
