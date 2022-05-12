//
// Created by renbin jiang on 2022/5/12.
//
#include "std_lib_facilities.h"

int main() {
    // open an istream for binary input from a file
    cout << "Please enter input file name\n";
    string name;
    cin >> name;
    ifstream ifs(FileSystem::getPath((CURRENT_PATH "Chapter11/res/" + name).c_str()), ios_base::binary);
    if (!ifs) error("can't open input file ", name);

    // open an ostream for binary output a file;
    cout << "Please enter output file name\n";
    cin >> name;
    ofstream ofs(FileSystem::getPath((CURRENT_PATH "Chapter11/res/" + name).c_str()), ios_base::binary);

    if (!ofs) error("can't open output file ", name);

    vector<int> v;
    // read from binary file;
    int i;
    while (ifs.read(as_bytes(i), sizeof(int))) v.push_back(i);
    for (auto const tmp : v) cout << "tmp:" << tmp << end;
    // write to binary file
    for (int i{}; i < v.size(); ++i)) ofs.write(as_bytes(v[i]), sizeof(int));

    if (ifs.is_open()) ifs.close();
    if (ofs.is_open()) ofs.close();
    return 0;
}