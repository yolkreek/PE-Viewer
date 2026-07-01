#include "headers.h"
#include <stdio.h>
#include <stdint.h>
#define MEM_SIZE 200
#define F_ALIGN 512 //0x200

char* sample = "samples/tiny.exe";
uint8_t memory[MEM_SIZE] = {0, 1, 2, 3, 4, 68, 29, 12, 16, 15, 18, 19, 50};
char memoryOfSample[MEM_SIZE] = {0,};

int main(int argc, char** argv)
{
    Status code1 = viewMemorySnippet(memory, MEM_SIZE, 50, 150);
    if (code1 != NOERROR) printf("There was some error: %d", code1);

    Status code2 = fileRead(memory, sample);
    if (code2 != NOERROR) printf("There was some error: %d", code2);
    viewMemoryMap(memory, MEM_SIZE);

    return 0;
}