#include <cmath>
#include <exception>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Commands.h"
#include "Settings.h"
#include "Utility.h"
#include "Window.h"
#include "Buffer.h"

std::vector<Window*> windowList = std::vector<Window*>();
unsigned int currentWindow = 0;
WINDOW* commandStatus;

namespace Windows {
    extern void add(Window* window) {
        windowList.push_back(window);
    }

    extern Window* getLast() {
        return windowList[windowList.size() - 1];
    }

    extern Window* get(const unsigned int number) {
        return windowList[number];
    }

    extern Window *get() {
        return get(currentWindow);
    }

    extern void setCurrent(const unsigned int setTo) {
        currentWindow = setTo;
    }

    extern unsigned int getCurrent() {
        return currentWindow;
    }

    extern unsigned int getSize() {
        return windowList.size();
    }

    extern void drawAll() {
        for(unsigned int i = 0; i < windowList.size(); i++) {
            windowList[i]->draw();
        }
    }

    extern void initCommandStatus() {
        commandStatus = newwin(1, COLS, LINES - 1, 0);
    }

    extern void drawCommandStatus(bool cursor) {
        wclear(commandStatus);
        wprintw(commandStatus, "%s", Commands::current.c_str());
        if(cursor)
            wmove(commandStatus, 0, Commands::current.size());
        wrefresh(commandStatus);
    }
}

void Window::initWindows() {
    this->textWindow = newwin(ySize - 1, xSize, y, x);
    this->statusWindow = newwin(1, xSize, y + ySize - 1, x);
}

void Window::drawText() {
    wclear(this->textWindow);
    long prevColor = this->buffer->colors[this->buffer->bound];
    wattron(this->textWindow, prevColor);

    unsigned int lastDrawing = this->buffer->bound;
    for(unsigned int i = lastDrawing; i < this->buffer->text.length(); i++) {
        if(this->buffer->colors[i] != prevColor) {
            wprintw(this->textWindow, "%s", this->buffer->text.substr(lastDrawing, i - lastDrawing).c_str());
            wattroff(this->textWindow, prevColor);
            prevColor = this->buffer->colors[i];
            wattron(this->textWindow, prevColor);
            lastDrawing = i;
        }
    }

    wprintw(this->textWindow, "%s",
            this->buffer->text.substr(lastDrawing, this->buffer->text.length() - lastDrawing - 1).c_str());

    wrefresh(this->textWindow);
}

void Window::drawStatus() {
    wclear(this->statusWindow);
    wbkgd(this->statusWindow, COLOR_PAIR(Settings::Colors::statusBar.number));
    wrefresh(this->statusWindow);
}

void Window::draw() {
    this->drawText();
    this->drawStatus();
}

void Window::resize() {
    wclear(this->textWindow);
    wresize(this->textWindow, this->ySize - 1, this->xSize);
    mvwin(this->textWindow, this->y, this->x);
    wrefresh(this->textWindow);

    wclear(this->statusWindow);
    wresize(this->statusWindow, 1, this->xSize);
    mvwin(this->statusWindow, this->y + this->ySize - 1, this->x);
    wrefresh(this->statusWindow);
}

void Window::processInput(bool cursor) {
    if(cursor) {
        for(int i = 0; i < buffer->position.size(); i++) {

            const unsigned int x1 = Buffers::getBackToNewLine(*this->buffer, i);
            const unsigned int y1 = Buffers::getY(*this->buffer, this->xSize, i);
            unsigned int xShift1 = std::floor(x1 / this->xSize);

            if(false && this->buffer->position[i].position1 != this->buffer->position[i].position2) {
                const unsigned int till1 = Buffers::getUntilNewLine(*this->buffer, i);
                this->buffer->position[i].moving = !this->buffer->position[i].moving;
                const unsigned int x2 = Buffers::getBackToNewLine(*this->buffer, i);
                const unsigned int y2 = Buffers::getY(*this->buffer, this->xSize, i);
                unsigned int xShift2 = std::floor(x2 / this->xSize);
                const unsigned int till2 = Buffers::getUntilNewLine(*this->buffer, i);
                this->buffer->position[i].moving = !this->buffer->position[i].moving;

                if(y1 == y2) {
                    mvwchgat(this->textWindow, y1, std::min(x1, x2) - xShift1 * this->xSize,
                            std::max(x1, x2) - std::min(x1, x2) - 1, 
                            0, COLOR_PAIR(Settings::Colors::highlighting.number), NULL);
                }
                else {
                    const unsigned int min = std::min(y1, y2);
                    unsigned int advancing = (min == y1) ? (y1 + till1) : (y2 + till2);
                    for(unsigned int i = min + 1; i < std::max(y1, y2); i++) {
                        const unsigned int current = Buffers::getUntilNewLineWithStartPos(*this->buffer, advancing);
                        mvwchgat(this->textWindow, i, 0, current, 
                                0, COLOR_PAIR(Settings::Colors::highlighting.number), NULL);
                        advancing += current;
                    }

                    if(y1 > y2) {
                        mvwchgat(this->textWindow, y1, 0, x1 - xShift1 * this->xSize, 
                                0, COLOR_PAIR(Settings::Colors::highlighting.number), NULL);
                        mvwchgat(this->textWindow, y2, x2 - xShift2 * this->xSize, till2, 
                                0, COLOR_PAIR(Settings::Colors::highlighting.number), NULL);
                    }
                    else {
                        mvwchgat(this->textWindow, y2, 0, x2 - xShift2 * this->xSize, 
                                0, COLOR_PAIR(Settings::Colors::highlighting.number), NULL);
                        mvwchgat(this->textWindow, y1, x1 - xShift1 * this->xSize, till1, 
                                0, COLOR_PAIR(Settings::Colors::highlighting.number), NULL);
                    }
                }
            }

            mvwchgat(this->textWindow, y1, x1 - xShift1 * this->xSize, 1, 
                    0, COLOR_PAIR(Settings::Colors::cursor.number), NULL);
        }
    }

    const unsigned int input = wgetch(this->textWindow);

 InputRepeat:
    
    if(input == KEY_ESCAPE || input == KEY_CTRL('c')) {
        if(((*this->buffer->mode)->map.count(KEY_MODE_EXIT))) 
            Commands::execute(((*this->buffer->mode)->map.find(KEY_MODE_EXIT)->second));

        this->currentMapping = 0;
        Commands::current = "";
        this->buffer->mode = &Modes::Main;
        return;
    }

    const KeyMapping oldMapping = this->currentMapping;
    const std::string oldCommand = Commands::current;
    this->currentMapping |= (((KeyMapping) input) << (this->keymapCounting * 10));
    const KeyMapping bitMask = (((KeyMapping) 1) << (this->keymapCounting * 10 + 10)) - 1;
    bool found = false;

    for(auto& [key, val] : (*this->buffer->mode)->map) {
        if((key & bitMask) == (this->currentMapping & bitMask) && key != KEY_MODE_EXIT) {
            found = true;
            break;
        }
    }

    if(!found) {
        this->currentMapping = input;
        this->keymapCounting = 1;
        Commands::current = "";
	goto InputRepeat;
        return;
    }

    Commands::current += Utils::getKeyName(input) + " => ";

    if((*this->buffer->mode)->map.count(this->currentMapping)) {
        std::tuple<bool, bool> success = 
            Commands::execute(((*this->buffer->mode)->map.find(this->currentMapping)->second));

        if(!std::get<0>(success) || std::get<1>(success)) {
            this->currentMapping = 0;
            this->keymapCounting = 0;
            Commands::current = "";
        }
        else {
            this->currentMapping = oldMapping;
            Commands::current = oldCommand;
        }

        return;
    }

    ++keymapCounting;
}
