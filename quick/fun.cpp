#include <stdio.h>
#include <iostream>
#include <math.h>

int main(int argc, char* argv[]) {
    while(1) {
        char test = 0;
        std::cin >> test;
        if(test != 'D' && test != 'd')
            continue;

        printf("Deine Mutter\n");
    }

    return 0;
}
