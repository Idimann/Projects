#include <iostream>
#include <string>
#include <fstream>
#include "reader.h"
#include "strings.h"
#include "readers.h"

Campaign Reader::read(std::string directory) {
    Campaign returning = Campaign("Unnamed");
    std::ifstream main(directory + "/main");

    std::string line;
    uint16_t counter = 0;
    while(std::getline(main, line)) {
        ++counter;

        if(line.size() <= 1)
            continue;

        const auto tuple = Strings::seperate(line, ':');
        bool error = false;

        if(std::get<0>(tuple) == std::get<1>(tuple)) {
            std::cout << "Error reading main at line " << counter << "! (Unkown Command)\n";
            error = true;
            break;
        }

        if(std::get<0>(tuple) == "N")
            returning.changeName(std::get<1>(tuple));
        else if(std::get<0>(tuple) == "S") {
            const auto tuple_2 = Strings::seperate(std::get<1>(tuple), '|');
            const auto tuple_3 = Strings::seperate(std::get<0>(tuple_2), '.');

            bool nameshown = false;
            if(std::get<1>(tuple_2).size() != 1) {
                std::cout << "Error reading main at line " << counter << 
                    "! (Wrong Nameshown Specifier)\n";
                error = true;
                break;
            }
            else {
                switch(std::get<1>(tuple_2)[0]) {
                    case 't':
                        nameshown = true;
                        break;
                    case 'f':
                        nameshown = false;
                        break;
                    default:
                        std::cout << "Error reading main at line " << counter << 
                            "! (Unknown Nameshown Specifier)\n";
                        error = true;
                        break;
                }
            }

            if(std::get<1>(tuple_3) == "gtex") {
                Stage_Text* inserting = read_Text(directory + "/" + std::get<0>(tuple_2));
                inserting->setName(std::get<0>(tuple_3));
                inserting->setNameShown(nameshown);

                returning.setBeginning(inserting);
            }
            else {
                std::cout << "Error reading main at line " << counter << "! (Unkown Filetype)\n";
                error = true;
                break;
            }
        }
        else if(std::get<0>(tuple) == "C") {
            const auto tuple_2 = Strings::seperate(std::get<1>(tuple), '|');

            switch(std::get<0>(tuple_2)[0]) {
                case '\"':
                    returning.addStuff(std::get<0>(tuple_2).substr(1, 
                                std::get<0>(tuple_2).size() - 1), charac(std::get<1>(tuple_2)));
                    break;
                case '&':
                    if(std::get<1>(tuple_2).size() != 1) {
                        std::cout << "Error reading main at line " << counter << "! (Wrong Bool)\n";
                        error = true;
                        break;
                    }

                    switch(std::get<1>(tuple_2)[0]) {
                        case 't':
                            returning.addStuff(std::get<0>(tuple_2).substr(1, 
                                        std::get<0>(tuple_2).size() - 1), charac(true));
                            break;
                        case 'f':
                            returning.addStuff(std::get<0>(tuple_2).substr(1, 
                                        std::get<0>(tuple_2).size() - 1), charac(false));
                            break;
                        default:
                            std::cout << "Error reading main at line " << counter << 
                                "! (Unkown Bool)\n";
                            error = true;
                            break;
                    }
                    break;
                case '$':
                    if(!Strings::isNumber(std::get<1>(tuple_2))) {
                        std::cout << "Error reading main at line " << counter << "! (Wrong Int)\n";
                        error = true;
                        break;
                    }


                    returning.addStuff(std::get<0>(tuple_2).substr(1, 
                                std::get<0>(tuple_2).size() - 1), 
                            charac(Strings::readNumber(std::get<1>(tuple_2))));
                    break;
                case '*':
                    if(!Strings::isFloat(std::get<1>(tuple_2))) {
                        std::cout << "Error reading main at line " << counter<< "! (Wrong Float)\n";
                        error = true;
                        break;
                    }


                    returning.addStuff(std::get<0>(tuple_2).substr(1, 
                                std::get<0>(tuple_2).size() - 1), 
                            charac(Strings::readFloat(std::get<1>(tuple_2))));
                    break;
                default:
                    std::cout << "Error reading main at line " << counter << "! (Unkown Type)\n";
                    error = true;
                    break;
            }

            if(error)
                break;
        }
    }

    return returning;
}
