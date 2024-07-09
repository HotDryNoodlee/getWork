#include "strblobptr.h"
#include "strblob.h"
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
using namespace std;


Strblob::Strblob():data(make_shared<vector<string>>()) { }
Strblob::Strblob(initializer_list<string> l) : data(make_shared<vector<string>>(l)){ }
void Strblob::check(int i, const string &s) const {
    if(i >= data->size()) {
        throw out_of_range(s);
    }
}
void Strblob::push_back(const string &s) {
    data->push_back(s);
}

void Strblob::pop_back() {
    check(0, "data empty");
    data->pop_back();
}

string& Strblob::front() {
    check(0, "data empty");
    return data->front();
}

string& Strblob::back() {
    check(0, "data empty");
    return data->back();
}

const string& Strblob::front() const {
    check(0, "data empty");
    return data->front();
}

const string& Strblob::back() const {
    check(0, "data empty");
    return data->back();
}

Strblobptr Strblob::end()
{
    return Strblobptr(*this, data->size());
}

Strblobptr Strblob::begin()
{
    return Strblobptr(*this);
}