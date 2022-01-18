#include <fstream>
#include <iostream>
#include <mutex>
using namespace std;

enum class shape_type {
    circle,
    triangle,
    rectangle,
};

class shape {
public:
    shape() { cout << "shape" << endl; }

    virtual void print() { cout << "I am shape" << endl; }

    virtual ~shape() {}
};

class circle : public shape {
public:
    circle() { cout << "circle" << endl; }

    void print() { cout << "I am circle" << endl; }
};

class triangle : public shape {
public:
    triangle() { cout << "triangle" << endl; }

    void print() { cout << "I am triangle" << endl; }
    static triangle *getinstance() {
        if (!tria) {
            tria = new triangle();
            return tria;
        } else {
            return tria;
        }
    }

private:
    static triangle *tria;
};
triangle *triangle::tria = nullptr;
class rectangle : public shape {
public:
    rectangle() { cout << "rectangle" << endl; }

    void print() {
        cout << "++++++++++++++" << endl;
        triangle *tri = triangle::getinstance();
        tri->print();
        cout << "I am rectangle" << endl;
        cout << "++++++++++++++" << endl;
    }

    static rectangle *getinstance() {
        if (!m_rect) {
            m_rect = new rectangle();
            return m_rect;
        } else {
            return m_rect;
        }
    }

private:
    static rectangle *m_rect;
};

// 利用多态 上转 如果返回值为shape,会存在对象切片问题。
shape *create_shape(shape_type type) {
    switch (type) {
        case shape_type::circle:
            return new circle();
        case shape_type::triangle:
            return new triangle();
        case shape_type::rectangle:
            return new rectangle();
    }
}

class shape_wrapper {
public:
    explicit shape_wrapper(shape *ptr = nullptr) : ptr_(ptr) {}

    ~shape_wrapper() { delete ptr_; }

    shape *get() const { return ptr_; }

private:
    shape *ptr_;
};

void foo() {
    shape_wrapper ptr(create_shape(shape_type::circle));
    ptr.get()->print();
}

int main() {
    // 第一种方式
    shape *sp = create_shape(shape_type::rectangle);
    sp->print();
    delete sp;

    // 第二种方式
    foo();

    return 0;
}
