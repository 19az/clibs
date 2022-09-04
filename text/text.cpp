#include <stdlib.h>

#include "text.h"
#include "../assert/my_assert.h"
#include "../rwfile/rwfile.h"
#include "../sorting/sorting.h"
#include "../strings/strings.h"

int read_text_file(Text *text, const char *filename) {
    ASSERT(text != NULL)
    ASSERT(filename != NULL)
    
    int file_size = get_file_size(filename);
    if (file_size == -1) {
        return ERR_FILE_SIZE_TEXT;
    } else if (file_size == 0) {
        return ERR_FILE_EMPTY_TEXT;
    }
    
    char *buffer = (char*) calloc((size_t) file_size + 2, sizeof(char));
    if (buffer == NULL) {
        return ERR_MEM_ALLOC_TEXT;
    }

    int rf_ret = read_file(filename, buffer, (size_t) file_size);
    if (rf_ret == -1) {
        free(buffer);
        return ERR_FILE_OPEN_TEXT;
    } else if (rf_ret == 0) {
        free(buffer);
        return ERR_FILE_READ_TEXT;
    }
    buffer[rf_ret] = '\n';
    text->buffer = buffer;
    text->nSymbols = (size_t) rf_ret + 1;

    return rf_ret;
}

int parse_lines_text(Text *text) {
    ASSERT(text != NULL)
    
    size_t nLines = count_char_str(text->buffer, '\n');
    if (nLines == 0)
        return 0;

    Line **lines = (Line**) calloc(nLines, sizeof(Line*));
    if (lines == NULL) {
        return ERR_MEM_ALLOC_TEXT;
    }

    char *line_ptr = text->buffer;
    for (size_t i = 0; i < nLines; i++) {
        lines[i] = (Line*) malloc(sizeof(Line));
        if (lines[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(lines[j]);
            }
            free(lines);
            return ERR_MEM_ALLOC_TEXT;
        }
        
        lines[i]->start = line_ptr;
        line_ptr += get_line_len(lines[i]) + 1;
    }
    text->nLines = nLines;
    text->lines = lines;
    return 0;
}

void print_all_lines_stdout(const Text *text) {
    ASSERT(text != NULL)
    
    size_t nLines = text->nLines;
    Line **lines = text->lines;
    for (size_t i = 0; i < nLines; ++i) {
        print_line_stdout(lines[i]);
    }
}

void reverse_order_lines(Text *text) {
    ASSERT(text != NULL)

    reverse_order(text->lines, text->nLines, sizeof(Line*));
}

void sort_lines_length_bubble_sort(Text *text) {
    ASSERT(text != NULL)

    bubble_sort(text->lines,
                text->nLines,
                sizeof(Line*),
                compare_lines_length);
}

void sort_lines_length_quick_sort(Text *text) {
    ASSERT(text != NULL)

    quick_sort(text->lines,
               text->nLines,
               sizeof(Line*),
               compare_lines_length);
}

void sort_lines_lexicographic_bubble_sort(Text *text) {
    ASSERT(text != NULL)

    bubble_sort(text->lines,
                text->nLines,
                sizeof(Line*),
                compare_lines_lexicographic);
}

void sort_lines_lexicographic_quick_sort(Text *text) {
    ASSERT(text != NULL)

    quick_sort(text->lines,
               text->nLines,
               sizeof(Line*),
               compare_lines_lexicographic);
}

void sort_lines_reverse_lexicographic_bubble_sort(Text *text) {
    ASSERT(text != NULL)

    bubble_sort(text->lines,
                text->nLines,
                sizeof(Line*),
                compare_lines_reverse_lexicographic);
}

void sort_lines_reverse_lexicographic_quick_sort(Text *text) {
    ASSERT(text != NULL)

    quick_sort(text->lines,
               text->nLines,
               sizeof(Line*),
               compare_lines_reverse_lexicographic);
}

void dealloc_struct_text(Text *text) {
    if (text == NULL)
        return;

    char *buffer = text->buffer;
    Line **lines = text->lines;
    size_t nLines = text->nLines;
    if (buffer) {
        free(buffer);
        buffer = NULL;
    }
    if (lines) {
        for (size_t i = 0; i < nLines; i++) {
            free(lines[i]);
        }
        free(lines);
        lines = NULL;
    }
}
