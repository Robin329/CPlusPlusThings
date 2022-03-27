//
// Created by renbin jiang on 2022/3/21.
//
/*
 * 判断一个点是否在三角形内，输入需要逆时针输入三个顶点
 */
#include <iostream>
#include <math.h>
using namespace std;
struct Point {
    double x;
    double y;
};
double product(Point p1,Point p2,Point p3) {
    //首先根据坐标计算p1p2和p1p3的向量，然后再计算叉乘
    //p1p2 向量表示为 (p2.x-p1.x,p2.y-p1.y)
    //p1p3 向量表示为 (p3.x-p1.x,p3.y-p1.y)
    return (p2.x-p1.x)*(p3.y-p1.y) - (p2.y-p1.y)*(p3.x-p1.x);
}
bool isInTriangle(Point p1,Point p2,Point p3,Point o) {
    //保证p1，p2，p3是逆时针顺序
    if(product(p1, p2, p3)<0) return isInTriangle(p1,p3,p2,o);
    if(product(p1, p2, o)>0 && product(p2, p3, o)>0 && product(p3, p1, o)>0)
        return true;
    return false;
}
int main() {
    Point p1,p2,p3,o;
    cout << "Please input First point:" << endl;
    cin >> p1.x >> p1.y;
    cout << "Please input Second point:" << endl;
    cin >> p2.x >> p2.y;
    cout << "Please input Third point:" << endl;
    cin >> p3.x >> p3.y;
    cout << "Please input Test point:" << endl;
    cin >> o.x >> o.y;
    bool flag = isInTriangle(p1,p2,p3,o);
    if(flag) puts("Yes");
    else puts("No");
}