//
// Created by Wermington on 15.2.16.
//

#include "stringLibraryDynamic.h"
#include "stringLibrary.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define UNUSED(a) ((void) (a))

char *dynamicStringCopy(const char *str)
{
      if (!str) {
          return NULL;
      }
      char* result = (char*) malloc(strlen(str)+1);
      if(!result) {
          free(result);
          exit(0);
      }

      char* p = result;

      while (*str != 0) {
              *result = *str;
              result++;
              str++;
      }

      *result = 0;
      return p;
}

char *dynamicStringCopyN(const char *str, size_t length)
{
    if (!str) {
            return NULL;
    }
    char* result = (char*) (strlen(str) < length) ? malloc(strlen(str)+1) : malloc(length + 1);
    if(!result) {
        free(result);
        exit(0);
    }

    size_t i = 0;
    while((str[i] != 0) && (i < length)) {
        result[i] = str[i];
        i++;
    }

    result[i] = 0;
    return result;
}

char *dynamicStringJoin(const char *pre, const char *post)
{
    if (!pre || !post) {
            return NULL;
    }
    char* result = (char*) malloc(strlen(pre) + strlen(post) + 1);
    if(!result) {
        free(result);
        exit(0);
    }
    strcpy(result, pre);
    strcpy(result + strlen(pre),post);
    return result;
}

char *dynamicStringReplace(const char *orig, const char *sample, const char *newSample)
{
    if (!orig || !sample || !newSample) {
            return NULL;
    }
    char* result = (char*) malloc(strlen(orig) + 1);
    if(!result) {
        free(result);
        exit(0);
    }
    while(strstr(orig, sample)) {
        strcpy(strstr(orig, sample), newSample);
    }
    return result;
}


char *readFullLine()
{
    size_t size = 10;
    size_t pos = 0;
    int c = 0;
    char* result = (char*) malloc(10);
    if(!result) {
        free(result);
        exit(0);
    }
    while(1) {
        c = getchar();
        if((c == EOF) || (c == 10)) {
            break;
        }
        result[pos] = (char) c;
        pos++;
        if(pos == size){
            result = realloc(result, size * 2);
            if(!result) {
                free(result);
                exit(0);
            }
            size *= 2;
        }
    }
    return result;
}



char *stringJoinStrings(char **array, size_t size, const char *joinStr)
{
    if (!array) {
            return NULL;
    }

    size_t sizeOfAll = 0;
    for(size_t i = 0; i < size; i++) {
        sizeOfAll += strlen(array[i]);
    }

    size_t sizeOfJoin = strlen(joinStr);

    char* result = (char*) malloc(sizeOfAll + (size - 1) * sizeOfJoin + 1);
    if(!result) {
        free(result);
        exit(0);
    }
    size_t pos = 0;
    for(size_t i = 0; i < size-1; i++){
        if(array[i]) {
            strcpy(result + pos, array[i]);
            pos += strlen(array[i]);
        }
        if(array[i]) {
            strcpy(result + pos, joinStr);
            pos += sizeOfJoin;
        }
    }
    if(array[size - 1]) {
        strcpy(result + pos, array[size - 1]);
        pos += strlen(array[size - 1]);
    }
    result[pos] = 0;

    return result;
}

char **dynamicStringSplitSub(const char *orig, const char *splitter, size_t *size)
{
    // TODO
    UNUSED(orig);
    UNUSED(splitter);
    UNUSED(size);
    return NULL;
}


