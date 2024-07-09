#ifndef SCREEN_H_
#define SCREEN_H_
#include <string>
#include <iostream>
#include "window_arg.h"
using namespace std;

// class Window_arg;

class Screen
{
public:
    typedef string::size_type pos;
private:
    unsigned height = 0, weight = 0;
    unsigned cursor = 0;
    string content;

public:
    Screen() = default;
    Screen(unsigned ht, unsigned wt) : height(ht), weight(wt), content(ht*wt, ' ')  { }
    Screen(unsigned ht, unsigned wt, char c) : height(ht), weight(wt), content(ht*wt, c)  { }

    friend void Window_arg::clear(Screen& befor);

    Screen& move(unsigned, unsigned);
    Screen& set(char);
    Screen& display();
    pos size() const;
    
};


#endif