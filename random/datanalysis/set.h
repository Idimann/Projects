#pragma once
#include "point.h"
#include <vector>

template<typename T>
class Set {
    private:
        std::vector<T> main;

    public:
        Set() : main(std::vector<Point<T>>{}) {}
        Set(std::vector<Point<T>> main_) : main(main_) {}
};
