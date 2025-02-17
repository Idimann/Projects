#pragma once

#include <string>

template<typename T>
class Type {
    public:
        T value;

        Type(T value_) : value(value_) {}

        //Formatting
        virtual std::string asString() {
            return std::string(value);
        }

        //Comparisons
        virtual bool operator==(const Type& other) {
            return value == other.value;
        }

        virtual bool operator>(const Type& other) {
            return value > other.value;
        }

        virtual bool operator<(const Type& other) {
            return value < other.value;
        }

        virtual bool operator>=(const Type& other) {
            return value >= other.value;
        }

        virtual bool operator<=(const Type& other) {
            return value <= other.value;
        }
};
