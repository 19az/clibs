
#include <stdio.h>

#include "sorting.h"

#include "../error_handling/error_handling.h"

void reverse_order(void* ptr, size_t count, size_t size)
{
    ASSERT(ptr  != NULL);
    ASSERT(size != 0);

    if (count == 0) return;

    size_t   left  = 0;
    size_t   right = count - 1;
    uint8_t *uptr  = (uint8_t*) ptr;
    
    while (left < right)
    {
        swap_objects(uptr + size * left++,
                     uptr + size * right--,
                     size);
    }
}

void bubble_sort(void*    ptr,
                 size_t   count,
                 size_t   size,
                 int    (*comp)(const void*, const void*))
{
    ASSERT(ptr  != NULL);
    ASSERT(size != 0);
    ASSERT(comp != NULL);

    if (count <= 1) return;

    uint8_t *uptr = (uint8_t*) ptr;

    for (size_t ascent = 0; ascent < count; ascent++)
    {
        size_t n_pairs = count - ascent - 1;

        for (size_t pair = 0; pair < n_pairs; pair++)
        {
            uint8_t *pair_ptr1 = uptr      + size * pair;
            uint8_t *pair_ptr2 = pair_ptr1 + size;

            if (comp        (pair_ptr1, pair_ptr2) > 0)
                swap_objects(pair_ptr1, pair_ptr2, size);
        }
    }
}

void quick_sort(void*    ptr,
                size_t   count,
                size_t   size,
                int    (*comp)(const void*, const void*))
{
    ASSERT(ptr   != NULL);
    ASSERT(size  != 0);
    ASSERT(comp  != NULL);

    if (count <= 1) return;

    uint8_t *left  = (uint8_t*) ptr;
    uint8_t *right = left + (count - 1) * size;

    uint8_t *pivot  = partition_quick_sort(left, right, size, comp);
    ASSERT  (pivot >= left);
    ASSERT  (pivot <= right);

    if (pivot == NULL) return;

    quick_sort(left,         ((size_t) (pivot - left) + size) / size, size, comp);
    quick_sort(pivot + size, ((size_t) (right - pivot))       / size, size, comp);
}

uint8_t *partition_quick_sort(uint8_t*  left,
                              uint8_t*  right,
                              size_t    size,
                              int     (*comp)(const void*, const void*))
{
    ASSERT(left         != NULL);
    ASSERT(right        != NULL);
    ASSERT(right - left >= 1);
    ASSERT(size         != 0);
    ASSERT(comp         != NULL);

    const uint8_t *value = right;
    
    while (left < right)
    {
        while (comp(left,  value) < 0) left  += size;
        while (comp(right, value) > 0) right -= size;
        
        if (left > right) break;

        swap_objects(left, right, size);
        
        (value == left)  ? value = right :
        (value == right) ? value = left  : 0;

        left  += size;
        right -= size;
    }

    return right;
}

#define SWAPTYPE(type, while_if)                   \
while_if (size >= sizeof(type))                    \
{                                                  \
    type tmp           = *(type*) voidptr_a;       \
    *(type*) voidptr_a = *(type*) voidptr_b;       \
    *(type*) voidptr_b = tmp;                      \
                                                   \
    size -= sizeof(type);                          \
    voidptr_a = (void*) (((type*) voidptr_a) + 1); \
    voidptr_b = (void*) (((type*) voidptr_b) + 1); \
                                                   \
    continue;                                      \
}

#define SWAPTYPE_IF(type)    SWAPTYPE(type, if)
#define SWAPTYPE_WHILE(type) SWAPTYPE(type, while)

void swap_objects(void*   voidptr_a,
                  void*   voidptr_b,
                  size_t  size)
{
    ASSERT(voidptr_a != NULL);
    ASSERT(voidptr_b != NULL);
    ASSERT(size      != 0);

    if (voidptr_a == voidptr_b) return;

    const size_t align64 = sizeof(uint64_t) - 1;
    const size_t align32 = sizeof(uint32_t) - 1;
    const size_t align16 = sizeof(uint16_t) - 1;

    while (size > 0) 
    {
        uintptr_t ptr_a = (uintptr_t) voidptr_a;
        uintptr_t ptr_b = (uintptr_t) voidptr_b;

        if ((ptr_a & align64) == 0 &&
            (ptr_b & align64) == 0)
            SWAPTYPE_WHILE(uint64_t)
        
        if ((ptr_a & align32) == 0 &&
            (ptr_b & align32) == 0)
            SWAPTYPE_IF(uint32_t)
      
        if ((ptr_a & align16) == 0 &&
            (ptr_b & align16) == 0)
            SWAPTYPE_IF(uint16_t)
        
        SWAPTYPE_IF(uint8_t)
    }
}

#undef SWAPTYPE

#include "../error_handling/undef_error_handling.h"
