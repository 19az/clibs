#ifndef TEXT_H
#define TEXT_H

/// @file text.h

#include <stdlib.h>

#include "../error_handling/error_handling.h"

/// Struct to represent one part of the partition of the text
struct Part {
    size_t size = 0; ///< size of struct with part

    size_t (*get_n_of_parts) (const char *buffer) = NULL; ///< Func which counts
                                                          /// number of parts
                                                          /// in the buffer
    size_t (*set_part) (void *part,
                        const char *start) = NULL;        ///< Func which set value
                                                          /// for one part
                                                          /// of the text

    void (*print_part_stream) (FILE *stream,
                               const void *part) = NULL;  ///< Func which prints
                                                          /// one part in stream
};

/// Struct to represent texts
struct Text {
    const Part *part = NULL; ///< pointer to the info struct about text partition
    char *buffer     = NULL; ///< buffer with text 
    void *parts      = NULL; ///< array of Lines of the text
    size_t n_parts   = 0;     ///< number of lines in text
};

/// Enum of error codes for text.h
enum errcodes_text
{
ERR_FILE_EMPT_TEXT  =  1,       ///< given file is empty
ERR_FILE_STAT_TEXT  = (1 << 1), ///< error during obtaining file stat
ERR_FILE_SIZE_TEXT  = (1 << 2), ///< error during obtaining file size
ERR_FILE_OPEN_TEXT  = (1 << 3), ///< error during openning file
ERR_FILE_READ_TEXT  = (1 << 4), ///< error during reading file
ERR_FILE_CLOS_TEXT  = (1 << 5), ///< error during closing file
ERR_MEM_ALLOC_TEXT  = (1 << 6)  ///< error during allocating memory
};

/// @brief Read text from file
///
/// @param[in] filename name of file
///
/// @note provides ERR_SUPPORT mode
///
/// @see ERR_SUPPORT
void read_text_file(Text *text, const char *filename ERR_SUPPORT_DECL);

/// @brief Parses parts in text
///
/// @param text pointer to the Text
///
/// @note provides ERR_SUPPORT mode
///
/// @see ERR_SUPPORT
void parse_text(Text *text ERR_SUPPORT_DECL);

/// @brief Prints all parts on the text in stream
///
/// @param text pointer to the Text
/// @param[in] stream stream to print parts
///
/// @note Function does not check if given pointers are valid
void print_all_parts_stream(FILE *stream, const Text *text);

/// @brief Replaces lines in reverse order
///
/// @param text pointer to the text
///
/// @note Function does not check if given pointers are valid
void reverse_order_parts(Text *text);

/// @brief Sorts parts with given comparator
///
/// @param text pointer to the text
/// @param[in] comp pointer to the comparator function
void sort_parts(Text *text, int (*comp) (const void *a, const void *b));

/// @brief Frees all dynamic memory links
///
/// @param text pointer to the text
void dealloc_struct_text(Text *text);

#include "../error_handling/undef_error_handling.h"

#endif /* TEXT_H */
