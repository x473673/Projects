#include <stdlib.h>
#include <assert.h>

//***********************************************
//              IMPORTANT NOTICE                *
//***********************************************
//  If you need to add more headers, which      *
//  you CAN, add them AFTER THIS LINE           *
#include <string.h>
//  but BEFORE the following one:               *
#include "memoryVM.h"
//  otherwise your code MAY FAIL TO COMPILE!    *
//                                              *
//  You have been warned.                       *
//***********************************************


// Here goes your glorious implementation.

size_t *getCounterPointer(void *memory){
    return ((size_t*) memory) - 2;
}

size_t getLength(void *memory){
    return ((size_t*) memory)[-1];
}

void freeVM(void *memory){
    free(((size_t*) memory) - 2);
    free(((size_t*) memory) - 1);
    free(memory);
}


bool initVM(void){
    return true;
}
void clearVM(void){

}

void* allocateArray(size_t elementSize, size_t elementCount){
    size_t *mem = (size_t*) malloc(2 * sizeof(size_t) + elementSize * elementCount);
    mem[0] = 1;
    mem[1] = elementCount;
    mem += 2;
    memset(mem, 0, elementSize * elementCount);
    return mem;
}

void* allocate(size_t size){
    int *mem = (int*) allocateArray(size,1);
    return mem;
}

void** allocateArray2D(size_t elementSize, size_t subarrays, size_t* elementCounts){
    size_t **mem2D = (size_t**) allocateArray(sizeof(size_t*), subarrays);
    if(!mem2D)
        return NULL;
    for(size_t i = 0; i < subarrays; i++) {
        mem2D[i] = (size_t*) allocateArray(elementSize, elementCounts ? elementCounts[i] : subarrays);
        if(!mem2D[i]) {
            for(size_t j = 0; j < i; j++) {
                freeVM(mem2D[j]);
            }
            freeVM(mem2D);
            return NULL;
        }
    }
    return (void**) mem2D;
}


void acquire(void* memory){
    assert(memory);
    (*getCounterPointer(memory))++;
}
void acquireArray2D(void** array){
    acquire(array);
    for(size_t i = 0; i < getLength(array); i++) {
        (*getCounterPointer(array[i]))++;
    }
}
bool release(void* memory){
    assert(memory);
    (*getCounterPointer(memory))--;
    if(*getCounterPointer(memory) == 0) {
        freeVM(memory);
        return true;
    }
    return false;
}
bool releaseArray2D(void** array){
    assert(array);
    (*getCounterPointer(array))--;
    if(*getCounterPointer(array) == 0) {
        for(size_t i = 0; i < getLength(array); i++)
            freeVM(array[i]);
        return true;
    }
    for(size_t i = 0; i < getLength(array); i++) {
        release(array[i]);
    }
    return false;

}

