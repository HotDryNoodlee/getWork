#include <iostream>
#include "capter.h"
using namespace std;

int main(){


    // int num;
    // cout << "please input a num :" << endl;
    // cin >> num;
    // cout << num << "的阶乘为:" << fact(num) << endl;
    // return 0;

    
    int a = 1, b = 2;
    int *p = &a, *q = &b;
    cout << "交换前：" << " a= " << a << " b= " << b << endl;
    myswap(p, q);
    cout << "交换后：" << " a= " << a << " b= " << b << endl;

    
	// int i = 0;//非常量int对象
	// const int ci = 0;//常量int对象

	// const int &a = i;//指向常量的引用（一般称为常量引用），绑定到非常量
	// const int &b = ci;//指向常量的引用，绑定到常量
    // cout << i << a << ci << b << endl;
    // i = 2;
    // cout << i << a << ci << b << endl;
}

// #include <iostream> 
// #include <vector> 
// #define NDEBUG
// using namespace std; // 递归函数输出vector<int>的内容 
// void print(vector<int> vInt, unsigned index) 
// {     
//     unsigned sz = vInt.size();   // 设置在此处输出调试信息     
//     #ifndef NDEBUG     
//     cout << "vector 对象的大小是：" << sz << endl;     
//     #endif // NDEBUG     
//     if(!vInt.empty() && index < sz)     
//     {         
//         cout << vInt[index] << endl;         
//         print(vInt, index + 1);     
//     } 
// }  
// int main() 
// {     
//     vector<int> v = {1,3,5,7,9,11,13,15};     
//     print(v, 0);     
//     return 0; 
// } 