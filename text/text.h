#ifndef TEXT_H
#define TEXT_H

/// @file text.h

#include <stdlib.h>

#include "../error_handling/error_handling.h"

/// Struct to represent one part of the partition of the text
struct Part {
    size_t size = 0;                                     ///< size of struct with part
    void* (*parse_buffer) (char *buffer,
                           size_t *n_lines) = NULL;      ///< Func which set value
                                                         /// for one part
                                                         /// of the text
    void (*print_part_stream) (FILE *stream,
                               const void *part) = NULL; ///< Func which prints
                                                         /// one part in stream
};

/// Struct to represent texts
struct Text {
    char *buffer     = NULL; ///< buffer with text 
    void *parts      = NULL; ///< array of Lines of the text
    const Part *part = NULL; ///< pointer to the info struct about text partition
    size_t n_parts   = 0;    ///< number of lines in text
};

/// @brief Constructs Text
///
/// @param[in] filename name of the file with text
/// @param[ni] part pointer to the struct with info
/// about partition
///
/// @return pointer to the Text allocated in dynamic memory
Text *construct_text_file(const char *filename, const Part *part);

/// @brief Prints all parts on the text in stream
///
/// @param text pointer to the Text
/// @param[in] stream stream to print parts
///
/// @note Function does not check if given pointers are valid
void print_all_parts_stream(FILE *stream, const Text *text);

/// @brief Frees all dynamic memory links
///
/// @param text pointer to the text
void destruct_text(Text *text);

#include "../error_handling/undef_error_handling.h"

#endif /* TEXT_H */
