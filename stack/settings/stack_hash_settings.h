
/// @file stack_hash_settings.h
///
/// @brief Настройка хешей для stack.h

#include <stdint.h>
#include <stdio.h>

typedef uint32_t HASH_TYPE_STACK;

#define FPRINTF_HASH_STACK(stream, hash) \
    ASSERT(stream != NULL);              \
    fprintf(stream, "%u\n", *(hash));

