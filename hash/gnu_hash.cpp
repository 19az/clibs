
#include "gnu_hash.h"

#include "../error_handling/error_handling.h"

uint32_t gnu_hash(const char *start, const char *finish)
{
    ASSERT(start  != NULL);
    ASSERT(finish != NULL);

    uint32_t hash = 5381;

    while (start != finish)
    {
        hash = ((hash << 5) + hash) + (uint32_t) *start++;
    }

    return hash;
}

