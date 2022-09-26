#ifndef STRINGS_H
#define STRINGS_H

/// @file strings.h

#include <stdlib.h>

/// @brief Count occurences of chars in string
///
/// @param[in] str null-terminated string
/// @param[in] chs string of counting chars
/// @param[in] skip_repeating determines if it is needed
/// to skip symbols that places in a row in the string
/// @param[in] count_null determines if it is needed
/// to add null-symbol to counting symbols
///
/// @return number of ch in text
///
/// @note undefined behaviour if str is not
/// a pointer to null-terminated byte string
size_t count_chars_str(const char *str, const char *chs, char count_null = 0, char skip_repeating = 0);

/// @brief Skips chars which are not letters in sequence of chars
///
/// @param[in] start pointer to the start of the sequence
/// @param[in] finish pointer to the next symbol after the last symbol of the sequence
///
/// @return pointer to the finded letter in sequence
/// or *finish if there are no letters in given sequence
char *skip_non_letters(const char *start, const char *finish);

/// @brief Skips chars which are not letters in sequence of utf8 chars
///
/// @param[in] start pointer to the start of the sequence
/// @param[in] finish pointer to the next symbol after the last symbol of the sequence
///
/// @return pointer to the finded letter in sequence
/// or *finish if there are no letters in given sequence
char *skip_non_letters_utf8(const char *start, const char *finish);

/// @brief Finds fisrt byte of wchar_t
///
/// @param[in] start pointer to some byte of wchar_t
/// @param[in] step step to the next byte of wchar_t
/// 
/// @return pinter to the first byte of wchar_t
char *find_first_byte_utf8(const char *start, int step);

/// @brief Compares two arrays of chars lexicographically
///
/// @param[in] start1 pointer to the start of the 1st line
/// @param[in] finish1 pointer to the finish of the 1st line
/// @param[in] start2 pointer to the start of the 2st line
/// @param[in] finish2 pointer to the finish of the 2st line
/// @param[in] is_skip_non_letters allows skips non-letter symbols
/// during comparison ("abc" == "a b,c."), 0 by default
/// @param[in] is_neglect_case allows to neglect case of the letters
/// ("abc" == "ABC"), 0 by default
///
/// @return a positive number if the 1st line is greater than the 2nd,
/// 0 if lines are equal and
/// a negative number if the 2nd is greater than the 1st
int compare_lines_lexicographic(const char *start1,
                                const char *finish1,
                                const char *start2,
                                const char *finish2,
                                      char is_skip_non_letters = 0,
                                      char is_neglect_case     = 0);

/// @brief Compares two arrays of wchars_t lexicographically
///
/// @param[in] start1 pointer to the start of the 1st line
/// @param[in] finish1 pointer to the finish of the 1st line
/// @param[in] start2 pointer to the start of the 2st line
/// @param[in] finish2 pointer to the finish of the 2st line
/// @param[in] is_skip_non_letters allows skips non-letter symbols
/// during comparison ("abc" == "a b,c."), 0 by default
/// @param[in] is_neglect_case allows to neglect case of the letters
/// ("abc" == "ABC"), 0 by default
///
/// @return a positive number if the 1st line is greater than the 2nd,
/// 0 if lines are equal and
/// a negative number if the 2nd is greater than the 1st
int compare_lines_lexicographic_utf8(const char *start1,
                                     const char *finish1,
                                     const char *start2,
                                     const char *finish2,
                                           char is_skip_non_letters = 0,
                                           char is_neglect_case     = 0);

#endif /* STRINGS_H */
