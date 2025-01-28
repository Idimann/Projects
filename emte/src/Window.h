#include <iostream>
#include <string>
#include <ncurses.h>
#include "Buffer.h"
#include "Settings.h"

class Window {
    public:
        std::vector<Buffer*> buffers;
        WINDOW* s_Window;
        WINDOW* t_Window;

        unsigned int x;
        unsigned int y;
        unsigned int x_Size;
        unsigned int y_Size;

        bool active;

        Window() {
            x = 0;
            y = 0;
            x_Size = COLS;
            y_Size = LINES - 1;
            init();
            //int wresize(WINDOW *win, int lines, int columns); 
        }

        Window(Buffer* buffer, const unsigned int x, const unsigned int y, const unsigned int x_Size, const unsigned int y_Size) {
            this->x = x;
            this->y = y;
            this->x_Size = x_Size;
            this->y_Size = y_Size;
            init();
            this->buffers.push_back(buffer);
        }

        ~Window() {
            delwin(t_Window);
            delwin(s_Window);
        }

        void move(const int x, const int y);
        void resize(const int x_Size, const int y_Size);
        void init();
        void draw(const bool active);
        void drawBuffer();
        void drawStatus();
        std::string parseStatusString();
        int proccessInput();
};
