
#include <stdlib.h>

#define STACK_CPP
#include "hash.h"

#ifdef HASH_PROTECT

#include "hash/gnu_hash.h"

/// @brief Алгоритм хэширования
#define HASH_ALG(...) gnu_hash(__VA_ARGS__)

HASH_TYPE_STACK GetHashStructStack_(const Stack* stk)
{
    ASSERT(stk       != NULL);
    
    return HASH_ALG( (const char*) &stk->data,
                    ((const char*) &stk->capacity) + sizeof(size_t));
}

HASH_TYPE_STACK GetHashDataStack_(const Stack* stk)
{
    ASSERT(stk       != NULL);
    ASSERT(stk->data != NULL);
    ASSERT(stk->data != POISON_ELEM_T_PTR_STACK);
    
    return HASH_ALG( (const char*)  stk->data,
                     (const char*) (stk->data + stk->capacity));
}

#endif /* HASH_PROTECT */

