#include <stdio.h>
#include "memory.h"
#define MEM_SIZE 200
#define F_ALIGN 512 //0x200

char* sample = "samples/tiny.exe";
char memory[MEM_SIZE] = {0, 1, 2, 3, 4, 68, 29, 12, 16, 15, 18, 19, 50};

int main(int argc, char** argv)
{
    printf("Hello, world.\n");
    int code = viewMemoryMap(memory, MEM_SIZE);
    int code1 = viewMemorySnippet(memory, MEM_SIZE, 50, 150);
    if (code != NOERROR) printf("There was some error: %d", code);
    return 0;
}