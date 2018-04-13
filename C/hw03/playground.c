#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataDef.h"
#include "memoryVM.h"
#include "memoryVMObject.h"

#define UNUSED(VAR) ((void) VAR)

/*
 * This file is not submitted as your homework.
 *
 * You should only use it to test and play with your implementation.
 */


size_t *getCounterPp(void *memory){
    return ((size_t*) memory) - 2;
}

size_t getLengthp(void *memory){
    return ((size_t*) memory)[-1];
}

void trySize() {
    size_t *size = (size_t*) allocate(sizeof(size_t));
    if(!size)
        return;
    *size = 5;
    release(size);
    printf("memory: %u\n",*size);
    printf("counter: %i\n",*getCounterPp(size));
    printf("length: %i\n",getLengthp(size));
}

void tryArray() {
    size_t *sizes = (size_t*) allocateArray(sizeof(size_t),5);
    if(!sizes)
        return;
    for(size_t i = 0; i < 5 ; i++){
        sizes[i] = i;
    }
    for(size_t i = 0; i < 5; i++){
        printf("memory: %u\n",sizes[i]);
    }
    printf("counter: %u\n",*getCounterPp(sizes));
    printf("length: %i\n",getLengthp(sizes));
    release(sizes);
}

void tryString() {
    char *string = (char*) allocateArray(sizeof(char),6);
    if(!string)
        return;
    strcpy(string,"Hello");
    printf("memory: %s\n",string);
    printf("counter: %u\n",*getCounterPp(string));
    printf("length: %i\n",getLengthp(string));
    release(string);
}

void trySizes2D() {
    size_t sizes[5] = {6,4,4,6,4};
    size_t **ints = (size_t**) allocateArray2D(sizeof(size_t),5,sizes);
    if(!ints)
        return;
    for(size_t i = 0; i < 5; i++){
        for(size_t j = 0; j < sizes[i]; j++){
            ints[i][j] = rand() % 10;
        }
    }
    acquireArray2D(ints);
    releaseArray2D(ints);
    releaseArray2D(ints);
    release(ints[3]);
    for(size_t i = 0; i < 5; i++){
        printf("memory: ");
        for(size_t j = 0; j < sizes[i]; j++){
            printf("%i ", ints[i][j]);
        }
        putchar('\n');
        printf("counter: %u\n",*getCounterPp(ints[i]));
        printf("length: %i\n",getLengthp(ints[i]));
    }
    printf("meta counter: %u\n",*getCounterPp(ints));
    printf("length: %i\n",getLengthp(ints));
}

void tryStrings() {
    size_t sizes[5] = {6,4,4,6,4};
    char **strings = (char**) allocateArray2D(sizeof(char),5,sizes);
    if(!strings)
        return;
    strcpy(strings[0],"jedna");
    strcpy(strings[1],"dve");
    strcpy(strings[2],"tri");
    strcpy(strings[3],"ctyri");
    strcpy(strings[4],"pet");
    for(size_t i = 0; i < 5; i++){
        printf("memory: %s\n", strings[i]);
        printf("counter: %u\n", *getCounterPp(strings[i]));
        printf("length: %i\n",getLengthp(strings[i]));
    }
    printf("meta counter: %u\n",*getCounterPp(strings));
    printf("length: %i\n",getLengthp(strings));
    releaseArray2D(strings);
}

void trySquare() {
    char **strings = (char**) allocateArray2D(sizeof(char),5,NULL);
    if(!strings)
        return;
    strcpy(strings[0],"oooo");
    strcpy(strings[1],"oooo");
    strcpy(strings[2],"oooo");
    strcpy(strings[3],"oooo");
    strcpy(strings[4],"oooo");
    for(size_t i = 0; i < 5; i++){
        printf("memory: %s\n", strings[i]);
        printf("counter: %u\n", *getCounterPp(strings[i]));
        printf("length: %i\n",getLengthp(strings[i]));
    }
    printf("meta counter: %u\n",*getCounterPp(strings));
    printf("length: %i\n",getLengthp(strings));
    releaseArray2D(strings);
}


int main()
{
    trySize();
    /*putchar('\n');
    tryString();
    putchar('\n');
    tryArray();
    putchar('\n');
    trySizes2D();
    putchar('\n');
    tryStrings();
    putchar('\n');
    trySquare();*/

    return 0;
}
