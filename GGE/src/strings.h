#pragma once

#include <iostream>
#include <string>
#include <tuple>

namespace Strings {
    static char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    std::tuple<std::string, std::string> seperate(std::string input, char at);
    bool isNumber(std::string checking);
    bool isFloat(std::string checking);

    int readNumber(std::string number);
    float readFloat(std::string number);
}
