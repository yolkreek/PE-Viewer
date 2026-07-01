#include <stdio.h>

#define NOERROR 0X0
#define ERROR_OUT_OF_RANGE 0X1
#define ERROR_INVALID_SIZE 0X2
#define ERROR_INVALID_RANGE 0X3
#define ERROR_INVALID_MEMORY 0X4


int viewMemoryMap(char* memory, int size); //if size is 0, show all memory map
int viewMemorySnippet(char* mem, int memSize, int rangeFrom, int rangeTo);
void printMemOutline();
void printMemoryLine(char* mem, int line, int rangeFrom, int rangeTo);