#include <iostream>
#include <string>

#pragma once

namespace Utils {
    extern void replaceAll(std::string& str, const std::string& from, const std::string& to);
    extern std::string constructNumber(const unsigned int number, const char character);
    extern bool isWhiteSpace(const char input);
    extern bool isNonWordSpace(const char input);
    extern unsigned int stringOcurrences(const std::string input, const char character);
    extern std::string parseDesc(const std::string input);
    extern std::string getKeyName(const unsigned int input);
}
