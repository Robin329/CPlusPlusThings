//
// Created by renbin jiang on 2022/3/28.
//
#include <armadillo>
#include <iostream>
#include <vector>
#include "1.spline_interpolation.h"
using namespace std;
using namespace arma;
using namespace SplineSpace;

//构造函数
Spline::Spline(const double* x0, const double* y0, const int& num, BoundaryCondition bc,
               const double& leftBoundary, const double& rightBoundary)
      : GivenX(x0), GivenY(y0), GivenNum(num), Bc(bc), LeftB(leftBoundary), RightB(rightBoundary) {
    if ((x0 == NULL) | (y0 == NULL) | (num < 3)) {
        throw SplineFailure("构造失败,已知点数过少");
    }
    PartialDerivative = new double[GivenNum]; //给偏导分配空间
    MaxX = *max_element(GivenX, GivenX + GivenNum);
    MinX = *min_element(GivenX, GivenX + GivenNum);
    if (Bc == GivenFirstOrder) // I型边界条件
        PartialDerivative1();
    else if (Bc == GivenSecondOrder) // II型边界条件
        PartialDerivative2();
    else {
        delete[] PartialDerivative;
        throw SplineFailure("边界条件参数错误");
    }
}

// I型边界条件求偏导
void Spline::PartialDerivative1(void) {
    //  追赶法解方程求二阶偏导数
    double* a = new double[GivenNum]; //  a:稀疏矩阵最下边一串数
    double* b = new double[GivenNum]; //  b:稀疏矩阵最中间一串数
    double* c = new double[GivenNum]; //  c:稀疏矩阵最上边一串数
    double* d = new double[GivenNum];

    double* f = new double[GivenNum];

    double* bt = new double[GivenNum];
    double* gm = new double[GivenNum];

    double* h = new double[GivenNum];

    for (int i = 0; i < GivenNum; i++) b[i] = 2;                             //  中间一串数为2
    for (int i = 0; i < GivenNum - 1; i++) h[i] = GivenX[i + 1] - GivenX[i]; // 各段步长
    for (int i = 1; i < GivenNum - 1; i++) a[i] = h[i - 1] / (h[i - 1] + h[i]);
    a[GivenNum - 1] = 1;

    c[0] = 1;
    for (int i = 1; i < GivenNum - 1; i++) c[i] = h[i] / (h[i - 1] + h[i]);

    for (int i = 0; i < GivenNum - 1; i++)
        f[i] = (GivenY[i + 1] - GivenY[i]) / (GivenX[i + 1] - GivenX[i]);

    d[0] = 6 * (f[0] - LeftB) / h[0];
    d[GivenNum - 1] = 6 * (RightB - f[GivenNum - 2]) / h[GivenNum - 2];

    for (int i = 1; i < GivenNum - 1; i++) d[i] = 6 * (f[i] - f[i - 1]) / (h[i - 1] + h[i]);

    bt[0] = c[0] / b[0]; //  追赶法求解方程
    for (int i = 1; i < GivenNum - 1; i++) bt[i] = c[i] / (b[i] - a[i] * bt[i - 1]);

    gm[0] = d[0] / b[0];
    for (int i = 1; i <= GivenNum - 1; i++)
        gm[i] = (d[i] - a[i] * gm[i - 1]) / (b[i] - a[i] * bt[i - 1]);

    PartialDerivative[GivenNum - 1] = gm[GivenNum - 1];
    for (int i = GivenNum - 2; i >= 0; i--)
        PartialDerivative[i] = gm[i] - bt[i] * PartialDerivative[i + 1];

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] d;
    delete[] gm;
    delete[] bt;
    delete[] f;
    delete[] h;
}

// II型边界条件求偏导
void Spline::PartialDerivative2(void) {
    //  追赶法解方程求二阶偏导数

    double* a = new double[GivenNum]; //  a:稀疏矩阵最下边一串数
    double* b = new double[GivenNum]; //  b:稀疏矩阵最中间一串数
    double* c = new double[GivenNum]; //  c:稀疏矩阵最上边一串数
    double* d = new double[GivenNum];

    double* f = new double[GivenNum];

    double* bt = new double[GivenNum];
    double* gm = new double[GivenNum];

    double* h = new double[GivenNum];

    for (int i = 0; i < GivenNum; i++) b[i] = 2;
    for (int i = 0; i < GivenNum - 1; i++) h[i] = GivenX[i + 1] - GivenX[i];
    for (int i = 1; i < GivenNum - 1; i++) a[i] = h[i - 1] / (h[i - 1] + h[i]);
    a[GivenNum - 1] = 1;

    c[0] = 1;
    for (int i = 1; i < GivenNum - 1; i++) c[i] = h[i] / (h[i - 1] + h[i]);

    for (int i = 0; i < GivenNum - 1; i++)
        f[i] = (GivenY[i + 1] - GivenY[i]) / (GivenX[i + 1] - GivenX[i]);

    for (int i = 1; i < GivenNum - 1; i++) d[i] = 6 * (f[i] - f[i - 1]) / (h[i - 1] + h[i]);

    d[1] = d[1] - a[1] * LeftB;
    d[GivenNum - 2] = d[GivenNum - 2] - c[GivenNum - 2] * RightB;

    bt[1] = c[1] / b[1];
    for (int i = 2; i < GivenNum - 2; i++) bt[i] = c[i] / (b[i] - a[i] * bt[i - 1]);

    gm[1] = d[1] / b[1];
    for (int i = 2; i <= GivenNum - 2; i++)
        gm[i] = (d[i] - a[i] * gm[i - 1]) / (b[i] - a[i] * bt[i - 1]);

    PartialDerivative[GivenNum - 2] = gm[GivenNum - 2]; //
    for (int i = GivenNum - 3; i >= 1; i--)
        PartialDerivative[i] = gm[i] - bt[i] * PartialDerivative[i + 1];

    PartialDerivative[0] = LeftB;
    PartialDerivative[GivenNum - 1] = RightB;

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] d;
    delete[] gm;
    delete[] bt;
    delete[] f;
    delete[] h;
}

//单个插值的实现
bool Spline::SinglePointInterp(const double& x, double& y) throw(SplineFailure) {
    if ((x < MinX) | (x > MaxX)) throw SplineFailure("不支持外插值");
    int klo, khi, k;
    klo = 0;
    khi = GivenNum - 1;
    double hh, bb, aa;

    while (khi - klo > 1) //  二分法查找x所在区间段
    {
        k = (khi + klo) >> 1;
        if (GivenX[k] > x)
            khi = k;
        else
            klo = k;
    }
    hh = GivenX[khi] - GivenX[klo];

    aa = (GivenX[khi] - x) / hh;
    bb = (x - GivenX[klo]) / hh;

    y = aa * GivenY[klo] + bb * GivenY[khi] +
            ((aa * aa * aa - aa) * PartialDerivative[klo] +
             (bb * bb * bb - bb) * PartialDerivative[khi]) *
                    hh * hh / 6.0;
    return true;
}

//多个插值的实现
bool Spline::MultiPointInterp(const double* x, const int& num, double* y) throw(SplineFailure) {
    for (int i = 0; i < num; i++) {
        SinglePointInterp(x[i], y[i]);
    }
    return true;
}

//自动多个插值的实现
bool Spline::AutoInterp(const int& num, double* x, double* y) throw(SplineFailure) {
    if (num < 2) throw SplineFailure("至少要输出两个点");
    double perStep = (MaxX - MinX) / (num - 1);

    for (int i = 0; i < num; i++) {
        x[i] = MinX + i * perStep;
        SinglePointInterp(x[i], y[i]);
    }
    return true;
}

Spline::~Spline() {
    delete[] PartialDerivative;
}

//异常类实现
SplineFailure::SplineFailure(const char* msg) : Message(msg){};
const char* SplineFailure::GetMessage() {
    return Message;
}

int main() {
    double x[] = {0, 3, 5, 7, 9, 11, 12, 13, 14, 15};
    double y[] = {0, 1.2, 1.7, 2.0, 2.1, 2.0, 1.8, 1.2, 1.0, 1.6};
    int size = sizeof(x) / sizeof(double);
    const double min = x[0];
    const double max = x[size - 1];

    vector<double> xx, yy; //插值点与计算的函数值
    for (double i = x[0]; i <= x[size - 1]; i = i + 0.1) {
        xx.push_back(i);
    }
    int size_xx = xx.size();

    vector<double> dx, dy; //差分，即步长
    for (int i = 0; i < size - 1; i++) {
        double temp_dx = x[i + 1] - x[i];
        dx.push_back(temp_dx);
        double temp_dy = y[i + 1] - y[i];
        dy.push_back(temp_dy);
    }

    mat H, Y, M; // H * M = Y
    H.zeros(size, size);
    Y.zeros(size, 1);
    // M.zeros(1, size);

    H(0, 0) = 1;
    H(size - 1, size - 1) = 1;
    for (int i = 1; i < size - 1; i++) {
        H(i, i - 1) = dx[i - 1];
        H(i, i) = 2 * (dx[i - 1] + dx[i]);
        H(i, i + 1) = dx[i];
        Y(i) = 3 * (dy[i] / dx[i] - dy[i - 1] / dx[i - 1]);
    }

    M = solve(H, Y);

    vector<double> ai, bi, ci, di; //系数
    for (int i = 0; i < size - 1; i++) {
        ai.push_back(y[i]);
        di.push_back((M(i + 1) - M(i)) / (3 * dx[i]));
        bi.push_back(dy[i] / dx[i] - dx[i] * (2 * M(i) + M(i + 1)) / 3);
        ci.push_back(M(i));
    }

    vector<int> x_, xx_;
    for (int i = 0; i < size; i++) {
        int temp = x[i] / 0.1;
        x_.push_back(temp);
    }
    for (int i = 0; i < size_xx; i++) {
        int temp = xx[i] / 0.1;
        xx_.push_back(temp);
    }

    for (int i = 0; i < size_xx; i++) {
        int k = 0;
        for (int j = 0; j < size - 1; j++) {
            if (xx_[i] >= x_[j] && xx_[i] < x_[j + 1]) {
                k = j;
                break;
            } else if (xx[i] == x[size - 1]) {
                k = size - 1;
            }
        }
        // yy(i) = y[i] + bi(k) * (xx[i] - x[k]) + 1 / 2.0 * M(i) * pow((xx[i] - x[k]) , 2) + di(k)
        // * pow((xx[i] - x[k]),3);
        double temp = ai[k] + bi[k] * (xx[i] - x[k]) + M(k) * pow((xx[i] - x[k]), 2) +
                di[k] * pow((xx[i] - x[k]), 3);
        yy.push_back(temp);
    }

    std::ofstream output;
    output.open("Spline.txt");
    for (unsigned i = 0; i < size_xx; i++) {
        output << xx[i] << '\t' << yy[i] << std::endl;
    }
    output.close();
    cout << "Hello World !" << endl;
}
