#ifndef LINE_H
#define LINE_H

/// @file line.h

struct Line {
    const char *start = NULL;
    size_t len = 0;
};

/// @brief Counts number of lines in given buffer
///
/// @param[in] buffer buffer to count lines
///
/// @return number of lines in the buffer
size_t get_n_lines(const char *buffer);

/// @brief Reads 1 line from stdin
///
/// @param line pointer to the Line
/// @param start pointer to the start of the line
///
/// @return number of read symbols
size_t set_line(void *voidptr_line, const char *start);

/// @brief Prints 1 line in stream
///
/// @param[in] pointer to the Line
/// @param[in] stream stream to print
void print_line_stream(FILE *stream, const void *voidptr_line);

/// @brief Compares two Lines by length
///
/// @param[in] ptr1 void pointer to the Line
/// @param[in] ptr2 void pointer to the Line
///
/// @return a positive number if 1st line's length
/// is greater than 2nd's,
/// 0 if lines' lengths are equal,
/// a negative number if 2nd line is larger,
int compare_lines_length(const void *ptr1, const void *ptr2);

/// @brief Compares two Lines lexicographically
///
/// @param[in] ptr1 void pointer to the Line
/// @param[in] ptr2 void pointer to the Line
///
/// @return a positive number if 1st line
/// is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// a negative number if 2nd line is larger,
int compare_lines_lex(const void *ptr1, const void *ptr2);

/// @brief Compares two reversed Lines lexicographically
///
/// @param[in] ptr1 void pointer to the Line
/// @param[in] ptr2 void pointer to the Line
///
/// @return a positive number if 1st reversed line
/// is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// a negative number if 2nd reversed line is larger,
int compare_lines_reverse_lex(const void *ptr1, const void *ptr2);

#endif /* LINE_H */
