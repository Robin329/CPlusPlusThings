//
// Created by renbin jiang on 2022/5/12.
//
#include "std_lib_facilities.h"

class Punct_stream {
public:
    Punct_stream(istream& is) : m_source(is), m_sensitive(true) {}
    void whitespace(const string& s) { m_white = s; } // make s the whitespace set
    void add_white(char c) { m_white += c; }          // add to th whitespace set
    bool is_whitespace(char c);                       // is c in the whitespace set?

    void case_sensitive(bool b) { m_sensitive = b; }
    bool is_case_sensitive() const { return m_sensitive; }

    Punct_stream& operator>>(string& s);
    operator bool();

private:
    istream& m_source;
    bool m_sensitive;
    istringstream m_buffer;
    string m_white;
};

Punct_stream& Punct_stream::operator>>(string& s) {
    while (!(m_buffer >> s)) {
        if (m_buffer.bad() || !m_source.good()) {
            //            cout << "Error, input err!\n";
            return *this;
        }
        m_buffer.clear();

        string line;
        getline(m_source, line); // get a line from source
        for (int i{}; i < line.size(); ++i) {
            if (is_whitespace(line[i]))
                line[i] = ' ';
            else if (!m_sensitive)
                line[i] = tolower(line[i]);
            //            cout << "line[" << i << "]:" << line[i] << endl;
        }
        m_buffer.str(line);
    }
    return *this;
}

bool Punct_stream::is_whitespace(char c) {
    for (int i{}; i < m_white.size(); ++i)
        if (c == m_white[i]) return true;
    return false;
}

Punct_stream::operator bool() {
    return !(m_source.fail() || m_source.bad() && m_source.good());
}

int main() {
    Punct_stream ps(cin);
    ps.whitespace(";:,.~!()*&^%$#@:\";></?|{}[]");
    ps.case_sensitive(false);
    cout << "Please enter words\n";
    vector<string> vs;
    string word;
    while (ps >> word) {    // Ctrl + D end input
        vs.push_back(word); // read words
                            //        cout << "word:" << word << endl;
    }

    sort(vs.begin(), vs.end()); // sort
    for (int i = 0; i < vs.size(); i++) {
        if (i == 0 || vs[i] != vs[i - 1]) cout << vs[i] << endl;
    }
    return 0;
}