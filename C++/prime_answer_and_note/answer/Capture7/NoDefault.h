#ifndef NODEFAULT_H_
#define NODEFAULT_H_

class NoDefault
{
private:
    int val;
public:
    NoDefault(int i): val(i) {}
    int get_val() {
        return val;
    }
};

#endif