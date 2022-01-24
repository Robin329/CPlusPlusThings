#include <iostream>
using namespace std;
class Figure {
protected:
    double x, y;

public:
    void set(double i, double j) {
        x = i;
        y = j;
    }
    virtual void area() = 0;
};

class Trianle : public Figure {
public:
    void area() { cout << "Area of the triangle:" << x * y * 0.5 << endl; }
};
class Rectangle : public Figure {
public:
    void area() { cout << "This is the rectangle and its area is:" << x * y << endl; }
};

int main(int argc, char const *argv[]) {
    //定义抽象类指针
    Figure *pF = NULL;
    // Figure f1; 抽象类不能被实例化
    Rectangle r;
    Trianle t;
    t.set(10, 20);
    pF = &t;
    pF->area();
    r.set(10, 20);
    pF = &r;
    pF->area();
    //定义抽象类引用
    Figure &rF = t;
    rF.set(20, 20);
    rF.area();
    //    system("pause");
    return 0;
}
