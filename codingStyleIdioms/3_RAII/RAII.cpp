#include "opencv2/calib3d.hpp"
#include "opencv2/core.hpp"
//#include "opencv2/features2d.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/xfeatures2d.hpp"
#include <fstream>
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>

using namespace std;
// RAII 资源获取即初始化,例1

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
};

class rectangle : public shape {
public:
    rectangle() { cout << "rectangle" << endl; }

    void print() { cout << "I am rectangle" << endl; }
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

void PrintMat(cv::Mat A) {
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++)
            //      cout << A.at<float>(i, j) << ' ';
            printf("%d %d %d %d\n", A.at<cv::Vec3b>(i, j)[0], A.at<cv::Vec3b>(i, j)[1], A.at<cv::Vec3b>(i, j)[2],
                   A.at<cv::Vec3b>(i, j)[3]);
        cout << endl;
    }
    cout << endl;
}

void printMat1(cv::Mat H) {
    for (int i = 0; i < H.rows; i++) {
        for (int j = 0; j < H.cols * H.elemSize(); j++) {
            printf("H.data[%lu]: %d\n", i * H.cols * H.elemSize() + j, H.data[i * H.cols * H.elemSize() + j]);
        }
    }
}
int main() {
    // 第一种方式
    shape *sp = create_shape(shape_type::circle);
    sp->print();
    delete sp;

    // 第二种方式 RAII
    foo();

    // -----------------------------------------
    float src[8] = {0.0, 0.0, 16.0, 0.0, 9.0, 0.0, 16.0, 9.0};
    float kstPoint[8] = {0, 0, 1920, 0, 1080, 0, 1920, 1080};
    vector<cv::Point2f> point;
    vector<cv::Point3f> point3f;
    point.push_back(cv::Point2f(src[0], src[1]));
    point.push_back(cv::Point2f(src[2], src[3]));
    point.push_back(cv::Point2f(src[4], src[5]));
    point.push_back(cv::Point2f(src[6], src[7]));
    //  cout << "point:" << point << endl;
    vector<cv::Point2f> kst2f;
    kst2f.push_back(cv::Point2f(kstPoint[0], kstPoint[1]));
    kst2f.push_back(cv::Point2f(kstPoint[2], kstPoint[3]));
    kst2f.push_back(cv::Point2f(kstPoint[4], kstPoint[5]));
    kst2f.push_back(cv::Point2f(kstPoint[6], kstPoint[7]));
    vector<cv::Point2f> pts_src;
    pts_src.push_back(cv::Point2f(141, 131));
    pts_src.push_back(cv::Point2f(480, 159));
    pts_src.push_back(cv::Point2f(493, 630));
    pts_src.push_back(cv::Point2f(64, 601));

    cv::Mat H;
    //  memset(&H, 0, sizeof(cv::Mat));
    H = cv::findHomography(pts_src, point);
    printMat1(H);

    PrintMat(H);
    return 0;
}
