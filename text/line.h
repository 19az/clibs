#ifndef LINE_H
#define LINE_H

/// @file line.h

/// Struct to represent lines of text
struct Line {
    char *start = NULL; ///< pointer to the start of str
    size_t length = 0;  ///< length of the str
};

/// @brief Prints 1 line in stdout
///
/// @param[in] pointer to the text
void print_line_stdout(const Line *line);

/// @brief Reads 1 line from stdin
///
/// @param line pointer to the Line
///
/// @return number of read symbols
size_t get_line_len(Line *line);

/// @brief Casts const void* to Line** for compare_lines_length()
///
/// @param[in] ptr void pointer to the pointer to Line
///
/// @return pointer to Line on success,
/// NULL if ptr == NULL
Line *cast_void_to_lineptr(const void *ptr);

/// @brief Compares two Lines by length
///
/// @param[in] ptr1 void pointer to the 1st Line
/// @param[in] ptr2 void pointer to the 2st Line
///
/// @return 1 if 1st line's length is greater than 2nd's,
/// 0 if lines' lengths are equal,
/// -1 if 2nd line is larger,
/// also return 0 if some of arguments are NULL
int compare_lines_length(const void *ptr1, const void *ptr2);

/// @brief Compares two Lines lexicographically
///
/// @param[in] ptr1 void pointer to the 1st Line
/// @param[in] ptr2 void pointer to the 2nd Line
///
/// @return 1 if 1st line is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// -1 if 2nd line is larger,
/// also return 0 if some of arguments are NULL
int compare_lines_lexicographic(const void *ptr1, const void *ptr2);

/// @brief Compares two reversed Lines lexicographically
///
/// @param[in] ptr1 void pointer to the 1st Line
/// @param[in] ptr2 void pointer to the 2nd Line
///
/// @return 1 if 1st reversed line is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// -1 if 2nd reversed line is larger,
/// also return 0 if some of arguments are NULL
int compare_lines_reverse_lexicographic(const void *ptr1, const void *ptr2);

#endif /* LINE_H */
