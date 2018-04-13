#ifndef STRING_LIBRARY_MATRIX_H
#define STRING_LIBRARY_MATRIX_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/**
 * Gets minimal and maximal value per each row
 * @param mrows - Number of rows
 * @param mcols - Number of cols
 * @param matrix - Input matrix which has given rows and cols
 * @param result - Input matrix which has given rows and 2 col - first contains minimal value, second maximal
 */
void matrixRowInfo(int mrows,
                   int mcols,
                   int matrix[mrows][mcols],
                   int result[mrows][2]);

/**
 * Gets matrix of strings and returns array containing string length per each row
 * @param mrows - Number of rows in matrix, cols are fixed do 256
 * @param matrix - Matrix of given rows and fixed cols of size 256 chars
 * @param result - Array of size_t lengths of strings in each row.
 * @return Pointer on the row containing longest string
 */
char *matrixStringInfo(const int mrows,
                       char matrix[mrows][256],
                       size_t result[mrows]);


/**
 * Splits given string and result puts into result matrix
 * @param original - Input string
 * @param result - Result matrix which has fixed 50 rows and 256 cols
 * @param size - Number of rows of result matrix which will be used
 * @param delim - Character by which will be split original string. Result substring will not contain this character.
 */
void stringSplit(const char *original, char result[50][256], int *size, char delim);

/**
 * This is an universal function which will apply some operation on each character in string
 * @param string - Input string
 * @param result - Any type of result
 * @void func - Function callback which will takes partial result, position in original string and actual character
 */
void stringMap(const char *string,
               void *result,
               void (*func)(void *, int, const char));


void stringSplit2(const char *orig, char *buffer, char delim, char *result[26]);



#endif
