#include "X.h"
#include <iostream>
#include <memory>
#include <vector>

int main()
{
    cout << "局部: ";
    X x;
    cout << endl;

    cout << "非引用参数传递：";
    f1(x);
    cout << endl;

    cout << "引用参数传递：";
    f2(x);
    cout << endl;

    cout << "动态分配：";
    X *px = new X;
    cout << endl;

    cout << "添加到容器中：";
    vector<X> vx;
    vx.push_back(x);
    cout << endl;

    cout << "释放动态分配对象：";
    delete px;
    cout << endl;

    cout << "间接初始化和赋值：";
    X y = x;
    y = x;
    cout << endl;

    cout << "程序结束：";
    return 0;
}