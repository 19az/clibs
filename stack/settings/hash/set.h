
/// @file stack_hash_settings.h
///
/// @brief Настройка хешей для stack.h

#include <stdint.h>
#include <stdio.h>

#define HASH_TYPE_STACK uint32_t

#define FPRINTF_HASH_STACK(stream, hash)                       \
    (ASSERT(stream != NULL), fprintf(stream, "%u\n", (hash) ))

