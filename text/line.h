#ifndef LINE_H
#define LINE_H

/// @brief Reads 1 line from stdin
///
/// @param line pointer to the Line
/// @param start pointer to the start of the line
///
/// @return number of read symbols
size_t set_line(Line *line, const char *start);

/// @file line.h

/// @brief Prints 1 line in stdout
///
/// @param[in] pointer to the Line
void print_line_stdout(Line *line);

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
int compare_lines_lexicographic(const void *ptr1, const void *ptr2);

/// @brief Compares two reversed Lines lexicographically
///
/// @param[in] ptr1 void pointer to the Line
/// @param[in] ptr2 void pointer to the Line
///
/// @return a positive number if 1st reversed line
/// is lexicographically greater than 2nd,
/// 0 if lines are equal,
/// a negative number if 2nd reversed line is larger,
int compare_lines_reverse_lexicographic(const void *ptr1, const void *ptr2);

#endif /* LINE_H */
