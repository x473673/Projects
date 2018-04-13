#include "pb071_io.h"
#include <stdio.h>
#include <stdlib.h>

#define INTERN_BUFFER_MAX_LEN (BUFFER_MAX_LEN+1)

int readInt(void)
{
    int buffer = 0;

    if (scanf("%d", &buffer) != 1) {
        return 0;
    }
    return buffer;
}

long readLong(void)
{
    long buffer = 0;

    if (scanf("%ld", &buffer) != 1) {
        return 0l;
    }

    return buffer;
}

long long readLongLong(void)
{
    long long buffer = 0;

    if (scanf("%lld", &buffer) != 1) {
        return 0ll;
    }

    return buffer;
}

unsigned int readUInt(void)
{
    unsigned int buffer = 0;

    if (scanf("%u", &buffer) != 1) {
        return 0u;
    }

    return buffer;
}

unsigned long readULong(void)
{
    unsigned long buffer = 0;

    if (scanf("%lu", &buffer) != 1) {
        return 0lu;
    }

    return buffer;
}

unsigned long long readULongLong(void)
{
    unsigned long long buffer = 0;

    if (scanf("%llu", &buffer) != 1) {
        return 0llu;
    }

    return buffer;
}

float readFloat(void)
{
    float buffer = 0;

    if (scanf("%f", &buffer) != 1) {
        return 0u;
    }

    return buffer;
}

double readDouble(void)
{
    double buffer = 0;

    if (scanf("%lf", &buffer) != 1) {
        return 0u;
    }

    return buffer;
}

char readChar(void)
{
    return (char) getchar();
}

char *readWord(void)
{
    static char buffer[256];

    if (scanf("%255s", buffer) == 0) {
        return NULL;
    }

    return buffer;
}

char *readLine(void)
{
    static char buffer[INTERN_BUFFER_MAX_LEN];

    return fgets(buffer, BUFFER_MAX_LEN, stdin);
}

int readEndOfLine(void)
{
    int c = 0;
    while ( (c = getchar() != '\n') && (c != EOF)) {
        /* Do nothing */
    }
    return (c == EOF);
}

