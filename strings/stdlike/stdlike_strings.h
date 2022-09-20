#ifndef STRINGS_H
#define STRINGS_H
#define HEADER

/// @file stdlike_strings.h

/// @brief puts from <string.h>
int my_puts(const char *str);

/// @brief strlen from <string.h>
size_t my_strlen(const char *str);

/// @brief strcpy from <string.h>
char *my_strcpy(char *dest, const char *src);

/// @brief strncpy from <string.h>
char *my_strncpy(char *dest, const char *src, size_t count);

/// @brief strcat from <string.h>
char *my_strcat(char *dest, const char *src);

/// @brief strncat from <string.h>
char *my_strncat(char *dest, const char *src, size_t count);

/// @brief fgets from <string.h>
char *my_fgets(char *str, int count, FILE *stream);

/// @brief strdup from <string.h>
char *my_strdup(const char *str);

/// @brief strchr from <string.h>
char *my_strchr(const char *str, int ch);

/// @brief strcmp from <string.h>
int my_strcmp(const char *str1, const char *str2);

#undef HEADER
#endif /* STRINGS_H */
