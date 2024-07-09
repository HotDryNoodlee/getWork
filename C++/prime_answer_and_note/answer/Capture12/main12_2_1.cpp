#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;


unique_ptr<char[]> cat(const string& s1, const string& s2){
    size_t len = s1.size() + s2.size();
    unique_ptr<char[]> du(new char[len]);
    for (size_t t = 0; t < len; t++) {
        if (t<s1.size()) {
            du[t] = s1[t];
        } else {
            du[t] = s2[t-s1.size()];
        }
    }
    return du;
}
int main () {
    string s1 = "zhu", s2 = "wenlong";
    unique_ptr<char[]> name = cat(s1, s2);
    size_t len = s1.size() + s2.size();
    for (size_t t = 0; t < len; t++) {
        cout << name[t] << endl;
    }
    // cout << name << " ";
    // cout << endl;
}