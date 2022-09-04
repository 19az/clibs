#include <stdio.h>

#include "line.h"
#include "../assert/my_assert.h"
#include "../strings/strings.h"
#include "../symbols/symbols.h"

void print_line_stdout(const Line *line) {
    ASSERT(line != NULL)

    for (size_t i = 0; i < line->length; i++) {
        putchar(line->start[i]);
    }
    putchar('\n');
}

size_t get_line_len(Line *line) {
    ASSERT(line != NULL)

    line->length = (size_t) (my_strchr(line->start, '\n') - line->start);
    return line->length;
}

int compare_lines_length(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL)
    ASSERT(ptr2 != NULL)
    if (ptr1 == ptr2)
        return 0;

    Line *lineptr1 = cast_void_to_lineptr(ptr1);
    Line *lineptr2 = cast_void_to_lineptr(ptr2);
    if (lineptr1->length > lineptr2->length) return 1;
    if (lineptr1->length < lineptr2->length) return -1;
    return 0;
}

Line *cast_void_to_lineptr(const void *ptr) {
    ASSERT(ptr != NULL)

    Line *lineptr = NULL;
    unsigned char *uchlineptr = (unsigned char*) &lineptr;
    const unsigned char *uchptr = (const unsigned char*) ptr;
    for (size_t i = 0; i < sizeof(Line*); i++) {
        uchlineptr[i] = uchptr[i];
    }
    return lineptr;
}

int compare_lines_lexicographic(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL)
    ASSERT(ptr2 != NULL)
    if (ptr1 == ptr2) 
        return 0;

    Line *lineptr1 = cast_void_to_lineptr(ptr1);
    Line *lineptr2 = cast_void_to_lineptr(ptr2);
    const char *str1 = lineptr1->start;
    const char *str2 = lineptr2->start;
    size_t len1 = lineptr1->length;
    size_t len2 = lineptr2->length;
    size_t index1 = 0;
    size_t index2 = 0;
    while (index1 < len1 && index2 < len2) {
        index1 += skip_no_letters(str1 + index1, len1 - index1);
        index2 += skip_no_letters(str2 + index2, len2 - index2);
        if (index1 == len1 || index2 == len2) break;

        if (upper_case(str1[index1]) != upper_case(str2[index2])) break;
        index1++;
        index2++;
    } 

    if (index1 == len1) {
        return (index2 == len2) ? 0 : -1;
    } else {
        if (index2 == len2) {
            return 1;
        } else {
            if (upper_case(str1[index1]) > upper_case(str2[index2])) return 1;
            if (upper_case(str1[index1]) < upper_case(str2[index2])) return -1;
            return 0;
        }
    }
}

int compare_lines_reverse_lexicographic(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL)
    ASSERT(ptr2 != NULL)
    if (ptr1 == ptr2) 
        return 0;

    Line *lineptr1 = cast_void_to_lineptr(ptr1);
    Line *lineptr2 = cast_void_to_lineptr(ptr2);
    const char *str1 = lineptr1->start;
    const char *str2 = lineptr2->start;
    size_t len1 = lineptr1->length;
    size_t len2 = lineptr2->length;
    while (len1 > 0 && len2 > 0) {
        len1 = skip_no_letters_reverse(str1, len1);
        len2 = skip_no_letters_reverse(str2, len2);
        if (len1 == 0 || len2 == 0) break;

        if (upper_case(str1[len1 - 1]) != upper_case(str2[len2 - 1])) break;
        len1--;
        len2--;
    } 

    if (len1 == 0) {
        return (len2 == 0) ? 0 : -1;
    } else {
        if (len2 == 0) {
            return 1;
        } else {
            if (upper_case(str1[len1 - 1]) > upper_case(str2[len2 - 1])) return 1;
            if (upper_case(str1[len1 - 1]) < upper_case(str2[len2 - 1])) return -1;
            return 0;
        }
    }
}
