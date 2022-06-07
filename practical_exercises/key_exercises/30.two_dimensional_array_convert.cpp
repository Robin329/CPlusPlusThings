#include <iostream>

#include "base.h"
#include "opencv2/calib3d.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define COLOR_UNIFORMITY_LINE 9
#define COLOR_UNIFORMITY_COLUMN 9
#define COLOR_GAIN_COEF_MIN_VAL 500
#define COLOR_GAIN_COEF_MAX_VAL 1500

typedef struct _color_gain_coef_t {
    U16 r[3]; // 0: low 1:middle 2:high, range is [500, 1500]
    U16 g[3]; // 0: low 1:middle 2:high
    U16 b[3]; // 0: low 1:middle 2:high
} __attribute__((packed)) color_gain_coef_t;

typedef struct _color_uniformity_t {
    S32 reserve; // reserved for future use
    color_gain_coef_t gain[COLOR_UNIFORMITY_LINE][COLOR_UNIFORMITY_COLUMN];
} __attribute__((packed)) color_uniformity_t;

typedef struct _GAIN_COEF_St {
    float r[3]; // [0]Low [1]Middle [2]High
    float g[3]; // [0]Low [1]Middle [2]High
    float b[3]; // [0]Low [1]Middle [2]High
} GAIN_COEF;

typedef enum {
    EN_PUT_POSITIVE_FRONT = 0,
    EN_PUT_NAGATIVE_BACK,
    EN_PUT_POSITIVE_BACK,
    EN_PUT_NAGATIVE_FRONT,
    EN_PUT_MAX = EN_PUT_NAGATIVE_FRONT,
} EN_PROJECTOR_PUT_MODE;

GAIN_COEF PM_GAIN[COLOR_UNIFORMITY_LINE][COLOR_UNIFORMITY_COLUMN];
GAIN_COEF PM_GAIN_FLIP[COLOR_UNIFORMITY_LINE][COLOR_UNIFORMITY_COLUMN];

bool setUniformFlip(GAIN_COEF srcGain[][COLOR_UNIFORMITY_COLUMN], EN_PROJECTOR_PUT_MODE en_mode);

void initUniformityGain(color_uniformity_t *color) {
    U16 *pgain = NULL;
    U16 len = 0;

    if (NULL == color) {
        return;
    }

    for (int i = 0; i < COLOR_UNIFORMITY_LINE; i++) {
        for (int j = 0; j < COLOR_UNIFORMITY_COLUMN; j++) {
            pgain = (U16 *)&color->gain[i][j];
            len = sizeof(color->gain[0][0]) / sizeof(U16);
            for (int k = 0; k < len; k++) {
                *pgain++ = 1000;
            }
        }
    }
}
int setColorGainCoef(color_uniformity_t color_unif) {
    U16 *pgain_int = NULL;
    float *pgain_float = NULL;

    for (int i = 0; i < COLOR_UNIFORMITY_LINE; i++) {
        for (int j = 0; j < COLOR_UNIFORMITY_COLUMN; j++) {
            pgain_int = (U16 *)&color_unif.gain[i][j];
            pgain_float = (float *)&PM_GAIN[i][j];

            for (int k = 0; k < 9; k++) { // r[3], g[3], b[3]
                // cout << " *pgain_int: " << *pgain_int << endl;
                if ((*pgain_int < COLOR_GAIN_COEF_MIN_VAL) ||
                    (*pgain_int > COLOR_GAIN_COEF_MAX_VAL)) {
                    return FALSE;
                }
                *pgain_float = *pgain_int / 1000.0;
                pgain_int++;
                pgain_float++;
            }
        }
    }
    // memcpy(PM_GAIN_FLIP, PM_GAIN, sizeof(PM_GAIN_FLIP));
    return TRUE;
}

void printGain(GAIN_COEF gain[][9], const char *name) {
    for (int i = 0; i < COLOR_UNIFORMITY_LINE; i++) {
        cout << name << "[" << i << "]:"
             << "\r\n"
             << std::setprecision(4) << setiosflags(ios_base::fixed);
        for (int j = 0; j < COLOR_UNIFORMITY_COLUMN; j++) {
            cout << "r=(" << gain[i][j].r[0] << "," << gain[i][j].r[1] << "," << gain[i][j].r[2]
                 << "), ";
            cout << "g=(" << gain[i][j].g[0] << "," << gain[i][j].g[1] << "," << gain[i][j].g[2]
                 << "), ";
            cout << "b=(" << gain[i][j].b[0] << "," << gain[i][j].b[1] << "," << gain[i][j].b[2]
                 << ")\r\n";
            cout << "\n";
        }
        cout << "\n";
    }
    cout << "--------------------------------------------------------------\n";
}

bool setUniformFlip(GAIN_COEF srcGain[][COLOR_UNIFORMITY_COLUMN], EN_PROJECTOR_PUT_MODE en_mode) {
    if ((en_mode < EN_PUT_POSITIVE_FRONT) || (en_mode > EN_PUT_MAX)) {
        printf("en_mode(%d) ERR\n", (U8)en_mode);
        return FALSE;
    }
    // printGain(srcGain, "srcGain");
    GAIN_COEF temp;
    // GAIN_COEF tempGain[COLOR_UNIFORMITY_LINE][COLOR_UNIFORMITY_COLUMN];
    // cout << "sizeof srcGain:" << (sizeof(tempGain) / sizeof(GAIN_COEF)) << endl;
    memcpy(&PM_GAIN_FLIP[0][0], &srcGain[0][0], sizeof(PM_GAIN_FLIP));
    srcGain[0][0].r[0] = 0.1;
    switch (en_mode) {
        // HFLIP
        case EN_PUT_POSITIVE_BACK: {
            memset(&temp, 0, sizeof(temp));
            for (U8 i = 0; i < COLOR_UNIFORMITY_LINE; i++) {
                for (U8 j = 0; j < COLOR_UNIFORMITY_COLUMN / 2; j++) {
                    memcpy(&temp, &PM_GAIN_FLIP[i][j], sizeof(temp));
                    memcpy(&PM_GAIN_FLIP[i][j], &PM_GAIN_FLIP[i][COLOR_UNIFORMITY_COLUMN - 1 - j],
                           sizeof(GAIN_COEF));
                    // cout << "temp:" << temp.g[0] << endl;
                    // cout << "temp:" << temp.g[1] << endl;
                    // cout << "temp:" << temp.g[2] << endl;
                    memcpy(&PM_GAIN_FLIP[i][COLOR_UNIFORMITY_COLUMN - 1 - j], &temp,
                           sizeof(GAIN_COEF));
                }
            }
        } break;
        // VFlip
        case EN_PUT_NAGATIVE_BACK: {
            memset(&temp, 0, sizeof(temp));
            for (U8 i = 0; i < COLOR_UNIFORMITY_LINE / 2; i++) {
                for (U8 j = 0; j < COLOR_UNIFORMITY_COLUMN; j++) {
                    memcpy(&temp, &PM_GAIN_FLIP[i][j], sizeof(temp));
                    memcpy(&PM_GAIN_FLIP[i][j], &PM_GAIN_FLIP[COLOR_UNIFORMITY_LINE - 1 - i][j],
                           sizeof(GAIN_COEF));
                    // cout << "temp:" << temp.g[0] << endl;
                    // cout << "temp:" << temp.g[1] << endl;
                    // cout << "temp:" << temp.g[2] << endl;
                    memcpy(&PM_GAIN_FLIP[COLOR_UNIFORMITY_LINE - 1 - i][j], &temp,
                           sizeof(GAIN_COEF));
                }
            }
        } break;
        // HFLIP + VFLIP
        case EN_PUT_NAGATIVE_FRONT: {
            GAIN_COEF tmp[COLOR_UNIFORMITY_LINE][COLOR_UNIFORMITY_COLUMN];
            memcpy(&tmp, &PM_GAIN_FLIP[0][0], sizeof(tmp));
            for (U8 i = 0; i < COLOR_UNIFORMITY_LINE; i++) {
                for (U8 j = 0; j < COLOR_UNIFORMITY_COLUMN; j++) {
                    memcpy(&PM_GAIN_FLIP[i][j],
                           &tmp[COLOR_UNIFORMITY_LINE - 1 - i][COLOR_UNIFORMITY_COLUMN - 1 - j],
                           sizeof(GAIN_COEF));
                    // cout << "temp:" << PM_GAIN_FLIP[COLOR_UNIFORMITY_LINE - 1 -
                    // i][COLOR_UNIFORMITY_COLUMN - 1 - j].g[0] << endl; cout << "temp:" <<
                    // PM_GAIN_FLIP[COLOR_UNIFORMITY_LINE - 1 - i][COLOR_UNIFORMITY_COLUMN - 1 -
                    // j].g[1] << endl; cout << "temp:" << PM_GAIN_FLIP[COLOR_UNIFORMITY_LINE - 1 -
                    // i][COLOR_UNIFORMITY_COLUMN - 1 - j].g[2] << endl;
                }
            }
        } break;
        default:
            break;
    }
    //    printGain(PM_GAIN_FLIP, "PM_GAIN_FLIP");
    return TRUE;
}

void setHflip(void) {
    GAIN_COEF temp;
    memset(&temp, 0, sizeof(temp));
    for (U8 i = 0; i < COLOR_UNIFORMITY_LINE; i++) {
        for (U8 j = 0; j < COLOR_UNIFORMITY_COLUMN / 2; j++) {
            memcpy(&temp, &PM_GAIN_FLIP[i][j], sizeof(temp));
            memcpy(&PM_GAIN_FLIP[i][j], &PM_GAIN_FLIP[i][COLOR_UNIFORMITY_COLUMN - 1 - j],
                   sizeof(GAIN_COEF));
            // cout << "temp:" << temp.g[0] << endl;
            // cout << "temp:" << temp.g[1] << endl;
            // cout << "temp:" << temp.g[2] << endl;
            memcpy(&PM_GAIN_FLIP[i][COLOR_UNIFORMITY_COLUMN - 1 - j], &temp, sizeof(temp));
        }
    }
}

void setVflip(void) {
    GAIN_COEF temp;
    memset(&temp, 0, sizeof(temp));
    for (U8 i = 0; i < COLOR_UNIFORMITY_LINE / 2; i++) {
        for (U8 j = 0; j < COLOR_UNIFORMITY_COLUMN; j++) {
            memcpy(&temp, &PM_GAIN_FLIP[i][j], sizeof(temp));
            memcpy(&PM_GAIN_FLIP[i][j], &PM_GAIN_FLIP[COLOR_UNIFORMITY_COLUMN - 1 - i][j],
                   sizeof(GAIN_COEF));
            // cout << "temp:" << temp.g[0] << endl;
            // cout << "temp:" << temp.g[1] << endl;
            // cout << "temp:" << temp.g[2] << endl;
            memcpy(&PM_GAIN_FLIP[COLOR_UNIFORMITY_COLUMN - 1 - i][j], &temp, sizeof(temp));
        }
    }
}

void setRotate(void) {
    GAIN_COEF temp;
    memset(&temp, 0, sizeof(temp));
    for (U8 i = 0; i < COLOR_UNIFORMITY_LINE; i++) {
        for (U8 j = 0; j < COLOR_UNIFORMITY_COLUMN; j++) {
            memcpy(&temp, &PM_GAIN_FLIP[i][j], sizeof(temp));
            memcpy(&PM_GAIN_FLIP[i][j],
                   &PM_GAIN_FLIP[COLOR_UNIFORMITY_COLUMN - 1 - i][COLOR_UNIFORMITY_COLUMN - 1 - j],
                   sizeof(temp));
            // cout << "temp:" << temp.g[0] << endl;
            // cout << "temp:" << temp.g[1] << endl;
            // cout << "temp:" << temp.g[2] << endl;
            memcpy(&PM_GAIN_FLIP[COLOR_UNIFORMITY_COLUMN - 1 - i][COLOR_UNIFORMITY_COLUMN - 1 - j],
                   &temp, sizeof(temp));
        }
    }
}
int main() {
    color_uniformity_t color_unif;
    memset(&color_unif, 0, sizeof(color_uniformity_t));
    initUniformityGain(&color_unif);
    cout << "sizeof(color_unif.gain):" << (sizeof(color_unif.gain) / sizeof(color_gain_coef_t))
         << endl;
    // memset(&color_unif.gain, 1, (sizeof(color_unif.gain) / sizeof(color_gain_coef_t)) * 9);

    if (!setColorGainCoef(color_unif)) {
        cout << "set color gain coef FAILED\n";
        return -1;
    }

    // [0][0] -> 0.5
    // memset(&PM_GAIN[0][0].r[0], 0.5, sizeof(PM_GAIN[0][0].r));
    // memset(&PM_GAIN[0][0].g[0], 0.5, sizeof(PM_GAIN[0][0].g));
    // memset(&PM_GAIN[0][0].b[0], 0.5, sizeof(PM_GAIN[0][0].b));
    // PM_GAIN[0][0].r[0] = 0.5;
    PM_GAIN[0][0].g[0] = 0.5;
    PM_GAIN[0][0].g[1] = 0.5;
    PM_GAIN[0][0].g[2] = 0.5;
    PM_GAIN[0][0].b[0] = 0.5;

    PM_GAIN[0][1].g[0] = 0.5;
    PM_GAIN[0][2].g[1] = 0.5;
    PM_GAIN[0][3].g[2] = 0.5;

    PM_GAIN[8][0].g[0] = 0.5;
    PM_GAIN[8][0].g[1] = 0.5;
    PM_GAIN[8][0].g[2] = 0.5;
    
    PM_GAIN[8][1].g[0] = 0.5;
    PM_GAIN[8][1].g[1] = 0.5;
    PM_GAIN[8][1].g[2] = 0.5;
    printGain(PM_GAIN, "PM_GAIN");
    // setVflip();
    // setHflip();
    // setRotate();
    // setUniformFlip(PM_GAIN, EN_PUT_POSITIVE_BACK);
    // setUniformFlip(PM_GAIN, EN_PUT_NAGATIVE_BACK);
    setUniformFlip(PM_GAIN, EN_PUT_NAGATIVE_FRONT);
    printGain(PM_GAIN_FLIP, "PM_GAIN_FLIP");
    cout << "sizeof float:" << sizeof(float) << endl;
    cout << "sizeof:" << sizeof(PM_GAIN_FLIP) << endl;
    std::cout << "This tutorial code needs the xfeatures2d contrib module to be run." << std::endl;
    return 0;
}
