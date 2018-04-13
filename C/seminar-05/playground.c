#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNUSED(a) ((void) a)

#include "stringLibraryMatrix.h"

void  matrixFiller(int rows, int cols, int matrix[rows][cols])
{
        for(int row = 0; row < rows; row++)
        {
                for(int col = 0; col < cols; col++)
                {
                        matrix[row][col] = row + col;
                }
        }
}


void matrixPrinter(int rows, int cols, int matrix[rows][cols])
{
        for(int row = 0; row < rows; row++)
        {
                for(int col = 0; col < cols; col++)
                {
                        printf("%d ", matrix[row][col]);
                }
                printf("\n");
        }
}

void resultPrinter(int rows, int matrix[rows][2])
{
        for(int row = 0; row < rows; row++)
        {
                for(int col = 0; col < 2; col++)
                {
                        printf("%d ", matrix[row][col]);
                }
                printf("\n");
        }
}

void playMatrixInt()
{
        const int rows = 5;
        const int cols = 4;        
        int matrix[rows][cols];
        int result[rows][2];
        matrixFiller(rows, cols, matrix);
        printf("Matrix: \n");
        matrixPrinter(rows, cols, matrix);
        printf("\nResult: \n");
        matrixRowInfo(rows, cols, matrix, result);
        resultPrinter(rows, result);
        printf("\n###############\n");

}



void playMatrixStringInfo()
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

        printf("Longest string: \"%s\"\n", longs);
        printf("Result array: [");

        for (int i = 0; i < rows; i++)
        {
                printf("%d, ", (int) result[i]);
        }
        printf(" ]\n\n");


}


void playSplit()
{
        const char *original = "Ahoj svet 000 Query";
        char result[50][256];
        int size;
        char delim = ' ';

        stringSplit(original, result, &size, delim);
        printf("SPLIT: \nSize: %d\nParts: \n", size);
        for(int i = 0; i < size; i++)
        {
                printf("   %d. - %s\n", i + 1, result[i]);
        }

}


void funcLen(void * l, int i, const char c)
{
        UNUSED(i);
        UNUSED(c);
        int *len = (int *)l;
        (*len)++;
}


void playMap()
{
        const char *string = "Ahoj svet";
        int length = 0;
        stringMap(string, &length, funcLen);
        printf("\nMap: ");
        printf("Strlen: %d\n", length);

}


int cmpInc(char a, char b)
{
        return a - b;
}

int cmpDec(char a, char b)
{
        return b - a;
}


int main(void)
{
        char buffer[60];
        char *result[26];
        /* Tato cast sa zaobera matrix info pre cele cisla */
        playMatrixInt();

        /* Praca s maticou retazcov  */
        playMatrixStringInfo();

        playSplit();

        playMap();

        stringSplit2("Hello world, I have not seen you for a long time!",
                     buffer,
                     ' ',
                     result);
        for(int i = 0; result[i] != NULL; i++){
            for(int j = 0; result[i][j] != 0; j++){
                putchar(result[i][j]);
            }
            putchar('\n');
        }


        return 0;
}

