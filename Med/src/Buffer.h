#include <curses.h>
#include <ncurses.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <map>

#pragma once

/*
    Keys are represented using bits: (10 bits at a time)
    This means you can represent a maximum of 6 keys pressed one after the other in a single Keymapping
    Example:
        |0000100000=' '|0001100110='f'|001110011='s'| <- This represents the keybinding in vim writing "<space>fs"
*/
typedef unsigned long KeyMapping;

struct WindowInformation {
    unsigned int x;
    unsigned int y;
    unsigned int xSize;
    unsigned int ySize;

    WindowInformation(const unsigned int x, const unsigned int y, const unsigned int xSize, const unsigned int ySize) {
        this->x = x;
        this->y = y;
        this->xSize = xSize;
        this->ySize = ySize;
    }
};

struct TextColor {
    short fg;
    short bg;

    TextColor(const short fg, const short bg) {
        this->fg = fg;
        this->bg = bg;
    }

    TextColor() {
        this->fg = 1;
        this->bg = -1;
    }
};

typedef std::vector<long> TextColors;

typedef std::tuple<bool, bool> 
(*FunctionPointer) (struct Buffer& buffer, struct WindowInformation& wInfo, std::vector<std::string> args);

typedef struct Mode {
    bool cursor;
    std::map<KeyMapping, std::string> map;
    
    Mode(bool cursor) {
        this->cursor = cursor;
    }
} Mode;

namespace Modes {
    inline Mode* Main = new Mode(true);
    inline Mode* Command = new Mode(false);

    extern void init();
}

#define KEY_ESCAPE 27
#define KEY_ALT KEY_ESCAPE
#define KEY_CTRL(X) ((X) & 0x1f)
#define KEY_MODE_EXIT 0b1111111111
#define KEY_ENTER_U '\n'
#define KEY_BACKSPACE_U 127


namespace Keys {
    extern KeyMapping construct(const std::vector<unsigned short> input);
}

namespace Buffers {
    extern std::string loadFile(const char* fileName);
    extern unsigned int getUntilNewLine(Buffer &buffer, const unsigned int index);
    extern unsigned int getBackToNewLine(Buffer &buffer, const unsigned int index);
    extern bool isNewLine(Buffer &buffer, const unsigned int index);
    extern unsigned int getLineSize(Buffer &buffer);
    extern unsigned int getLineSizeBackwards(Buffer &buffer);
    extern int getUntilWord(Buffer &buffer, const unsigned int index);
    extern int getUntilWordBackwards(Buffer &buffer, const unsigned int index);
    extern bool isNewLineTimes(Buffer &buffer, unsigned int times, const unsigned int index);
    extern int getY(Buffer &buffer, const unsigned int size, const unsigned int index);
    extern void moveTillNoWhitespace(Buffer &buffer, const unsigned int index);
    extern unsigned int getUntilNewLineWithStartPos(Buffer &buffer, const unsigned int startPos);
    extern void add(Buffer* buffer);
    extern Buffer* get(const unsigned int number);
    extern Buffer* getLast();
}

struct TextPosition {
    unsigned int position1;
    unsigned int position2;
    unsigned int x1;
    unsigned int x2;
    bool moving;

    unsigned int getPosition() {
        return moving ? position2 : position1;
    }

    unsigned int getX() {
        return moving ? x2 : x1;
    }

    void swapPrevious() {
        if(moving) {
            position1 = position2;
            x1 = x2;
        }
        else {
            position2 = position1;
            x2 = x1;
        }
    }

    void setPosition(const int position) {
        if(moving)
            position2 = position;
        else
            position1 = position;
    }

    void setX(const int x) {
        if(moving)
            x2 = x;
        else
            x1 = x;
    }

    void setPositionOp(const int position) {
        if(!moving)
            position2 = position;
        else
            position1 = position;
    }

    void setXOp(const int x) {
        if(!moving)
            x2 = x;
        else
            x1 = x;
    }

    void addPosition(const int position) {
        if(moving)
            position2 += position;
        else
            position1 += position;
    }

    void addX(const int x) {
        if(moving)
            x2 += x;
        else
            x1 += x;
    }
};

typedef struct Buffer {
    std::string name;
    std::string text;
    TextColors colors;
    std::vector<struct TextPosition> position;
    unsigned int bound;
    std::string fileName;
    bool isFile;
    Mode** mode;
    
    Buffer(std::string name) {
        this->name = name;
        this->text = "\n";
        this->colors = {COLOR_PAIR(0)};

        this->position = {
            {
                .position1 = 0,
                .position2 = 0,
                .x1 = 0,
                .x2 = 0,
                .moving = false,
            },
        };

        this->bound = 0;
        this->mode = &Modes::Main;
        this->isFile = false;
        this->fileName = "";
    }

    void loadFile(const std::string fileName) {
        this->position = {
            {
                .position1 = 0,
                .position2 = 0,
                .x1 = 0,
                .x2 = 0,
                .moving = false,
            },
        };

        this->text = Buffers::loadFile(fileName.c_str());

        this->colors.clear();
        for(int i = 0; i < this->text.length(); i++)
            this->colors.push_back(COLOR_PAIR(0));

        this->fileName = fileName;
        this->name = this->fileName;
        this->isFile = true;
    }
} Buffer;
