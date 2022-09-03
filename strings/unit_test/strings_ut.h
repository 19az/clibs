#ifndef STRINGS_UT_H
#define STRINGS_UT_H

/// @file strings_test.h

const size_t MAXNTESTS = 100; ///< max number of tests in unit test

const char *filename_fgets_test = "fgets_test.txt"; ///< name of file with test for my_fgets()

/// @brief Unit test function for my_puts()
void puts_test(const char *str);

/// @brief Unit test function for my_strlen()
void strlen_test(const char *str);

/// @brief Unit test function for my_strcpy()
void strcpy_test(const char *str);

/// @brief Unit test function for my_strncpy()
void strncpy_test(const char *str, size_t count);

/// @brief Unit test function for my_strcat()
void strcat_test(const char *dest, const char *src);

/// @brief Unit test function for my_strncat()
void strncat_test(const char *dest, const char *src, size_t count);

/// @brief Unit test function for ny_fgets()
void fgets_test();

/// @brief Unit test function for my_strdup()
void strdup_test(const char *str);

/// @brief Unit test function for my_strchr()
void strchr_test(const char *str, int ch);

/// @brief Unit test function for count_char_str()
void count_char_str_test(const char *str, char ch, size_t result);

/// @brief Unit test function for my_puts()
void puts_ut();

/// @brief Unit test function for my_strlen()
void strlen_ut();

/// @brief Unit test function for my_strcpy()
void strcpy_ut();

/// @brief Unit test function for my_strncpy()
void strncpy_ut();

/// @brief Unit test function for my_strcat()
void strcat_ut();

/// @brief Unit test function for my_strncat()
void strncat_ut();

/// @brief Unit test function for ny_fgets()
void fgets_ut();

/// @brief Unit test function for my_strdup()
void strdup_ut();

/// @brief Unit test function for my_strchr()
void strchr_ut();

/// @brief Unit test function for count_char_str()
void count_char_str_ut();

#endif /* STRINGS_UT_H */
