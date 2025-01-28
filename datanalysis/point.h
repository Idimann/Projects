#pragma once

#include <iostream>
#include <cstdint>
#include <string>

template<typename T>
class TimePoint {
    private:
        uint64_t time;
        T value;

    public:
        TimePoint() : time(0), value({}) {}
        TimePoint(uint64_t time_, T init) : time(time_), value(init) {}

        T get() {
            return value;
        }

        void set(T new_) {
            value = new_;
        }

        uint64_t getTime() {
            return time;
        }

        void setTime(uint64_t new_) {
            time = new_;
        }
};

#define POINT(name, type, value) Point<type> name = Point<type>(value)

template<typename T>
class Point {
    private:
        T value;

    public:
        Point() : value({}) {}
        Point(T init) : value(init) {}

        T get() {
            return value;
        }

        void set(T new_) {
            value = new_;
        }
};
