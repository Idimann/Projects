#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int m;
    int n;
    float* numbers;
} matrix_f;

void setElement(matrix_f* matrix, int i, int j, float setting) {
    if(i >= matrix->m || j >= matrix->n) {
        printf("Fuck\n");
        return;
    }

    matrix->numbers[i * matrix->n + j] = setting;
}

float giveElement(matrix_f* matrix, int i, int j) {
    if(i >= matrix->m || j >= matrix->n) {
        printf("Fuck\n");
        return 0;
    }

    return matrix->numbers[i * matrix->n + j];
}

matrix_f* inputMatrix() {
    matrix_f* output = malloc(sizeof(matrix_f));
    printf("Size: ");
    scanf("%i", &output->m);
    output->n = output->m;
    printf("\n");
    if(output->m <= 0 || output->n <= 0) {
        printf("Idiot\n");
        exit(0);
    }
    output->numbers = malloc(sizeof(float) * output->m * output->n);

    for(int i = 0; i < (output->m); i++) {
        for(int j = 0; j < (output->n); j++) {
            float input = 0;
            if(i == output->m - 1 && j == output->n - 1)
                scanf("%f", &input);
            else if(j == output->n -1) {
                char next = 0;
                char next2 = 0;
                scanf("%f %c %c", &input, &next, &next2);

                if(next != '\\' || next2 != '\\')
                    printf("Strange linebreak\n");
            }
            else {
                char next = 0;
                scanf("%f %c", &input, &next);

                if(next != '&')
                    printf("Strange\n");
            }

            setElement(output, i, j, input);
        }
    }

    return output;
}

void outputMatrix(matrix_f* matrix) {
    for(int i = 0; i < (matrix->m); i++) {
        for(int j = 0; j < (matrix->n); j++) {
            printf("%1.2f", giveElement(matrix, i, j));

            if(j != matrix->n - 1)
                printf(" & ");
        }

        if(i != matrix->m - 1)
            printf(" \\\\\n");
    }

    printf("\n");
}

float det(matrix_f* matrix) {
    if(matrix->m == matrix->n && matrix->m == 1)
        return giveElement(matrix, 0, 0);

    float result = 0;

    for(int i = 0; i < (matrix->n); i++) {
        matrix_f* new = malloc(sizeof(matrix_f));
        new->m = matrix->m - 1;
        new->n = matrix->n - 1;
        new->numbers = malloc(sizeof(float) * new->m * new->n);

        for(int r = 1; r < (matrix->m); r++) {
            for(int s = 0; s < (matrix->n); s++) {
                if(s == i)
                    continue;
                setElement(new, r - 1, (s < i) ? s : (s - 1), giveElement(matrix, r, s));
            }
        }

        if(i % 2 == 0)
            result += giveElement(matrix, 0, i) * det(new);
        else
            result -= giveElement(matrix, 0, i) * det(new);
    }

    return result;
}

int main(int argc, char** argv) {
    matrix_f* input = inputMatrix();
    printf("%f\n", det(input));

    return 0;
}
