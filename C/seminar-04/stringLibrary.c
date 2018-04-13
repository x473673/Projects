#include <stdio.h>
#include "stringLibrary.h"

#define UNUSED(param) ((void) (param))

size_t stringLength(const char *str){
    size_t i = 0;
    if (str == NULL)
        return 0;
    while(str[i] != 0)
        i++;
    return i;
}


char *stringCopy(char *result, const char *origin)
{
    size_t i = 0;
    if (origin == NULL)
        return 0;
    while(origin[i] != 0){
        result[i] = origin[i];
        i++;
    }
    result[i] = 0;
    return result;
}

size_t stringCountChar(const char *string, char ch)
{
    size_t i = 0;
    size_t counter = 0;
    if (string == NULL)
        return 0;
    while(string[i] != 0){
        if(string[i] == ch){
            counter++;
        }
        i++;
    }
    return counter;
}



int stringCompare(const char *first, const char *second)
{
    size_t i = 0;
    if (first == NULL || second == NULL)
        return 0;
    do{
        if(first[i] != second[i])
            return first[i] - second[i];
        i++;
    }while(first[i] != 0);
    return 0;
}


int stringCompareN(const char *first, const char *second, size_t n)
{
    size_t i = 0;
    if (first == NULL || second == NULL)
        return 0;
    while(i < n){
        if(first[i] != second[i])
            return first[i] - second[i];
        i++;
    }
    return 0;
}


size_t stringCountSubstring(const char *original, const char *substring)
{
    size_t counter = 0;
    if (original == NULL || substring == NULL)
        return 0;
    for(size_t i = 0; original[i] != 0; i++){
        for(size_t j = 0; substring[j] == original[i+j]; j++){
            if(substring[j+1] == 0)
                counter++;
        }
    }
    return counter;
}


const char *stringFindChar(const char *original, const char ch)
{
    size_t counter = 0;
    if (original == NULL)
        return 0;
    for(size_t i = 0; original[i] != 0; i++){
        if(original[i] == ch)
            return original+i;
    }
    return NULL;
}

const char *stringFindSubstring(const char *orig, const char *sub)
{
    if (orig == NULL || sub == NULL)
        return 0;
    for(size_t i = 0; orig[i] != 0; i++){
        for(size_t j = 0; sub[j] == orig[i+j]; j++){
            if(sub[j+1] == 0)
                return orig+i;
        }
    }
    return NULL;
}

char *stringToUpper(const char *origin, char *result)
{
    size_t i = 0;
    if (origin == NULL)
        return 0;
    while(origin[i] != 0){
        if(origin[i] < 123 && origin[i] > 96)
            result[i] = origin[i] - 32;
        else
            result[i] = origin[i];
        i++;
    }
    result[i] = 0;
    return result;
}

char *stringToLower(const char *origin, char *result)
{
    size_t i = 0;
    if (origin == NULL)
        return 0;
    while(origin[i] != 0){
        if(origin[i] < 91 && origin[i] > 64)
            result[i] = origin[i] + 32;
        else
            result[i] = origin[i];
        i++;
    }
    result[i] = 0;
    return result;
}

int cmp(char a, char b)
{
    return a - b;
}

void stringInsertSort(char *string, int (*comparator)(char , char))
{
    char help;
    if (string == NULL)
        return 0;
   for(size_t i = 0; string[i] != 0; i++){
        for(size_t j = i; j > 0; j--){
            if(comparator(string[j - 1],string[j])>0){
                help = string[j - 1];
                string[j - 1] = string[j];
                string[j] = help;
            }
        }
    }
}
