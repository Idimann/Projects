#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "readers.h"

std::tuple<Stage*, std::string> Reader::readLine(std::string line) {
    const auto tuple = Strings::seperate(line, '|');

    bool nameshown = false;
    if(std::get<1>(tuple).size() != 1)
        return std::tuple<Stage*, std::string>(nullptr, "Wrong Nameshown Specifier");
    else {
        switch(std::get<1>(tuple)[0]) {
            case 't':
                nameshown = true;
                break;
            case 'f':
                nameshown = false;
                break;
            default:
                return std::tuple<Stage*, std::string>(nullptr, "Unknown Nameshown Specifier");
                break;
        }
    }
}

Stage_Text* Reader::read_Text(std::string file) {
    Stage_Text* returning = new Stage_Text("Unnamed", false);

    std::ifstream stream(file);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    std::string string = buffer.str();

    unsigned long counter = string.find("\\\\");

    while(counter != std::string::npos) {
        returning->addText(string.substr(0, counter));

        string = string.substr(counter + 2, string.size() - counter - 2);
        counter = string.find("\\\\");
    }

    string.pop_back(); //Idk why theres a \n at the end but its popped
    returning->addText(string);

    return returning;
}
