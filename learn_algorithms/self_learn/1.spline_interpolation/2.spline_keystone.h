//
// Created by renbin jiang on 2022/4/5.
//

#ifndef CPLUSPLUSTHINGS_2_SPLINE_KEYSTONE_H
#define CPLUSPLUSTHINGS_2_SPLINE_KEYSTONE_H
#include "base.h"

typedef struct {
    int S16X;
    int S16Y;
} PointCoordinate;

#define SPLINE_T_LOG(tag, var) \
    { printf("%s  %s[a=%f, b=%f, c=%f, d=%f]\n", __FUNCTION__, tag, var.a, var.b, var.c, var.d);}
// x: variable name, y: row num, z: line num
#define COORDINATE_LOG(tag, x, y, z)                                                         \
    ({                                                                                       \
        do {                                                                                 \
            int i, j;                                                                        \
            printf("%s:\n", tag);                                                            \
            for (i = 0; i < y; i++) {                                                        \
                printf("\trow:%d ", i);                                                      \
                for (j = 0; j < z; j++) {                                                    \
                    printf("[%d][%d] = (%*d, %*d)", i, j, 4, x[i][j].S16X, 4, x[i][j].S16Y); \
                }                                                                            \
                printf("\r\n");                                                              \
            }                                                                                \
        } while (0);                                                                         \
    })
//===== Input resolution =====//
#define DEF_IACTHW 3840 // Horizontal resolution (Total)	- Fix for 3840x2160@60 resolution
#define DEF_IACTVW \
    2160 // Vorizontal resolution			- Fix for 3840x2160@60 resolution

//===== Output resolution =====//
#define DEF_OACTHW 3840 // Horizontal resolution (Total)	- Fix for 3840x2160@60 resolution
#define DEF_OACTVW \
    2160 // Vorizontal resolution			- Fix for 3840x2160@60 resolution

//===== Warping mode =====//
//===== Number of warping cursor =====//
#define DEF_NUM_WPMODE 3 // Number of cursor mode, 2x2, 3x3, 5x3
#define DEF_CUREN_H                                         \
    {                                                       \
        {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, { 1, 1, 1, 1, 1 } \
    } // Horizontal cursor enable. 2(2x2),3(3x3),5(5x3)
#define DEF_CUREN_V                       \
    {                                     \
        {1, 0, 1}, {1, 1, 1}, { 1, 1, 1 } \
    }                       // Vertical cursor enable.   2(2x2),3(3x3),3(5x3)
#define DEF_NUM_CUR_MAX_H 5 // Maximum number of horizontal cursors
#define DEF_NUM_CUR_MAX_V 3 // Maximum number of vertical cursors
#define DEF_NUM_CUR_MAX \
    5 // = (DEF_NUM_CUR_MAX_V > DEF_NUM_CUR_MAX_H) ? DEF_NUM_CUR_MAX_V : DEF_NUM_CUR_MAX_H

//===== for calc =====//
// divide by 0
#define DEF_DIV0 0xFFFFFFFF

//===== Warp Param =====//
#define DEF_HW_MAX 4096
#define DEF_VW_MAX 2400
#define DEF_HW_MAX_GRD \
    129 // = DEF_HW_MAX / PS_WP_SPACE + 1	[roundup]	// PS_WP_SPACE = ((HW > 2048) | (VW
// > 1200)) ? 32 : 16;
#define DEF_VW_MAX_GRD \
    76 // = DEF_VW_MAX / PS_WP_SPACE + 1	[roundup]	// PS_WP_SPACE = ((HW > 2048) | (VW
// > 1200)) ? 32 : 16;

//===== Warp Lim =====//
#define DEF_WPLIM_VSH_AVE 0.6 // Limitation of averate V-shrink rate
#define DEF_CURMD                \
    {                            \
        {2, 2}, {3, 3}, { 5, 3 } \
    } // Cursor number setting
// {{H,V},{H,V},...} (e.g. {{2,2},{3,3}} -> WPMODE=0 : 2x2, WPMODE=1 : 3x3
// Values that can be set = 2,3,5,9,17,(2^n+1)
// Please set the number of cursors not to decrease when increasing the WPMODE.

#define DEF_WPLIMANG_H 1.19 // Limitation of H-slope : tan(50deg)
#define DEF_WPLIMANG_V 5.67 // Limitation of V-slope : tan(80deg)
#define DEF_WPLIMITV_H 2    // Limitation of horizontal interval of grid : DEF_WPLIMITV_H > 0
#define DEF_WPLIMITV_V 2    // Limitation of vertical interval of grid : DEF_WPLIMITV_V > 0
#define DEF_NUM_CUR_MAX_H_M1 (DEF_NUM_CUR_MAX_H - 1)
#define DEF_NUM_CUR_MAX_V_M1 (DEF_NUM_CUR_MAX_V - 1)
//===== Structure =====//
typedef struct {
    int dist;
    int vw;
    int axis;
} wp_prjp; // Projection system parameter

typedef struct {
    float x, y, z;
} wp_3dpos;

typedef struct {
    float x, y;
} wp_2dpos;

// tmp struct define
typedef struct {
    int tl_x_ofs; // poinit 1
    int tl_y_ofs;

    int tr_x_ofs;
    int tr_y_ofs;

    int bl_x_ofs;
    int bl_y_ofs;

    int br_x_ofs;
    int br_y_ofs;

    int tm_x_ofs;
    int tm_y_ofs;

    int bm_x_ofs;
    int bm_y_ofs;

    int lm_x_ofs;
    int lm_y_ofs;

    int rm_x_ofs;
    int rm_y_ofs;

    int ang_h_ofs;
    int ang_v_ofs;
} wp_ofst; // 4-corner position

typedef struct _wp_ofs_f {
    double tl_x_ofs; // poinit 1
    double tl_y_ofs;

    double tr_x_ofs;
    double tr_y_ofs;

    double bl_x_ofs;
    double bl_y_ofs;

    double br_x_ofs;
    double br_y_ofs;

    double tm_x_ofs;
    double tm_y_ofs;

    double bm_x_ofs;
    double bm_y_ofs;

    double lm_x_ofs;
    double lm_y_ofs;

    double rm_x_ofs;
    double rm_y_ofs;

    double ang_h_ofs;
    double ang_v_ofs;
} wp_ofst_f; // 4-corner position

// tmp struct define
typedef struct {
    int tl_x; // poinit 1
    int tl_y;

    int tr_x;
    int tr_y;

    int bl_x;
    int bl_y;

    int br_x;
    int br_y;

    int tm_x; // poinit 1
    int tm_y;

    int bm_x;
    int bm_y;

    int lm_x;
    int lm_y;

    int rm_x;
    int rm_y;

    int angh;
    int angv;
} wp_coo; // 4-corner position

typedef struct _ipc381_db {
    U32 update_flag[1];
    U8 _3d;
    U8 mode_li;
    U8 mode_col;
    U16 ofst_sca_hf;
    U16 ofst_sca_vf;
    U32 hsres;
    U32 vsres;
    wp_ofst ofst;
    wp_ofst_f ofst_f;
} Ipc381Db;

// parameter
typedef struct {
    int x;
    int y;
} coord_t;

typedef struct {
    float x;
    float y;
} coord_f_t;

typedef struct {
    double a[3];
    double b[3];
    double c[3];
} homography_coef_t;

typedef struct {
    float a;
    float b;
    float c;
    float d;
} spline_coef_t;

//===== Enum =====//
enum enm_warping_error_tag {
    WARPING_NO_ERROR,
    WARPING_ERROR_ANG_H, // Warping error : H-slope
    WARPING_ERROR_ANG_V, // Warping error : V-slope
    WARPING_ERROR_VSH_L, // Warping error : local V-shrink rate
    WARPING_ERROR_VSH_A, // Warping error : average V-shrink rate
    WARPING_ERROR_HSH,   // Warping error : H-shrink rate
    //	WARPING_ERROR_OUTSIDE_AREA,		// Warping error : outside
    // of ACT
    WARPING_ERROR_GRID_INTERVAL, // Warping error : grid interval
    WARPING_ERROR                // Warping error : other reasons
};

int GV_NUM_WPCUR_H = 5;
int GV_NUM_WPCUR_V = 3;
// Make a global declaration to avoid stack overflow.
//===== Use only in CalcWpTable() ====//
int PS_WPSPACE;
int PS_WPSPACE_BIT;
float PS_WPLIMVSH_L; // Limitation of local V-shrink rate
float PS_WPLIMVSH_A; // Limitation of averate V-shrink rate
float PS_WPLIMHSH;   // Limitation of H-shrink rate

// const (Constants are initialized in headers_main.h)
extern const int PS_NUM_WPMODE;
extern const int PS_NUM_CUR_MAX_H;
extern const int PS_NUM_CUR_MAX_V;
extern const char PS_WPCUR_H_EN[DEF_NUM_WPMODE][DEF_NUM_CUR_MAX_H];
extern const char PS_WPCUR_V_EN[DEF_NUM_WPMODE][DEF_NUM_CUR_MAX_V];

//===== output parameters =====//
int PS_WP_HW;
int PS_WP_VW;
int PS_WP_HW_GRD;
int PS_WP_VW_GRD;
float PS_CUR_DEF_OX[DEF_NUM_CUR_MAX_H];
float PS_CUR_DEF_OY[DEF_NUM_CUR_MAX_V];

//===== Input parameters =====//
int PS_WP_IHW;
int PS_WP_IVW;
float PS_CUR_DEF_IX[DEF_NUM_CUR_MAX_H];
float PS_CUR_DEF_IY[DEF_NUM_CUR_MAX_V];
spline_coef_t g_hline[DEF_NUM_CUR_MAX_H + 1][DEF_NUM_CUR_MAX_V];
spline_coef_t g_vline[DEF_NUM_CUR_MAX_H][DEF_NUM_CUR_MAX_V + 1];
spline_coef_t g_hline_mv[DEF_NUM_CUR_MAX_H + 1];
spline_coef_t g_vline_mv[DEF_HW_MAX_GRD][DEF_NUM_CUR_MAX_V + 1];
float g_ver_line_x[DEF_NUM_CUR_MAX_H];
float g_hor_line_y[DEF_HW_MAX_GRD][DEF_NUM_CUR_MAX_V];

//===== Use only in MoveCur() ====//
coord_f_t g_mv_curpos_old[DEF_NUM_CUR_MAX_H][DEF_NUM_CUR_MAX_V];

//===== Use only in CalcWpCur() ====//
coord_f_t g_pj_curpos[DEF_NUM_CUR_MAX_H][DEF_NUM_CUR_MAX_V];

coord_f_t PM_WPCUR[DEF_NUM_CUR_MAX_H][DEF_NUM_CUR_MAX_V];
const int PS_NUM_WPMODE = DEF_NUM_WPMODE;
const int PS_NUM_CUR_MAX_H = DEF_NUM_CUR_MAX_H;
const int PS_NUM_CUR_MAX_V = DEF_NUM_CUR_MAX_V;
const char PS_WPCUR_H_EN[DEF_NUM_WPMODE][DEF_NUM_CUR_MAX_H] = DEF_CUREN_H;
const char PS_WPCUR_V_EN[DEF_NUM_WPMODE][DEF_NUM_CUR_MAX_V] = DEF_CUREN_V;

#define C382_PANEL_V 2160
#define C382_PANEL_H 3840

int PM_WPMODE = 1;
typedef Ipc381Db Ipc382Db;
Ipc382Db m_ipcIns;

#endif // CPLUSPLUSTHINGS_2_SPLINE_KEYSTONE_H
