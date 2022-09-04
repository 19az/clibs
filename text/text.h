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

enum retcodes_text       /// Enum of return codes of read_text_file()
{
ERR_FILE_EMPTY_TEXT =  0, ///< given file is empty
ERR_FILE_SIZE_TEXT  = -1, ///< getting file size error
ERR_FILE_OPEN_TEXT  = -2, ///< file openning error
ERR_FILE_READ_TEXT  = -3, ///< read file error
ERR_MEM_ALLOC_TEXT  = -4  ///< memory allocation error
};

/// @brief Read text from file
///
/// @param[in] filename name of file
///
/// @return number of bytes read on success,
/// 0  if given file is empty,
/// -1 on getting file size error,
/// -2 on file openning error,
/// -3 on reading file error,
/// -4 on allocating memory error
int read_text_file(Text *text, const char *filename);

/// @brief Parses lines in text
///
/// @param text pointer to the Text
///
/// @return 0 on success,
/// -1 on memory allocation error
///
/// @note Function does not check if given pointers are valid
int parse_lines_text(Text *text);

/// @brief Prints Line in stdout
///
/// @param[in] text pointer to the Text
///
/// @note Function does not check if given pointers are valid
void print_all_lines_stdout(const Text *text);

/// @brief Replaces lines in reverse order
///
/// @param text pointer to the text
///
/// @note Function does not check if given pointers are valid
void reverse_order_lines(Text *text);

/// @brief Sorts lines of given text by lengths in ascending order
///
/// @details uses bubble sort algorithm
///
/// @param text text to sort
///
/// @note Function does not check if given pointers are valid
void sort_lines_length_bubble_sort(Text *text);

/// @brief Sorts lines of given text by lengths in ascending order
///
/// @details uses quicksort algorithm
///
/// @param text text to sort
///
/// @note Function does not check if given pointers are valid
void sort_lines_length_quick_sort(Text *text);

/// @brief Sorts lines of given text lexicographically in ascending order
///
/// @details uses bubble sort algorithm
///
/// @param text text to sort
///
/// @note Function does not check if given pointers are valid
void sort_lines_lexicographic_bubble_sort(Text *text);

/// @brief Sorts lines of given text lexicographically in ascending order
///
/// @details uses quicksort algorithm
///
/// @param text text to sort
///
/// @note Function does not check if given pointers are valid
void sort_lines_lexicographic_quick_sort(Text *text);

/// @brief Sorts reversed lines of given text lexicographically in ascending order
///
/// @details uses bubble sort algorithm
///
/// @param text text to sort
///
/// @note Function does not check if given pointers are valid
void sort_lines_reverse_lexicographic_bubble_sort(Text *text);

/// @brief Sorts reversed lines of given text lexicographically in ascending order
///
/// @details uses quicksort algorithm
///
/// @param text text to sort
///
/// @note Function does not check if given pointers are valid
void sort_lines_reverse_lexicographic_quick_sort(Text *text);

/// @brief Frees all dynamic memory links
///
/// @param text pointer to the text
///
/// @note Function does not check if given pointers are valid
void dealloc_struct_text(Text *text);

#endif /* TEXT_H */
