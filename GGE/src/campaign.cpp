#include <iostream>
#include "campaign.h"

void Campaign::changeName(std::string name_) {
    name = name_;
}

void Campaign::addStuff(std::string id, charac stuff_) {
    stuff.emplace(id, stuff_);
}

void Campaign::setBeginning(Stage* stage) {
    beginning = stage;
}

void Campaign::play() {
    std::cout << "\n\n------ " << name << " ------\n\n\n";

    beginning->execute(characters);

    std::cout << "\n\n\n~~~~~~ The End ~~~~~~\n\n";
}
