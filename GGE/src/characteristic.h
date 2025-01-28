#pragma once

#include <iostream>
#include <string>

class charac {
    public:
        int int_;
        float float_;
        bool bool_;
        std::string string_;

        charac(int int__) {
            int_ = int__;
            float_ = 0;
            bool_ = false;
            string_ = "";
        }

        charac(float float__) {
            int_ = 0;
            float_ = float__;
            bool_ = false;
            string_ = "";
        }

        charac(bool bool__) {
            int_ = 0;
            float_ = 0;
            bool_ = bool__;
            string_ = "";
        }

        charac(std::string string__) {
            int_ = 0;
            float_ = 0;
            bool_ = false;
            string_ = string__;
        }
};
