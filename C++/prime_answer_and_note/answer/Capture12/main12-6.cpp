// #include <iostream>
// #include <vector>
// #include <memory>
// using namespace std;

// shared_ptr<vector<int>> create()
// {
//     return make_shared<vector<int>>();
// }

// void read(shared_ptr<vector<int>> p)
// {
//     int v;
//     while (cin >> v)
//     {
//         p->push_back(v);
//     }
// }

// void print(shared_ptr<vector<int>> p)
// {
//     for (const auto &v : *p)
//     {
//         cout << v << ' ';
//     }
//     cout << endl;
// }

// int main()
// {
//     auto p = create();
//     if (!p)
//     {
//         cout << "out of memory" << endl;
//         return -1;
//     }
//     read(p);
//     print(p);

//     return 0;
// }

#include <iostream> 
#include <vector>  
using namespace std;  
vector<int> *new_vector(void) 
{   
    return new (nothrow) vector<int>; 
}  

void read_ints(vector<int> *pv) 
{   
    int v;    
    while (cin >> v)     
        pv->push_back(v); 
}  

void print_ints(vector<int> *pv) 
{   
    for (const auto &v : *pv)     
        cout << v << " ";   
    cout << endl; 
}  

int main(int argc, char **argv) 
{   
    vector<int> *pv = new_vector();   
    if (!pv) 
    {     
        cout << "内存不足！" << endl;     
        return -1;   
    }    
    read_ints(pv);
    print_ints(pv);
    delete pv;
    pv = nullptr;
    return 0;
}