
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "../error_handling/error_handling.h"

size_t count_char_str(const char *str, char ch) {
    ASSERT(str != NULL);
    size_t count = 0;
    do {
        count += (*str == ch);
    } while (*str++ != '\0');
    return count;
}

char *skip_non_letters(const char *start, const char *finish, int step) {
    ASSERT(start  != NULL);
    ASSERT(finish != NULL);
    ASSERT(step   != 0);

    char *ptr = const_cast<char*>(start);
    while ((finish - ptr) * step > 0 && !isalpha(*ptr)) ptr += step;
    return ptr;
}

int compare_lines_lexicographic(const char *start1,
                                const char *finish1,
                                const char *start2,
                                const char *finish2,
                                int is_skip_non_letters /* = 0 */,
                                int is_neglect_case     /* = 0 */)
{
    ASSERT(start1  != NULL);
    ASSERT(start1  != NULL);
    ASSERT(finish1 != NULL);
    ASSERT(finish2 != NULL);

    int step1 = ((finish1 - start1) >= 0) ? 1 : -1;
    int step2 = ((finish2 - start2) >= 0) ? 1 : -1;

    while (start1 != finish1 && start2 != finish2) {
        if (is_skip_non_letters) {
            start1 = skip_non_letters(start1, finish1, step1);
            ASSERT(start1 == finish1 || isalpha(*start1));

            start2 = skip_non_letters(start2, finish2, step2);
            ASSERT(start2 == finish2 || isalpha(*start2));
        }

        int cur_letter1 = *start1;
        int cur_letter2 = *start2;
        if (is_neglect_case) {
            cur_letter1 = toupper(cur_letter1);
            cur_letter2 = toupper(cur_letter2);
        }
        if (start1 == finish1 ||
            start2 == finish2 ||
            cur_letter1 != cur_letter2) {
            break;
        }
        start1 += step1;
        start2 += step2;
    }
    if (is_skip_non_letters) {
        start1 = skip_non_letters(start1, finish1, step1);
        ASSERT(start1 == finish1 || isalpha(*start1));

        start2 = skip_non_letters(start2, finish2, step2);
        ASSERT(start2 == finish2 || isalpha(*start2));
    }

    int result = 0;
    if (start1 == finish1) {
        result = (start2 == finish2) ? 0 : -1;
    } else {
        if (start2 == finish2) {
            result = 1;
        } else {
            if (is_neglect_case) {
                result = (toupper(*start1) - toupper(*start2));
            } else {
                result = *start1 - *start2;
            }
        }
    }
    return result;
}


#include "../error_handling/undef_error_handling.h"
