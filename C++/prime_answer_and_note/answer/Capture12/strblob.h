#ifndef STRBLOB_H_
#define STRBLOB_H_
#include <memory>
#include <string>
#include <vector>
#include <initializer_list> 
// #include "strblobptr.h"
using namespace std;

class Strblobptr;

class Strblob
{
    friend class Strblobptr;
private:
    shared_ptr<vector<string>> data;
    void check(int i, const string &s) const;
public:
    typedef vector<string>::size_type datasize;
    Strblob();
    Strblob(initializer_list<string> l);
    datasize size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const string &s);
    void pop_back();
    string& front();
    string& back();
    const string& front() const;
    const string& back() const;
    Strblobptr end();
    Strblobptr begin();
};


#endif