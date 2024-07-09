#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include "strblobptr.h"
#include "strblob.h"
using namespace std;

shared_ptr<vector<string>> Strblobptr::check(datasize i, const string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw runtime_error("unbound StrBlobPt");
    if (i >= (ret->size()))
        throw out_of_range(msg);
    return ret;
}


string &Strblobptr::deref() const
{
    auto p = check(curr, "out of range");
    return (*p)[curr];
}

Strblobptr &Strblobptr::incr()
{
    check(curr, "out of range");
    curr++;
    return *this;
}

Strblobptr &Strblobptr::decr()
{
    curr--;
    check(curr, "-1");
    return *this;
}

bool eq(const Strblobptr &lhs, const Strblobptr &rhs)
{
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock(); // 若底层的vector 是同一个
    if (l == r)                                    // 则两个指针都是空，或者指向相同元素时，它们相等
        return (!r || lhs.curr == rhs.curr);
    else
        return false; // 若指向不同vector，则不可能相等
}

bool neq(const Strblobptr &lhs, const Strblobptr &rhs) 
{ 
    return !eq(lhs, rhs); 
}