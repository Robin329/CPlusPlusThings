// Eg9-1.cpp
#include <iostream>
//ע��һ��, max��minʹ�õ�ʱ��, ���������ͻ, ���д��������һ�д���, ��Ҫ�ı亯��ģ������,
//����ֱ��ʹ��std::cout��std::endl
using namespace std;
/*
��Ҫ�������class����������ؼ���class������һ��, ��Ȼ��������ͬ����ĸ���, �������ǲ�ͬ�ġ�
�����class��ʾT��һ�����Ͳ���, �������κ���������, ��int��float��char��,
�����û������struct��enum��class���Զ����������͡�
*/
template <class T>
T Min(T a, T b) {
    return (a < b) ? a : b;
}
/*
Ϊ����������ģ������е����͹ؼ���class, ��׼C++���?����typename��Ϊģ����������͹ؼ���,
ͬʱҲ֧��ʹ��class�� ����, ��min�����template <class T>д���������ʽ����ȫ�ȼ۵ģ�
*/
template <typename T>
T myMin(T a, T b) {
    return (a < b) ? a : b;
}

/*
ģ��ʵ���������ڵ���ģ�庯��ʱ�������������������жԺ���ģ��ĵ���ʱ,
���Ż���ݵ��������ʵ�εľ�������, ȷ��ģ���������������,
���ô������滻����ģ���е�ģ�����, �����ܹ���������͵ĺ�������, ��ģ�庯����
����η���������ͬ�Ĳ�������ʱ, ֻ�ڵ�1�ν���ʵ������������ֻ�ڵ�1�ε���ʱ����ģ�庯��,
��֮��������ͬ���͵Ĳ�������ʱ, ������������ģ�庯��, �������õ�1��ʵ�������ɵ�ģ�庯����
*/
int main() {
    double a = 2, b = 3.4;
    float c = 2.3, d = 3.2;
    cout << "2, 3     's Max Value is:" << Min<int>(2, 3) << endl; //��ʽ����
    cout << "2, 3.4   's Max Value is:" << Min(a, b) << endl;      //��ʽ����
    cout << "'a', 'b' 's Max Value is:" << Min('a', 'b') << endl;
    cout << "2.3, 3.2 's Max Value is:" << Min(c, d) << endl;
    cout << "2.3, 3.2 's Min Value is:" << std::min(c, d) << endl; //���������ռ��ڲ�����Сֵ����
    cout << "2.3, 3.2 's Max Value is:" << myMin(c, d) << endl;    //����classΪtypename
    // cout<<"2, 'a'    ����Сֵ�ǣ�"<<Min(2,'a')<<endl;
    // //����,��ͬ�����޷�����, �뿴9-3-1.cpp
    //    system("pause");
    return 0;
}
