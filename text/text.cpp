
#include "text.h"
#include "../rwfile/rwfile.h"

#include "../error_handling/error_handling.h"

Text* construct_text_file(const char* filename, const Part* part)
{
    ASSERT(part     != NULL);
    ASSERT(filename != NULL);
    
    ERR_TYPE_RWFILE err_read_whole_file = 0;
    char* buffer = (char*) read_whole_file(filename,
                                           sizeof(char),
                                           NULL,
                                           &err_read_whole_file);

    if (err_read_whole_file)
    {
        ERR_CHECK_MSSG(stderr, err_read_whole_file, ERR_FILE_STAT_RWFILE);
        ERR_CHECK_MSSG(stderr, err_read_whole_file, ERR_FILE_SIZE_RWFILE);
        ERR_CHECK_MSSG(stderr, err_read_whole_file, ERR_FILE_OPEN_RWFILE);
        ERR_CHECK_MSSG(stderr, err_read_whole_file, ERR_FILE_READ_RWFILE);
        ERR_CHECK_MSSG(stderr, err_read_whole_file, ERR_FILE_CLOS_RWFILE);
        ERR_CHECK_MSSG(stderr, err_read_whole_file, ERR_MEM_ALLOC_RWFILE);

        free(buffer);

        return NULL;
    }
    ASSERT(buffer != NULL);

    size_t n_parts = 0;
    void* parts = part->parse_buffer(buffer, &n_parts);
    
    if (parts == NULL || n_parts == 0)
    {
        ERR_REPORT_MSSG(stderr, "error during parsing text");
        
        free(parts);

        return NULL;
    }

    Text *text = (Text*) calloc(1, sizeof(Text));
    
    if (text == NULL)
    {
        ERR_REPORT_MSSG(stderr, "error during calloc");
    
        free(parts);
        free(buffer);
        
        return NULL;
    }

    text->buffer  = buffer;
    text->part    = part;
    text->parts   = parts;
    text->n_parts = n_parts;
    
    return text;
}

void print_all_parts_stream(FILE* stream, const Text* text) {
    ASSERT(text != NULL);
    
    for (size_t i = 0; i < text->n_parts; i++)
    {
        text->part->print_part_stream(stream,
            (unsigned char*) text->parts + i * text->part->size);
    }
}

void destruct_text(Text* text) {
    if (text == NULL) return;

    free(text->buffer);
    text->buffer = NULL;

    free(text->parts);
    text->parts = NULL;

    text->part = NULL;
    text->n_parts = 0;

    free(text);
}

#include "../error_handling/undef_error_handling.h"
