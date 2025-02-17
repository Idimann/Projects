#include <iostream>
#include "point.h"
#include "base.h"

int main(int argc, char** argv) {
    POINT(p1, TimePoint<int>, TimePoint<int>(60, 50));

    std::cout << p1.get().get() << '\n';

    return 0;
}
