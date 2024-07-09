#ifndef HASHPTR_H_
#define HASHPTR_H_
#include <memory>
#include <string>
using namespace std;

class HashPtr {
public: 
    HashPtr(const string& s = string())
        : ps(new string(s)), i(0) { }
    
    HashPtr(const HashPtr& rhs) {
        ps = new string(*rhs.ps);
        i = rhs.i
    }
    HashPtr& operator=(const HashPtr& rhs) {
        auto newps = new string(*rhs.ps);
        delete ps;
        ps = newps;
        i = rhs.i;
        return *this;
    }
    ~HashPtr() {
        delete ps;
    }
private:
    string *ps;
    int i;
}

#endif