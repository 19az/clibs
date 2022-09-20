
#include <stdio.h>

#include "line.h"
#include "../strings/strings.h"
#include "../symbols/symbols.h"

#include "../error_handling/error_handling.h"

struct Line {
    const char *start = NULL;
    size_t len = 0;
};

void set_line(Line *line, const char *start) {
    ASSERT(line != NULL);
    
    line->start = start;
    line->len = (size_t) (my_strchr(line->start, '\n') - line->start);
}

void print_line_stdout(const Line *line) {
    ASSERT(line != NULL);

    const char *ptr = line->start;
    while (*ptr != '\n') putchar(*ptr++);
    putchar('\n');
}

int compare_lines_length(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL);
    ASSERT(ptr2 != NULL);
    if (ptr1 == ptr2)
        return 0;

    size_t size1 = ((const Line*) ptr1)->len;
    size_t size2 = ((const Line*) ptr2)->len;
    if (size1 > size2) return 1;
    if (size1 < size2) return -1;
    return 0;
}

int compare_lines_lexicographic(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL);
    ASSERT(ptr2 != NULL);
    if (ptr1 == ptr2) 
        return 0;

    const Line *line1  = (const Line*) ptr1;
    const Line *line2  = (const Line*) ptr2;
    const char *left1  = line1->start;
    const char *left2  = line2->start;
    const char *right1 = left1 + line1->len;
    const char *right2 = left2 + line2->len;
    while (1) {
        left1 = skip_no_letters(left1, right1, 1);
        left2 = skip_no_letters(left2, right2, 1);
        if (left1 == right1 || left2 == right2) break;

        if (upper_case(*left1) != upper_case(*left2) break;
        left1++;
        left2++;
    } 

    if (left1 == right1) {
        return (left2 == right2) ? 0 : -1;
    } else {
        if (left2 == right2) {
            return 1;
        } else {
            if (upper_case(left1) > upper_case(left2) return 1;
            if (upper_case(left1) < upper_case(left2) return -1;
            return 0;
        }
    }
}

int compare_lines_reverse_lexicographic(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL);
    ASSERT(ptr2 != NULL);
    if (ptr1 == ptr2) 
        return 0;

    Line *line1 = (const Line*) ptr1;
    Line *line2 = (const Line*) ptr2;
    const char *left1  = line1->start - 1;
    const char *left2  = line2->start - 1;
    const char *right1 = left1 + line1->len - 1;
    const char *right2 = left2 + line2->len - 1;
    while (1) {
        right1 = skip_no_letters_reverse(right1, left1, -1);
        right2 = skip_no_letters_reverse(right2, left2, -1);
        if (right1 == left1 || right2 == left2) break;

        if (upper_case(left1) != upper_case(right2)) break;
        right1--;
        right2--;
    } 

    if (right1 == left1) {
        return (right2 == left2) ? 0 : -1;
    } else {
        if (right2 == left2) {
            return 1;
        } else {
            if (upper_case(right1) > upper_case(right2)) return 1;
            if (upper_case(right1) < upper_case(right2)) return -1;
            return 0;
        }
    }
}

#include "../error_handling/undef_error_handling.h"
