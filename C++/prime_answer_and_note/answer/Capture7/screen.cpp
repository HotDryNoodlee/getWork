
#include "screen.h"


Screen& Screen::set(char ch){
    content[cursor] = ch;
    return *this;
}
Screen& Screen::display(){
    cout << content;
    return *this;
}

Screen& Screen::move(unsigned r, unsigned c) {
    cursor = r * weight + c;
    return *this;
}

Screen::pos Screen::size() const
{
    return height*weight;
}