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

/// @brief Skips chars in string which are not letters
///
/// @param[in] str pointer to the start of the string
/// @param[in] len length of given string
///
/// @return number of skipped symbols
size_t skip_no_letters(const char *str, size_t len);

/// @brief Skips chars in string which are not letters in reverse order
///
/// @param[in] str pointer to the start of the string
/// @param[in] len length of given string
///
/// @return number of skipped symbols
size_t skip_no_letters_reverse(const char *str, size_t len);

#endif /* SYMBOLS_H */
