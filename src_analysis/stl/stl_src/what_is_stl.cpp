//
// Created by renbin jiang on 2021/3/24.
//
#include <string.h>

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    vector<int> a; //定义 a 数组，当前数组长度为 0，但和普通数组不同的是，此数组
    // a 可以根据存储数据的数量自动变长。 向数组 a 中添加 10 个元素
    for (int i = 0; i < 10; i++) a.push_back(i);
    //还可以手动调整数组 a 的大小
    a.resize(100);
    a[90] = 100;
    //还可以直接删除数组 a 中所有的元素，此时 a 的长度变为 0
    a.clear();
    //重新调整 a 的大小为 20，并存储 20 个 -1 元素。
    a.resize(20, 0);
    for (int i = 0; i < a.size(); i++) {
        cout << i << " is " << a.at(i) << endl;
    }
    cout << " ------ case 2 -----------" << endl;

    vector<int>(var);
    for (int i = 0; i < 5; i++) {
        var.push_back(i);
        cout << var[i] << ",";
    }
    for (int i = 0; i < 5; i++) //去掉数组最后一个数据
    {
        var.pop_back();
        cout << var[i] << endl;
    }

    cout << "--------迭代器访问---------" << endl;
    //顺序访问
    vector<int> obj;
    for (int i = 0; i < 10; i++) {
        obj.push_back(i);
    }

    cout << "直接利用数组：";
    for (int i = 0; i < 10; i++) //方法一
    {
        cout << obj[i] << " ";
    }

    cout << endl;
    cout << "利用迭代器：";
    //方法二，使用迭代器将容器中数据输出
    vector<int>::iterator it; //声明一个迭代器，来访问vector容器，作用：遍历或者指向vector容器的元素
    for (it = obj.begin(); it != obj.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "--------迭代器访问---------" << endl;

    cout << "--------二维数组-----------" << endl;
    int N = 5, M = 6;
    vector<vector<int>> obj1(N);         //定义二维动态数组大小5行
    for (int i = 0; i < obj.size(); i++) //动态二维数组为5行6列，值全为0
    {
        obj1[i].resize(M);
    }

    for (int i = 0; i < obj1.size(); i++) //输出二维动态数组
    {
        for (int j = 0; j < obj1[i].size(); j++) {
            obj1[i][j] = 1;
            cout << obj1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "--------二维数组------------" << endl;

    return 0;
}