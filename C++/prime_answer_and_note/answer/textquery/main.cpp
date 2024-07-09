#include "TextQuery.h"
#include "QueryResult.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string make_plural(int n) {
    if (n <= 1) 
        return "time";
    else
        return "times";
}
ostream &print(ostream &os,const QueryResult &qs) {
    os << qs.query_word << " ocurs " << qs.line_set->size() << " "
        << make_plural(qs.line_set->size()) << endl;
    for (auto const &num : *qs.line_set) {
        os << "\t(line " << num+1 << " ): " << *(qs.per_line_word->begin() + num) << endl;
    }
    return os;
}
void runQueries(string word) {

}
int main() {
    string word;
    ifstream data("/home/zwl/workplace/study/huawei/C++/prime_answer_and_note/answer/textquerytext/TextQuery.cpp");
    TextQuery tq(data);
    tq.print_map(cout);
    while(true) {
        cin >> word;
        if(!cin.get() || word == "q")
            break;
        print(cout, tq.query(word));
    }
}