#include <iostream>
#include "terminal.h"

static struct termios old, current;

void Terminal::initTermios(bool echo) {
    tcgetattr(0, &old);
    current = old;
    current.c_lflag &= ~ICANON;

    if(echo)
        current.c_lflag |= ECHO;
    else
        current.c_lflag &= ~ECHO;

    tcsetattr(0, TCSANOW, &current);
}

void Terminal::resetTermios() {
    tcsetattr(0, TCSANOW, &old);
}

char Terminal::getch_(bool echo) {
    initTermios(echo);
    char ch = getchar();
    resetTermios();

    return ch;
}

char Terminal::getch() {
    return getch_(false);
}

char Terminal::getche() {
    return getch_(true);
}
