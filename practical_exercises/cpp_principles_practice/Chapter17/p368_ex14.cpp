//
// Created by renbin jiang on 2022/5/24.
//
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct God {
    God() {}
    God(string n, string m = "", string v = "", string w = "")
          : name(n), mythology(m), vehicle(v), weapon(w) {}

    string name, mythology, vehicle, weapon;
};

// -----------------------------------------------------------------------------

class SingleLink {
public:
    SingleLink(God g, SingleLink* p = nullptr, SingleLink* s = nullptr)
          : m_god(g), m_value(g.name), m_succ(s) {}

    SingleLink* insert(SingleLink* n);
    SingleLink* addAtPosition(SingleLink* n, int p);
    SingleLink* advance(int n);
    void erase(SingleLink* n);
    SingleLink* find(const string& s);
    SingleLink* next();
    string getName() { return m_god.name; }
    void setName(string n) { m_god.name = n; }

private:
    God m_god;
    SingleLink* m_succ;
    string m_value;
};

// -----------------------------------------------------------------------------

// always inserts at end
SingleLink* SingleLink::insert(SingleLink* n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;

    SingleLink* temp = this;
    while (temp->next()) {
        // advance til we find the tail of the list
        temp = temp->next();
    }

    temp->m_succ = n;

    return n;
}

// -----------------------------------------------------------------------------

// inserts after a given position
SingleLink* SingleLink::addAtPosition(SingleLink* n, int p) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;

    // start at first and advance p, then insert
    SingleLink* temp = advance(p);
    n->m_succ = temp->m_succ;
    temp->m_succ = n;

    return temp;
}

// -----------------------------------------------------------------------------

SingleLink* SingleLink::advance(int n) {
    if (this == nullptr) return nullptr;

    SingleLink* temp = this;
    for (int i = 0; i < n; ++i) temp = temp->m_succ;

    return temp;
}

// -----------------------------------------------------------------------------

void SingleLink::erase(SingleLink* n) {
    // find the previous to n
    SingleLink* temp = this;
    while (temp->next()) {
        if (temp->next() == n)
            break;
        else
            temp = temp->next();
    }

    if (n->m_succ) temp->m_succ = n->m_succ;
    n->m_succ = nullptr;
}

// -----------------------------------------------------------------------------

SingleLink* SingleLink::find(const string& s) {
    SingleLink* temp = this;
    while (temp) {
        if (temp->m_value == s) return temp;
        temp = temp->m_succ;
    }
    return nullptr;
}

// -----------------------------------------------------------------------------

SingleLink* SingleLink::next() {
    return m_succ;
}

// -----------------------------------------------------------------------------

void print_all(SingleLink* p) {
    SingleLink* first = p;
    cout << "{";
    while (first) {
        cout << first->getName();
        if (first = first->next()) cout << ", ";
    }
    cout << "}" << endl;
}

// -----------------------------------------------------------------------------

int main() {
    SingleLink* norse_gods = new SingleLink{God("Thor")};
    norse_gods->insert(new SingleLink{God("Odin")});
    norse_gods->insert(new SingleLink{God("Zeus")});
    norse_gods->insert(new SingleLink{God("Freia")});

    SingleLink* greek_gods = new SingleLink{God("Hera")};
    greek_gods->insert(new SingleLink{God("Athena")});
    greek_gods->insert(new SingleLink{God("Mars")});
    greek_gods->insert(new SingleLink{God("Poseidon")});

    // print out the lists
    print_all(norse_gods);
    print_all(greek_gods);

    // correct name of god of war
    SingleLink* p = greek_gods->find("Mars");
    if (p) p->setName("Ares");

    // move zeus to correct pantheon
    SingleLink* p2 = norse_gods->find("Zeus");
    if (p2) {
        if (p2 == norse_gods) norse_gods = p2->next();
        norse_gods->erase(p2);
        greek_gods->insert(p2);
    }

    // print out the lists
    print_all(norse_gods);
    print_all(greek_gods);

    //    keep_window_open();
    return 0;
}
