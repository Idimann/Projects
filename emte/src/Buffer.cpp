#include "Buffer.h"
#include "Utility.h"
#include "Settings.h"
#include "Mode.h"
#include "Window.h"
#include <complex>
#include <curses.h>
#include <functional>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <fstream>
#include <system_error>

#define ctl(x) ((x) & 0x1f)

Buffer* Buffer::loadFile(std::string fileName) {
    std::ifstream file(fileName);
    this->text.clear();

    this->file.name = fileName;
    this->file.can = true;
    free(this->mode);
    this->mode = new Main_Mode();

    if(!file.good()) {
        text.push_back("\n");

        return this;
    }

    this->name = fileName;

    std::string line;
    std::string multiChar = createMultiChar(' ', TAB_LENGTH);

    while(std::getline(file, line))
        text.push_back(replaceAll(line, "\t", multiChar) + '\n');

    file.close();

    return this;
}

void Buffer::init() {
    this->bound = 0;

    this->x = 0;
    this->y = 0;
    this->realX = x;
    this->spacePrefix = false;

    this->written = false;
    this->saved = false;
    this->did = false;
}

void Buffer::saveFile() {
    if(!this->file.can)
        return;

    if(this->file.name == "") {
        this->file.name = "untitled";
        int number = 1;
        while(std::ifstream(this->file.name).good()) {
            this->file.name = "untitled-" + std::to_string(number);
            ++number;
        }

        this->name = this->file.name;
    }

    std::ofstream writing(this->file.name.c_str());

    std::string multiChar = createMultiChar(' ', TAB_LENGTH);

    for(int i = 0; i < this->text.size(); i++)
        writing << replaceAll(this->text[i], multiChar, "\t");

    writing.close();

    this->written = false;
    this->saved = true;
    this->did = true;
}

void Buffer::moveUp() {
    if(y == bound && bound == 0)
        return;

    if(y <= bound + SCROLL_OFFSET && bound != 0)
        --bound;

    --y;
    x = realX;

    adjustX();
}

void Buffer::moveDown(const int lowerBound) {
    if(y == this->text.size() - 1)
        return;

    if(y >= bound + lowerBound - 2 - SCROLL_OFFSET && (this->text.size() - 1 - y > SCROLL_OFFSET))
        ++bound;

    ++y;
    x = realX;

    adjustX();
}

void Buffer::adjustX() {
    const unsigned int textLength = this->text[y].length() - 1;
    if(x > textLength)
        x = textLength;
}

void Buffer::moveRight() {
    if(x == this->text[y].length() - 1)
        return;

    ++x;
    realX = x;
}

void Buffer::moveLeft() {
    if(x == 0)
        return;

    --x;
    realX = x;
}

int Buffer::registerInput(Window* parent) {
    const int returning = wgetch(parent->t_Window);
    int checking = 0;

    switch(returning) {
        case CTRL(' '):
            free(this->mode);
            this->mode = new Main_Mode();
            this->spacePrefix = false;
            break;
        default:
            checking = this->mode->keymap(parent, returning);
            break;
    }

    if(!this->spacePrefix && checking >= CODE_DONE) {
        free(this->mode);
        this->mode = new Main_Mode();
        this->spacePrefix = false;
    }

    return checking;
}
