//
// Created by renbin jiang on 2022/4/13.
//
#include "std_lib_facilities.h"
#define MIN(x, y) ((x) > (y) ? (y) : (x))
enum cbFlags {
	ENUM_CB_NONE = -1,
	ENUM_CB_ONE,
	ENUM_CB_TWO,
	ENUM_CB_THREE,
	ENUM_CB_FOUR,
	ENUM_CB_MAX,
};
int main() {
    vector<double> x;
    vector<string> s = {"cm", "in", "ft", "m"};
    std::map<int, std::string> m;
    m[1] = "ro";
    m[2] = "in";
    vector<int> mVecFlag;
    cout << "sizeof:" << sizeof(cbFlags) << endl;
    vector<vector<int> > vec;
    vec.resize(1);
    vec[0].push_back(1);
    vec[0].push_back(2);
    vector<int> v(vec[0]);
    for (const auto t : v)
	    cout << "t:" << t << endl;
    int flag = 0;
    mVecFlag.push_back(0);
    int i;
    for (i = 0; i < mVecFlag.size(); i++) {
	    if (flag != mVecFlag[i])
		    continue;
	    else {
		    cout << "flag:" << flag << " not registered!!!\n";
		    return false;
	    }
    }
    return 0;
}