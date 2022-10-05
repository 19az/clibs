
/// @file stack_elem_t.h
///
/// @brief Настройка типа элементов стека, параметров защиты и логов

#include <stdint.h>
#include <stdio.h>

const char* const logfilename = "logfile.txt";

typedef uint32_t Elem_t;

#define POISON_ELEM_T_PROTECT
const Elem_t  POISON_ELEM_T_STACK = 0xDEADF00D;

Elem_t* const POISON_ELEM_T_PTR_STACK = (Elem_t*) 0xDEADE1E17712DEAD;

#define FPRINTF_ELEM_T_STACK(stream, elem) \
    ASSERT(stream != NULL);                \
    fprintf(stream, "%x\n", *(elem));

#define CANARY_PROTECT
#define HASH_PROTECT

