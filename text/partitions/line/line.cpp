
#include <stdio.h>
#include <string.h>

#include "line.h"
#include "../../../sorting/sorting.h"
#include "../../../strings/strings.h"

#include "../../../error_handling/error_handling.h"

size_t count_n_lines(const char *buffer) {
    ASSERT(buffer != NULL);

    while (*buffer == '\n') buffer++;
    return count_chars_str(buffer, "\n", 1, 1);
}

void *parse_buffer_lines(char *buffer, size_t *n_lines) {
    ASSERT(buffer  != NULL);
    ASSERT(n_lines != NULL);

    *n_lines = count_n_lines(buffer);
    ASSERT(*n_lines != 0);
    
    Line *lines = (Line*) calloc(*n_lines, sizeof(Line));
    ASSERT(lines != NULL);

    const char *delim = "\n";
    char *saveptr = NULL;
    char *start_line = strtok_r(buffer, delim, &saveptr);
    for (size_t line = 0; line < *n_lines; line++) {
        ASSERT(start_line != NULL);
        lines[line] = {start_line, (size_t) (saveptr - start_line - 1)};
        start_line = strtok_r(NULL, delim, &saveptr);
    }

    return lines;
}

void print_line_stream(FILE *stream, const void *voidptr_line) {
    ASSERT(stream       != NULL);
    ASSERT(voidptr_line != NULL);

    const Line *line = (const Line*) voidptr_line;
    ASSERT(line->start != NULL);
    fprintf(stream, "%s\n", line->start);
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
