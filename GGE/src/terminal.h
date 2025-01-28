#pragma once

#include <iostream>
#include <termios.h>

namespace Terminal {
    static struct termios old, current;

    void initTermios(bool echo);
    void resetTermios();
    
    char getch_(bool echo);

    char getch();
    char getche();
}
