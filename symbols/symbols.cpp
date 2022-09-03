#include "symbols.h"

int is_letter(char ch) {
    return ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z'));
}

int is_lower_case_letter(char ch) {
    return (ch >= 'a' &&
            ch <= 'z');
}

int is_upper_case_letter(char ch) {
    return (ch >= 'A' &&
            ch <= 'Z');
}

char upper_case(char ch) {
    if (is_lower_case_letter(ch)) {
        return ch - UPPERCASE;
    }
    return ch;
}

char lower_case(char ch) {
    if (is_upper_case_letter(ch)) {
        return ch + UPPERCASE;
    }
    return ch;
}

size_t skip_no_letters(const char *str, size_t len) {
    size_t skip = 0;
    while (skip < len && !is_letter(str[skip])) {
        skip++;
    }
    return skip;
}

size_t skip_no_letters_reverse(const char *str, size_t len) {
    while (len > 0 && !is_letter(str[len - 1])) len--;
    return len;
}

