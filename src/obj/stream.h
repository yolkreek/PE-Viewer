#pragma once

#include "object.h"

typedef struct _Stream Stream;
struct _Stream
{
    objMagic magic;
    char* str;
    unsigned int size;
    char* cursor;

    //buffer changes every time you read through stream
    char* buffer;
    unsigned int bufferSize;
};

Stream *streamCreate(const char *str, unsigned int size);
Status streamDestroy(Stream *s);
char *streamTell(Stream *s);
Status streamShift(Stream *s, int offset);
Status streamWarp(Stream *s, unsigned int index);
Status streamRead(Stream *s, unsigned int count);
void streamPrintBuffer(Stream* s);
