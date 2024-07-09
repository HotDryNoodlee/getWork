#ifndef Q_H_
#define Q_H_
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

class TextQuery;


class QueryResult {
    friend ostream& print(ostream &, const QueryResult& );
public:
    typedef vector<string>::size_type line_no; 
    QueryResult(const string &s,
                shared_ptr<set<line_no>> ls,
                shared_ptr<vector<string>> pld) :
            query_word(s), line_set(ls), per_line_word(pld) { }
    void print(ostream &os,const QueryResult &qs) { }
private:
    string query_word;
    shared_ptr<set<line_no>> line_set;
    shared_ptr<vector<string>> per_line_word;
};


#endif