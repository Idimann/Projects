#pragma once

#include <iostream>
#include <cstdint>
#include <list>
#include <string>
#include <map>
#include <vector>
#include "characteristic.h"

inline static std::map<std::string, charac> DEFAULT_ATTR = std::map<std::string, charac>();

class Character {
    private:
        std::map<std::string, charac> attr;
        std::list<std::string> items;
        std::map<std::string, bool> equipped;

    public:
        Character() {
            attr = DEFAULT_ATTR;
            items = std::list<std::string>();
            equipped = std::map<std::string, bool>();
        }

        charac get(std::string string);
        bool set(std::string att, charac charac);

        void addItem(std::string item);
        bool removeItem(std::string item);

        bool equipItem(std::string item);
        bool removeEquipped(std::string item);
};
