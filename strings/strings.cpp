
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#include "strings.h"
#include "../error_handling/error_handling.h"

size_t count_chars_str(const char *str, const char *chs, char count_null /* = 0 */, char skip_repeating /* = 0 */) {
    ASSERT(str != NULL);
    ASSERT(chs != NULL);
    if (strlen(chs) == 0)
        return 0;

    size_t count = 0;
    int prev_matches = 0;
    while (*str != '\0') {
        int curr_matches = 0;

        for (const char *ch = chs; *ch != '\0'; ch++) {
            curr_matches = (*str == *ch);

            if (skip_repeating) {
                count += (size_t) (curr_matches && !prev_matches);
            } else {
                count += (size_t) curr_matches; 
            }

            if (curr_matches) break;
        }
        prev_matches = curr_matches;
        str++;
    }
   
    if (count_null)
        count += !(skip_repeating && prev_matches);

    return count;
}

char *skip_non_letters(const char *start, const char *finish) {
    ASSERT(start  != NULL);
    ASSERT(finish != NULL);

    int step = (finish >= start) ? 1 : -1;
    char *ptr = const_cast<char*>(start);
    while ((finish - ptr) * step > 0 && !isalpha(*ptr)) ptr += step;
    return ptr;
}

const int TWO_BIG_BITS       = 0xc0;
const int TAIL_BYTE_TEMPLATE = 0x80;

char *find_first_byte_utf8(const char *start, int step) {
    ASSERT(start != NULL);
    ASSERT(step  != 0)

    char *ptr = const_cast<char*>(start);
    while ((*ptr & TWO_BIG_BITS) == TAIL_BYTE_TEMPLATE) 
        ptr += step;
    
    return ptr;
}

char *skip_non_letters_utf8(const char *start, const char *finish) {
    ASSERT(start  != NULL);
    ASSERT(finish != NULL);

    int step = (finish >= start) ? 1 : -1;
    wchar_t wc = 0;
    char *ptr = const_cast<char*>(start);
    while ((finish - ptr) * step > 0) {
        ptr = find_first_byte_utf8(ptr, step);
        mbrtowc(&wc, ptr, sizeof(wchar_t), NULL);
        if (iswalpha((wint_t) wc)) {
            break;
        } else {
            ptr += step;
        }
    }
    return ptr;
}

int compare_lines_lexicographic(const char *start1,
                                const char *finish1,
                                const char *start2,
                                const char *finish2,
                                      char is_skip_non_letters /* = 0 */,
                                      char is_neglect_case     /* = 0 */)
{
    ASSERT(start1  != NULL);
    ASSERT(start2  != NULL);
    ASSERT(finish1 != NULL);
    ASSERT(finish2 != NULL);

    int step1 = ((finish1 - start1) >= 0) ? 1 : -1;
    int step2 = ((finish2 - start2) >= 0) ? 1 : -1;
    while (1) {
        if (is_skip_non_letters) {
            start1 = skip_non_letters(start1, finish1);
            ASSERT(start1 == finish1 || isalpha(*start1));

            start2 = skip_non_letters(start2, finish2);
            ASSERT(start2 == finish2 || isalpha(*start2));
        }
        if (start1 == finish1 || start2 == finish2)
            break;

        int cur_letter1 = *start1;
        int cur_letter2 = *start2;
        if (is_neglect_case) {
            cur_letter1 = toupper(cur_letter1);
            cur_letter2 = toupper(cur_letter2);
        }
        if (cur_letter1 != cur_letter2)
            return cur_letter1 - cur_letter2;

        start1 += step1;
        start2 += step2;
    }

    ASSERT(start1 == finish1 || start2 == finish2);
    return (start2 == finish2) - (start1 == finish1);
}


int compare_lines_lexicographic_utf8(const char *start1,
                                     const char *finish1,
                                     const char *start2,
                                     const char *finish2,
                                           char is_skip_non_letters /* = 0 */,
                                           char is_neglect_case     /* = 0 */)
{
    ASSERT(start1  != NULL);
    ASSERT(start2  != NULL);
    ASSERT(finish1 != NULL);
    ASSERT(finish2 != NULL);

    int step1 = (finish1 >= start1) ? 1 : -1;
    int step2 = (finish2 >= start2) ? 1 : -1;
    while (1) {
        start1 = find_first_byte_utf8(start1, step1);
        ASSERT((finish1 - start1) * step1 >= 0);
        start2 = find_first_byte_utf8(start2, step2);
        ASSERT((finish2 - start2) * step2 >= 0);

        if (is_skip_non_letters) {
            start1 = skip_non_letters_utf8(start1, finish1);
            ASSERT((finish1 - start1) * step1 >= 0);
            start2 = skip_non_letters_utf8(start2, finish2);
            ASSERT((finish2 - start2) * step2 >= 0);
        }
        if (start1 == finish1 || start2 == finish2)
            break;

        wchar_t wc1 = 0;
        wchar_t wc2 = 0;
        mbrtowc(&wc1, start1, sizeof(wchar_t), NULL);
        mbrtowc(&wc2, start2, sizeof(wchar_t), NULL);
        if (is_neglect_case) {
            wc1 = (wchar_t) towupper((wint_t) wc1);
            wc2 = (wchar_t) towupper((wint_t) wc2);
        }
        if (wc1 != wc2)
            return wc1 - wc2;

        start1 += step1;
        start2 += step2;
    }

    ASSERT(start1 == finish1 || start2 == finish2);
    return (start2 == finish2) - (start1 == finish1);
}

#include "../error_handling/undef_error_handling.h"
