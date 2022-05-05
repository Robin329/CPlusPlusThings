//
// Created by renbin jiang on 2022/5/6.
//
/*
        Exercise 1 - this uses my code from chapter 7, exercise 10
*/

// -----------------------------------------------------------------------------

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct Token {
    Token(char ch) : kind(ch), value(0) {}
    Token(char ch, int val) : kind(ch), value(val) {}
    Token(char ch, string s) : kind(ch), name(s) {}

    char kind;
    double value;
    string name;
};

// -----------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream() : full(0), buffer(0) {}
    Token_stream(istream&) : full(0), buffer(0) {}

    Token get();
    void unget(Token t) {
        buffer = t;
        full = true;
    }

    void ignore(char);

private:
    bool full;
    Token buffer;
};

// -----------------------------------------------------------------------------

// introduced in C++11, enums can now have a type instead of just being an integer
// it does add a little extra text but groups them together nicely
enum Symbol : const char {
    let = '#',
    quit = 'Q',
    print = ';',
    number = '8',
    name = 'a',
    sqrtCh = 's',
    powCh = 'p',
    constCh = 'c',
    help = 'H',
    newLine = '\n'
};

const string quitKey = "quit";
const string helpKey = "help";
const string sqrtKey = "sqrt";
const string letKey = "let";
const string powKey = "pow";
const string constKey = "const";

// -----------------------------------------------------------------------------

Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    char ch;

    cin.get(ch); // doesn't skip whitespace characters

    // check if ch is space
    while (isspace(ch)) {
        // if '\n' then return
        if (ch == newLine) return Token(print);

        // skip whitespace characters
        cin.get(ch);
    }
    switch (ch) {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case ',':
        case let:
        case print:
            return Token(ch);
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            cin.unget();
            int val;
            cin >> val;
            return Token(number, val);
        }
        default:
            if (isalpha(ch) || ch == '_') {
                string s;
                s += ch;

                while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
                cin.unget();

                if (s == letKey)
                    return Token(Symbol::let);
                else if (s == quitKey || s == "Q" || s == "q")
                    return Token(Symbol::quit);
                else if (s == sqrtKey)
                    return Token(Symbol::sqrtCh);
                else if (s == powKey)
                    return Token(Symbol::powCh);
                else if (s == constKey)
                    return Token(Symbol::constCh);
                else if (s == helpKey || s == "H" || s == "h")
                    return Token(Symbol::help);

                return Token(name, s);
            }
            error("Bad token");
    }
}

// -----------------------------------------------------------------------------

void Token_stream::ignore(char c) {
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    cout << "Enter ';' to continue. ";
    char ch;
    while (cin >> ch)
        if (ch == c) return;
}

// -----------------------------------------------------------------------------

struct Variable {
    Variable(string n, int v) : name(n), value(v) {}
    Variable(string n, int v, bool b) : name(n), value(v), isConst(b) {}

    string name;
    int value;
    bool isConst;
};

class Symbol_table {
public:
    Symbol_table() {}
    ~Symbol_table() {}

    vector<Variable> getNames() { return names; }
    void addName(string s, int d, bool b) { names.push_back(Variable(s, d, b)); }

    double get_value(string s);
    void set_value(string s, int d);
    int is_declared(string s);
    int isSetConst(string s);
    void reassignVariable(string name, int val, bool b);
    double define_name(string var, int val, bool isConst);

private:
    vector<Variable> names;
};

// -----------------------------------------------------------------------------

double Symbol_table::get_value(string s) {
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return names[i].value;
    error(s, " is undefined.");
}

// -----------------------------------------------------------------------------

void Symbol_table::set_value(string s, int d) {
    for (int i = 0; i < names.size(); ++i) {
        if (names[i].name == s) {
            names[i].value = d;
            return;
        }
    }

    error(s, " is undefined.");
}

// -----------------------------------------------------------------------------

int Symbol_table::is_declared(string s) {
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return true;
    return false;
}

// -----------------------------------------------------------------------------

int Symbol_table::isSetConst(string s) {
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) {
            if (names[i].isConst == true) return true;
        }
    return false;
}

// -----------------------------------------------------------------------------

void Symbol_table::reassignVariable(string name, int val, bool b) {
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == name) {
            names[i].value = val;
            names[i].isConst = b;
        }
    cout << "\nValue re-assigned." << endl;
}

// -----------------------------------------------------------------------------

// add {variable, value} to var_table
double Symbol_table::define_name(string var, int val, bool isConst) {
    if (is_declared(var)) {
        if (!isSetConst(var))
            Symbol_table::reassignVariable(var, val, isConst);
        else
            cout << "\nValue cannot be re-assigned." << endl;
        return val;
    }

    names.push_back(Variable{var, val, isConst});

    return val;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

Symbol_table st;

double expression(Token_stream& ts);

// -----------------------------------------------------------------------------

// handle sqrt(expression)
double squareRoot(Token_stream& ts) {
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            int d = narrow_cast<int>(expression(ts));

            // handle if d is 0 or negative
            if (d <= 0) error(to_string(d), " cannot be square routed.");

            t = ts.get();
            if (t.kind != ')') error(" ')' was expected.");
            return std::sqrt(d);
        }
        default:
            error(" '(' was expected.");
    }
}

// -----------------------------------------------------------------------------

// handle pow(expression, expression)
double powpow(Token_stream& ts) {
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            int d = narrow_cast<int>(expression(ts)); // first expression

            t = ts.get();
            if (t.kind != ',') error(" ',' was expected.");

            int d2 = narrow_cast<int>(expression(ts)); // second expression

            t = ts.get();
            if (t.kind != ')') error(" ')' was expected.");

            return std::pow(d, d2);
        }
        default:
            error(" '(' was expected.");
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

double primary(Token_stream& ts) {
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            int d = narrow_cast<int>(expression(ts));
            t = ts.get();
            if (t.kind != ')') error(" ')' was expected.");
            return d;
        }
        case '-':
            return -narrow_cast<int>(primary(ts));
        case Symbol::number:
            return t.value;
        case Symbol::name:
            return st.get_value(t.name);
        case Symbol::sqrtCh:
            return narrow_cast<int>(squareRoot(ts));
        case Symbol::powCh:
            return narrow_cast<int>(powpow(ts));
        default:
            error("primary expected.");
    }
}

// -----------------------------------------------------------------------------

double term(Token_stream& ts) {
    int left = narrow_cast<int>(primary(ts));
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '*':
                left *= narrow_cast<int>(primary(ts));
                break;
            case '/': {
                int d = narrow_cast<int>(primary(ts));
                if (d == 0) error("divide by zero. ");
                left /= d;
                break;
            }
            case '%': {
                int d = narrow_cast<int>(primary(ts));
                if (d == 0) error("Divide by zero. ");
                left = fmod(left, d);
                break;
            }
            default:
                ts.unget(t);
                return left;
        }
    }
}

// -----------------------------------------------------------------------------

double expression(Token_stream& ts) {
    int left = narrow_cast<int>(term(ts));
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '+':
                left += narrow_cast<int>(term(ts));
                break;
            case '-':
                left -= narrow_cast<int>(term(ts));
                break;
            default:
                ts.unget(t);
                return left;
        }
    }
}

// -----------------------------------------------------------------------------

double declaration(Token_stream& ts) {
    int d(0);
    Token t = ts.get();

    switch (t.kind) {
        case Symbol::name: {
            string name = t.name;
            if (st.is_declared(name)) {
                if (st.isSetConst(name)) error("variable is set to const and cannot be changed.");

                Token t2 = ts.get();
                if (t2.kind != '=') error(name, "= missing in declaration. ");

                d = narrow_cast<int>(expression(ts));
                st.reassignVariable(name, d, false);
            } else {
                Token t2 = ts.get();
                if (t2.kind != '=') error(name, "= missing in declaration. ");

                d = narrow_cast<int>(expression(ts));
                st.addName(name, d, false);
            }
            break;
        }
        case Symbol::constCh: {
            Token t = ts.get();
            if (t.kind != name) error("name expected in declaration. ");

            // check to see if already declared
            string name = t.name;
            if (st.is_declared(name)) {
                // now check to see if it was const
                if (st.isSetConst(name)) {
                    error("That variable cannot be changed.");
                } else {
                    Token t2 = ts.get();
                    if (t2.kind != '=') error(name, "= missing in declaration.");

                    // variable wasn't const, allow it to be overwritten && set to const
                    d = narrow_cast<int>(expression(ts));
                    st.reassignVariable(name, d, true);
                }
            } else {
                // no existing variable - create a new const one
                Token t2 = ts.get();
                if (t2.kind != '=') error(name, "= missing in declaration. ");

                d = narrow_cast<int>(expression(ts));
                st.addName(name, d, true);
            }
            break;
        }
        default:
            error("name expected in declaration or const name.");
            break;
    }

    return d;
}

// -----------------------------------------------------------------------------

void printHelp() {
    cout << "//------------------------------------------------------------------------------//"
         << endl;
    cout << "Operators available: {}, (), +, -, /, *" << endl;
    cout << "Pre-defined names: k = 1000 || sqrt() || pow(,)" << endl;
    cout << "Define your own names using " << letKey << " name = number;" << endl;
    cout << "Define const names using " << letKey << " const name = number;" << endl;
    cout << "use enter to print and 'exit' to quit" << endl;
    cout << "//------------------------------------------------------------------------------//"
         << endl;
}

// -----------------------------------------------------------------------------

// forward declare functions
void calculate();

double statement(Token_stream& ts) {
    Token t = ts.get();
    switch (t.kind) {
        case Symbol::let:
            return declaration(ts);
        default:
            ts.unget(t);
            return expression(ts);
    }
}

// -----------------------------------------------------------------------------

void clean_up_mess(Token_stream& ts) {
    ts.ignore(print);
}

// -----------------------------------------------------------------------------

const string prompt = "> ";
const string result = "= ";

// -----------------------------------------------------------------------------

void calculate() {
    Token_stream ts;
    cout << prompt;

    while (true) try {
            Token t = ts.get();

            while (t.kind == Symbol::print) {
                cout << prompt;
                t = ts.get();
            }

            if (t.kind == Symbol::help) {
                printHelp();
                cin.clear();
                cin.ignore(); // flush out everything in cin to 'reset' calculator
                cout << prompt;
                t = ts.get();
            }

            if (t.kind == Symbol::quit) return;
            ts.unget(t);

            cout << result << statement(ts) << endl;
        } catch (runtime_error& e) {
            cerr << e.what() << endl;
            clean_up_mess(ts);
        }
}

// -----------------------------------------------------------------------------

int main() try {
    // pre-defined names
    st.define_name("k", 1000, true);

    cout << "//------------------------------------------------------------------------------//"
         << endl;
    cout << "Welcome to our simple calculator.\nPress H for instructions." << endl;
    cout << "//------------------------------------------------------------------------------//"
         << endl;

    calculate();
    return 0;
} catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    char c;
    while (cin >> c && c != ';')
        ;
    return 1;
} catch (...) {
    cerr << "exception\n";
    char c;
    while (cin >> c && c != ';')
        ;
    return 2;
}
