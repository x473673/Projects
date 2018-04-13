#define TESTING
#define TESTING_MAIN
#include "testing.h"
#include "stringLibraryMatrix.h"
#define UNUSED(a) ((void) (a))

int matrixFiller(int rows, int cols, int matrix[rows][cols])
{
        for(int row = 0; row < rows; row++)
        {
                for(int col = 0; col < cols; col++)
                {
                        matrix[row][col] = row + col;
                }
        }
        return 0;
}

int asserter(int rows, int cols, int result[rows][2])
{
        for(int row = 0; row < rows; row++)
        {
                // MAXIMUM
                ASSERT(result[row][1] == row + cols - 1);
                // MINIMUM
                ASSERT(result[row][0] == row);

        }
        return 0;
}





TEST(MatrixRowInfo)
{
        const int rows = 5;
        const int cols = 4;
        int matrix[rows][cols];
        int result[rows][2];
        matrixFiller(rows, cols, matrix);
        matrixRowInfo(rows, cols,matrix,result);
        asserter(rows, cols, result);
}


TEST(MatrixStringInfo)
{
        const int rows = 10;
        char matrix[rows][256];
        size_t result[rows];
        const char * longest = "ahoj svet ahoj ahoj";
        strcpy(matrix[0], "Ahoj svet");
        strcpy(matrix[1], "ahoj svet");
        strcpy(matrix[2], "hoj svet");
        strcpy(matrix[3], "ahojsvet");
        strcpy(matrix[4], "ahoj Svet");
        strcpy(matrix[5], longest);
        strcpy(matrix[6], "123ahoj svet");
        strcpy(matrix[7], ".4855ahoj svet");
        strcpy(matrix[8], "protokol");
        strcpy(matrix[9], "0000000000");
        char * longs = matrixStringInfo(rows, matrix, result);

        ASSERT(strcmp(longest, longs) == 0);
        ASSERT(result[0] == strlen("ahoj svet"));
}


TEST(Split)
{
        const char *original = "Ahoj svet 000 Query";
        char result[50][256];
        int size;
        char delim = ' ';

        stringSplit(original, result, &size, delim);
        ASSERT(strcmp(result[0], "Ahoj") == 0);
        ASSERT(strcmp(result[1], "svet") == 0);
        ASSERT(strcmp(result[2], "000") == 0);
        ASSERT(strcmp(result[3], "Query") == 0);
        ASSERT(size == 4);




}

void funcLen(void * l, int i, const char c)
{
            // TODO
        UNUSED(i);
        UNUSED(c);
        int *len = (int *)l;
        (*len)++;
}


TEST(Map)
{
        const char *string = "Ahoj svet";
        size_t length = 0;
        stringMap(string, &length, funcLen);
        ASSERT(length == strlen(string));
}

