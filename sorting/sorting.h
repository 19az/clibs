#ifndef SORTING_H
#define SORTING_H

#include <stdlib.h>

/// @file sorting.h

/// @brief Swaps two objects
///
/// @param[in] a pointer to the 1st object to swap
/// @param[in] b pointer to the 2nd object to swap
/// @param[in] size sizeof type of objects
///
/// @note if a == b returns, function does not check
/// if given pointers and size are valid
void swap_objects(void *a, void *b, size_t size);

/// @brief Replaces elements of the given array in reverse order
///
/// @param ptr pointer to the array to sort
/// @param[in] count number of elements in the array
/// @param[in] size size of each element in the array in bytes
///
/// @note if count == 0 returns, function does not check
/// if given pointers and size are valid
void reverse_order(void *ptr, size_t count, size_t size);

/// @brief Sorts the given array pointed to by ptr in ascending order.
///
/// @details Uses bubble sort algorythm
/// 
/// @param ptr pointer to the array to sort
/// @param[in] count number of elements in the array
/// @apram[in] size size of each element in the array in bytes
/// @param[in] comp comparison function which returns
/// a negative integer value if the first argument is less than the second,
/// a positive integer value if the first argument is greater than the second
/// and zero if the arguments are equivalent.
///
/// @note if count == 0 returns, function does not check
/// if given pointers and size are valid
void bubble_sort(void *ptr, size_t count, size_t size, int (*comp)(const void*, const void*));

/// @brief Does partition for quick_sort()
///
/// @param ptr array to do partition
/// @param[in] count number of elements in the array
/// @param[in] size size of each element of the array in bytes
/// @param[in] comp comparison function which returns
/// a negative integer value if the first argument is less than the second,
/// a positive integer value if the first argument is greater than the second
/// and zero if the arguments are equivalent.
///
/// @note if count == 0 returns, function does not check
/// if given pointers and size are valid
unsigned char *partition_quick_sort(unsigned char *ptr, size_t count, size_t size, int (*comp)(const void*, const void*));

/// @brief Sorts the given array pointed to by ptr in ascending order.
///
/// @details Uses quicksort algorythm
/// 
/// @param ptr pointer to the array to sort
/// @param[in] count number of elements in the array
/// @apram[in] size size of each element in the array in bytes
/// @param[in] comp comparison function which returns
/// a negative integer value if the first argument is less than the second,
/// a positive integer value if the first argument is greater than the second
/// and zero if the arguments are equivalent.
///
/// @note if count == 0 returns, function does not check
/// if given pointers and size are valid
void quick_sort(void *ptr, size_t count, size_t size, int (*comp)(const void*, const void*));

#endif /* ENDIF */
