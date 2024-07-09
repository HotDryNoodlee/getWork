#ifndef C_H_
#define C_H_

class NoDefault;

class C
{
private:
    NoDefault member;

public:
    C(int i = 0):member(i) {}
    NoDefault get_member() {
        return member;
    }
};



#endif