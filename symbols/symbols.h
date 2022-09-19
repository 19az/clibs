#ifndef SYMBOLS_H
#define SYMBOLS_H

/// @file symbols.h

#include <stdlib.h>

const int UPPERCASE = 'a' - 'A';  ///< displacement between lower and upper case in ASCII

/// @brief Checks if given char is english letter
///
/// @param[in] ch char to check
///
/// @return 1 if ch is letter, 0 ohterwise
int is_letter(char ch);

/// @brief Checks if given letter in lower case
///
/// @param[in] ch char to check
///
/// @return 1 if yes, 0 otherwise
int is_lower_case_letter(char ch);

/// @brief Checks if given letter in upper case
///
/// @param[in] ch char to check
///
/// @return 1 if yes, 0 otherwise
int is_upper_case_letter(char ch);

/// @brief Changes case of given letter to lower
///
/// @param[in] ch char to change case
///
/// @return letter in lower case or unchanged given symbol if it is not a letter
char lower_case(char ch);

/// @brief Changes case of given letter to upper case
///
/// @param[in] ch char to change case
///
/// @return letter in upper case or unchanged given symbol if it is not a letter
char upper_case(char ch);

/// @brief Skips chars which are not letters in sequence of chars
///
/// @param[in] start pointer to the start of the sequence
/// @param[in] finish pointer to the next symbol after the last symbol of the sequence
/// @param[in} step step to next symbol of sequence
///
/// @return pointer to the finded letter in sequence
/// or *finish if there are no letters in given sequence
char *skip_no_letters(const char *start, const char *finish, int step);

#endif /* SYMBOLS_H */
