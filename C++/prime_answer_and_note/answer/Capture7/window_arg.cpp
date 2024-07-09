#include <string>
#include <iostream>
#include "window_arg.h"
#include "screen.h"
using namespace std;

void Window_arg::clear(Screen& befor)
{
    cout << "清理之前myScreen 的内容是：" << endl;
    cout << befor.content << endl;
    befor.content = "000";
    cout << "清理之后myScreen 的内容是：" << endl;
    cout << befor.content << endl;
}