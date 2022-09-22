
#include <stdio.h>
#include <string.h>

#include "line.h"
#include "../../../sorting/sorting.h"
#include "../../../strings/strings.h"

#include "../../../error_handling/error_handling.h"

size_t count_n_lines(const char *buffer) {
    return count_char_str(buffer, '\n');
}

size_t set_line(void *voidptr_line, const char *start) {
    ASSERT(voidptr_line != NULL);
    ASSERT(start        != NULL);
    
    Line *line = (Line*) voidptr_line;
    line->start = start;
    const char *end = strchr(start, '\n');
    ASSERT(end != NULL);
    line->len = (size_t) (end - start);
    return line->len;
}

void print_line_stream(FILE *stream, const void *voidptr_line) {
    ASSERT(stream       != NULL);
    ASSERT(voidptr_line != NULL);

    const Line *line = (const Line*) voidptr_line;
    for (size_t index = 0; index < line->len; index++) {
        fputc(line->start[index], stream);
    }
    fputc('\n', stream);
}

int compare_lines_length(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL);
    ASSERT(ptr2 != NULL);
    if (ptr1 == ptr2)
        return 0;

    size_t size1 = ((const Line*) ptr1)->len;
    size_t size2 = ((const Line*) ptr2)->len;
    return (int) (size1 - size2);
}

int compare_lines_lex(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL);
    ASSERT(ptr2 != NULL);
    if (ptr1 == ptr2)
        return 0;

    const Line *line1 = (const Line*) ptr1;
    const Line *line2 = (const Line*) ptr2;
    return compare_lines_lexicographic(line1->start, line1->start + line1->len,
                                       line2->start, line2->start + line2->len,
                                       1, 1);
}

int compare_lines_reverse_lex(const void *ptr1, const void *ptr2) {
    ASSERT(ptr1 != NULL);
    ASSERT(ptr2 != NULL);
    if (ptr1 == ptr2)
        return 0;

    const Line *line1 = (const Line*) ptr1;
    const Line *line2 = (const Line*) ptr2;
    return compare_lines_lexicographic(line1->start + line1->len - 1, line1->start - 1,
                                       line2->start + line2->len - 1, line2->start - 1,
                                       1, 1);
}

#include "../../../error_handling/undef_error_handling.h"
