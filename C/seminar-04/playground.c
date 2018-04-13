//
// Created by Peter Stanko on 13.2.16.
//

#include <stdio.h>

#include "stringLibrary.h"




/*
 * Tento subor sluzi na jednoduche testovanie na roznych vstupoch a pomocne vypisy.
 *
 * TU si mozete odskusat funkcionalitu pred tym ako spustite unit testy.
 */
int main()
{
        const char *testString = "Ahoj svet!";
        const char *testString2 = "Ahoj Svet ahoj!";
        const char *testUp = "SVET AHOJ!";
        const char *testLow = "svet ahoj!";
        const char *charCount = "aabbaabb"; // a - 4*
        char *sortedString = testString;
        stringInsertSort(sortedString, cmp);


        char result[256];

        printf("Text: %s\n", testString);
        printf("Length: %u\n", (unsigned) stringLength(testString));
        printf("Copy: %s\n", stringCopy(result, testString));
        printf("Compare (%s == %s) : %s\n", testString2, testString, (stringCompare(testString2, testString) == 0 ? "EQUAL" : "NOT EQUAL"));
        printf("Count char ['a']: %u \n", (unsigned) stringCountChar(charCount, 'a'));
        printf("Count sub [\"aa\"]: %u \n", (unsigned) stringCountSubstring(charCount, "aa"));
        printf("String find [e]: %c\n", *stringFindChar(testString,'e'));
        printf("String find [vet] %s\n",  stringFindSubstring(testString, "vet"));
        printf("String UP: %s\n", stringToUpper(testString, result));
        printf("String LOW: %s\n", stringToLower(testString, result));
        printf("Sorted string: %s\n", sortedString);


        char array[] = "Hello world!";

        printf("FIND:  %s\n", stringFindSubstring(array, "H"));




        return 0;
}

