#pragma once

#include <iostream>
#include <list>
#include "player.h"
#include "strings.h"

class Stage {
    private:
        std::string name;
        bool nameshown;

        virtual void exec(std::vector<Character*> characters) = 0;
    public:
        Stage(std::string name_, bool nameshown_) {
            name = name_;
            nameshown = nameshown_;
        }

        void setName(std::string name_);
        void setNameShown(bool nameshown_);

        void execute(std::vector<Character*> characters);
};

//Text
class Stage_Text : public Stage {
    private:
        std::list<std::string> text;
        Stage* next;

        void exec(std::vector<Character*> characters) override;

    public:
        using Stage::Stage;

        void addText(std::string text_);
};

//Tree

class Stage_Tree : public Stage {
    private:
        class Node {
            private:
                std::string name;
                Stage* playing;
                std::vector<Node> choices;
            public:
                std::string getName() {return name;}

                void exec(std::vector<Character*> characters, std::string choice) {
                    playing->execute(characters);
                    std::cout << '\n';
                    for(int i = 0; i < choices.size(); i++)
                        std::cout << i + 1 << ". " << choices[i].getName() << '\n';
                    std::cout << '\n' << choice;
                    std::string chosen;
                    std::cin >> chosen;
                    while(!Strings::isNumber(chosen) ||
                            Strings::readNumber(chosen) > choices.size()) {
                        std::cout << "Wrong Input. Try again.\n" << choice;
                        std::cin >> chosen;
                    }

                    
                }
        };

        void exec(std::vector<Character*> characters) override;
        Node start;
    public:
        using Stage::Stage;
};
