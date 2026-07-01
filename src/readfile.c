#include "readfile.h"
#include <stdio.h>

static uint32_t getFileSize(const char *filename)
{
    FILE* f = fopen(filename, "r");
    fseek(f, 0, SEEK_END);
    uint32_t fileSize = ftell(f);
    fclose(f);

    return fileSize;
}

static uint32_t getFileLastIndex(const char *filename)
{
    return getFileSize(filename) - 1;
}

Status fileDump(uint8_t* buffer, const char* filename, int dumpFrom, int dumpTo)
{
    if (buffer == NULL) return ERROR_NULLPTR;
    if (filename == NULL) return ERROR_NULLPTR;
    if (dumpFrom < 0) return ERROR_OUT_OF_FILE;

    FILE* f = fopen(filename, "rb");
    if (f == NULL) return ERROR_NULLPTR;

    uint32_t fileLastIndex = getFileLastIndex(filename);

    if (fileLastIndex < dumpTo)
    {
        fclose(f);
        return ERROR_OUT_OF_FILE;
    }
    
    fseek(f, dumpFrom, SEEK_SET);

    fread(buffer, sizeof(uint8_t), dumpTo - dumpFrom + 1, f);

    fclose(f);

    return NOERROR;
}

Status fileRead(uint8_t *buffer, const char *filename)
{
    return fileDump(buffer, filename, 0, getFileLastIndex(filename));
}