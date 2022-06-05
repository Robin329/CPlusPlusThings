//
// Created by renbin jiang on 2022/6/4.
//
#include "std_lib_facilities.h"

template <typename T>
struct S {
    S() {}
    S(T t) : val(t) {}

    istream operator>>(T t) { cin >> val; }
    const T& get() const { return val; }
    void set(T t) { val = t; }
    S& operator=(const T& newVal) {
        val = newVal;
        return *this;
    }
    // returns non-const reference to val
    T& getRef() { return val; }

private:
    T val;
};

template <typename T>
const T& get(S<T>& s) {
    return s.get();
}

// drill 12
template <typename T>
void readVal(T& v) {
    cin >> v;
}

// drill 14

// -----------------------------------------------------------------------------

// handles most standard types. No error checking for incorrect input though
// example:
//     { 1, 2, 3 }
template <typename T>
istream& operator>>(istream& is, vector<T>& vt) {
    T temp;
    string s;
    while (is >> s) {
        if (s == "}") break;
        if (is.fail()) {
            is.clear();
            is.ignore(INT_MAX, '\n');
        }
        if (s != "{" && s != " " && s != ",") {
            // clean up commas - if you put a comma in it...tough luck
            s.erase(remove(s.begin(), s.end(), ','));
            // convert cleaned up string into whatever type we're dealing with
            stringstream ss;
            ss << s;
            ss >> temp;
            vt.push_back(temp);
        }
    }

    return is;
}
template<typename T>
ostream& operator<<(ostream& os, vector<T>& vt)
{
    os <<  "{ ";
    for (uint32_t i = 0; i < vt.size() - 1; ++i)
    {
        os << vt[i] << ", ";
    }
    os << vt[vt.size() - 1] << " }" << endl;
    return os;
}

int main() {
    S<vector<int>> sv(vector<int>(10, 100));

    // drill 09
    sv.set(vector<int>(10, 23));
    for (int i : get(sv)) cout << i << ", ";
    cout << endl;
    // drill 011
    S<int> si(101);
    si = 10;
    cout << si.getRef() << endl;
    cout << "Enter int: ";
    readVal(si.getRef());
    cout << si.get() << endl;

    // drill 14
    S<vector<int>> svi;
    cout << "Enter ints in format { val, val, val } etc., : ";
    cin >> svi.getRef();
    cout << svi.getRef();

    S<vector<char>> svc;
    cout << "Enter chars in format { val, val, val } etc., : ";
    cin >> svc.getRef();
    cout << svc.getRef();

    S<vector<double>> svd;
    cout << "Enter doubles in format { val, val, val } etc., : ";
    cin >> svd.getRef();
    cout << svd.getRef();

    S<vector<double>> svf;
    cout << "Enter floats in format { val, val, val } etc., : ";
    cin >> svf.getRef();
    cout << svf.getRef();

    S<vector<string>> svs;
    cout << "Enter strings in format { val, val, val } etc., : ";
    cin >> svs.getRef();
    cout << svs.getRef();

    cout << endl;
    return 0;
}