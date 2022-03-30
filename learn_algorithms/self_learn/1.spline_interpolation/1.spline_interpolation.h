//
// Created by renbin jiang on 2022/3/28.
//

#ifndef CPLUSPLUSTHINGS_1_SPLINE_INTERPOLATION_H
#define CPLUSPLUSTHINGS_1_SPLINE_INTERPOLATION_H
//----------------------------------------------------------------------------
// 文件名：Spline.h
//----------------------------------------------------------------------------
// 功能:	使用三次样条曲线进行插值
//----------------------------------------------------------------------------
// 说明：	1.提供了两种边界条件的设定方式：
//				1)给定端点的一阶导
//				2)给定端点的二阶导
//			2.提供了三种插值计算方式：
//				1)给定一个点计算对应插值,可能抛出外插值异常
//				2)给定多个点计算对应插值，可能抛出外插值异常
//				3)设定插值的输出个数(至少为2),自动在Max(x)和Min(x)之间等间距的输出插值.
//				x为已知数据自变量序列,可能抛出点数过少异常
//----------------------------------------------------------------------------
// 作者： 刘亚彬
// 创建日期: 2017年2月20日
// 修改日期：
//-----------------------------------------------------------------------------

#include <algorithm>
#include <cstring>

#include "Spline.h"

using namespace std;

//因为里面的类名都比较短,为了防止重名这里用一个命名空间进行包裹
namespace SplineSpace {

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

class SplineFailure //异常类
{
private:
    const char* Message;

public:
    SplineFailure(const char* msg);
    const char* GetMessage();
};

class SplineInterface //接口类
{
public:
    //单点插值:
    // x->输入自变量(输入)
    // y->返回插值结果(输出)
    //如果x不是内插值点则插值失败
    virtual bool SinglePointInterp(const double& x, double& y) = 0;
    //多点插值:
    // x->输入自变量数组首指针,num->自变量个数的引用(输入)
    // y->返回插值结果的首指针(输出数组)
    virtual bool MultiPointInterp(const double* x, const int& num, double* y) = 0;
    //自动插值:
    // num->需要生成的插值个数的引用(输入)
    // x->存放自变量数组的首指针(输出数组)
    // y->对应拟合结果的首指针(输出数组)
    virtual bool AutoInterp(const int& num, double* x, double* y) = 0;

    virtual ~SplineInterface(){};
};

enum BoundaryCondition //边界条件枚举
{
    GivenFirstOrder = 1, //给定一阶导数

    GivenSecondOrder //给定二阶导数
};

class Spline : public SplineInterface //实现类
{
public:
    //构造函数:
    // x0->已知的自变量数组首指针,y0->已知的因变量数组首指针,num->已知数据的个数
    // bc->边界条件,默认给定二阶导数
    // leftBoundary,rightBoundary左右边界导数值的引用,默认都是0
    Spline(const double* x0, const double* y0, const int& num,
           BoundaryCondition bc = GivenSecondOrder, const double& leftBoundary = 0,
           const double& rightBoundary = 0);

    bool SinglePointInterp(const double& x, double& y) throw(SplineFailure); //虚函数实现
    bool MultiPointInterp(const double* x, const int& num, double* y) throw(SplineFailure);
    bool AutoInterp(const int& num, double* x, double* y) throw(SplineFailure);

    ~Spline();

private:
    //方法
    void PartialDerivative1(void); //求一阶导
    void PartialDerivative2(void); //求二阶导
    //属性
    const double* GivenX;       //已知数据的自变量
    const double* GivenY;       //已知数据的因变量
    const int GivenNum;         //给定的已知数据点数
    const BoundaryCondition Bc; //边界类型
    const double LeftB;
    const double RightB;

    double* PartialDerivative; //保存对应的二阶或者一阶偏导数
    double MaxX;               //自变量的最大值
    double MinX;               //自变量的最小值

    const double* SplineX; //插值自变量
    double* SplineY;       //插值因变量
    const int* SplineNum;  //插值个数
};
} // namespace SplineSpace

#endif // CPLUSPLUSTHINGS_1_SPLINE_INTERPOLATION_H
