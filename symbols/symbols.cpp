
#include "symbols.h"
#include "../error_handling/error_handling.h"

/// @brief Checks if given char is an English letter
///
/// @param{in] ch char to check
///
/// @return 1 if yes, 0 otherwise
int is_letter(char ch) {
    return ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z'));
}

/// @brief Checks if given char is an English letter in lower case
///
/// @param{in] ch char to check
///
/// @return 1 if yes, 0 otherwise
int is_lower_case_letter(char ch) {
    return (ch >= 'a' &&
            ch <= 'z');
}

/// @brief Checks if given char is an English letter in upper case
///
/// @param{in] ch char to check
///
/// @return 1 if yes, 0 otherwise
int is_upper_case_letter(char ch) {
    return (ch >= 'A' &&
            ch <= 'Z');
}

/// @brief Switches case of given English letter to upper
///
/// @param{in] ch char to switch case
///
/// @return given letter in upper case or same char if it is not an English letter
char upper_case(char ch) {
    if (is_lower_case_letter(ch)) {
        return ch - UPPERCASE;
    }
    return ch;
}

/// @brief Switches case of given English letter to lower
///
/// @param{in] ch char to switch case
///
/// @return given letter in lower case or same char if it is not an English letter
char lower_case(char ch) {
    if (is_upper_case_letter(ch)) {
        return ch + UPPERCASE;
    }
    return ch;
}

/// @brief Skips all non-letters chars in given sequence of chars
///
/// @param start pointer to the start position
/// @param finish pointer to the finish position
///
/// @return pointer to the first letter in sequnce
/// or pointer to the finish in there are no letters
char *skip_no_letters(const char *start, const char *finish, int step) {
    ASSERT(start  != NULL);
    ASSERT(finish != NULL);
    ASSERT(step   != 0);

    char *ptr = const_cast<char*>(start);
    while ((finish - ptr) * step > 0 && !is_letter(*ptr)) ptr += step;
    return ptr;
}

#include "../error_handling/undef_error_handling.h"
