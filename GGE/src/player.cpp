#include <algorithm>
#include "player.h"

charac Character::get(std::string string) {
    return attr.at(string);
}

bool Character::set(std::string att, charac charac) {
    return attr.emplace(att, charac).second;
}

void Character::addItem(std::string item) {
    items.push_back(item);
}

bool Character::removeItem(std::string item) {
    const auto found = std::find(items.begin(), items.end(), item);

    if(found != items.end()) {
        items.erase(found);
        return true;
    }

    return false;
}

bool Character::equipItem(std::string item) {
    const auto found = std::find(items.begin(), items.end(), item);

    if(found != items.end())
        return equipped.emplace(item, true).second;

    return false;
}

bool Character::removeEquipped(std::string item) {
    const auto found = std::find(items.begin(), items.end(), item);

    if(found != items.end())
        return equipped.emplace(item, false).second;

    return false;
}
