#include <stdint.h>
#include <stdio.h>
#include <math.h>

int64_t calc(uint64_t x, float n) {
    int64_t returning = 0;

    for(uint64_t i = 0; i < x; i++) {
        returning += floor(log10(1 - i/n));
    }

    return returning;
}

int main(int argc, char** argv) {
    printf("%ld\n", calc(1000, 100000));
    //for(uint64_t i = 1; i < 1000000; i++)
        //printf("%f\n", 1 - calc(i, 10000000));

    return 0;
}
