#define TESTING
#define TESTING_MAIN
#include <stdlib.h>
#include <string.h>
#include "testing.h"
#include "stringLibraryDynamic.h"



#define STREQ(a, b) ASSERT(strcmp((a), (b)) == 0)


TEST(DynamicStringCopy)
{
        const char *orig = "Ahoj svet !";
        char *copy = dynamicStringCopy(orig);
        STREQ(orig, copy);
        free(copy);

        ASSERT(dynamicStringCopy(NULL) == NULL);
}

TEST(DynamicStringCopyN)
{
        const char *orig = "Ahoj svet !";
        char *copyN = dynamicStringCopyN(orig, 4);
        STREQ("Ahoj", copyN);
        free(copyN);

        ASSERT(dynamicStringCopyN(NULL, 100) == NULL);
}


TEST(DynamicStringJoin)
{
        const char *ahoj = "Ahoj ";
        const char *svet = "svet!";
        char *result = dynamicStringJoin(ahoj, svet);
        STREQ(result, "Ahoj svet!");
        free(result);

        ASSERT(dynamicStringJoin(NULL, "ahoj") == NULL);
        ASSERT(dynamicStringJoin("ahoj", NULL) == NULL);
}


TEST(StringStringsJoin)
{
        char *strings[5];
        for(int i = 0; i < 5; i++)
        {
                strings[i] = (char*) malloc(sizeof(char) * 10);
        }

        strcpy(strings[0], "Ahoj");
        strcpy(strings[1], "svet");
        strcpy(strings[2], "moriak");
        strcpy(strings[3], "kalerab");
        strcpy(strings[4], "snicla");

        char *result = stringJoinStrings( (char**) strings, 5, ", ");

        STREQ(result, "Ahoj, svet, moriak, kalerab, snicla");

        free(result);
        for(int i = 0; i < 5; i++)
        {
                free(strings[i]);
        }

        ASSERT(stringJoinStrings( NULL, 5, ", ") == NULL);
}


TEST(playReplace)
{
        const char *orig = "123 123 456 123 456 852";
        const char *sample = "456";
        const char *news = "123";
        char *replace = dynamicStringReplace(orig, sample, news);

        STREQ(replace, "123 123 123 123 123 852");

        free(replace);
        ASSERT(dynamicStringReplace(NULL, sample, news) == NULL);
}



TEST(Split)
{
        const char *orig = "carrot, bannana, orange, kebab, mouse";
        size_t size;
        char **split = dynamicStringSplitSub(orig, ", ", &size);
        ASSERT(size == 5);
        STREQ(split[0], "carrot");
        STREQ(split[1], "bannana");
        STREQ(split[2], "orange");
        STREQ(split[3], "kebab");
        STREQ(split[4], "mouse");


        for(size_t i = 0; i < size + 1; i++)
        {
                free(split[i]);
        }
        free(split);

        ASSERT( dynamicStringSplitSub(NULL, ", ", &size) == NULL);
}



