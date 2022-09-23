
#include "text.h"
#include "../rwfile/rwfile.h"

#include "../error_handling/error_handling.h"

Text *construct_text_file(const char *filename, const Part *part) {
    ASSERT(part     != NULL);
    ASSERT(filename != NULL);
    
    ERR_TYPE_RWFILE err_read_whole_file = 0;
    char *buffer = (char*) read_whole_file(filename,
                                           sizeof(char),
                                           NULL,
                                           &err_read_whole_file);
    
    ASSERT(buffer != NULL);
    if (ERR_CHECK_CODE(err_read_whole_file, CODE_FROM_ERR_RWFILE))
        return NULL;

    size_t n_parts = 0;
    void *parts = part->parse_buffer(buffer, &n_parts);
    if (parts == NULL || n_parts == 0) { // TO DO: ADD ERROR HANDLER
        ERR_REPORT_MSSG("error during parsing text");
        if (buffer)
            free(buffer);
        return NULL;
    }

    Text *text = (Text*) calloc(1, sizeof(Text));
    if (text == NULL) {
        ERR_REPORT_MSSG("error during calloc");
        free(parts);
        free(buffer);
        return NULL;
    }

    text->buffer = buffer;
    text->part = part;
    text->parts = parts;
    text->n_parts = n_parts;
    return text;
}

void print_all_parts_stream(FILE *stream, const Text *text) {
    ASSERT(text != NULL);
    
    for (size_t i = 0; i < text->n_parts; i++) {
        text->part->print_part_stream(stream,
                (unsigned char*) text->parts + i * text->part->size);
    }
}

void destruct_text(Text *text) {
    if (text == NULL)
        return;

    if (text->buffer) {
        free(text->buffer);
        text->buffer = NULL;
    }
    if (text->parts) {
        free(text->parts);
        text->parts = NULL;
    }
    text->part = NULL;
    text->n_parts = 0;
    free(text);
}

#include "../error_handling/undef_error_handling.h"
