#include "memory.h"
#include <stdio.h>

Status viewMemoryMap(uint8_t* mem, int memSize)
{
    return viewMemorySnippet(mem, memSize, 0, memSize - 1);
}

//regarding that you're inputting correct memSize.
Status viewMemorySnippet(uint8_t* mem, int memSize, int rangeFrom, int rangeTo) 
{
    if (mem == NULL) return ERROR_NULLPTR;
    if (memSize <= 0) return ERROR_INVALID_SIZE;
    if (rangeFrom < 0 || rangeTo > memSize - 1) return ERROR_OUT_OF_RANGE;

    int range = rangeTo - rangeFrom + 1;

    if (range <= 0) return ERROR_INVALID_RANGE;
    
    int startLine = rangeFrom >> 4;
    int endLine = rangeTo >> 4;
    int lines = endLine - startLine + 1;
    //printf("%d %d %d %d %d", memSize, range, lines, startLine, endLine);

    printMemOutline();
    
    for (int i = startLine; i < endLine + 1; i++)
    {
        printMemoryLine(mem, i, i == startLine ? rangeFrom % 0x10 : 0, i == endLine ? rangeTo % 0x10 : 0x10);
        printf("\n");
    }
    
    return NOERROR;
}

void printMemoryLine(uint8_t* mem, int line, int rangeFrom, int rangeTo) 
{
    int indexCursor = line * 0x10 + rangeFrom;
    printf("%08X ", 0x10 * line);
    for (int j = 0; j < 0x10; j++)
        {
            if (j < rangeFrom || j > rangeTo) printf("%3s", " ");
            else printf("%02X ", mem[indexCursor++] & 0xFF);
        }
}

void printMemOutline()
{
    printf("%9s", " ");
    for (int i = 0; i < 16; i++)
        printf("%02X ", i);
    printf("\n");
}