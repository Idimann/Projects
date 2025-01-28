#pragma once

#include <iostream>
#include "player.h"
#include "stage.h"

class Campaign {
    private:
        std::string name;
        std::vector<Character*> characters;
        std::map<std::string, charac> stuff;
        Stage* beginning;

    public:
        Campaign(std::string name_) {
            name = name_;
            characters = std::vector<Character*>();
            beginning = nullptr;
        }

        ~Campaign() {
            for(std::vector<Character*>::iterator i=characters.begin(); i!=characters.end(); i++) {
                delete (*i);
            }
        }

        void changeName(std::string name_);
        void addStuff(std::string id, charac stuff_);
        void setBeginning(Stage* stage);

        void play();
};
