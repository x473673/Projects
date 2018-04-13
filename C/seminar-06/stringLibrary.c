#include <stdio.h>
#include "stringLibrary.h"


size_t stringLength(const char *str)
{
        if (!str) { // str == NULL can be rewrited as !str
                return 0;
        }

        const char *it = str;

        while (*it != 0) {
                it++;
        }

        return it - str;
}

/**
 * Creates string copy
 * @return pointer to copied string 
 */
char *stringCopy(char *result, const char *origin)
{
        if (!result || !origin) {
                return NULL;
        }

        char *p = result;

        while (*origin != 0) {
                *result = *origin;
                result++;
                origin++;
        }

        *result = 0;

        return p;
}

/** 
 * Counts chars in string
 */
size_t stringCountChar(const char *string, char ch)
{
        if (!string) {
                return 0;
        }

        size_t counter = 0;

        while (*string) {

                if (*string == ch) {
                        counter++;

                }

                string++;
        }

        return counter;
}


/**
 * Compares strings 
 */
int stringCompare(const char *first, const char *second)
{
        size_t lenS = stringLength(second); // get length of first string
        size_t lenF = stringLength(first); // get length of second string
        size_t resLen = (lenF >= lenS) ? lenF : lenS; // use longer

        // Avoid code repetition
        return stringCompareN(first, second, resLen);
}


int stringCompareN(const char *first, const char *second, size_t n)
{
        if (first == second) { // CASE NULL == NULL && pointer == pointer
                return 0;
        }

        if (!first) { // First is NULL
                return -1;
        }

        if (!second) { // Second is NULL
                return 1;
        }

        while (*first && *second && n--) {

                if (*first == *second) {
                        first++;
                        second++;
                        continue;
                }

                return *first - *second;
        }

        if (n == 0) { // Case when first N are same
                return 0;
        }

        if (*first == '\0' && *second != '\0') { // case when N is not 0 and first < second
                return -1;
        }

        if (*first != '\0' && *second == '\0') { // case when N is not 0 and first > second
                return 1;
        }

        return 0;
}

/* COMPLEX */

size_t stringCountSubstring(const char *original, const char *substring)
{
        if (!original || !substring) {
                return 0;
        }

        size_t len = stringLength(substring);
        size_t counter = 0;

        while (*original) {

                if (!stringCompareN(original, substring, len)) {
                        counter++;
                }
                original++;
        }

        return counter;
}


const char *stringFindChar(const char *original, const char ch)
{
        if (!original) {
                return NULL;
        }

        while (*original) {
                if (*original == ch) { return original; }
                original++;
        }

        return NULL;
}

const char *stringFindSubstring(const char *orig, const char *sub)
{
        if (!orig || !sub) {
                return NULL;
        }

        size_t len = stringLength(sub);

        while (*orig) {
                if (stringCompareN(orig, sub, len) == 0) {
                        return orig;
                }
                orig++;
        }

        return NULL;
}

char *stringToUpper(const char *origin, char *result)
{
        if (!origin || !result) {
                return NULL;
        }
        char *pointer = result;

        while (*origin) {
                char c = *origin;
                if (c >= 'a' && c <= 'z') {
                        c = (char) ((c - 'a') + 'A');

                }
                *result = c;
                result++;
                origin++;
        }

        *result = 0;

        return pointer;
}

char *stringToLower(const char *origin, char *result)
{
        if (!origin || !result) {
                return NULL;
        }

        char *pointer = result;

        while (*origin) {
                char c = *origin;

                if (c >= 'A' && c <= 'Z') {
                        c = (char) ((c - 'A') + 'a');

                }
                *result = c;
                result++;
                origin++;
        }

        *result = 0;

        return pointer;
}

