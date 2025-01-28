#include <iostream>
#include "strings.h"

std::tuple<std::string, std::string> Strings::seperate(std::string input, char at) {
    std::string::size_type pos = input.find(at);
    if(pos == std::string::npos)
        return {input, input};
    else
        return {input.substr(0, pos), input.substr(pos + 1, input.size() - pos - 1)};
}

bool Strings::isNumber(std::string checking) {
    for(char c : checking)
        if(numbers[c - '0'] != c)
            return false;

    return true;
}

bool Strings::isFloat(std::string checking) {
    bool dot = false;


    for(char c : checking)
        if(numbers[c - '0'] != c && (dot || c != '.'))
            return false;

    return true;
}

int Strings::readNumber(std::string number) {
    return std::stoi(number);
}

float Strings::readFloat(std::string number) {
    return std::stof(number);
}
