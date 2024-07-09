#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
using namespace std;

string make_plural(int n) {
    if (n <= 1) 
        return "time";
    else
        return "times";
}

int main(){
    ifstream infile("main.cpp");
    shared_ptr<vector<string>> text(new vector<string>);
    map<string, shared_ptr<set<int>>> word_map;
    string line;
    while(getline(infile, line)) {
        text->push_back(line);
        int n = text->size();
        istringstream iss(line);
        string word;
        while(iss >> word) {
            auto &word_lines = word_map[word];
            if (!word_lines)
                word_lines.reset(new set<int>);
            word_lines->insert(n-1);
        }
    }
    while (true) {
        string query;
        cin >> query;
        if(!cin.get() || query == "q")
            break;
        if (word_map.find(query) == word_map.end()) {
                cout << query << " ocurs " << "0" << " "
        << make_plural(0) << endl;
        }
        else {
            cout << query << " ocurs " << word_map[query]->size() << " "
            << make_plural(word_map[query]->size()) << endl;
            for (auto const &num : *(word_map[query])) {
                cout << "\t(line " << num+1 << " ): " << *(text->begin() + num) << endl;
            }
        }
    }
}