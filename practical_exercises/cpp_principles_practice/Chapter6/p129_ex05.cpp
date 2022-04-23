//
// Created by renbin jiang on 2022/4/23.
//
#include "std_lib_facilities.h"
//written by Jtaim
//date 21 Nov 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
A program that checks if a sentence is correct.
According to the grammar from 6.4.1
Assume sentence is terminated " . " surrounded by whitespace
Reply "ok" or "not ok"

Sentence:
  Noun Verb						          // e.g., C++ rules
  Sentence Conjunction Sentence	// e.g., Birds fly but fish swim
Conjunction:
  "and"
  "or"
  "but"
Verb:
  "rules"
  "fly"
  "swim"
Noun:
  "birds"
  "fish"
  "c++"
Article:
  "the"
*/


//------------------------------------------------------------------------------
class str
{
private:
    string in_str;
public:
    str() {}
    str(string s) : in_str(s) {}
    bool compare(const vector<string>& vs);
};

bool str::compare(const vector<string>& vs)
{
    return (find(begin(vs), end(vs), in_str) != end(vs));
}

//------------------------------------------------------------------------------
class str_stream
{
private:
    bool full;
    str buffer;
public:
    stringstream stream;
    
    str_stream() : full(false), buffer() {}
    str get();
    void putback(str old);
};

//------------------------------------------------------------------------------
void str_stream::putback(str s)
{
    // precondition check
    if (full)
    {
        error("putback() into full buffer");
    }
    buffer = s;
    full = true;
}

//------------------------------------------------------------------------------
str str_stream::get()
{
    // do we already have a string ready
    if (full)
    {
        full = false;
        return buffer;
    }
    string new_string;
    stream >> new_string;
    transform(new_string.begin(), new_string.end(), new_string.begin(), [](unsigned char c) { return narrow_cast<char>(tolower(c)); });
    return str(new_string);
}

//------------------------------------------------------------------------------
str_stream ss;	// provides get() and putback()
//------------------------------------------------------------------------------
bool conjunctions();
//------------------------------------------------------------------------------
bool article();
//------------------------------------------------------------------------------
bool noun();
//------------------------------------------------------------------------------
bool verb();
//------------------------------------------------------------------------------
int main()
{
    try
    {
        cout << "Enter a sentence terminated with \" . \" surrounded by whitespace\n";
        string input;
        getline(cin, input);
        ss.stream.str(input);
        if (conjunctions())
        {
            cout << "Sentence is OK.\n";
        }
        else
        {
            cout << "Sentence is Not OK.\n";
        }
        keep_window_open();
        return 0;
    }
    catch (exception& e)
    {
        cerr << "error: " << e.what() << '\n';
        keep_window_open();
        return 1;
    }
    catch (...)
    {
        cerr << "Oops: unknown exception!\n";
        keep_window_open();
        return 2;
    }
}

//------------------------------------------------------------------------------
bool conjunctions()
{
    bool check = verb();
    if (check)
    {
        str s = ss.get();
        vector<string> test{"and","or","but"};
        if (s.compare(test))
        {
            check = verb();
        }
        else
        {
            check = s.compare({"."});
        }
    }
    return check;
}

//------------------------------------------------------------------------------
bool verb()
{
    bool check = noun();
    if (check)
    {
        str s = ss.get();
        vector<string> test{"rules","fly","swim"};
        check = s.compare(test);
    }
    return check;
}

//------------------------------------------------------------------------------
bool noun()
{
    article();
    vector<string> test{"birds","fish","c++"};
    str s = ss.get();
    // check for a noun
    return s.compare(test);
}

//------------------------------------------------------------------------------
bool article()
{
    vector<string> test{"the"};
    auto s = ss.get();
    auto check = s.compare(test);
    if (check == false)
    {
        ss.putback(s);
    }
    return check;
}
