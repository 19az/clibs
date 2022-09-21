
#include "text.h"
#include "../assert/my_assert.h"
#include "../rwfile/rwfile.h"
#include "../sorting/sorting.h"
#include "../strings/strings.h"

#include "../error_handling/error_handling.h"

void read_text_file(Text *text, const char *filename ERR_SUPPORT_DEFN) {
    ASSERT(text     != NULL);
    ASSERT(filename != NULL);
    
    int err_get_file_size = 0;
    size_t file_size = get_file_size(filename, &err_get_file_size);
    if (file_size == 0 ERR_HANDLED(ERR_FILE_EMPT_TEXT, "empty file"))
        return;
    if (err_get_file_size != 0) {
        err_get_file_size & ERR_FILE_STAT_RWFILE
            ERR_HANDLED(ERR_FILE_STAT_TEXT, "cannot get file stat");
        err_get_file_size & ERR_FILE_SIZE_RWFILE
            ERR_HANDLED(ERR_FILE_SIZE_TEXT, "cannot get file size");
        return;
    }
    
    char *buffer = (char*) calloc((size_t) file_size + 2, sizeof(char));
    if (buffer == NULL ERR_HANDLED(ERR_MEM_ALLOC_TEXT, "cannot calloc"))
        return;

    int err_read_file = 0;
    size_t read_bytes = read_file(filename, buffer, (size_t) file_size, &err_read_file);
    if (err_read_file != 0) {
        err_read_file & ERR_FILE_OPEN_RWFILE
            ERR_HANDLED(ERR_FILE_OPEN_TEXT, "cannot open file");
        err_read_file & ERR_FILE_READ_RWFILE
            ERR_HANDLED(ERR_FILE_READ_TEXT, "cannot read file");
        err_read_file & ERR_FILE_CLOSE_RWFILE
            ERR_HANDLED(ERR_FILE_CLOS_TEXT, "cannot close file");
        free(buffer);
        return;
    }
    buffer[read_bytes] = '\n';
    text->buffer = buffer;
}

void parse_lines_text(Text *text) {
    ASSERT(text != NULL)
    
    size_t n_parts = count_char_str(text->buffer, '\n');
    if (n_parts == 0)
        return 0;

    void *parts = calloc(n_parts, text->part->size);
    if (parts == NULL ERR_HANDLED(ERR_MEM_ALLOC_TEXT, "cannot calloc"))
        return;

    char *line_ptr = text->buffer;
    for (size_t i = 0; i < n_parts; i++) {
       // alloc 
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
    
    size_t n_parts = text->n_parts;
    uint8_t *lines = (uint8_t*) text->parts;
    for (size_t i = 0; i < n_parts; ++i) {
        text->part->print_line_stdout(lines + i * text->part->size);
    }
}

void reverse_order_lines(Text *text) {
    ASSERT(text != NULL)

    reverse_order(text->parts, text->n_parts, text->part->size);
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

#include "../error_handling/undef_error_handling.h"
