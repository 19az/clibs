#include <stdlib.h>

#include "../rwfile/rwfile.h"
#include "../sorting/sorting.h"
#include "text.h"

int read_text_file(Text *text, const char *filename) {
    if (text == NULL || filename == NULL) {
        return ERR_ARGS_NULL_READ_TEXT_FILE;
    }
    
    off_t file_size = get_file_size(filename);
    if (file_size == -1) {
        return ERR_FILE_SIZE_READ_TEXT_FILE;
    }
    
    char *buffer = (char*) calloc((size_t) file_size + 2, sizeof(char));
    if (buffer == NULL) {
        return ERR_MEM_ALLOC_READ_TEXT_FILE;
    }

    int rf_ret = read_file(filename, buffer, (size_t) file_size);
    if (rf_ret == -1) {
        free(buffer);
        return ERR_FILE_OPEN_READ_TEXT_FILE;
    } else if (rf_ret == 0) {
        free(buffer);
        return ERR_NO_BYTES_READ_TEXT_FILE;
    }

    buffer[file_size] = '\n';
    text->buffer = buffer;
    text->nSymbols = (size_t) file_size + 1;
    return rf_ret;
}

int parse_lines_text(Text *text) {
    if (text == NULL) {
        return ERR_ARG_NULL_PARSE_LINES_TEXT;
    }
    
    size_t nLines = count_char_buffer(text->buffer, '\n');
    if (nLines == 0)
        return 0;

    Line **lines = (Line**) calloc(nLines, sizeof(Line*));
    if (lines == NULL) {
        return ERR_MEM_ALLOC_PARSE_LINES_TEXT;
    }

    char *line_ptr = text->buffer;
    size_t line_length = 0;
    for (size_t i = 0; i < nLines; i++) {
        lines[i] = (Line*) calloc(sizeof(Line));
        if (lines[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(lines[j]);
            }
            free(lines);
            return ERR_MEM_ALLOC_PARSE_LINES_TEXT;
        }
        
        line_length = read_line_buffer(line_ptr);
        lines[i]->start = line_ptr;
        lines[i]->length = line_length;
        line_ptr += line_length + 1;
    }
    text->nLines = nLines;
    text->lines = lines;
    return 0;
}

void print_all_lines_stdout(const Text *text) {
    if (text == NULL)
        return;
    
    size_t nLines = text->nLines;
    Line **lines = text->lines;
    for (size_t i = 0; i < nLines; ++i) {
        print_line_stdout(lines[i]);
    }
}

void reverse_order_lines(Text *text) {
    if (text == NULL)
        return;

    reverse_order(text->lines, text->nLines, sizeof(Line*));
}

void sort_lines_length_bubble_sort(Text *text) {
    if (text == NULL)
        return;

    bubble_sort(text->lines,
                text->nLines,
                sizeof(Line*),
                compare_lines_length);
}

void sort_lines_length_quick_sort(Text *text) {
    if (text == NULL)
        return;

    quick_sort(text->lines,
               text->nLines,
               sizeof(Line*),
               compare_lines_length);
}

void sort_lines_lexicographic_bubble_sort(Text *text) {
    if (text == NULL)
        return;

    bubble_sort(text->lines,
                text->nLines,
                sizeof(Line*),
                compare_lines_lexicographic);
}

void sort_lines_lexicographic_quick_sort(Text *text) {
    if (text == NULL)
        return;

    quick_sort(text->lines,
               text->nLines,
               sizeof(Line*),
               compare_lines_lexicographic);
}

void sort_lines_reverse_lexicographic_bubble_sort(Text *text) {
    if (text == NULL)
        return;

    bubble_sort(text->lines,
                text->nLines,
                sizeof(Line*),
                compare_lines_reverse_lexicographic);
}

void sort_lines_reverse_lexicographic_quick_sort(Text *text) {
    if (text == NULL)
        return;

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
