#include "../headers.h"
#include "stream.h"

static bool isStreamObj(Stream* s)
{
    return s != NULL && s->magic == STREAM_MAGIC;
}

static Status createBuffer(Stream* s, unsigned int bsize)
{
    s->buffer = (char*)malloc(bsize + 1);
    memset(s->buffer, 0, bsize + 1);
    s->bufferSize = bsize;

    return NOERROR;
}

static Status optimizeBuffer(Stream* s, unsigned int ssize)
{
    if (ssize == 0) return ERROR_INVALID_SIZE;
    if (s->bufferSize == ssize) return NOERROR;

    float ratio = (float)s->bufferSize / (float)ssize;

    if (ratio > 2.f || ratio < 1.f) 
        realloc(s->buffer, ssize + 1);
    
    s->bufferSize = ssize;
    memset(s->buffer, 0, s->bufferSize + 1);

    return NOERROR;
}

static bool isUnderflow(Stream* s, char* address)
{
    return address < s->str;
}

static bool isOverflow(Stream* s, char* address)
{
    return address >= s->str + s->size;
}

static bool isValidAddress(Stream* s, char* address)
{
    return !isUnderflow(s, address) && !isOverflow(s, address); 
}


Stream* streamCreate(const char* str, unsigned int size)
{
    Stream* s = (Stream*)malloc(sizeof(Stream));
    s->magic = STREAM_MAGIC;
    s->str = (char*)malloc(size);
    s->size = size;
    strncpy(s->str, str, size);
    s->cursor = s->str;

    s->buffer = NULL;
    s->bufferSize = 0;

    return s;
}

Status streamDestroy(Stream* s)
{
    if (!isStreamObj(s))
        return ERROR_INVALID_ADDRESS;
    s->magic = NONE_MAGIC;
    s->cursor = NULL;
    free(s->str);
    free(s);
    

    return NOERROR;
}

char* streamTell(Stream* s)
{
    return s->cursor;
}

Status streamShift(Stream* s, int offset)
{
    if (!isStreamObj(s))
        return ERROR_INVALID_ADDRESS;

    char* changeTo = s->cursor + offset;
    if (isValidAddress(s, changeTo))
    {
        s->cursor = changeTo;
        return NOERROR;
    }
    else
        return ERROR_INVALID_ADDRESS;
}

Status streamWarp(Stream* s, unsigned int index)
{
    return streamShift(s, s->str - s->cursor + index);
}

Status streamRead(Stream* s, unsigned int count)
{
    if (!isStreamObj(s))
        return ERROR_INVALID_ADDRESS;

    int validCount;
    bool cursorEnd = false;

    if (isOverflow(s, s->cursor + count))
    {
        validCount = s->str + s->size - s->cursor;
        cursorEnd = true;
    }
    else validCount = count;

    if (s->buffer == NULL)
        createBuffer(s, validCount);
    else 
        optimizeBuffer(s, validCount);

    for (int i = 0; i < validCount; i++)
        s->buffer[i] = *(s->cursor++);

    if (cursorEnd) s->cursor = s->str;

    return NOERROR;
    
}

void streamPrintBuffer(Stream* s)
{
    printf("%s\n", s->buffer);
}





