#include <stdio.h>

#define HEAP_SIZE 64000

unsigned char HEAP[HEAP_SIZE];

typedef struct {
    const unsigned char* pointer;
    size_t size;
} HEAP_SECTION;

HEAP_SECTION FREE_SPACES[HEAP_SIZE / 2] = {{.pointer = &HEAP[0], .size = HEAP_SIZE}};
HEAP_SECTION ALLOCED_SPACES[HEAP_SIZE / 2];

size_t FREE_INDEX = 1;
size_t ALLOCED_INDEX = 0;

void sortFree() { //Idk some sort of sorting algo
    for(size_t i = 0; i <= FREE_INDEX / 2; i++) {
        for(size_t j = FREE_INDEX - i - 1; j > 0; j--) {
            if(FREE_SPACES[j].size < FREE_SPACES[j - 1].size) { //Swap them
                const HEAP_SECTION temp = FREE_SPACES[j];
                FREE_SPACES[j] = FREE_SPACES[j - 1];
                FREE_SPACES[j - 1] = temp;
            }
        }
    }
}

void* my_malloc(const size_t size) {
    if(!size)
        return NULL;

    size_t foundIndex = 0;

    //Searching for allocable section
    for(size_t i = 0; i < FREE_INDEX; i++) { //This could be faster, cause FREE_SPACES is sorted
        if(FREE_SPACES[i].size < size)
            continue;

        foundIndex = i + 1;
        break;
    }

    //Couldn't find allocable section
    if(!foundIndex)
        return NULL;

    HEAP_SECTION* section = &FREE_SPACES[--foundIndex]; //foundIndex has to be bigger than 0
    const void* pointer = section->pointer;

    //Add it to ALLOCED_SPACES
    ALLOCED_SPACES[ALLOCED_INDEX].pointer = section->pointer; 
    ALLOCED_SPACES[ALLOCED_INDEX].size = size; 
    ++ALLOCED_INDEX;

    //Change or remove the FREE_SPACES block
    if(section->size == size) { //Removing it
        if(FREE_INDEX >= HEAP_SIZE / 2) {
            for(size_t i = foundIndex; i < HEAP_SIZE / 2 - 1; i++)
                FREE_SPACES[i] = FREE_SPACES[i + 1];

            FREE_SPACES[HEAP_SIZE / 2 - 1].size = 0;
        }
        else {
            for(size_t i = foundIndex; i < FREE_INDEX; i++)
                FREE_SPACES[i] = FREE_SPACES[i + 1];
        }

        --FREE_INDEX;
    }
    else { //Changing it
        section->pointer = &section->pointer[size]; //This is a nice trick
        section->size -= size;
    }

    sortFree();

    return (void*) pointer;
}

void my_free(const void* at) {
    if(!at || at < (void*) &HEAP || at >= (void*) &HEAP[HEAP_SIZE]) //Checking for an invalid ptr
        return;

    size_t foundIndex = 0;

    //Searching for the section
    for(size_t i = 0; i < ALLOCED_INDEX; i++) {
        if(ALLOCED_SPACES[i].pointer != at)
            continue;

        foundIndex = i + 1;
        break;
    }

    if(!foundIndex)
        return;

    HEAP_SECTION* section = &ALLOCED_SPACES[--foundIndex]; //foundIndex > 0

    //Adding to free spaces
    size_t foundIndex2 = 0;
    size_t foundIndex3 = 0;
    
    //Searching for free block right before and after it
    for(size_t i = 0; i < FREE_INDEX; i++) {
        if(foundIndex2 && foundIndex3)
            break;

        if(FREE_SPACES[i].pointer == &section->pointer[section->size])
            foundIndex2 = i + 1;
        else if(&FREE_SPACES[i].pointer[FREE_SPACES[i].size] == section->pointer)
            foundIndex3 = i + 1;
    }

    //Actually freeing it
    if(foundIndex3) { //We find free block right before
        section->pointer = FREE_SPACES[--foundIndex3].pointer;
        section->size += FREE_SPACES[foundIndex3].size;
        FREE_SPACES[foundIndex3].size = section->size;
    }

    if(foundIndex2) { //We find free block right after
        if(foundIndex3) { //We have to remove the foundIndex2 block
            if(foundIndex3 > foundIndex2)
                --foundIndex3;

            FREE_SPACES[foundIndex3].size += FREE_SPACES[--foundIndex2].size;

            if(FREE_INDEX >= HEAP_SIZE / 2) {
                for(size_t i = foundIndex2; i < HEAP_SIZE / 2 - 1; i++)
                    FREE_SPACES[i] = FREE_SPACES[i + 1];

                FREE_SPACES[HEAP_SIZE / 2 - 1].size = 0;
            }
            else {
                for(size_t i = foundIndex2; i < FREE_INDEX; i++)
                    FREE_SPACES[i] = FREE_SPACES[i + 1];
            }
        }
        else {
            FREE_SPACES[--foundIndex2].pointer = section->pointer;
            FREE_SPACES[foundIndex2].size += section->size;
        }
    }
    else if(!foundIndex3) { // We don't find that block
        FREE_SPACES[FREE_INDEX].pointer = section->pointer; 
        FREE_SPACES[FREE_INDEX].size = section->size; 
        ++FREE_INDEX;
    }

    //Removing from alloced spaces
    if(ALLOCED_INDEX >= HEAP_SIZE / 2) {
        for(size_t i = foundIndex; i < HEAP_SIZE / 2 - 1; i++)
            ALLOCED_SPACES[i] = ALLOCED_SPACES[i + 1];

        ALLOCED_SPACES[HEAP_SIZE / 2 - 1].size = 0;
    }
    else {
        for(size_t i = foundIndex; i < ALLOCED_INDEX; i++)
            ALLOCED_SPACES[i] = ALLOCED_SPACES[i + 1];
    }

    --ALLOCED_INDEX;

    sortFree();
}

void dump_heap() {
    printf("\nDumping heap \t (Starts at: %p)\n", &HEAP);
    for(size_t i = 0; i < ALLOCED_INDEX; i++) {
        printf("Alloced block: \t Pointer: %p \t Size: %lu\n", 
                ALLOCED_SPACES[i].pointer, ALLOCED_SPACES[i].size);
    }
    printf("\n");
    for(size_t i = 0; i < FREE_INDEX; i++) {
        printf("Free block: \t Pointer: %p \t Size: %lu\n", 
                FREE_SPACES[i].pointer, FREE_SPACES[i].size);
    }
    printf("\n");
}

void garbage_collect() {
    for(size_t i = 0; i < ALLOCED_INDEX; i++) {
BEGINNING:
        for(size_t j = 0; j < ALLOCED_INDEX; j++) {
            if(i == j) //Things can't ref themselves
                continue;

            if(ALLOCED_SPACES[j].size != sizeof(unsigned char*)) //Only consider actual ptrs
                continue;

            if(*((unsigned char**)ALLOCED_SPACES[j].pointer) != ALLOCED_SPACES[i].pointer)
                continue;

            goto FOUND; //Lol
        }

        my_free(ALLOCED_SPACES[i].pointer); //Calling my_free while iterating could cause problems
        if(ALLOCED_INDEX != 0)
            goto BEGINNING;

FOUND:
        continue;
    }
}

int main(int argc, char** argv) {
    const void* first = my_malloc(50);
    const void* second = my_malloc(3);

    dump_heap();

    //garbage_collect();
    my_free(first);
    my_free(second);
    dump_heap();

    return 0;
}
