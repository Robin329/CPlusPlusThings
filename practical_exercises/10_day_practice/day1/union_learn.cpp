#include <iostream>
using namespace std;
union myun {
    struct {
        int x;
        int y;
        int z;
    } u;
    int k;
} a;
int main() {
    a.u.x = 4;
    a.u.y = 5;
    a.u.z = 6;
    a.k = 0;
    printf("%d %d %d %d\n", a.u.x, a.u.y, a.u.z, a.k);
    cout << "sizeof a:" << sizeof(a); // only struct u is large
    //    system("pause");
    return 0;
}