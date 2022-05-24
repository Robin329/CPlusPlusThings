//
// Created by renbin jiang on 2022/5/23.
//
#include "std_lib_facilities.h"

class Link {
public:
    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
          : m_value(v), m_prev(p), m_succ(s) {}
    virtual ~Link(){}
    Link* insert(Link* n);
    Link* add(Link* n);
    Link* erase();
    Link* find(const string& s);
    const Link* find(const string& s) const;
    Link* advance(int n) const;
    Link* next() const { return m_succ; }
    Link* previous() const { return m_prev; }
    string getName() const { return m_value; }
    void setName(string value) { m_value = value; }

private:
    Link* m_prev;
    Link* m_succ;

    string m_value;
};

// -----------------------------------------------------------------------------

Link* Link::insert(Link* n) {
    if (n == nullptr) return this;

    // this object comes after n
    n->m_succ = this;

    if (m_prev) m_prev->m_succ = n;

    // this objects predecessor becomes n's predecessor
    n->m_prev = m_prev;

    // n becomes this object's predecessor
    m_prev = n;

    return n;
}

// -----------------------------------------------------------------------------

Link* Link::add(Link* n) {
    // much like insert

    return nullptr;
}

// -----------------------------------------------------------------------------

Link* Link::erase() {
    if (m_succ) m_succ->m_prev = m_prev;
    if (m_prev) m_prev->m_succ = m_succ;

    return m_succ;
}

// -----------------------------------------------------------------------------

Link* Link::find(const string& s) {
    Link* temp = this;
    while (temp) {
        if (temp->m_value == s) return temp;
        temp = temp->m_succ;
    }
    return nullptr;
}

// -----------------------------------------------------------------------------

const Link* Link::find(const string& s) const {
    return nullptr;
}

// -----------------------------------------------------------------------------

Link* Link::advance(int n) const {
    Link* temp = const_cast<Link*>(this);
    if (temp == nullptr) return nullptr;
    if (0 < n) {
        while (n--) {
            if (temp->m_succ == nullptr) return nullptr;
            temp = temp->m_succ;
        }
    } else if (n < 0) {
        while (n++) {
            if (temp->m_prev == nullptr) return nullptr;
            temp = temp->m_prev;
        }
    }

    return temp;
}
// -----------------------------------------------------------------------------

void print_all(Link* p) {
    cout << "{";
    while (p) {
        cout << p->getName();
        if (p = p->next()) cout << ", ";
    }
    cout << "}" << endl;
}

// -----------------------------------------------------------------------------

int main() {
    Link* norse_gods = new Link{"Thor"};
    norse_gods = norse_gods->insert(new Link{"Odin"});
    norse_gods = norse_gods->insert(new Link{"Zeus"});
    norse_gods = norse_gods->insert(new Link{"Freia"});

    Link* greek_gods = new Link{"Hera"};
    greek_gods = greek_gods->insert(new Link{"Athena"});
    greek_gods = greek_gods->insert(new Link{"Mars"});
    greek_gods = greek_gods->insert(new Link{"Poseidon"});

    // correct name of god of war
    Link* p = greek_gods->find("Mars");
    if (p) p->setName("Ares");

    // move zeus to correct pantheon
    Link* p2 = norse_gods->find("Zeus");
    if (p2) {
        if (p2 == norse_gods) norse_gods = p2->next();
        p2->erase();
        greek_gods = greek_gods->insert(p2);
    }

    // print out the lists
    print_all(norse_gods);
    print_all(greek_gods);

    //    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
