#include "strblobptr.h"
#include "strblob.h"
#include <iostream>
using namespace std;

int main() {
    Strblob b1;
    {
        Strblob b2 = {"zhu", "wen", "long"};
        b1 = b2;
        b2.push_back("god");
        cout << b2.size() << endl;
    }
    cout << b1.size() << endl;
    cout << b1.front() << " " << b1.back() << endl;

    const Strblob b3 = b1;
    cout << b3.front() << " " << b3.back() << endl;

    for (auto it = b1.begin(); !eq(it, b1.end()); it.incr()){
        cout << it.deref() << endl;
    } 
    return 0; 
}

