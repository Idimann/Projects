#include <iostream>
#include "terminal.h"
#include "stage.h"

void Stage::setName(std::string name_) {
    name = name_;
}

void Stage::setNameShown(bool nameshown_) {
    nameshown = nameshown_;
}

void Stage::execute(std::vector<Character*> characters) {
    if(nameshown)
        std::cout << "\n\n-- " << name << " --\n\n";

    exec(characters);
}

void Stage_Text::addText(std::string text_) {
    text.push_back(text_);
}

void Stage_Text::exec(std::vector<Character*> characters) {
    for(std::list<std::string>::iterator i = text.begin(); i != text.end(); i++) {
        std::cout << *i;
        Terminal::getch();
    }
}
