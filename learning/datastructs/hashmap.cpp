#include <iostream>

template <typename O, typename T>
class Map {
private:
    T *array;
    size_t size;
    size_t (*hashFunc)(const O&);

public:
    Map(size_t (*hash)(const O&)) {
        array = nullptr;
        size = 0;
        hashFunc = hash;
    }

    const T& operator[](O input) const {
        if(size == 0)
            throw std::exception();

        return array[hashFunc(input) % size];
    }
};

size_t stringHash(const std::string& input) {
    size_t returning = 0;
    size_t factor = 1;
    for(const char& c : input) {
        returning += c * factor;
        factor *= 128;
    }
    return returning;
}

int main(int argc, char** argv) {
    auto map = Map<std::string, int>(stringHash);
    return 0;
}
