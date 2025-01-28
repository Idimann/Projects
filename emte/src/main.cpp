#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include "Buffer.h"
#include "Window.h"
#include "Utility.h"

std::vector<Window*> windows = std::vector<Window*>();
int currentWindow = 0;

int getLeftWindow(const int number) {
    for(int i = 0; i < windows.size(); i++) {
        if(windows[i]->x + windows[i]->x_Size == windows[number]->x &&
                windows[i]->y <= windows[number]->buffers[0]->y + windows[number]->y &&
                windows[i]->y + windows[i]->y_Size > windows[number]->buffers[0]->y + windows[number]->y)
            return i;

    }

    return -1;
}

int getRightWindow(const int number) {
    for(int i = 0; i < windows.size(); i++) {
        if(windows[number]->x + windows[number]->x_Size == windows[i]->x &&
                windows[i]->y <= windows[number]->buffers[0]->y + windows[number]->y &&
                windows[i]->y + windows[i]->y_Size > windows[number]->buffers[0]->y + windows[number]->y)
            return i;

    }

    return -1;
}

int getTopWindow(const int number) {
    for(int i = 0; i < windows.size(); i++) {
        if(windows[i]->y + windows[i]->y_Size == windows[number]->y &&
                windows[i]->x <= windows[number]->buffers[0]->x + windows[number]->x &&
                windows[i]->x + windows[i]->x_Size > windows[number]->buffers[0]->x + windows[number]->x)
            return i;

    }

    return -1;
}

int getBottomWindow(const int number) {
    for(int i = 0; i < windows.size(); i++) {
        if(windows[number]->y + windows[number]->y_Size == windows[i]->y &&
                windows[i]->x <= windows[number]->buffers[0]->x + windows[number]->x &&
                windows[i]->x + windows[i]->x_Size > windows[number]->buffers[0]->x + windows[number]->x)
            return i;

    }

    return -1;
}

void startUpWindow(std::string argv1) {
    windows.push_back(new Window());

    windows[0]->buffers.push_back((new Buffer())->loadFile(argv1));
}

void runLoop() {
    for(int i = 0; i < windows.size(); i++)
        if(i != currentWindow)
        windows[i]->draw(false);

    windows[currentWindow]->draw(true);
    const int input = windows[currentWindow]->proccessInput();

    const int winX = windows[currentWindow]->x;
    const int winY = windows[currentWindow]->y;
    const int winSizeX = windows[currentWindow]->x_Size;
    const int winSizeY = windows[currentWindow]->y_Size;

    const int prevCurrentWindow = currentWindow;

    switch(input) {
        case CODE_EXIT:
            goto ExitPoint;
        case CODE_SPLIT_HT:
            windows[currentWindow]->resize(winSizeX,
                    winSizeY - winSizeY / 2); //Cause of integer rounding
            windows[currentWindow]->move(winX,
                    winY + winSizeY / 2);
            windows.push_back(new Window(new Buffer(),
                            winX,
                            winY,
                            winSizeX,
                            winSizeY / 2));
            currentWindow = windows.size() - 1;
            break;
        case CODE_SPLIT_HB:
            windows[currentWindow]->resize(winSizeX,
                    winSizeY - winSizeY / 2); //Cause of integer rounding
            windows.push_back(new Window(new Buffer(),
                            winX,
                            winY + winSizeY / 2,
                            winSizeX,
                            winSizeY / 2));
            currentWindow = windows.size() - 1;
            break;
        case CODE_SPLIT_VL:
            windows[currentWindow]->resize(winSizeX - winSizeX / 2, //Cause of integer rounding
                    winSizeY);
            windows[currentWindow]->move(winX + winSizeX / 2,
                    winY);
            windows.push_back(new Window(new Buffer(),
                            winX,
                            winY,
                            winSizeX / 2,
                            winSizeY));
            currentWindow = windows.size() - 1;
            break;
        case CODE_SPLIT_VR:
            windows[currentWindow]->resize(winSizeX - winSizeX / 2, //Cause of integer rounding
                    winSizeY);
            windows.push_back(new Window(new Buffer(),
                            winX + winSizeX / 2,
                            winY,
                            winSizeX / 2,
                            winSizeY));
            currentWindow = windows.size() - 1;
            break;
        case CODE_MOVE_L:
            currentWindow = getLeftWindow(currentWindow);
            break;
        case CODE_MOVE_R:
            currentWindow = getRightWindow(currentWindow);
            break;
        case CODE_MOVE_U:
            currentWindow = getTopWindow(currentWindow);
            break;
        case CODE_MOVE_D:
            currentWindow = getBottomWindow(currentWindow);
            break;
    }

    if(currentWindow == -1)
        currentWindow = prevCurrentWindow;

    return;

ExitPoint:
    clear();
    endwin();
    exit(0);
}

int main(int argc, char* argv[]) {
    init();

    startUpWindow(argc > 1 ? argv[1] : "");

    while(1) {
        runLoop();
    }

    clear();
    endwin();
    return 0;
}
