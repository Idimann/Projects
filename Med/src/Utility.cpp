#include "Utility.h"
#include "Settings.h"
#include <curses.h>

namespace Utils {
    extern void replaceAll(std::string& str, const std::string& from, const std::string& to) {
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

    extern std::string constructNumber(const unsigned int number, const char character) {
        std::string returning = "";

        for(int i = 0; i < number; i++)
            returning += character;

        return returning;
    }

    extern bool isWhiteSpace(const char input) {
        switch(input) {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                return true;
        }

        return false;
    }

    extern bool isNonWordSpace(const char input) {
        return !((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') ||
                input == '-' ||
                input == '+' ||
                input == '#' ||
                input == '\\');
    }

    extern unsigned int stringOcurrences(const std::string input, const char character) {
        unsigned int returning = 0;
        for(const char c : input) 
            if(c == character)
                ++returning;

        return returning;
    }

    extern std::string parseDesc(const std::string input) {
        if(input == "SPC")
            return " ";
        else if(input == "RTN")
            return "\n";
        else if(input == "TAB")
            return constructNumber(Settings::tabSize, ' ');

        return input;
    }

    extern std::string getKeyName(const unsigned int input) {
        if(input == ' ')
            return "SPC";
        else if(input == KEY_CTRL(' '))
            return "C-SPC";
        else if(input == '\t')
            return "TAB";
        else if(input == KEY_CTRL('\t'))
            return "C-TAB";
        else if(input == '\n')
            return "RTN";
        else if(input == KEY_CTRL('\n'))
            return "C-RTN";

        std::string returning = "";
        for(char c = 'a'; c <= 'z'; c++) {
            if(input == c)
                return returning + c;
            else if(input == KEY_CTRL(c))
                return returning + "C-" + c;
        }

        for(char c = 'A'; c <= 'Z'; c++) {
            if(input == c)
                return returning + (char) (c + 32);
            else if(input == KEY_CTRL(c))
                return returning + "C-" + (char) (c + 32);
        }

        for(char c = 33; c <= 64; c++) {
            if(input == c)
                return returning + c;
            else if(input == KEY_CTRL(c))
                return returning + "C-" + c;
        }

        for(char c = 91; c <= 96; c++) {
            if(input == c)
                return returning + c;
            else if(input == KEY_CTRL(c))
                return returning + "C-" + c;
        }

        for(char c = 123; c <= 126; c++) {
            if(input == c)
                return returning + c;
            else if(input == KEY_CTRL(c))
                return returning + "C-" + c;
        }

        return returning;
    }
}
