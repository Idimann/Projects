#pragma once

#include <curses.h>
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include "Mode.h"

struct Conditional_Filename {
    std::string name;
    bool can;
};

class Buffer {
    public:
        std::vector<std::string> text;
        unsigned int x, y, bound, realX;
        struct Conditional_Filename file;
        bool spacePrefix;
        std::string name;

        Mode* mode = new Main_Mode();

        bool written;
        bool saved;
        bool did;

        //int toplimit, bottomlimit;
        
        Buffer(std::string name, const std::vector<std::string> text, const int x, const int y) {
            this->text = text;
            this->file.can = false;
            this->name = name;
            init();
        }

        Buffer(std::string name, const std::vector<std::string> text) {
            this->text = text;
            this->file.can = false;
            this->name = name;
            init();
        }

        Buffer(std::string name) {
            this->text = std::vector<std::string>({"\n"});
            this->file.can = false;
            this->name = name;
            init();
        }

        Buffer() {
            this->text = std::vector<std::string>({"\n"});
            this->file.can = false;
            this->name = "scratch";
            init();
        }

        ~Buffer() {
            delete mode;
        }

        void init();

        Buffer* loadFile(std::string fileName);
        void saveFile();

        int registerInput(Window* parent);

        void moveUp();
        void moveDown(const int lowerBound);
        void moveRight();
        void moveLeft();
        void adjustX();
};
