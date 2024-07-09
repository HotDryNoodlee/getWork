#include "TextQuery.h"
#include "QueryResult.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
using namespace std;

TextQuery::TextQuery(ifstream& inf){
    text.reset(new vector<string>);
    string line;
    while(getline(inf, line)) {
        text->push_back(line);
        line_no n = text->size() - 1;
        istringstream one_line_word(line);
        string word;
        while(one_line_word >> word) {
            auto &word_line_no = wm[word];
            if (!word_line_no) 
                word_line_no.reset(new set<line_no>);
            word_line_no->insert(n);
        }
    }
}

void TextQuery::print_map(ostream& os){
    for (auto const& word : wm) {
        os << word.first << " ";
        for (auto const& index : *(word.second)) 
            os << index << " ";
        os << endl;
    }
}


QueryResult TextQuery::query(const string &query_word) const {
    static shared_ptr<set<line_no>> no_word(new set<line_no>);

    auto query_word_lines = wm.find(query_word);

    if (query_word_lines == wm.end())
        return QueryResult(query_word, no_word, text);
    else
        return QueryResult(query_word, query_word_lines->second, text);
}