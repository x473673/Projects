//
// Created by Peter Stanko on 15.2.16.
//

#ifndef STRING_LIB_DYNAMIC_H
#define STRING_LIB_DYNAMIC_H


#include <stddef.h>


/**
 * Copies string and returns pointer to new string
 * @param str - original string
 * @return New string allocated by malloc
 */
char * dynamicStringCopy(const char *str);

/**
 * Copies only first N (length) of characters
 * @param str - Original string
 * @param length - number of characters to be copied
 * @return New string
 */
char * dynamicStringCopyN(const char *str, size_t length);

/**
 * Joins both strings into one
 * @param pre - First string
 * @param post - Second string
 * @return New string
 */
char * dynamicStringJoin(const char * pre, const char *post);

/**
 * Join strings contained in array of strings of size defined by param size
 * @param array - Input array of string of size defined by size
 * @param size - size of array
 * @param joinStr - String between each substrings
 */
char *stringJoinStrings(char **array, size_t size, const char *joinStr);

/**
 * Reads full line from standard input (stdin)
 * @return Whole line
 */
char * readFullLine();


/**
 * Implementation of dynamic split
 */
char **dynamicStringSplitSub(const char *orig, const char *splitter, size_t *size);

/**
 * Impmenetation of dynamic string replace
 */
char * dynamicStringReplace(const char * orig, const char *sample, const char *newSample);






#endif //STRING_LIB_DYNAMIC
