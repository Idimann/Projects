#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define POLY_SIZE 100
typedef float poly[POLY_SIZE];

#define POINT_SIZE 2
typedef float points[2][POINT_SIZE];

size_t degree(poly* pol) {
    for(size_t i = 0; i < POLY_SIZE; i++) {
        if((*pol)[POLY_SIZE - 1 - i])
            return POLY_SIZE - 1 - i;
    }

    return 0;
}

float compute(poly* pol, float input) {
    float returning = 0;

    float factor = 1;
    for(size_t i = 0; i < degree(pol); i++) {
        returning += factor * (*pol)[i];
        factor *= input;
    }

    return returning;
}

#define APPROX_SIZE .001f
poly* approx(points* points) {
    poly* pol = malloc(sizeof(poly));

    for(size_t i = 0; i < POLY_SIZE; i++) {
        for(size_t j = 0; j <= i; j++) {
            for(float x = -FLT_MAX; x < FLT_MAX; x += APPROX_SIZE) {

            }
        }
    }

    return pol;
}

int main(int argc, char** argv) {
    points points = {{1, 1}, {2, 2}};
    poly* pol = approx(&points);

    printf("Value %lu: %f\n", degree(pol), compute(pol, 3));
    return 0;
}
