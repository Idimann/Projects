#include <csignal>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include "Settings.h"
#include "curses/curses.h"
#include "Window.h"
#include "Buffer.h"
#include "Commands.h"

void sighandler(int s) {}

int main(int argc, char* argv[]) {
    Modes::init();
    Commands::init();
    initNcurses();
    Settings::Colors::update();
    Windows::initCommandStatus();

    //Prevents C-c closing
    if(Settings::no_CTRL_C)
        std::signal(SIGINT, sighandler);
  
    Buffers::add(new Buffer("--new--"));
    if(argc > 1)
        Buffers::getLast()->loadFile(argv[1]);

    Windows::add(new Window(Buffers::getLast()));

    Windows::drawCommandStatus(false);
    Windows::drawAll();

    while(true) {
        Windows::drawAll();
        Windows::drawCommandStatus(!((*Windows::get()->buffer->mode)->cursor));
        Windows::get()->processInput((*Windows::get()->buffer->mode)->cursor);
    }

    quitNcurses();
    return 0;
}
