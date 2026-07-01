#include "error.h"
#include <stdint.h>

Status fileDump(uint8_t *buffer, const char *filename, int dumpFrom, int dumpTo);
Status fileRead(uint8_t *buffer, const char *filename);