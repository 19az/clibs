#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "../assert/my_assert.h"

int my_puts(const char *str) {
    ASSERT(str != NULL)
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (putchar(str[i]) == EOF) return EOF;
    }
    return putchar('\n');
}

size_t my_strlen(const char *str) {
    ASSERT(str != NULL)
    size_t i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *my_strcpy(char *dest, const char *src) {
    ASSERT(dest != NULL)
    ASSERT(src != NULL)
    char *dest_ret = dest;
    while (*src != '\0') *(dest++) = *(src++);
    *dest = '\0';
    return dest_ret;
}

char *my_strncpy(char *dest, const char *src, size_t count) {
    ASSERT(dest != NULL)
    ASSERT(src != NULL)
    char *dest_ret = dest;
    for (size_t i = 0; i < count; ++i) {
        if (*src == '\0') {
            for (size_t j = i; j < count; ++j) {
                *(dest++) = '\0';
            }
            break;
        }
        *(dest++) = *(src++);
    }
    return dest_ret;
}

char *my_strcat(char *dest, const char *src) {
    ASSERT(dest != NULL)
    ASSERT(src != NULL)
    char *dest_ret = dest;
    while (*dest != '\0') dest++;
    while (*src  != '\0') *(dest++) = *(src++);
    *dest = '\0';
    return dest_ret;
}

char *my_strncat(char *dest, const char *src, size_t count) {
    ASSERT(dest != NULL)
    ASSERT(src != NULL)
    char *dest_ret = dest;
    while (*dest != '\0') dest++;
    for (size_t i = 0; i < count; ++i) {
        if (*src == '\0') {
            break;
        }
        *(dest++) = *(src++);
    }
    *dest = '\0';
    return dest_ret;
}

char *my_fgets(char *str, int count, FILE *stream) {
    ASSERT(str != NULL)
    ASSERT(stream != NULL)
    char *str_ret = str;
    int ch = 0;
    for (int i = 0; i < count - 1; ++i) {
        ch = fgetc(stream);
        if (ch == EOF) {
            if (i == 0) {
                str_ret = NULL;
            } else {
                *str = '\0';
            }
            break;
        } else if (ch == '\n') {
            *(str++) = '\n';
            *str = '\0';
            break;
        } else {
            *(str++) = (char) ch;
        }
    }
    *str = '\0';
    return str_ret;
}

char *my_strdup(const char *str) {
    ASSERT(str != NULL)
    size_t len = my_strlen(str) + 1;
    char *dm_str = (char*) malloc(len * sizeof(char));
    if (dm_str == NULL) {
        return NULL;
    }
    char *dm_str_ret = dm_str;
    for (size_t i = 0; i < len; ++i) {
        *(dm_str++) = *(str++);
    }
    return dm_str_ret;
}

char *my_strchr(const char *str, int ch) {
    ASSERT(str != NULL)
    while (*str != ch) {
        if (*str == '\0') return NULL;
        str++;
    }
    return const_cast<char*>(str);
}

int my_strcmp(const char *str1, const char *str2) {
    ASSERT(str1 != NULL)
    ASSERT(str2 != NULL)
    while (*str1 != '\0' && *str1++ == *str2++); 
    if (*str1 > *str2) return 1;
    if (*str1 < *str2) return -1;
    return 0;
}

size_t count_char_str(const char *str, char ch) {
    ASSERT(str != NULL)
    size_t count = 0;
    do {
        count += (*str == ch);
    } while (*str++ != '\0');
    return count;
}
