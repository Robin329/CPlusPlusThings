//
// Created by renbin jiang on 2022/5/8.
//
/*
        Written by Jtaim
        Date 15 Jan 2019
        Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

        Section 9 Exercise 2
        Design and implement a Name_pairs class (name,age) pairs.
        - name is a vector<string>
        - age is a vector<double>
        - read_names() to read in a series of names
        - read_ages() to prompt user for an age for each name
        - print() to print name[i], age[i] pairs. One per line in the order determined by the name
   vector.
        - sort() to sort name vector is alphabetical order and reorganizes age vector to match.

        Implement all operations as members functions.
        Test the class.
*/

#include <iostream>
#include "std_lib_facilities.h"

class Name_pairs {
public:
    Name_pairs();
    void read_names();
    void read_ages();
    void print() const;
    void sort();
    // 参数只能传入类,两个入参
    friend std::ostream& operator<<(std::ostream& os, const Name_pairs& np);
    // Error
    // friend std::ostream& operator<<(std::ostream& os, const Name_pairs& np, const Name_pairs&
    // np1);

    friend bool operator==(const Name_pairs& np1, const Name_pairs& np2);
    friend bool operator!=(const Name_pairs& np1, const Name_pairs& np2);

private:
    vector<string> m_names;
    vector<double> m_ages;
};

Name_pairs::Name_pairs() {}

void Name_pairs::read_names() {
    cout << "Enter names separated by ',' or new line. EOF (Enter key) to exit.\n";
    char c{};
    string name;
    while (cin.get(c)) {
        if (c != ',' && c != '\n') {
            if (!name.empty()) {
                name += c;
            } else if (c != ' ') {
                name += c;
            }
        } else if (!name.empty()) {
            m_names.push_back(name);
            name.clear();
        } else if (c == '\n')
            break;
    }
    if (cin.eof()) {
        cin.clear(); // clear EOF
    }
}

void Name_pairs::read_ages() {
    for (auto n : m_names) {
        cout << "Enter age for " << n << ": ";
        double age{};
        for (;;) {
            if (!(cin >> age)) {
                cin.clear();
                cin.ignore(numeric_limits<int>::max(), '\n');
            } else {
                char c{};
                cin.get(c);
                // when entering numbers '\n' is left in the buffer.
                // cin will take the first valid number leaving rest in the stream
                // so added check that nothing left after number other than new line.
                if (c != '\n') {
                    cin.ignore(numeric_limits<int>::max(), '\n');
                } else {
                    m_ages.push_back(age);
                    break;
                }
            }
            cout << "Invalid age entered!\nRenter age for " << n << ": ";
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Name_pairs& np) {
    os << "----------------------";
    if (np.m_names.size() == np.m_ages.size()) {
        for (auto itr{np.m_names.begin()}; itr < np.m_names.cend(); ++itr) {
            size_t index = static_cast<size_t>(itr - np.m_names.begin());
            os << np.m_names.at(index) << " is " << np.m_ages.at(index) << " years old.\n";
        }
    } else {
        error("vector sizes do not match!");
    }
    return os;
}

bool operator==(const Name_pairs& np1, const Name_pairs& np2) {
    return np1.m_names == np2.m_names && np1.m_ages == np2.m_ages;
}

bool operator!=(const Name_pairs& np1, const Name_pairs& np2) {
    return !(np1 == np2);
}

void Name_pairs::print() const {
    cout << "----------------------" << std::endl;
    if (m_names.size() == m_ages.size()) {
        for (auto itr{m_names.begin()}; itr < m_names.cend(); ++itr) {
            size_t index = static_cast<size_t>(itr - m_names.begin());
            cout << m_names.at(index) << " is " << m_ages.at(index) << " years old.\n";
        }
    } else {
        error("vector sizes do not match!");
    }
    std::cout << "----------------------" << std::endl;
}

void Name_pairs::sort() {
    using it_size = vector<string>::size_type;

    vector<string> copy_names = m_names;
    vector<double> copy_ages = m_ages;

    stable_sort(m_names.begin(), m_names.end());

    if (m_names.size() == m_ages.size()) {
        for (it_size i{}; i < m_names.size(); ++i) {
            const auto itr{find(copy_names.begin(), copy_names.end(), m_names.at(i))};
            if (itr == copy_names.cend()) error("Name not found!");

            it_size index = static_cast<it_size>(itr - copy_names.begin());
            m_ages.at(i) = copy_ages.at(index);
        }
    } else {
        error("vector sizes do not match!");
    }
}

int main() try {
    Name_pairs np;
    np.read_names();
    np.read_ages();
    Name_pairs copy_np{np};

    if (np == copy_np) {
        std::cout << "np == copy_np\n";
    } else if (np != copy_np) {
        std::cout << "np != copy_np\n";
    }
    std::cout << "np:\n" << np << "\n";
    std::cout << "copy_np:\n" << copy_np << "\n";

    np.sort();
    if (np == copy_np) {
        std::cout << "np == copy_np\n";
    } else if (np != copy_np) {
        std::cout << "np != copy_np\n";
    }
    std::cout << "np:\n" << np << "\n";
    std::cout << "copy_np:\n" << copy_np << "\n";

    keep_window_open();
    return 0;
} catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    keep_window_open();
    return 1;
} catch (...) {
    cerr << "exception\n";
    keep_window_open();
    return 2;
}