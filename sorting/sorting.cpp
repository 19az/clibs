#include <stdio.h>

#include "sorting.h"
#include "../assert/my_assert.h"

void swap_objects(void *a, void *b, size_t size) {
    ASSERT(a != NULL)
    ASSERT(b != NULL)
    ASSERT(size != 0)
    if (a == b)
        return;

    unsigned char *ucha = (unsigned char*) a;
    unsigned char *uchb = (unsigned char*) b;
    unsigned char tmp = 0;
    for (size_t i = 0; i < size; ++i) {
        tmp = ucha[i];
        ucha[i] = uchb[i];
        uchb[i] = tmp;
    }
}

void reverse_order(void *ptr, size_t count, size_t size) {
    ASSERT(ptr != NULL)
    ASSERT(size != 0)
    if (count == 0)
        return;

    size_t left  = 0;
    size_t right = count - 1;
    unsigned char *uchptr = (unsigned char*) ptr;
    while (left < right) {
        swap_objects(uchptr + size*left++, uchptr + size*right--, size);
    }
}

void bubble_sort(void *ptr,
                 size_t count,
                 size_t size,
                 int (*comp)(const void*, const void*))
{
    ASSERT(ptr != NULL)
    ASSERT(size != 0)
    ASSERT(comp != 0)
    if (count == 0)
        return;

    unsigned char *uchptr = (unsigned char*) ptr;
    for (size_t ascent = 0; ascent < count; ascent++) {
        size_t nPairs = count - ascent - 1;
        for (size_t pair = 0; pair < nPairs; pair++) {
            unsigned char *pair_ptr1 = uchptr + size*pair;
            unsigned char *pair_ptr2 = pair_ptr1 + size;
            if (comp(pair_ptr1, pair_ptr2) > 0) {
                swap_objects(pair_ptr1, pair_ptr2, size);
            }
        }
    }
}

unsigned char *partition_quick_sort(unsigned char *ptr,
                                    size_t count,
                                    size_t size,
                                    int (*comp)(const void*, const void*))
{
    ASSERT(ptr != NULL)
    ASSERT(size != 0)
    ASSERT(comp != 0)
    ASSERT(count != 0)

    const unsigned char *value = ptr + size*(count - 1);
    unsigned char *left  = ptr;
    unsigned char *right = ptr + size*(count - 1);
    const unsigned char  *left_border = left;
    const unsigned char *right_border = right;
    while (left <= right) {
        while (comp(left,  value) < 0) {
            left += size;
            if (left > right_border) return NULL;
        }
        while (comp(right, value) > 0) {
            right -= size;
            if (right < left_border) return NULL;
        }
        if (left >= right) break;
        
        swap_objects(left, right, size);
        if (value == left) {
            value = right;
        } else if (value == right) {
            value = left;
        }
        left  += size;
        right -= size;
    }
    return left;
}

void quick_sort(void *ptr,
                size_t count,
                size_t size,
                int (*comp)(const void*, const void*))
{
    ASSERT(ptr != NULL)
    ASSERT(size != 0)
    ASSERT(comp != 0)
    if (count == 0)
        return;

    if (count <= 1)
        return;
    unsigned char *uchptr = (unsigned char*) ptr;
    unsigned char *pivot = partition_quick_sort(uchptr, count, size, comp);
    if (pivot == NULL)
        return;

    size_t left_count  = ((size_t) (pivot - uchptr)) / size;
    size_t right_count = count - left_count;
    quick_sort(ptr,    left_count, size, comp);
    quick_sort(pivot, right_count, size, comp);
}
