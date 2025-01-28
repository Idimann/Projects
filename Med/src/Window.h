#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "Buffer.h"

#pragma once

class Window {
    private:
        WINDOW* textWindow = nullptr;
        WINDOW* statusWindow = nullptr;

        KeyMapping currentMapping = 0;
        unsigned char keymapCounting = 0;

        ~Window() {
            delwin(textWindow);
            delwin(statusWindow);
            delete buffer;
        }

        void initWindows();
        void drawText();
        void drawStatus();

    public:
        unsigned int x;
        unsigned int y;
        unsigned int xSize;
        unsigned int ySize;

        Buffer* buffer;

        Window(Buffer* buffer) {
            x = 0;
            y = 0;
            ySize = LINES - 1;
            xSize = COLS;
            this->buffer = buffer;
            initWindows();
        }

        Window(Buffer* buffer, const unsigned int x, const unsigned int y,
                const unsigned int xSize, const unsigned int ySize) {
            this->x = x;
            this->y = y;
            this->xSize = xSize;
            this->ySize = ySize;
            this->buffer = buffer;
            initWindows();
        }

        void resize();
        void processInput(bool cursor);
        void draw();
};

namespace Windows {
    extern void add(Window* window);
    extern Window* getLast();
    extern Window* get(const unsigned int number);
    extern Window* get();
    extern void setCurrent(const unsigned int setTo);
    extern unsigned int getCurrent();
    extern unsigned int getSize();
    extern void drawAll();
    extern void initCommandStatus();
    extern void drawCommandStatus(bool cursor);
}
