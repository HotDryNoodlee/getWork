#ifndef STRBLOBPTR_H_
#define STRBLOBPTR_H_
#include <memory>
#include <string>
#include <vector>
#include "strblob.h"
using namespace std;



class Strblobptr
{
    friend bool eq(const Strblobptr&, const Strblobptr&);

public:
    typedef vector<string>::size_type datasize;
    Strblobptr(): curr(0) { }   
    Strblobptr(Strblob &a,  datasize sz = 0): wptr(a.data), curr(sz) { }
    string& deref() const;
    Strblobptr& incr();
    Strblobptr& decr();

private:
    weak_ptr<vector<string>> wptr;
    shared_ptr<vector<string>> check(datasize i, const string &msg) const;
    datasize curr;
};

#endif