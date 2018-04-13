#include "stringLibraryMatrix.h"
#define UNUSED(a) ((void)(a))

void matrixRowInfo(int mrows,
                   int mcols,
                   int matrix[mrows][mcols],
                   int result[mrows][2])
{
    for (int row = 0; row < mrows; row++) {
        int min = INT_MAX;
        int max = INT_MIN;
        for(int col = 0; col < mcols; col++) {
            if(matrix[row][col] < min)
                min = matrix[row][col];
            if(matrix[row][col] > max)
                max = matrix[row][col];
        }
        result[row][0] = min;
        result[row][1] = max;
    }

}


char *matrixStringInfo(const int mrows, char matrix[mrows][256], size_t result[mrows])
{
    size_t max = 0;
    int maxRow = 0;
    for(int row = 0; row < mrows; row++){
        result[row] = strlen(matrix[row]);
        if (result[row] > max){
            max = result[row];
            maxRow = row;
        }
    }
    return matrix[maxRow];
}

void stringSplit(const char *original, char result[50][256], int *size, char delim)
{
    *size = 0;
    int col = 0;
    for(int i = 0; original[i] != 0; i++){
        if(original[i] == delim) {
            result[*size][col] = 0;
            col = 0;
            (*size)++;
        } else {
            result[*size][col] = original[i];
            col++;
        }
    }
    result[*size][col] = 0;
    (*size)++;

}

void stringSplit2(const char *orig, char *buffer, char delim, char *result[26]){
    int count = 0;
    int i = 0;
    result[0] = buffer;
    while(orig[i] != 0){
        if(orig[i] == delim) {
            count++;
            buffer[i] = 0;
            result[count] = buffer + i + 1;
        } else {
            buffer[i] = orig[i];
        }
        i++;
    }
    buffer[i] = 0;
    result[count+1] = NULL;
}


void stringMap(const char *string,
               void *result,
               void (*func)(void *, int, const char))
{
    for(int i = 0; string[i] != 0; i++){
        (*func)(result, i, string[i]);
    }
}





