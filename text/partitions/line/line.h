#ifndef LINE_H
#define LINE_H

/// @file line.h

struct Line
{
    const char* start = NULL;
    size_t len = 0;
};

/// @brief Counts number of lines in given buffer
///
/// @param[in] buffer buffer to count lines
///
/// @return number of lines in the buffer
size_t count_n_lines(const char* buffer);

/// @brief Parses buffer into lines
///
/// @param buffer pointer to the buffer to parse
/// @param[out] n_lines pointer to variable where
/// number of lines store to
///
/// @return pointer to array of Lines in dynamic memory
void* parse_buffer_lines(char* buffer, size_t* n_lines);

/// @brief Prints one line in stream
///
/// @param[in] pointer to the Line
/// @param[in] stream stream to print
void print_line_stream(FILE* stream, const void* voidptr_line);

/// @brief Compares two Lines by length
///
/// @param[in] ptr1 void pointer to the Line
/// @param[in] ptr2 void pointer to the Line
///
/// @return a positive number if 1st line's length
/// is greater than 2nd's,
/// 0 if lines' lengths are equal,
/// a negative number if 2nd line is larger,
int compare_lines_length(const void* ptr1, const void* ptr2);

/// @brief Compares two Lines lexicographically
///
/// @param[in] ptr1 void pointer to the Line
/// @param[in] ptr2 void pointer to the Line
///
/// @return a positive number if 1st line
/// is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// a negative number if 2nd line is larger,
int compare_lines_lex(const void* ptr1, const void* ptr2);

/// @brief Compares two utf8 Lines lexicographically
///
/// @param[in] ptr1 void pointer to the utf8 Line
/// @param[in] ptr2 void pointer to the utf8 Line
///
/// @return a positive number if 1st line
/// is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// a negative number if 2nd line is larger,
int compare_lines_lex_utf8(const void* ptr1, const void* ptr2);

/// @brief Compares two reversed Lines lexicographically
///
/// @param[in] ptr1 void pointer to the Line
/// @param[in] ptr2 void pointer to the Line
///
/// @return a positive number if 1st reversed line
/// is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// a negative number if 2nd reversed line is larger,
int compare_lines_reverse_lex(const void* ptr1, const void* ptr2);

/// @brief Compares two reversed utf8 Lines lexicographically
///
/// @param[in] ptr1 void pointer to the utf8 Line
/// @param[in] ptr2 void pointer to the utf8 Line
///
/// @return a positive number if 1st reversed line
/// is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// a negative number if 2nd reversed line is larger,
int compare_lines_reverse_lex_utf8(const void* ptr1, const void* ptr2);

#endif /* LINE_H */
