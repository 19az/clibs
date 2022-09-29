
#include <stdio.h>
#include <stdint.h>

#define ERR_TYPE_STACK uint32_t

#ifndef STACK_ERRORS_H
#define STACK_ERRORS_H

const size_t POISON_STACK_SIZE_T         = 0xDEADF00D;
const Stack* POISON_STACK_FREE_STACK_PTR = (const Stack*) 1;

typedef struct {
    VAR_DATA var_data = {};
    FILE *logfile     = NULL;
} DEBUG_DATA;

const char *logfilename = "logfile.txt";

#endif /* STACK_ERRORS_H */

