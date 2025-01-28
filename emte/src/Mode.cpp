#include "Mode.h"
#include "Window.h"
#include "Settings.h"
#include "Utility.h"

int Main_Mode::keymap(Window* window, const int input) {
    switch(input) {
        case 'i':
        case KEY_UP:
            window->buffers[0]->moveUp();
            break;
        case 'k':
        case KEY_DOWN:
            window->buffers[0]->moveDown(window->y_Size);
            break;
        case 'j':
        case KEY_LEFT:
            window->buffers[0]->moveLeft();
            break;
        case 'l':
        case KEY_RIGHT:
            window->buffers[0]->moveRight();
            break;
        
        case ' ':
            window->buffers[0]->spacePrefix = !window->buffers[0]->spacePrefix;
            break;

        case 't':
            free(window->buffers[0]->mode);
            window->buffers[0]->mode = new Text_Mode();
            break;
        case 'f':
            free(window->buffers[0]->mode);
            window->buffers[0]->mode = new File_Mode();
            break;
        case 'w':
            free(window->buffers[0]->mode);
            window->buffers[0]->mode = new Window_Mode();
            break;
    }

    return 0;
}

int Window_Mode::keymap(Window* window, const int input) {
    switch(input) {
        case 'q':
            return CODE_EXIT;
        case 's':
            this->split = true;
            break;

        case 'j':
            if(this->split)
                return CODE_SPLIT_VL;
            return CODE_MOVE_L;
        case 'l':
            if(this->split)
                return CODE_SPLIT_VR;
            return CODE_MOVE_R;
        case 'i':
            if(this->split)
                return CODE_SPLIT_HT;
            return CODE_MOVE_U;
        case 'k':
            if(this->split)
                return CODE_SPLIT_HB;
            return CODE_MOVE_D;
    }

    return 0;
}

int File_Mode::keymap(Window* window, const int input) {
    switch(input) {
        case 's':
            window->buffers[0]->saveFile();
            window->buffers[0]->did = true;
            window->buffers[0]->saved = true;
            window->buffers[0]->written = false;
            return CODE_DONE;
    }

    return 0;
}

int Text_Mode::keymap(Window* window, const int input) {
    bool tab_backspacing = true;
    switch(input) {
        case KEY_ENTER:
        case 10:
            window->buffers[0]->text.insert(window->buffers[0]->text.begin() + window->buffers[0]->y + 1, window->buffers[0]->text[window->buffers[0]->y].substr(window->buffers[0]->x));
            window->buffers[0]->text[window->buffers[0]->y].erase(window->buffers[0]->x);
            window->buffers[0]->text[window->buffers[0]->y].append("\n");
            if(window->buffers[0]->y >= window->buffers[0]->bound + window->y_Size - 2 - SCROLL_OFFSET)
                ++window->buffers[0]->bound;
            ++window->buffers[0]->y;
            window->buffers[0]->x = 0;
            window->buffers[0]->realX = 0;
            window->buffers[0]->adjustX();
            break;
        case KEY_BACKSPACE:
            if(window->buffers[0]->x == 0) {
                if(window->buffers[0]->y == 0)
                    break;

                window->buffers[0]->x = window->buffers[0]->text[window->buffers[0]->y - 1].length() - 1;
                window->buffers[0]->realX = window->buffers[0]->x;
                window->buffers[0]->text[window->buffers[0]->y - 1].erase(window->buffers[0]->text[window->buffers[0]->y - 1].length() - 1);
                window->buffers[0]->text[window->buffers[0]->y - 1] += window->buffers[0]->text[window->buffers[0]->y];
                window->buffers[0]->text.erase(window->buffers[0]->text.begin() + window->buffers[0]->y);
                window->buffers[0]->moveUp();
                break;
            }

            for(int i = 1; i <= minInt(TAB_LENGTH, window->buffers[0]->x); i++) {
                if(window->buffers[0]->text[window->buffers[0]->y][window->buffers[0]->x - i] != ' ') {
                    tab_backspacing = false;
                    break;
                }
            }

            if(window->buffers[0]->x >= TAB_LENGTH && tab_backspacing) {
                window->buffers[0]->text[window->buffers[0]->y].erase(window->buffers[0]->x - TAB_LENGTH, TAB_LENGTH);
                window->buffers[0]->x -= TAB_LENGTH;
            }
            else
                window->buffers[0]->text[window->buffers[0]->y].erase(--window->buffers[0]->x, 1);

            window->buffers[0]->realX = window->buffers[0]->x;
            break;
        case KEY_DOWN:
            window->buffers[0]->moveDown(window->y_Size);
            break;
        case KEY_UP:
            window->buffers[0]->moveUp();
            break;
        case KEY_LEFT:
            window->buffers[0]->moveLeft();
            break;
        case KEY_RIGHT:
            window->buffers[0]->moveRight();
            break;
        case '\t':
            window->buffers[0]->text[window->buffers[0]->y].insert(window->buffers[0]->x, TAB_LENGTH, ' ');
            window->buffers[0]->x += TAB_LENGTH;
            window->buffers[0]->realX = window->buffers[0]->x;
            break;
        default:
            window->buffers[0]->text[window->buffers[0]->y].insert(window->buffers[0]->x, 1, input);
            ++window->buffers[0]->x;
            window->buffers[0]->realX = window->buffers[0]->x;
            break;
    }

    window->buffers[0]->did = true;
    window->buffers[0]->written = true;
    return 0;
}
