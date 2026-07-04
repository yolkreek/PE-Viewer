#pragma once

#include "error.h"
#include <stdint.h>

Status viewMemoryMap(uint8_t* memory, int size); //if size is 0, show all memory map
Status viewMemorySnippet(uint8_t* mem, int memSize, int rangeFrom, int rangeTo);