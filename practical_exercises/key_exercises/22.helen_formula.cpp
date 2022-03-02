#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

/**
 * 求两点间的距离
 * @param x1 点1的x
 * @param y1 点1的y
 * @param x2 点2的x
 * @param y2 点2的y
 * @return 两点间的距离
 */
float getLineLen(float x1, float y1, float x2, float y2) {
    return sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
}

/**
 * 海伦公式，求三角形的面积
 * 三角形的变长分别为a, b, c, 三角形的半周长:p = (a+b+c)/2
 * 三角形的面积S=sqrt(p*(p-a)*(p-b)*(p-c))
 */
float helenFormula(float a, float b, float c) {
    float p = (a + b + c) / 2;
    return sqrtf(p * (p - a) * (p - b) * (p - c));
}

/**
 * 计算4边形面积
 * @param point 四边形的坐标，逆时针排列
 * @return 四边形的面积
 */
float calcQuadArea(float point[8]) {
    //0(0,1)  1(2,3) 2(4,5) 3(6,7)
    float sideLen01 = getLineLen(point[0], point[1], point[2], point[3]);
    float sideLen12 = getLineLen(point[2], point[3], point[4], point[5]);
    float sideLen23 = getLineLen(point[4], point[5], point[6], point[7]);
    float sideLen30 = getLineLen(point[6], point[7], point[0], point[1]);
    float sideLen20 = getLineLen(point[4], point[5], point[0], point[1]);

    float S1 = helenFormula(sideLen01, sideLen12, sideLen20);
    float S2 = helenFormula(sideLen20, sideLen23, sideLen30);

    return S1 + S2;
}

int main() {
    float point[8] = {
            0, 1920,
            1920, 1920,
            1920, 0,
            0, 0,
    };

    printf("area: %f\n", calcQuadArea(point));
    return 0;
}
