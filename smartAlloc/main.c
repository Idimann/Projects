#include<stdlib.h>
#include<stdio.h>

#define STACK_SIZE 100
#define SCOPE_SIZE 100

typedef struct smart_alloc {
    void (*push)(struct smart_alloc*);
    void *(*alloc)(struct smart_alloc*, size_t);
    void (*pop)(struct smart_alloc*);

    size_t stack_size;
    void **stack[STACK_SIZE];
    size_t scope_size[STACK_SIZE];
} smart_alloc;

void std_push(smart_alloc *alloc) {
    ++alloc->stack_size;
}

void std_pop(smart_alloc *alloc) {
    --alloc->stack_size;

    printf("%lu\n", alloc->scope_size[alloc->stack_size]);

    for(size_t i = 0; i < alloc->scope_size[alloc->stack_size]; i++)
        free(alloc->stack[alloc->stack_size][i]);

    alloc->scope_size[alloc->stack_size] = 0;
}

void *std_alloc(smart_alloc *alloc, size_t size) {
    if(alloc->stack_size >= STACK_SIZE)
        return NULL;

    void *const returning = malloc(size);

    alloc->stack[alloc->stack_size - 1]
        [alloc->scope_size[alloc->stack_size - 1]++] = returning;
    //printf("%lu\n", alloc->stack_sizes[alloc->stack_size - 1]);

    return returning;
}

smart_alloc std_make() {
    return (smart_alloc) {
        .push = std_push,
        .alloc = std_alloc,
        .pop = std_pop,

        .stack_size = 0,
    };
}

int main(int argc, char **argv) {
    smart_alloc alloc = std_make();
    alloc.push(&alloc);

    int* test = alloc.alloc(&alloc, sizeof(int));
    /**test = 4;*/
    /**test += 5;*/

    //alloc.pop(&alloc);
    return 0;
}
