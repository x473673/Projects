#define TESTING
#define TESTING_MAIN
#include "testing.h"
#include "stringLibrary.h"


#include <string.h>

char buffer[255];
char *pointer = NULL;

#define STRLEN_REQ(a, len) ASSERT(stringLength(a) == len)

#define STRCMP_SREQ(a, b) ASSERT(stringCompare(a, b) == 0)

#define TEST_CPY(a) do {        \
        pointer = stringCopy(buffer, a); \
        ASSERT(buffer == pointer);\
        STRCMP_SREQ(buffer, pointer);\
}while(0)

#define STRCC(a, b, l) ASSERT(stringCountChar(a, b) == l)

#define STRCMP_EQ(a, b) ASSERT(stringCompare(a,b) == 0)
#define STRCMP_NEQ(a, b) ASSERT(stringCompare(a,b) != 0)
#define STRCMP_FIRST(a, b) ASSERT(stringCompare(a,b) <  0)
#define STRCMP_SEC(a, b) ASSERT(stringCompare(a,b) > 0)

#define STRSTR(a, b, l) ASSERT(stringCountSubstring(a,b) == l)




// String length 
TEST(length)
{
        STRLEN_REQ("Ahoj", 4);
        STRLEN_REQ("", 0);
        STRLEN_REQ(NULL, 0);

        STRLEN_REQ("Ahoj svet!", 10);
        STRLEN_REQ("Lorem\nIpsum\n Tabs Cols Rows\n", 28);
}


// String copy
TEST(copy)
{
        TEST_CPY("Ahoj");
        TEST_CPY("");
}


// String char count
TEST(charCount)
{
        STRCC("Ahoj", 'A', 1);
        STRCC("", 'A', 0);
        STRCC(NULL, 'A', 0);
        STRCC("AAAA", 'A', 4);
        STRCC("Ahoj", 'a', 0);
        STRCC("a aa aa bb ab bca", 'a', 7);
}

// String compare
TEST(compare)
{
        STRCMP_EQ("Ahoj svet", "Ahoj svet");
        STRCMP_NEQ("Ahoj", "ahoj");
        STRCMP_NEQ("aaa aa", "aaaa a");
        STRCMP_NEQ("aaaaa", "aaaa");
        STRCMP_FIRST("abc", "bcd");
        STRCMP_FIRST("Abc", "abc");
        STRCMP_SEC("abc", "abb");
}

// String N compare
TEST(compareN)
{
        ASSERT(stringCompareN("Ahoj", "Agoj", 1) == 0);
        ASSERT(stringCompareN("Ahoj", "Ahoj", 100) == 0);
        ASSERT(stringCompareN("Ahoj", "Agoj", 100) > 0);
        ASSERT(stringCompareN("Ahoj", "Agoj", 5) != 0);
}


// String Substr count
TEST(substringCount)
{
        STRSTR("aaa", "a", 3);
        STRSTR("", "a", 0);
        STRSTR(NULL, "a", 0);
        STRSTR("aaa", NULL, 0);
        STRSTR("aaab", "aa", 2);
        STRSTR("abba baa ba b", "a b", 3);
}



// String Char find
TEST(charFind)
{
        char array[] = "Hello world!";

        ASSERT(stringFindChar(array, 'H') == array);
        ASSERT(stringFindChar(array, 'l') == array + 2);
        ASSERT(stringFindChar(array, 'X') == NULL);

}


// String Substr find
TEST(substringFind)
{
        char array[] = "Hello world!";

        ASSERT(stringFindSubstring(array, "H") == array);
        ASSERT(stringFindSubstring(array, "ll") == array + 2);
        ASSERT(stringFindSubstring(array, "elo") == NULL);

}



// String to upper
TEST(stringUp)
{
        char result[255];
        STRCMP_SREQ(stringToUpper("ahoj", result), "AHOJ");
        STRCMP_SREQ(stringToUpper("ahoj svet", result), "AHOJ SVET");
        STRCMP_SREQ(stringToUpper("NulPoIn teR", result), "NULPOIN TER");
}


// String to lower
TEST(stringLow)
{
        char result[255];
        STRCMP_SREQ(stringToLower("AHOJ", result), "ahoj");
        STRCMP_SREQ(result, "ahoj");
        STRCMP_SREQ(stringToLower("AhOJ svERT 968", result), "ahoj svert 968");

        STRCMP_SREQ(result, "ahoj svert 968");

        STRCMP_SREQ(stringToLower("NulPoIn teR", result), "nulpoin ter");
        STRCMP_SREQ(result, "nulpoin ter");
}


