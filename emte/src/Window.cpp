#include "Window.h"
#include "Utility.h"
#include "Colors.h"
#include "Settings.h"
#include <curses.h>
#include <ncurses.h>

void Window::init() {
    t_Window = newwin(y_Size - 1, x_Size, y, x);
    s_Window = newwin(1, x_Size, y + y_Size - 1, x);

    wrefresh(t_Window);
    wrefresh(s_Window);
    wmove(t_Window, 0, 0);
    
    this->buffers = std::vector<Buffer*>();
    keypad(t_Window, true);
}

void Window::resize(const int x_Size, const int y_Size) {
    wclear(t_Window);
    wrefresh(t_Window);
    wresize(t_Window, y_Size - 1, x_Size);
    wrefresh(t_Window);

    wclear(s_Window);
    wrefresh(s_Window);
    mvwin(s_Window, y + y_Size - 1, x);
    wresize(s_Window, 1, x_Size);
    wrefresh(s_Window);

    this->x_Size = x_Size;
    this->y_Size = y_Size;
}

void Window::move(const int x, const int y) {
    wclear(t_Window);
    wrefresh(t_Window);
    mvwin(t_Window, y, x);
    wrefresh(t_Window);

    wclear(s_Window);
    wrefresh(s_Window);
    mvwin(s_Window, y + y_Size - 1, x);
    wresize(s_Window, 1, x_Size);
    wrefresh(s_Window);

    draw(this->active);

    this->x = x;
    this->y = y;
}

void Window::drawBuffer() {
    wclear(this->t_Window);
    Buffer* drawing = this->buffers[0];

    for(int i = drawing->bound; i < minInt(this->y_Size + drawing->bound - 1, drawing->text.size()); i++)
        mvwprintw(this->t_Window, i - drawing->bound, 0, "%s", drawing->text[i].c_str());

    if(this->active)
        wmove(this->t_Window, drawing->y - drawing->bound, drawing->x);
    wrefresh(this->t_Window);
}

void Window::drawStatus() {
    wclear(this->s_Window);
    if(supportColors())
        wbkgd(this->s_Window, get_curses_pair("Status bar"));
    mvwprintw(this->s_Window, 0, 0, "%s", parseStatusString().c_str());
    wrefresh(s_Window);
}

void Window::draw(const bool active) {
    this->active = active;

    drawStatus();
    drawBuffer();
}

std::string Window::parseStatusString() {
    std::string returning = STATUS_BAR_STRING;

    returning = replaceAll(returning, "%l", std::to_string(this->buffers[0]->y + 1));
    returning = replaceAll(returning, "%c", std::to_string(this->buffers[0]->x + 1));
    returning = replaceAll(returning, "%w", this->buffers[0]->written ? "+" : "-");
    returning = replaceAll(returning, "%s", this->buffers[0]->saved ? "+" : "-");
    returning = replaceAll(returning, "%d", this->buffers[0]->did ? "+" : "-");
    returning = replaceAll(returning, "%b", this->buffers[0]->name);
    returning = replaceAll(returning, "%W", this->buffers[0]->written ? "y" : "n");
    returning = replaceAll(returning, "%S", this->buffers[0]->saved ? "y" : "n");
    returning = replaceAll(returning, "%D", this->buffers[0]->did ? "y" : "n");
    returning = replaceAll(returning, "%m", this->buffers[0]->mode->name);
    returning = replaceAll(returning, "%q", this->buffers[0]->spacePrefix ? "*" : "");
    returning = replaceAll(returning, "%Q", this->buffers[0]->spacePrefix ? "+" : "-");

    //Unfinished
    returning = replaceAll(returning, "%t", ""); // Utf/Unicode stuff
    returning = replaceAll(returning, "%e", ""); // Editor Mode


    return returning;
}

int Window::proccessInput() {
    return this->buffers[0]->registerInput(this);
}
