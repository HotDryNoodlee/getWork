#ifndef T_H_
#define T_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include "QueryResult.h"
// class QueryResult;

class TextQuery {
public:
    typedef vector<string>::size_type line_no; 
    TextQuery(ifstream& );
    QueryResult query(const string&) const;
    void print_map(ostream&);
private:
    shared_ptr<vector<string>> text;
    map<string, shared_ptr<set<line_no>>> wm;
};


#endif