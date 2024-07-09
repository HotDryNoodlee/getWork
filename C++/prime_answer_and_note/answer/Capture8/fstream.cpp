#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "saleclass.h"
using namespace std;
// using namespace fstream;



// 8.1 2 3
istream& readss(istream& is){
    string v;
    while(is>>v, !is.eof()) {
        if(is.bad())
            throw runtime_error("io_error");
        if(is.fail()){
            cerr << "数据错误" << endl;
            is.clear();
            is.ignore(100, '\n');
            continue;
        }
        cout << v << endl;
    }
    is.clear();
    return is;
}

// 8.4
void readfl(string str){
    ifstream ifs(str, fstream::in);
    if (!ifs) {
        cerr << "can`t open file" << endl;
        return;
    }
    string line;
    vector<string> ans;
    while(getline(ifs, line)){
        ans.push_back(line);
    }
    ifs.close();

    for (auto i = ans.begin(); i != ans.end(); i++){
        cout << *i << endl;
    }
    return;
}


// 8.5
void readfw(string str){
    ifstream ifs(str, fstream::in);
    if (!ifs) {
        cerr << "can`t open file" << endl;
        return;
    }
    string line;
    vector<string> ans;
    while(ifs >> line){
        ans.push_back(line);
    }
    ifs.close();

    for (auto i = ans.begin(); i != ans.end(); i++){
        cout << *i << endl;
    }
    return;
}

// 8.7

int ftf(string inf, string outf)
{
    ifstream in(inf);
    if(!in){
        cerr << "in error" << endl;
        return -1;
    }
    ofstream out(outf, ofstream::app);
    if (!out){
        cerr << "out error" << endl;
        return -1;
    }
    CSales_data total;
    if(read(in, total)){
        CSales_data trans;
        while (read(in, trans)) {
            if (total.isbn() == trans.isbn()){
                total.combine(trans);
            } else {
                print(out, total) << endl;
                total = trans;
            }
        }
        print(out, total) << endl;
    } else {
        cerr << "no data" << endl;
    }
    return 0;
}




int main(){
    // readss(cin);
    // readfl("/home/zwl/workplace/study/facetest/prime_answer_and_note/answer/Capture7/C.h");
    // readfw("/home/zwl/workplace/study/facetest/prime_answer_and_note/answer/Capture7/C.h");
    // ftf("in", "out");
    
    // 8.8
    ostringstream p;
    p << "hello world" << endl;
    istringstream q(p.str());
    readss(q);
}