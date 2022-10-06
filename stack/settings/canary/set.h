
/// @file stack_canaries_settings.h
///
/// @brief Настройка "канареек" для stack.h

#include <stdint.h>
#include <stdio.h>

#define CANARY_STACK uint64_t
    
#define POISON_CANARY_STACK 0xDEADCA17A129DEAD

#define FPRINTF_CANARY_STACK(stream, canary)                      \
    (ASSERT(stream != NULL), fprintf(stream, "%lx\n", (canary) ))

