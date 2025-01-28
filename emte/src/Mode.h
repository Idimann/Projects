#pragma once

#include <iostream>
#include <string>
#include <vector>

class Window;

#define CreateModeFull(X, Y, Z, A) \
    class X : public Mode { \
        public: \
            Z \
            int keymap(Window* window, const int input); \
            void init() { \
                A \
            } \
            X() { \
                this->name = Y; \
                init(); \
            } \
    }; \
    bool X::keymap(Buffer &buffer, const int input)

#define CreateMode(X, Y, Z, A) \
    class X : public Mode { \
        public: \
            Z \
            int keymap(Window* window, const int input); \
            void init() { \
                A \
            } \
            X() { \
                this->name = Y; \
                init(); \
            } \
    }

class Mode {
    public:
        virtual void init();
        virtual int keymap(Window* window, const int input) {return false;}
        std::string name;

        //virtual ~Mode() {}
};

CreateMode(Main_Mode, "Main Mode",,); //The main mode containing access to all other modes

CreateMode(Window_Mode, "Window Mode",

            bool split;

            ,

            split = false;

        ); // Mode for Operations influencing windows and the whole Editor

CreateMode(Text_Mode, "Text Mode",,); //The text mode makes you able to type normally and edit simple text
                                     //
CreateMode(Structure_Mode, "Structure Mode",,); // Formatting and brackets
                                               //
CreateMode(File_Mode, "File Mode",,); // For openinng/saving/other file actions
