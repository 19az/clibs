#ifndef TEXT_H
#define TEXT_H

/// @file text.h

#include "line.h"

/// Struct to represent texts
struct Text {
    char *buffer = NULL; ///< buffer with text 
    Line **lines = NULL; ///< array of Lines of the text
    size_t nSymbols = 0; ///< number of symbols in text
    size_t nLines   = 0; ///< number of lines in text
};

enum retcodes_read_text_file       /// Enum of return codes of read_text_file()
{
ERR_NO_BYTES_READ_TEXT_FILE  =  0, ///< no bytes read error
ERR_FILE_OPEN_READ_TEXT_FILE = -1, ///< file openning error
ERR_MEM_ALLOC_READ_TEXT_FILE = -2, ///< memory allocation error
ERR_FILE_SIZE_READ_TEXT_FILE = -3, ///< getting file size error
ERR_ARGS_NULL_READ_TEXT_FILE = -4  ///< some args are NULL
};

/// @brief Read text from file
///
/// @param[in] filename name of file
///
/// @return number of bytes read on success,
/// 0  on no bytes read,
/// -1 on file opening error,
/// -2 on allocating memory error,
/// -3 on getting file size error,
int read_text_file(Text *text, const char *filename);

enum retcodes_parse_lines_text       /// Enum of return codes of parse_lines_text()
{
ERR_MEM_ALLOC_PARSE_LINES_TEXT = -1, ///< memory allocation error
ERR_ARG_NULL_PARSE_LINES_TEXT  = -2  ///< argument == NULL
};

/// @brief Parses lines in text
///
/// @param text pointer to the Text
///
/// @return 0 on success,
/// -1 on memory allocation error
int parse_lines_text(Text *text);

/// @brief Prints Line in stdout
///
/// @param[in] text pointer to the Text
void print_all_lines_stdout(const Text *text);

/// @brief Replaces lines in reverse order
///
/// @param text pointer to the text
void reverse_order_lines(Text *text);

/// @brief Sorts lines of given text by lengths in ascending order
///
/// @details uses bubble sort algorithm
///
/// @param text text to sort
void sort_lines_length_bubble_sort(Text *text);

/// @brief Sorts lines of given text by lengths in ascending order
///
/// @details uses quicksort algorithm
///
/// @param text text to sort
void sort_lines_length_quick_sort(Text *text);

/// @brief Sorts lines of given text lexicographically in ascending order
///
/// @details uses bubble sort algorithm
///
/// @param text text to sort
void sort_lines_lexicographic_bubble_sort(Text *text);

/// @brief Sorts lines of given text lexicographically in ascending order
///
/// @details uses quicksort algorithm
///
/// @param text text to sort
void sort_lines_lexicographic_quick_sort(Text *text);

/// @brief Sorts reversed lines of given text lexicographically in ascending order
///
/// @details uses bubble sort algorithm
///
/// @param text text to sort
void sort_lines_reverse_lexicographic_bubble_sort(Text *text);

/// @brief Sorts reversed lines of given text lexicographically in ascending order
///
/// @details uses quicksort algorithm
///
/// @param text text to sort
void sort_lines_reverse_lexicographic_quick_sort(Text *text);

/// @brief Frees all dynamic memory links
///
/// @param text pointer to the text
void dealloc_struct_text(Text *text);

#endif /* TEXT_H */
