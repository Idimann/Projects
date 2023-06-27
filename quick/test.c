#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    double d = 0;
    float f = 0;
    int i = 0;
    long l = 0;
    long long ll = 0;
    short s = 0;
    char c = 0;

    char asozial[31] = "hallo";
    char* test = "hallo";

    printf("Double: %lu\nFloat: %lu\nInt: %lu\nLong: %lu\nLong Long: %lu\nShort: %lu\nChar: %lu\nAsozial: %lu\n", 
            sizeof(d),
            sizeof(f),
            sizeof(i),
            sizeof(l),
            sizeof(ll),
            sizeof(s),
            sizeof(c),
            sizeof(asozial));

    return 0;
}
