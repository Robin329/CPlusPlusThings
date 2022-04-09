//
// Created by renbin jiang on 2022/4/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <magic_enum.hpp>

#include "2.spline_keystone.h"

using namespace std;
using namespace base;

void InitParamWp(void);
U8 getRefMatrixCoor(U8 li, U8 col, coord_t *point);
void InitParamWp(void);
int CheckWpLimitA(int tbl_tlx, int tbl_tly, int tbl_trx, int tbl_try, int tbl_blx, int tbl_bly, int tbl_brx,
                  int tbl_bry, int *x, int *y, float *diffy_y_sum, float *divn);
int CheckWpLimitB(float *diffy_y_sum, float *divn);
void updateWpMatrix(PointCoordinate *pOfst);
coord_f_t Homography(homography_coef_t coef, coord_f_t pt, coord_f_t stp);
int CalcSplineCoef(coord_f_t p[], int pnum, spline_coef_t cf[]);
int CalcWpCur(void);
float CalcSpline(spline_coef_t coef, float x, float x0);
void CalcPjConv(coord_f_t wpcur[][DEF_NUM_CUR_MAX_V], coord_f_t pjcur[][DEF_NUM_CUR_MAX_V]);
void CalcHomographyCoef(coord_f_t tl, coord_f_t tr, coord_f_t bl, coord_f_t br, coord_f_t stp, float hw, float vw,
                        homography_coef_t *coef);
void updateWpMatrix(PointCoordinate *pOfst);
int CalcWpTable(coord_f_t cur_pos[][DEF_NUM_CUR_MAX_V]);

// ref: https://www.cnblogs.com/ondaytobewhoyouwant/p/8989497.html
float CalcSpline(spline_coef_t coef, float x, float x0) {
    float pt;
    float w;
    float w_sq; // square 二次
    float w_cu; // cube 三次

    w = x - x0;
    w_sq = w * w;
    w_cu = w_sq * w;

    pt = coef.a * w_cu + coef.b * w_sq + coef.c * w + coef.d;

    return pt;
}

int CalcSplineCoef(coord_f_t p[], int pnum, spline_coef_t cf[]) {
    float u[DEF_NUM_CUR_MAX];
    float h[DEF_NUM_CUR_MAX - 1], vh[DEF_NUM_CUR_MAX - 1];
    float hr[DEF_NUM_CUR_MAX - 1]; // Reciprocal of h[].
    float e[DEF_NUM_CUR_MAX - 1], f[DEF_NUM_CUR_MAX - 1];
    float v[DEF_NUM_CUR_MAX - 2], m[3];

    float den;
    float denr; // Reciprocal of den.
    int i;

    if ((pnum < 3) || (pnum > DEF_NUM_CUR_MAX)) {
        return 1;
    } // Out of range

    h[0] = p[1].x - p[0].x;
    //	if (h[0] < 0.000001) { h[0] = 0.000001; }// Reversal of the coordinate is not allowed
    if (h[0] < 0.000001) {
        return 1;
    } // Reversal of the coordinate is not allowed
    hr[0] = 1 / h[0];
    vh[0] = (p[1].y - p[0].y) * hr[0];

    e[0] = 0;
    f[0] = 0;
    m[2] = 0;
    for (i = 1; i <= (pnum - 2); i++) { // i -> p,h,e,f
        h[i] = p[i + 1].x - p[i].x;
        //		if (h[i] < 0.000001) { h[i] = 0.000001; }// Reversal of the coordinate is
        // not allowed
        if (h[i] < 0.000001) {
            return 1;
        } // Reversal of the coordinate is not allowed
        hr[i] = 1 / h[i];
        vh[i] = (p[i + 1].y - p[i].y) * hr[i];

        v[i - 1] = vh[i] - vh[i - 1];
        m[0] = m[2];
        m[1] = 2 * (h[i - 1] + h[i]);
        m[2] = h[i];

        den = m[1] - e[i - 1] * m[0];
        if (den == 0) {
            den = 0.000001;
        } // Div0
        denr = 1 / den;

        e[i] = m[2] * denr;
        f[i] = (v[i - 1] - f[i - 1] * m[0]) * denr;
    }

    u[pnum - 1] = 0;
    for (i = (pnum - 2); i >= 1; i--) {
        u[i] = f[i] - e[i] * u[i + 1];
    }
    u[0] = 0;

    // Spline interpolation from start point to end point
    for (i = 0; i <= (pnum - 2); i++) {
        cf[i + 1].a = (u[i + 1] - u[i]) * hr[i];
        cf[i + 1].b = 3.0 * u[i];
        cf[i + 1].c = vh[i] - (u[i + 1] + 2 * u[i]) * h[i];
        cf[i + 1].d = p[i].y;
    }

    // Before the starting point
    cf[0].a = 0;
    cf[0].b = 0;
    cf[0].c = cf[1].c;
    cf[0].d = cf[1].d;

    // After the ending point
    cf[pnum].a = 0;
    cf[pnum].b = 0;
    cf[pnum].c = cf[pnum - 1].c + cf[pnum - 1].b * h[pnum - 2];
    cf[pnum].d = p[pnum - 1].y;

    return 0; // No Error
}

void CalcHomographyCoef(coord_f_t tl, coord_f_t tr, coord_f_t bl, coord_f_t br, coord_f_t stp, float hw, float vw,
                        homography_coef_t *coef) {
    float det;

    tl.x = tl.x - stp.x;
    tl.y = tl.y - stp.y;

    tr.x = tr.x - stp.x;
    tr.y = tr.y - stp.y;

    bl.x = bl.x - stp.x;
    bl.y = bl.y - stp.y;

    br.x = br.x - stp.x;
    br.y = br.y - stp.y;

    //===== calculate homography coefficient =====//
    det = (br.x - tr.x) * (br.y - bl.y) - (br.x - bl.x) * (br.y - tr.y);
    coef->a[0] = ((det == 0) || (hw == 0)) ? DEF_DIV0
                                           : ((tr.x - tl.x) * (br.y - bl.y) - (br.x - bl.x) * (tr.y - tl.y)) / det / hw;
    coef->b[0] = ((det == 0) || (vw == 0)) ? DEF_DIV0
                                           : ((tr.x - br.x) * (tl.y - bl.y) - (tl.x - bl.x) * (tr.y - br.y)) / det / vw;
    coef->c[0] = 1.0;
    coef->a[1] = (hw == 0) ? DEF_DIV0 : tr.x * coef->a[0] + (tr.x - tl.x) / hw;
    coef->b[1] = (vw == 0) ? DEF_DIV0 : bl.x * coef->b[0] + (bl.x - tl.x) / vw;
    coef->c[1] = tl.x;
    coef->a[2] = (hw == 0) ? DEF_DIV0 : tr.y * coef->a[0] + (tr.y - tl.y) / hw;
    coef->b[2] = (vw == 0) ? DEF_DIV0 : bl.y * coef->b[0] + (bl.y - tl.y) / vw;
    coef->c[2] = tl.y;
}

void CalcPjConv(coord_f_t wpcur[][DEF_NUM_CUR_MAX_V], coord_f_t pjcur[][DEF_NUM_CUR_MAX_V]) {
    homography_coef_t cf;
    coord_f_t tl, tr, bl, br;
    coord_f_t stp, pt;
    float hw, vw;
    int h, v;
    int hedge, vedge;

    tl = wpcur[0][0];
    tr = wpcur[PS_NUM_CUR_MAX_H - 1][0];
    bl = wpcur[0][PS_NUM_CUR_MAX_V - 1];
    br = wpcur[PS_NUM_CUR_MAX_H - 1][PS_NUM_CUR_MAX_V - 1];

    stp.x = PS_CUR_DEF_IX[0];
    stp.y = PS_CUR_DEF_IY[0];

    hw = PS_CUR_DEF_IX[PS_NUM_CUR_MAX_H - 1] - stp.x;
    vw = PS_CUR_DEF_IY[PS_NUM_CUR_MAX_V - 1] - stp.y;

    CalcHomographyCoef(tl, tr, bl, br, stp, hw, vw, &cf);

    for (v = 0; v < PS_NUM_CUR_MAX_V; v++) {
        for (h = 0; h < PS_NUM_CUR_MAX_H; h++) {
            hedge = ((h == 0) || (h == PS_NUM_CUR_MAX_H - 1)) ? 1 : 0; // Horizontal edge
            vedge = ((v == 0) || (v == PS_NUM_CUR_MAX_V - 1)) ? 1 : 0; // Vertical edge

            if ((hedge == 1) && (vedge == 1)) { // corner
                pjcur[h][v] = wpcur[h][v];
            } else {
                pt.x = PS_CUR_DEF_IX[h];
                pt.y = PS_CUR_DEF_IY[v];
                pjcur[h][v] = Homography(cf, pt, stp);
            }
        }
    }
}

coord_f_t Homography(homography_coef_t coef, coord_f_t pt, coord_f_t stp) {
    coord_f_t opt;
    float denom;

    pt.x = pt.x - stp.x;
    pt.y = pt.y - stp.y;

    denom = coef.a[0] * pt.x + coef.b[0] * pt.y + coef.c[0];
    if (denom < 0.000001) {
        denom = 0.000001;
    }
    opt.x = (coef.a[1] * pt.x + coef.b[1] * pt.y + coef.c[1]) / denom + stp.x;
    opt.y = (coef.a[2] * pt.x + coef.b[2] * pt.y + coef.c[2]) / denom + stp.y;

    return opt;
}

int CheckWpLimitA(int tbl_tlx, int tbl_tly, int tbl_trx, int tbl_try, int tbl_blx, int tbl_bly, int tbl_brx,
                  int tbl_bry, int *x, int *y, float *diffy_y_sum, float *divn) {
    float diffx_x, diffy_x, diffx_y, diffy_y, idiffy_y;
    float tan_h = 0;
    float tan_v = 0;
    int ihw = PS_WP_IHW * 8;
    int ivw = PS_WP_IVW * 8;
    printf("tlx:%d tly:%d trx:%d try:%d blx:%d bly:%d brx:%d bry:%d x:%d y:%d\n", tbl_tlx, tbl_tly, tbl_trx, tbl_try, tbl_blx, tbl_bly, tbl_brx, tbl_bry, *x, *y);
    if ((*x > 0) || (*y > 0)) {
        if ((tbl_tlx < 0) && (tbl_trx < 0) && (tbl_blx < 0) && (tbl_brx < 0)) {
            return WARPING_NO_ERROR; // Outside of ACT (Horizontal)
        }
        if ((tbl_tlx > ihw) && (tbl_trx > ihw) && (tbl_blx > ihw) && (tbl_brx > ihw)) {
            return WARPING_NO_ERROR; // Outside of ACT (Horizontal)
        }
        if ((tbl_tly < 0) && (tbl_try < 0) && (tbl_bly < 0) && (tbl_bry < 0)) {
            return WARPING_NO_ERROR; // Outside of ACT (Vertical)
        }
        if ((tbl_tly > ivw) && (tbl_try > ivw) && (tbl_bly > ivw) && (tbl_bry > ivw)) {
            return WARPING_NO_ERROR; // Outside of ACT (Vertical)
        }

        if (*x > 0) {
            diffx_x = (float)(tbl_brx - tbl_blx);
            diffy_x = (float)(tbl_bry - tbl_bly);

            // Horizontal zoom
            if (diffx_x <= 0) { // The zoom rate is infinite.
                return WARPING_ERROR_GRID_INTERVAL;
            }
            // Horizontal slope
            tan_h = diffy_x / diffx_x;
            if ((tan_h < (-DEF_WPLIMANG_H)) || (tan_h > DEF_WPLIMANG_H)) {
                return WARPING_ERROR_ANG_H;
            }
            // Horizontal shrink rate
            if (diffx_x > PS_WPLIMHSH) {
                return WARPING_ERROR_HSH;
            }
        } // end if(x < PS_WP_HW_GRD)

        if (*y > 0) {
            diffx_y = (float)(tbl_brx - tbl_trx);
            diffy_y = (float)(tbl_bry - tbl_try);

            idiffy_y = diffy_y + diffx_y * (-tan_h);

            // Vertical zoom
            if (diffy_y <= 0) { // The zoom rate is infinite.
                return WARPING_ERROR_GRID_INTERVAL;
            }
            // Vertical local shrink rate
            if (idiffy_y > PS_WPLIMVSH_L) {
                return WARPING_ERROR_VSH_L;
            }
            // Vertical slope
            tan_v = diffx_y / diffy_y;
            if ((tan_v < (-DEF_WPLIMANG_V)) || (tan_v > DEF_WPLIMANG_V)) {
                std::cout << "tav_v:" << tan_v << " out of [" << DEF_WPLIMANG_V << "]" << std::endl; return WARPING_ERROR_ANG_V;
            }

            *diffy_y_sum = (*diffy_y_sum) + idiffy_y;
            *divn = (*divn) + 1;
        } // end if(y > 0)
    }     // end if((x > 0)||(y > 0))

    return WARPING_NO_ERROR; // no error
}

int CheckWpLimitB(float *diffy_y_sum, float *divn) {
    if ((*diffy_y_sum) > (PS_WPLIMVSH_A * (*divn))) {
        return WARPING_ERROR_VSH_A;
    }

    return WARPING_NO_ERROR; // no error
}

int CalcWpCur(void) {
    coord_f_t temp_pt[DEF_NUM_CUR_MAX] = {};
    spline_coef_t temp_spl_cf[DEF_NUM_CUR_MAX + 1] = {};

    float scla;
    float scl_pj, scl_cur;
    float sclb[2];

    int i, j;
    int h, v;
    int h0, v0;
    float t;
    int area;

    // Calculate the projective transformation for spline interpolation.
    // 计算样条插值的投影变换。
    //    COOR_T_LOG("PM_WPCUR", PM_WPCUR, 5, 3);
    CalcPjConv(PM_WPCUR, g_pj_curpos);
    //    COOR_T_LOG("g_pj_curpos", g_pj_curpos, 5, 3);
    for (v = 0; v < PS_NUM_CUR_MAX_V; v++) {
        for (h = 0; h < PS_NUM_CUR_MAX_H; h++) {
            if ((PS_WPCUR_H_EN[PM_WPMODE][h] == 0) || (PS_WPCUR_V_EN[PM_WPMODE][v] == 0)) {
                PM_WPCUR[h][v] = g_pj_curpos[h][v]; //不能调整的点设为默认的初始值
            }
        }
    }
    //    COOR_T_LOG("PM_WPCUR", PM_WPCUR, 5, 3);
    // Calculate the coordinates of the cursor on the line where spline interpolation is
    // possible.(Horizontal line) 计算光标在可以进行样条插值的线上的坐标。（水平线）
    if ((GV_NUM_WPCUR_H >= 3) && (GV_NUM_WPCUR_H < PS_NUM_CUR_MAX_H)) {
        for (v = 0; v < PS_NUM_CUR_MAX_V; v++) {
            if ((v == 0) || (v == (PS_NUM_CUR_MAX_V - 1))) {
                area = 0;
                for (h = 0; h < PS_NUM_CUR_MAX_H; h++) {
                    if (PS_WPCUR_H_EN[PM_WPMODE][h] != 0) {
                        temp_pt[area].x = PM_WPCUR[h][v].x;
                        temp_pt[area].y = PM_WPCUR[h][v].y;
                        printf("H --->> area:%d PM_WPCUR[%d][%d] = (%f, %f) temp_pt[%d] = (%f, "
                               "%f)\n",
                               area, h, v, PM_WPCUR[h][v].x, PM_WPCUR[h][v].y, area, temp_pt[area].x, temp_pt[area].y);
                        area = area + 1;
                    }
                }
                //				CalcSplineCoef(temp_pt, GV_NUM_WPCUR_H,
                // temp_spl_cf);
                //
                if (0 != CalcSplineCoef(temp_pt, GV_NUM_WPCUR_H, temp_spl_cf)) {
                    return 1; // Reversal of the coordinate is not allowed
                }
                SPLINE_T_LOG("temp_spl_cf0", temp_spl_cf[0]);
                SPLINE_T_LOG("temp_spl_cf1", temp_spl_cf[1]);
                SPLINE_T_LOG("temp_spl_cf2", temp_spl_cf[2]);
                SPLINE_T_LOG("temp_spl_cf3", temp_spl_cf[3]);
                SPLINE_T_LOG("temp_spl_cf4", temp_spl_cf[4]);
                SPLINE_T_LOG("temp_spl_cf5", temp_spl_cf[5]);
                COOR_T_LOG("PM_WPCUR", PM_WPCUR, 5, 3);
                h0 = 0;
                area = 0;
                for (i = 1; i < PS_NUM_CUR_MAX_H; i++) {
                    if (PS_WPCUR_H_EN[PM_WPMODE][i] != 0) {
                        for (h = h0 + 1; h < i; h++) {
                            if (g_pj_curpos[i][v].x == g_pj_curpos[h0][v].x) {
                                printf("i:%d, h0:%d, v:%d\n", i, h0, v);
                                // div0
                            } else {
                                t = (g_pj_curpos[h][v].x - g_pj_curpos[h0][v].x) /
                                    (g_pj_curpos[i][v].x - g_pj_curpos[h0][v].x);
                                printf("v:%d t:%f g_pj_curpos[h][v].x:%f g_pj_curpos[h0][v].x:%f "
                                       "g_pj_curpos[i][v].x:%f\n",
                                       v, t, g_pj_curpos[h][v].x, g_pj_curpos[h0][v].x, g_pj_curpos[i][v].x);
                                PM_WPCUR[h][v].x = PM_WPCUR[h][v].x +
                                                   (PM_WPCUR[h0][v].x - g_pj_curpos[h0][v].x) * (1 - t) +
                                                   (PM_WPCUR[i][v].x - g_pj_curpos[i][v].x) * t;
                            }
                            printf("PM_WPCUR[h][v].x:%f area:%d PM_WPCUR[h0][v].x:%f\n", PM_WPCUR[h][v].x, area,
                                   PM_WPCUR[h0][v].x);
                            PM_WPCUR[h][v].y = CalcSpline(temp_spl_cf[area + 1], PM_WPCUR[h][v].x, PM_WPCUR[h0][v].x);
                            printf("PM_WPCUR[h][v].y:%f\n", PM_WPCUR[h][v].y);
                        }
                        h0 = i;
                        area = area + 1;
                    }
                }
            }
        }
    }

    // Calculate the coordinates of the cursor on the line where spline interpolation is
    // possible.(Vertical line)
    if ((GV_NUM_WPCUR_V >= 3) && (GV_NUM_WPCUR_V < PS_NUM_CUR_MAX_V)) {
        for (h = 0; h < PS_NUM_CUR_MAX_H; h++) {
            if ((h == 0) || (h == (PS_NUM_CUR_MAX_H - 1))) {
                area = 0;
                for (v = 0; v < PS_NUM_CUR_MAX_V; v++) {
                    if (PS_WPCUR_V_EN[PM_WPMODE][v] != 0) {
                        temp_pt[area].x = PM_WPCUR[h][v].y; // x -> y
                        temp_pt[area].y = PM_WPCUR[h][v].x; // y -> x
                        printf("\n V --->> PM_WPCUR[%d][%d] = (%f, %f) temp_pt[%d] = (%f, %f)\n", h, v,
                               PM_WPCUR[h][v].x, PM_WPCUR[h][v].y, area, temp_pt[area].x, temp_pt[area].y);
                        area = area + 1;
                    }
                }
                //				CalcSplineCoef(temp_pt, GV_NUM_WPCUR_V,
                // temp_spl_cf);
                if (0 != CalcSplineCoef(temp_pt, GV_NUM_WPCUR_V, temp_spl_cf)) {
                    return 1; // Reversal of the coordinate is not allowed
                }
                SPLINE_T_LOG("temp_spl_cf0", temp_spl_cf[0]);
                SPLINE_T_LOG("temp_spl_cf1", temp_spl_cf[1]);
                SPLINE_T_LOG("temp_spl_cf2", temp_spl_cf[2]);
                SPLINE_T_LOG("temp_spl_cf3", temp_spl_cf[3]);
                SPLINE_T_LOG("temp_spl_cf4", temp_spl_cf[4]);
                SPLINE_T_LOG("temp_spl_cf5", temp_spl_cf[5]);
                v0 = 0;
                area = 0;
                for (i = 1; i < PS_NUM_CUR_MAX_V; i++) {
                    if (PS_WPCUR_V_EN[PM_WPMODE][i] != 0) {
                        for (v = v0 + 1; v < i; v++) {
                            if (g_pj_curpos[h][i].y == g_pj_curpos[h][v0].y) {
                                // div0
                            } else {
                                t = (g_pj_curpos[h][v].y - g_pj_curpos[h][v0].y) /
                                    (g_pj_curpos[h][i].y - g_pj_curpos[h][v0].y);
                                PM_WPCUR[h][v].y = PM_WPCUR[h][v].y +
                                                   (PM_WPCUR[h][v0].y - g_pj_curpos[h][v0].y) * (1 - t) +
                                                   (PM_WPCUR[h][i].y - g_pj_curpos[h][i].y) * t;
                            }
                            PM_WPCUR[h][v].x = CalcSpline(temp_spl_cf[area + 1], PM_WPCUR[h][v].y, PM_WPCUR[h][v0].y);
                        }
                        v0 = i;
                        area = area + 1;
                    }
                }
            }
        }
    }
    COOR_T_LOG("g_pj_curpos", g_pj_curpos, 5, 3);
    // Calculate the internal cursor coordinates.
    v0 = 0; // top side
    for (j = 1; j < PS_NUM_CUR_MAX_V; j++) {
        if (j == (PS_NUM_CUR_MAX_V - 1)) {
            for (v = (v0 + 1); v < j; v++) {
                h0 = 0; // left side
                for (i = 1; i < PS_NUM_CUR_MAX_H; i++) {
                    if (i == (PS_NUM_CUR_MAX_H - 1)) {
                        for (h = (h0 + 1); h < i; h++) {
                            // x
                            printf("v:%d h:%d v0:%d h0:%d i:%d j:%d g_pj_curpos[%d][%d].x:%f g_pj_curpos[%d][%d].x:%f "
                                   "g_pj_curpos[%d][v].x:%f\n",
                                   v, h, v0, h0, i, j, h, v, g_pj_curpos[h][v].x, h0, v, g_pj_curpos[h0][v].x, i,
                                   g_pj_curpos[i][v].x);
                            scla = (g_pj_curpos[i][v].x == g_pj_curpos[h0][v].x)
                                           ? 0
                                           : (g_pj_curpos[h][v].x - g_pj_curpos[h0][v].x) /
                                                     (g_pj_curpos[i][v].x - g_pj_curpos[h0][v].x);
                            // top side
                            scl_pj = (g_pj_curpos[i][v0].x == g_pj_curpos[h0][v0].x)
                                             ? 0
                                             : (g_pj_curpos[h][v0].x - g_pj_curpos[h0][v0].x) /
                                                       (g_pj_curpos[i][v0].x - g_pj_curpos[h0][v0].x);
                            // 调整之后的第一小段占整个余下的段的比例
                            scl_cur = (PM_WPCUR[i][v0].x == PM_WPCUR[h0][v0].x)
                                              ? 0
                                              : (PM_WPCUR[h][v0].x - PM_WPCUR[h0][v0].x) /
                                                        (PM_WPCUR[i][v0].x - PM_WPCUR[h0][v0].x);
                            sclb[0] = (scl_pj == 0) ? 0 : scl_cur / scl_pj;
                            printf("top --> t:%f scla:%f scl_pj:%f scl_cur:%f\n", t, scla, scl_pj, scl_cur);
                            // bottom side
                            scl_pj = (g_pj_curpos[i][j].x == g_pj_curpos[h0][j].x)
                                             ? 0
                                             : (g_pj_curpos[h][j].x - g_pj_curpos[h0][j].x) /
                                                       (g_pj_curpos[i][j].x - g_pj_curpos[h0][j].x);
                            scl_cur = (PM_WPCUR[i][j].x == PM_WPCUR[h0][j].x)
                                              ? 0
                                              : (PM_WPCUR[h][j].x - PM_WPCUR[h0][j].x) /
                                                        (PM_WPCUR[i][j].x - PM_WPCUR[h0][j].x);
                            sclb[1] = (scl_pj == 0) ? 0 : scl_cur / scl_pj;
                            printf("bottom --> t:%f scla:%f scl_pj:%f scl_cur:%f sclb[0]:%f sclb[1]:%f\n", t, scla,
                                   scl_pj, scl_cur, sclb[0], sclb[1]);
                            // Calculate the internal cursor : x
                            t = (g_pj_curpos[h][j].y == g_pj_curpos[h][v0].y)
                                        ? 0
                                        : (g_pj_curpos[h][v].y - g_pj_curpos[h][v0].y) /
                                                  (g_pj_curpos[h][j].y - g_pj_curpos[h][v0].y);
                            PM_WPCUR[h][v].x = PM_WPCUR[h0][v].x + (PM_WPCUR[i][v].x - PM_WPCUR[h0][v].x) * scla *
                                                                           (sclb[0] * (1 - t) + sclb[1] * t);
                            printf("internal x --> t:%f scla:%f scl_pj:%f scl_cur:%f PM_WPCUR[%d][%d].x = [%f]\n", t,
                                   scla, scl_pj, scl_cur, h, v, PM_WPCUR[h][v].x);
                            // y
                            scla = (g_pj_curpos[h][v].y - g_pj_curpos[h][v0].y) /
                                   (g_pj_curpos[h][j].y - g_pj_curpos[h][v0].y);
                            // left side
                            scl_pj = (g_pj_curpos[h0][j].y == g_pj_curpos[h0][v0].y)
                                             ? 0
                                             : (g_pj_curpos[h0][v].y - g_pj_curpos[h0][v0].y) /
                                                       (g_pj_curpos[h0][j].y - g_pj_curpos[h0][v0].y);
                            scl_cur = (PM_WPCUR[h0][j].y == PM_WPCUR[h0][v0].y)
                                              ? 0
                                              : (PM_WPCUR[h0][v].y - PM_WPCUR[h0][v0].y) /
                                                        (PM_WPCUR[h0][j].y - PM_WPCUR[h0][v0].y);
                            sclb[0] = (scl_pj == 0) ? 0 : scl_cur / scl_pj;
                            // right side
                            scl_pj = (g_pj_curpos[i][j].y == g_pj_curpos[i][v0].y)
                                             ? 0
                                             : (g_pj_curpos[i][v].y - g_pj_curpos[i][v0].y) /
                                                       (g_pj_curpos[i][j].y - g_pj_curpos[i][v0].y);
                            scl_cur = (PM_WPCUR[i][j].y == PM_WPCUR[i][v0].y)
                                              ? 0
                                              : (PM_WPCUR[i][v].y - PM_WPCUR[i][v0].y) /
                                                        (PM_WPCUR[i][j].y - PM_WPCUR[i][v0].y);
                            sclb[1] = (scl_pj == 0) ? 0 : scl_cur / scl_pj;
                            // Calculate the internal cursor : y
                            t = (g_pj_curpos[h][v].x - g_pj_curpos[h0][v].x) /
                                (g_pj_curpos[i][v].x - g_pj_curpos[h0][v].x);
                            PM_WPCUR[h][v].y = PM_WPCUR[h][v0].y + (PM_WPCUR[h][j].y - PM_WPCUR[h][v0].y) * scla *
                                                                           (sclb[0] * (1 - t) + sclb[1] * t);
                            printf("internal y --> t:%f scla:%f scl_pj:%f scl_cur:%f PM_WPCUR[%d][%d].y = [%f]\n", t,
                                   scla, scl_pj, scl_cur, h, v, PM_WPCUR[h][v].y);
                        }
                        h0 = i; // new left side
                    }
                }
            }
            v0 = j; // new top side
        }
    }
    COOR_T_LOG("PM_WPCUR", PM_WPCUR, 5, 3);
    return 0;
}

int CalcWpTable(coord_f_t cur_pos[][DEF_NUM_CUR_MAX_V]) {
    coord_f_t temp_pt[DEF_NUM_CUR_MAX];
    spline_coef_t temp_spl_cf[DEF_NUM_CUR_MAX + 1];

    float x, y;
    int i, j;
    float x0, y0;
    int area;

    float diffy_y_sum, divn;
    // Limitation
    float tblx_min = -(float)PS_WPSPACE * 12;
    float tblx_max = PS_CUR_DEF_IX[PS_NUM_CUR_MAX_H - 1] + (float)PS_WPSPACE * 12;
    float tbly_min = -(float)PS_WPSPACE * 12;
    float tbly_max = PS_CUR_DEF_IY[PS_NUM_CUR_MAX_V - 1] + (float)PS_WPSPACE * 12;

    int wptbl_x_prev_line[DEF_HW_MAX_GRD];
    int wptbl_y_prev_line[DEF_HW_MAX_GRD];
    int wptbl_x_prev_pix;
    int wptbl_y_prev_pix;
    int tbl_tlx, tbl_tly;
    int tbl_trx, tbl_try;
    int tbl_blx, tbl_bly;
    int tbl_brx, tbl_bry;

    // Warp table access
    int wdt_x, wdt_y;
    int adsft;
    int x2k_ad_jmp;
    int x2k_grd_jmp;
    int x2k_ad_ysft;

    char err = WARPING_NO_ERROR;

    // spline
    // horizontal line
    for (j = 0; j < PS_NUM_CUR_MAX_V; j++) {
        for (i = 0; i < PS_NUM_CUR_MAX_H; i++) {
            temp_pt[i].x = cur_pos[i][j].x;
            temp_pt[i].y = cur_pos[i][j].y;
        }
        //		CalcSplineCoef(temp_pt, PS_NUM_CUR_MAX_H, temp_spl_cf);
        if (0 != CalcSplineCoef(temp_pt, PS_NUM_CUR_MAX_H, temp_spl_cf)) {
            err = WARPING_ERROR_GRID_INTERVAL;
            return err;
        }

        for (i = 0; i < (PS_NUM_CUR_MAX_H + 1); i++) {
            g_hline[i][j] = temp_spl_cf[i];
            // SPLINE_T_LOG("g_hline[i][j]", g_hline[i][j]);
        }
    }
    // vertical line
    for (j = 0; j < PS_NUM_CUR_MAX_H; j++) {
        for (i = 0; i < PS_NUM_CUR_MAX_V; i++) {
            temp_pt[i].x = cur_pos[j][i].y;
            temp_pt[i].y = cur_pos[j][i].x;
        }
        //		CalcSplineCoef(temp_pt, PS_NUM_CUR_MAX_V, temp_spl_cf);
        if (0 != CalcSplineCoef(temp_pt, PS_NUM_CUR_MAX_V, temp_spl_cf)) {
            err = WARPING_ERROR_GRID_INTERVAL;
            return err;
        }

        for (i = 0; i < (PS_NUM_CUR_MAX_V + 1); i++) {
            g_vline[j][i] = temp_spl_cf[i];
            // SPLINE_T_LOG("g_vline[j][i]", g_vline[j][i]);
        }
    }
    // SPLINE_T_LOG("temp_spl_cf0", temp_spl_cf[0]);
    // SPLINE_T_LOG("temp_spl_cf1", temp_spl_cf[1]);
    // SPLINE_T_LOG("temp_spl_cf2", temp_spl_cf[2]);
    // SPLINE_T_LOG("temp_spl_cf3", temp_spl_cf[3]);
    // SPLINE_T_LOG("temp_spl_cf4", temp_spl_cf[4]);
    // SPLINE_T_LOG("temp_spl_cf5", temp_spl_cf[5]);
    // table
    for (i = 0; i <= PS_WP_HW_GRD; i++) {
        x0 = (float)(i << PS_WPSPACE_BIT);

        for (j = 0; j < PS_NUM_CUR_MAX_V; j++) {
            area = 0;
            while (area < PS_NUM_CUR_MAX_H) {
                if (x0 < cur_pos[area][j].x) {
                    break;
                }
                area = area + 1;
            }

            if (area == 0) {
                // x0：步长 g_hline：样条系数 cur_pos：
                g_hor_line_y[i][j] = CalcSpline(g_hline[area][j], x0, cur_pos[area][j].x);
            } else {
                g_hor_line_y[i][j] = CalcSpline(g_hline[area][j], x0, cur_pos[area - 1][j].x);
            }
            // printf("area:%d i:%d j:%d x0:%f cur_pos[%d][%d].x:%f g_hor_line_y[%d][%d]:%f\n", area, i, j, x0,
            //        area == 0 ? area : area - 1, j, cur_pos[area == 0 ? area : area - 1][j].x, i, j, g_hor_line_y[i][j]);
        }
        // vertical line
        for (j = 0; j < PS_NUM_CUR_MAX_V; j++) {
            temp_pt[j].x = g_hor_line_y[i][j];
            temp_pt[j].y = (float)PS_CUR_DEF_IY[j] - g_hor_line_y[i][j];
            // printf("temp_pt[%d]:[%f, %f]\n",j,temp_pt[j].x, temp_pt[j].y);
        }
        //		CalcSplineCoef(temp_pt, PS_NUM_CUR_MAX_V, g_vline_mv[i]);
        if (0 != CalcSplineCoef(temp_pt, PS_NUM_CUR_MAX_V, g_vline_mv[i])) {
            err = WARPING_ERROR_GRID_INTERVAL;
            return err;
        }
    }

    // Set warp table access enable
    //    WpTableAccOpen(&adsft, &x2k_ad_jmp, &x2k_grd_jmp, &x2k_ad_ysft);

    wptbl_x_prev_pix = 0;
    wptbl_y_prev_pix = 0;
    for (j = 0; j <= PS_WP_VW_GRD; j++) {
        y0 = (float)(j << PS_WPSPACE_BIT);

        for (i = 0; i < PS_NUM_CUR_MAX_H; i++) {
            area = 0;
            while (area < PS_NUM_CUR_MAX_V) {
                if (y0 < cur_pos[i][area].y) {
                    break;
                }
                area = area + 1;
            }
            if (area == 0) {
                g_ver_line_x[i] = CalcSpline(g_vline[i][area], y0, cur_pos[i][area].y);
            } else {
                g_ver_line_x[i] = CalcSpline(g_vline[i][area], y0, cur_pos[i][area - 1].y);
            }
            // printf("i:%d j:%d area:%d y0:%f  g_ver_line_x[%d]:%f cur_pos[%d][%d].y:%f\n", i, j, area, y0, i,
            //        g_ver_line_x[i], i, area == 0 ? area : area - 1, cur_pos[i][area == 0 ? area : area - 1].y);
        }

        // horizontal line
        for (i = 0; i < PS_NUM_CUR_MAX_H; i++) {
            temp_pt[i].x = g_ver_line_x[i];
            temp_pt[i].y = (float)PS_CUR_DEF_IX[i] - g_ver_line_x[i];
            printf("temp_pt[%d]:[%f, %f]\n", i, temp_pt[i].x, temp_pt[i].y);
        }
        //		CalcSplineCoef(temp_pt, PS_NUM_CUR_MAX_H, g_hline_mv);
        if (0 != CalcSplineCoef(temp_pt, PS_NUM_CUR_MAX_H, g_hline_mv)) {
            err = WARPING_ERROR_GRID_INTERVAL;
            return err;
        }

        diffy_y_sum = 0;
        divn = 0;

        for (i = 0; i <= PS_WP_HW_GRD; i++) {
            x0 = (float)(i << PS_WPSPACE_BIT);
            // x
            area = 0;
            while (area < PS_NUM_CUR_MAX_H) {
                if (x0 < g_ver_line_x[area]) {
                    break;
                }
                area = area + 1;
            }

            if (area == 0) {
                x = CalcSpline(g_hline_mv[area], x0, g_ver_line_x[area]);
            } else {
                x = CalcSpline(g_hline_mv[area], x0, g_ver_line_x[area - 1]);
            }
            // printf("x:%f x0:%f area:%d g_ver_line_x[%d]:%f\n", x, x0, area, area, g_ver_line_x[area]);
            x = x + (float)(i << PS_WPSPACE_BIT);
            x = (x > tblx_max) ? tblx_max : (x < tblx_min) ? tblx_min : x;
            wdt_x = (int)(x * 8 + 0.5);
            // printf("x:%f wdt_x:%d\n", x, wdt_x);
            // y
            area = 0;
            while (area < PS_NUM_CUR_MAX_V) {
                if (y0 < g_hor_line_y[i][area]) {
                    break;
                }
                area = area + 1;
            }

            if (area == 0) {
                y = CalcSpline(g_vline_mv[i][area], y0, g_hor_line_y[i][area]);
            } else {
                y = CalcSpline(g_vline_mv[i][area], y0, g_hor_line_y[i][area - 1]);
            }
            y = y + (float)(j << PS_WPSPACE_BIT);
            y = (y > tbly_max) ? tbly_max : (y < tbly_min) ? tbly_min : y;
            wdt_y = (int)(y * 8 + 0.5);
            //            printf("wdt[%d, %d]\n", wdt_x, wdt_y);
            // Warp error
            // Check Limit
            if (j == 0) {
                tbl_tlx = (i == 0) ? wdt_x : wptbl_x_prev_pix;
                tbl_tly = (i == 0) ? wdt_y : wptbl_y_prev_pix;
                tbl_trx = wdt_x;
                tbl_try = wdt_y;
            } else {
                tbl_tlx = (i == 0) ? wptbl_x_prev_line[0] : wptbl_x_prev_line[i - 1];
                tbl_tly = (i == 0) ? wptbl_y_prev_line[0] : wptbl_y_prev_line[i - 1];
                tbl_trx = wptbl_x_prev_line[i];
                tbl_try = wptbl_y_prev_line[i];
            }
            tbl_blx = (i == 0) ? wdt_x : wptbl_x_prev_pix;
            tbl_bly = (i == 0) ? wdt_y : wptbl_y_prev_pix;
            tbl_brx = wdt_x;
            tbl_bry = wdt_y;

            err = CheckWpLimitA(tbl_tlx, tbl_tly, tbl_trx, tbl_try, tbl_blx, tbl_bly, tbl_brx,
                                tbl_bry, &i, &j, &diffy_y_sum, &divn);
            printf("diffy_y_sum:%f divn:%f\n", diffy_y_sum, divn);
            if (err != WARPING_NO_ERROR) {
                //                write_C382_force();
                //                WpTableAccClose(0);
                return err;
            }

            // Write warp table
            //            WpTableWriteData(i, j, &wdt_x, &wdt_y, adsft, x2k_ad_jmp, x2k_grd_jmp,
            //            x2k_ad_ysft);

            if (i > 0) {
                wptbl_x_prev_line[i - 1] = wptbl_x_prev_pix;
                wptbl_y_prev_line[i - 1] = wptbl_y_prev_pix;
            }
            wptbl_x_prev_pix = wdt_x;
            wptbl_y_prev_pix = wdt_y;
        }
        wptbl_x_prev_line[PS_WP_HW_GRD] = wptbl_x_prev_pix; // i - 1
        wptbl_y_prev_line[PS_WP_HW_GRD] = wptbl_y_prev_pix; // i - 1

        // Check Limit
        err = CheckWpLimitB(&diffy_y_sum, &divn);
        if (err != WARPING_NO_ERROR) {
            //            write_C382_force();
            //            WpTableAccClose(0);
            return err;
        }
    }
    //    write_C382_force();
    //    WpTableAccClose(1);

    return err;
}

U8 getRefMatrixCoor(U8 li, U8 col, coord_t *point) {
    const int curmd[DEF_NUM_WPMODE][2] = DEF_CURMD;

    if (PM_WPMODE >= DEF_NUM_WPMODE) return false;
    if (li >= curmd[PM_WPMODE][0]) return false;
    if (col >= curmd[PM_WPMODE][1]) return false;

    if (NULL == point) return false;
    // DEF_NUM_CUR_MAX_H_M1_ -> reference matrix line number
    // DEF_NUM_CUR_MAX_V_M1_ -> reference matrix column number
    point->y = col * DEF_NUM_CUR_MAX_V_M1 / (curmd[PM_WPMODE][1] - 1);
    point->x = li * DEF_NUM_CUR_MAX_H_M1 / (curmd[PM_WPMODE][0] - 1);
    if (point->x >= DEF_NUM_CUR_MAX_H) return false;
    if (point->y >= DEF_NUM_CUR_MAX_V) return false;

    // XGIMI_DBG("ref.x = %d\r\n", point->x);
    // XGIMI_DBG("ref.y = %d\r\n", point->y);
    return true;
}

void updateWpMatrix(PointCoordinate *pOfst) {
    U8 i = 0;
    U8 j = 0;
    U16 hres = 3840;
    U16 vres = 2160;
    U16 hspace = 0;
    U16 vspace = 0;
    coord_t ref = {0, 0};

    if (NULL == pOfst) return;
    //    getCurrentResolution(&hres, &vres);
    hspace = hres / (m_ipcIns.mode_li - 1);
    vspace = vres / (m_ipcIns.mode_col - 1);
    for (i = 0; i < m_ipcIns.mode_col; i++) {    // column
        for (j = 0; j < m_ipcIns.mode_li; j++) { // line
            if (false == getRefMatrixCoor(j, i,
                                          &ref)) // get the ipc382 internal two dimentional matrix index
                continue;
            // PM_WPCUR[x][y] <-> PointCoordinate[m][n]
            // x <--> n
            // y <--> m
            // 2159 -> 2160 | 3839 -> 3840
            PM_WPCUR[ref.x][ref.y].x = (hspace * j > 0 && (pOfst[i * m_ipcIns.mode_li + j].S16X == hspace * j - 1))
                                               ? hspace * j
                                               : pOfst[i * m_ipcIns.mode_li + j].S16X;
            PM_WPCUR[ref.x][ref.y].y = (vspace * i > 0 && (pOfst[i * m_ipcIns.mode_li + j].S16Y == vspace * i - 1))
                                               ? vspace * i
                                               : pOfst[i * m_ipcIns.mode_li + j].S16Y;
        }
    }
    //     COOR_T_LOG("PM_WPCUR", PM_WPCUR, 5, 3);
}

void InitParamWp(void) {
    int i, j;
    // System parameter
    PS_WP_HW = DEF_OACTHW;
    PS_WP_VW = DEF_OACTVW;
    PS_WP_IHW = DEF_IACTHW;
    PS_WP_IVW = DEF_IACTVW;

    if ((PS_WP_HW <= 2048) && (PS_WP_VW <= 1200)) {
        // 16dot mode
        PS_WPSPACE = 16;
        PS_WPSPACE_BIT = 4;
    } else {
        // 32dot mode
        PS_WPSPACE = 32;
        PS_WPSPACE_BIT = 5;
    }

    PS_WP_HW_GRD = (PS_WP_HW + PS_WPSPACE - 1) / PS_WPSPACE; // = roundup(PS_WP_HW / PS_WPSPACE)
    PS_WP_VW_GRD = (PS_WP_VW + PS_WPSPACE - 1) / PS_WPSPACE; // = roundup(PS_WP_VW / PS_WPSPACE)

    //	PS_WPLIMVSH_L = ((float)PS_WPSPACE / (1.0 / 3.0) * 8.0);
    PS_WPLIMVSH_A = ((float)PS_WPSPACE / DEF_WPLIM_VSH_AVE * 8.0); // 4K:426.66 FHD：213.3336
    PS_WPLIMVSH_L = PS_WPLIMVSH_A;                                 // C382
    PS_WPLIMHSH = ((float)PS_WPSPACE / (1.0 / 8.0) * 8.0);         // 4K:2048 FHD：1024

    // Warping parameters
    for (j = 0; j < PS_NUM_CUR_MAX_V; j++) {
        PS_CUR_DEF_OY[j] = (float)(PS_WP_VW * j) / (float)(PS_NUM_CUR_MAX_V - 1);
        PS_CUR_DEF_IY[j] = (float)(PS_WP_IVW * j) / (float)(PS_NUM_CUR_MAX_V - 1);

        for (i = 0; i < PS_NUM_CUR_MAX_H; i++) {
            if (j == 0) {
                PS_CUR_DEF_OX[i] = (float)(PS_WP_HW * i) / (float)(PS_NUM_CUR_MAX_H - 1);
                PS_CUR_DEF_IX[i] = (float)(PS_WP_IHW * i) / (float)(PS_NUM_CUR_MAX_H - 1);
            }

            // Initialize the warping cursor position
            PM_WPCUR[i][j].x = PS_CUR_DEF_OX[i];
            PM_WPCUR[i][j].y = PS_CUR_DEF_OY[j];
        }
    }

    //===== Menu parameters =====//
    // Warping
    PM_WPMODE = 1;

    // H
    GV_NUM_WPCUR_H = 0;
    for (int h = 0; h < PS_NUM_CUR_MAX_H; h++) {
        GV_NUM_WPCUR_H = GV_NUM_WPCUR_H + PS_WPCUR_H_EN[PM_WPMODE][h];
    }

    // V
    GV_NUM_WPCUR_V = 0;
    for (int v = 0; v < PS_NUM_CUR_MAX_V; v++) {
        GV_NUM_WPCUR_V = GV_NUM_WPCUR_V + PS_WPCUR_V_EN[PM_WPMODE][v];
    }
}

int main() {
    constexpr auto warpErr = magic_enum::enum_names<enm_warping_error_tag>();
    InitParamWp();
    m_ipcIns.mode_li = 3;
    m_ipcIns.mode_col = 3;

    PointCoordinate point[3][3];
    memset(&point[0][0], 0, sizeof(point));
    point[0][0].S16X = 0;
    point[0][0].S16Y = 0;
    point[0][1].S16X = (C382_PANEL_H / 2) - 1;
    point[0][1].S16Y = 0;
    point[0][2].S16X = C382_PANEL_H - 1;
    point[0][2].S16Y = 0x00;

    point[1][0].S16X = 2730;
    point[1][0].S16Y = (C382_PANEL_V / 2) - 1;
    point[1][1].S16X = (C382_PANEL_H / 2) - 1;
    point[1][1].S16Y = (C382_PANEL_V / 2) - 1;
    point[1][2].S16X = C382_PANEL_H - 1;
    point[1][2].S16Y = (C382_PANEL_V / 2) - 1;

    point[2][0].S16X = 0x00;
    point[2][0].S16Y = C382_PANEL_V - 1;
    point[2][1].S16X = (C382_PANEL_H / 2) - 1;
    point[2][1].S16Y = C382_PANEL_V - 1;
    point[2][2].S16X = C382_PANEL_H - 1;
    point[2][2].S16Y = C382_PANEL_V - 1;

    updateWpMatrix((PointCoordinate *)point);
    //    COOR_T_LOG("PM_WPCUR", PM_WPCUR, 5, 3);
    char err;
    printf("GV_NUM_WPCUR_V:%d\n", GV_NUM_WPCUR_V);
    if (0 != CalcWpCur()) {
        err = WARPING_ERROR_GRID_INTERVAL;
    } else {
            //    COOR_T_LOG("PM_WPCUR", PM_WPCUR, 5, 3);
        err = CalcWpTable(PM_WPCUR);
    }
    COOR_T_LOG("PM_WPCUR", PM_WPCUR, 5, 3);
    // printf("\r\nerr:%d\n", err);
    std::cout << "err: " << warpErr[err] << std::endl;
    return 0;
}