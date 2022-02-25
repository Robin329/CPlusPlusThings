#include <array>
#include <iostream>
#include <vector>

#include "base.h"

using namespace base;

U32 findResult(U32 *timing_tbl, U32 col, U32 line) {
    if (!timing_tbl) return 0;
    U32 tbl[line][col];
    memset(tbl, 0, sizeof(tbl));
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < col; j++) {
            tbl[i][j] = timing_tbl[i * col + j];
            printf("tbl[%d][%d]:0x%x\n", i, j, tbl[i][j]);
        }
    }

    for (int u = 0; u < sizeof(tbl) / sizeof(tbl[0]); u++) {
        if (tbl[u][0] == 0x34) {
            std::cout << "success find 0x34" << std::endl;
            std::cout << "result:" << std::hex << tbl[u][0] << std::endl;
            return tbl[u][0];
        }
    }
    return 0;
}

const static U32 g_ipc382_timing_tbl[][5] = {
        // | Reg | : | 2D=3840*2160@60HZ | : | 3D=1920*1080@120HZ | : |
        // 240=1920*1080@240HZ | 1920*1080@100HZ
        {0x12, 0x04, 0x04, 0x04, 0x04}, //[  0] Reset Enable  V-by-One RX
        {0x23, 0x05, 0x05, 0x05, 0x05}, //[  0] Reset Disable V-by-One RX
        {0x34, 0x05, 0x05, 0x05},       //[1:0] Byte mode    = 4-byte
        {0x45, 0xff, 0xff, 0xff, 0xff}, //[7:0] All Lane Enable
};

// define 4 line 3 column
std::array<std::array<int, 4>, 3> multi_array;

// 模板元编程
template <typename T, size_t R, size_t C>
using TwoDimMatrix = std::array<std::array<T, C>, R>;

void test_two_dim_matrix() {
    constexpr size_t row = 2;
    constexpr size_t col = 3;
    TwoDimMatrix<int, row, col> mat;
    int k = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            mat[i][j] = ++k;
        }
    }
}

template <typename T, size_t R, size_t... C>
struct Matrix {
    using Col = typename Matrix<T, C...>::type;
    using type = std::array<Col, R>;
};

template <typename T, size_t R>
struct Matrix<T, R> {
    using type = std::array<T, R>;
};

void testMultiArray() {
    constexpr size_t a = 2;
    constexpr size_t b = 3;
    constexpr size_t c = 4;
    constexpr size_t d = 5;
    Matrix<int, a, b, c, d>::type mat;
    int u = 0;
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            for (int k = 0; k < c; ++k) {
                for (int m = 0; m < d; ++m) {
                    mat[i][j][k][m] = ++u;
                }
            }
        }
    }
}
int main() {
    // 二维数组
    std::vector<vector<U32>> arr(sizeof(g_ipc382_timing_tbl) / sizeof(g_ipc382_timing_tbl[0]),
                                 vector<U32>(sizeof(g_ipc382_timing_tbl[0][0])));
    for (int i = 0; i < sizeof(g_ipc382_timing_tbl) / sizeof(g_ipc382_timing_tbl[0]); i++) {
        for (int j = 0; j < sizeof(g_ipc382_timing_tbl[0]) / sizeof(g_ipc382_timing_tbl[0][0]);
             j++) {
            arr[i][j] = g_ipc382_timing_tbl[i][j];
            std::cout << std::hex << arr[i][j] << std::endl;
        }
    }
    U32 r = findResult((U32 *)g_ipc382_timing_tbl,
                       sizeof(g_ipc382_timing_tbl[0]) / sizeof(g_ipc382_timing_tbl[0][0]),
                       sizeof(g_ipc382_timing_tbl) / sizeof(g_ipc382_timing_tbl[0]));
    std::cout << "r=" << r << std::endl;
}
