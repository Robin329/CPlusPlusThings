#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "base.h"

using namespace std;
using namespace base;

#define WIDTH_H 1920
#define HEIGHT_V 1080

float averag(float line1, float line2, float line3, float line4);

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
 * 海伦公式，求内接圆的四边形的面积
 * 四条边长分别为a,b,c,d
 * p = (a+b+c+d)/2
 * 四边形的面积S=sqrt(p*(p-a)*(p-b)*(p-c))
 */
float helenAnyQuardFormula(float a, float b, float c, float d) {
    float p = averag(a, b, c, d);
    return sqrtf((p - a) * (p - b) * (p - c) * (p - d));
}

/**
 * 计算4边形面积
 * @param point 四边形的坐标，逆时针排列
 * @return 四边形的面积
 */
float calcQuadArea(float point[8]) {
    // 0(0,1)  1(2,3) 2(4,5) 3(6,7)
    float sideLen01 = getLineLen(point[0], point[1], point[2], point[3]);
    float sideLen12 = getLineLen(point[2], point[3], point[4], point[5]);
    float sideLen23 = getLineLen(point[4], point[5], point[6], point[7]);
    float sideLen30 = getLineLen(point[6], point[7], point[0], point[1]);
    float sideLen20 = getLineLen(point[4], point[5], point[0], point[1]);

    float S1 = helenFormula(sideLen01, sideLen12, sideLen20);
    float S2 = helenFormula(sideLen20, sideLen23, sideLen30);

    return S1 + S2;
}

/**
 * @brief calculate the Polygon Area with vertex coordinates
 * @refer https://blog.csdn.net/qq_38862691/article/details/87886871
 *
 * @param points: input vertex coordinates
 * @return float: polygon area
 */
double getPolygonArea(vector<cv::Point> const& points) {
    const int sizep = points.size();
    if (sizep < 3) return 0.0;

    double area = points.back().x * points[0].y - points[0].x * points.back().y;
    for (int i = 1, v = 0; i < sizep; i++, v++) {
        area += (points[v].x * points[i].y);
        area -= (points[i].x * points[v].y);
    }

    return fabs(0.5 * area);
}

float averag(float line1, float line2, float line3, float line4) {
    return (line1 + line2 + line3 + line4) / 2.0;
}

float calcAnyQuadArea(float point[8]) {
    // 0(0,1)  1(2,3) 2(4,5) 3(6,7)
    float sideLen01 = getLineLen(point[0], point[1], point[2], point[3]);
    float sideLen12 = getLineLen(point[2], point[3], point[4], point[5]);
    float sideLen23 = getLineLen(point[4], point[5], point[6], point[7]);
    float sideLen30 = getLineLen(point[6], point[7], point[0], point[1]);
    return helenAnyQuardFormula(sideLen01, sideLen12, sideLen23, sideLen30);
}

int PointCoordinate2point(point point[2][2], float *p) {
    if (!p) return -1;
    // tl
     p[0] = point[0][0].S16X;
     p[1] = HEIGHT_V - point[0][0].S16Y;
     // tr
     p[2] = point[0][1].S16X;
     p[3] = HEIGHT_V - point[0][1].S16Y;
     // bl
     p[4] = point[1][0].S16X;
     p[5] = HEIGHT_V - point[1][0].S16Y;
     // br
     p[6] = point[1][1].S16X;
     p[7] = HEIGHT_V - point[1][1].S16Y;
     for (int i = 0; i < sizeof (p);i++) {
         std::cout << "p" << i << ":" << p[i] << std::endl;
     }
     return 0;
}

int main() {
    float point[8] = {
            0, 1080, 1920, 1080, 1920, 0, 0, 0,
    };
    // method : 1
    //    ^
    //    |
    //    |(0,1080)             (1920,1080)
    //    +-------------------+
    //    |                   |
    //    |                   |
    //    |                   |
    //    |                   |
    //    (0,0)               | (1920,0)
    //+---------------------------->
    //    |
    //    +
    printf("method1 area: %f\n", calcQuadArea(point));

    // method : 2
    // 需要内接于圆
    printf("method2 area: %f\n", calcAnyQuadArea(point));
    // method : 3
    float point1[8] = {
            0, 1080, 1920, 1080, 1920, 0, 0, 0,
    };
    vector<cv::Point> point2;
    point2.push_back(cv::Point(point1[0], point1[1]));
    point2.push_back(cv::Point(point1[2], point1[3]));
    point2.push_back(cv::Point(point1[4], point1[5]));
    point2.push_back(cv::Point(point1[6], point1[7]));
    printf("method3 area: %f\n", getPolygonArea(point2));
    
    float p1[8] = {};
    base::point point4[2][2]={};
    point4[0][0].S16X = 24;
    point4[0][0].S16Y = 0;
    
    point4[0][1].S16X = 1920;
    point4[0][1].S16Y = 0;
    
    point4[1][0].S16X = 0;
    point4[1][0].S16Y = 1080;
    
    point4[1][1].S16X = 1920;
    point4[1][1].S16Y = 1080;
    
    PointCoordinate2point(point4, p1);
    for (int i = 0; i < sizeof (p1)/sizeof(float);i++) {
        std::cout << "p" << i << ":" << p1[i] << std::endl;
    }
    vector<cv::Point> point5;
    point5.push_back(cv::Point(p1[0], p1[1]));
    point5.push_back(cv::Point(p1[2], p1[3]));
    point5.push_back(cv::Point(p1[4], p1[5]));
    point5.push_back(cv::Point(p1[6], p1[7]));
    printf("method3 area: %f\n", getPolygonArea(point5));
    
    return 0;
}
