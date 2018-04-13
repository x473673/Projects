#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringLibraryDynamic.h"


void playDynamicStringCopy()
{
        const char *orig = "Ahoj svet !";
        char *copy = dynamicStringCopy(orig);
        char *copyN = dynamicStringCopyN(orig, 4);
        printf("Original: %s\n", orig);
        printf("Copy: %s\n", copy);
        printf("Copy N: %s\n", copyN);
        free(copy);
        free(copyN);
}

void playDynamicStringJoin()
{
        const char *ahoj = "Ahoj ";
        const char *svet = "svet!";
        char *result = dynamicStringJoin(ahoj, svet);
        printf("Joined strings: \"%s\"\n", result);
        free(result);
}

void playStringStringsJoin()
{
        char *strings[5];
        for(int i = 0; i < 5; i++)
        {
                strings[i] = (char *)  malloc(sizeof(char) * 10);
        }

        strcpy(strings[0], "Ahoj");
        strcpy(strings[1], "svet");
        strcpy(strings[2], "moriak");
        strcpy(strings[3], "kalerab");
        strcpy(strings[4], "snicla");

        char *result = stringJoinStrings( (char**) strings, 5, ", ");

        printf("Joined: %s\n", result);
        free(result);
        for(int i = 0; i < 5; i++)
        {
                free(strings[i]);
        }

}


void playReadFullLine()
{
        printf("Write something: ");
        char *line = readFullLine();
        printf("You have typed: \"%s\"\n", line);
        free(line);
}



void playReplace()
{
        const char *orig = "123 123 456 123 456 852";
        const char *sample = "456";
        const char *news = "123";
        char *replace = dynamicStringReplace(orig, sample, news);

        printf("Original string: %s\n", orig);
        printf("Replaced: %s\n", replace);

        free(replace);
}


void stringsPrinter(char **array, size_t size)
{
        for (int i = 0; i < (int) size; i++)
        {
                printf("%d - %s\n", i + 1, array[i]);
        }
}

void playSplit()
{
        const char *orig = "carrot, bannana, orange, kebab, mouse";
        size_t size;
        char **split = dynamicStringSplitSub(orig, ", ", &size);
        printf("Original string: %s\n", orig);
        printf("Splited:\n");
        stringsPrinter(split, size);
        for(size_t i = 0; i < size + 1; i++)
        {
                free(split[i]);
        }
        free(split);
}


int main()
{
    /*char* string = readFullLine();
    printf("%zu\n", strlen(string));
    free(string);*/

        playDynamicStringCopy();
        playDynamicStringJoin();
        playStringStringsJoin();
        playSplit();
        playReplace();


        return 0;
}

