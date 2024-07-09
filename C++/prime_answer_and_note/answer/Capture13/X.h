#ifndef X_H_
#define X_H_
#include <memory>
#include <string>
#include <iostream>
using namespace std;

struct X
{
    X() { cout << "X()" << endl; }
    X(const X &) { cout << "X(const X&)" << endl; }
    X &operator=(const X &rhs)
    {
        cout << "X& operator=(const X& rhs)" << endl;
        return *this;
    }
    ~X()
    {
        cout << "~X()" << endl;
    }
};

void
f1(X x)
{
}
void f2(X &x)
{
}
#endif

