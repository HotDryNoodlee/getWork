#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("in");
    if(!in) {
        cerr << "in error" << endl;
        return -1;
    }

    string lines;
    vector<string> words;
    while (getline(in, lines))
    {
        words.push_back(lines);
    }
    in.close();

    for (auto i = words.begin(); i != words.end(); i++) {
        istringstream line(*i);
        string word;
        while ( line >> word )
            cout << word << " ";
        cout << endl;
    }
    return 0;
}