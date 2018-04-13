#include <stdlib.h>
#include <stddef.h>


#ifndef MY_STRING_H
#define MY_STRING_H

/*
 * Count of string length
 * @param str - Input string
 * @return Length of string; if str is NULL returns 0
 */
size_t stringLength(const char *str);


/**
 * Creates string copy
 * @param result - Where copy will be stored
 * @param origin - From what string you will create copy
 * @return pointer to copied string 
 */
char *stringCopy(char *result, const char *origin);

/** 
 * Counts chars in string
 * @param string - Input string where you will count chars
 * @param ch - Char to be count
 * @return Number of occurrences of character ch
 */
size_t stringCountChar(const char *string, char ch);

/**
 * Compares strings
 * @param first - First string to compare
 * @param second - Second string to compare
 * @return negative if first is "greater", zero if same, positive if sencod "greater"
 */
int stringCompare(const char *first, const char *second);

/**
 * Comares first N characters of string
 * @param first - First string to compare
 * @param second - Second string to compare
 * @param n - size of compared strings
 * @return negative if first is "greater", zero if same, positive if sencod "greater"
 */
int stringCompareN(const char *first, const char *second, size_t n);

/* COMPLEX */

/**
 * Counts substrings in string
 * @param original - Input string where you counting substrings
 * @param substring - Substring to be count
 * @return Number of substrings
 */
size_t stringCountSubstring(const char *original, const char *substring);

/**
 * Finding character in string and returns the pointer to that character
 * @param original - Input string where you are trying to find character
 * @param ch - Character you are trying to find
 * @return Pointer to first occurrence of character in string, NULL if string does not contains character
 */
const char *stringFindChar(const char *original, const char ch);

/**
 * Finding substring in string and returns the pointer to beginning of that substring
 * @param original - Input string where you are trying to find character
 * @param sub - Substring you are trying to find
 * @return Pointer to first occurrence of character in string, NULL if string does not contains character
 */
const char *stringFindSubstring(const char *orig, const char *sub);

/**
 * Converts all letters in string to upper
 * @param origin - Original string
 * @param result - Result of operation - must be same size or greater than original string
 * @return NULL if origin or result is NULL; pointer on the beginning of result
 */
char *stringToUpper(const char *origin, char *result);

/**
 * Converts all letters in string to lower
 * @param origin - Original string
 * @param result - Result of operation - must be same size or greater than original string
 * @return NULL if origin or result is NULL; pointer on the beginning of result
 */
char *stringToLower(const char *origin, char *result);

void stringInsertSort(char *string, int (*comparator)(char , char));

int cmp(char a, char b);


#endif
