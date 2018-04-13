#ifndef __READ_LIB_H__
#define __READ_LIB_H__

#define BUFFER_MAX_LEN 1024

int readInt(void);
long readLong(void);
long long readLongLong(void);
unsigned int readUInt(void);
unsigned long readULong(void);
unsigned long long readULongLong(void);

float readFloat(void);
double readDouble(void);

char readChar(void);
char *readWord(void);
char *readLine(void);

/**
 * Reads any characters until new line or End of file signal
 * @return 1 if EOF and 0 if new line
 */
int readEndOfLine(void);

#endif // __READ_LIB_H__

