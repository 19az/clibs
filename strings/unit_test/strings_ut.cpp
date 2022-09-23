
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../strings.h"
#include "../../unit_testing/unit_testing.h"

#include "../../error_handling/error_handling.h"

//count_chars_str-decl----------------------------------------------------------

const size_t MAXLEN_COUNT_CHAR_STR = 10;
struct CountCharsStrArgs {
    char str[MAXLEN_COUNT_CHAR_STR] = {};
    char counting_chars[MAXLEN_COUNT_CHAR_STR] = {};
    size_t exp_no_repeated = 0;
    size_t res_no_repeated = 0;
    size_t exp_repeated = 0;
    size_t res_repeated = 0;
    size_t exp_repeated_null = 0;
    size_t res_repeated_null = 0;
};

size_t get_one_test_count_chars_str(void *voidptr_test, const char *buffer);

int run_one_test_count_chars_str(void *voidptr_test);

void failed_test_report_count_chars_str(const void *voidptr_test);

//skip_non_letters-decl----------------------------------------------------------

const size_t MAXLEN_SKIP_NON_LETTERS = 10;
struct SkipNonLettersArgs {
    char  str[MAXLEN_SKIP_NON_LETTERS] = {};
    char *start       = 0;
    char *finish      = 0;
    int   step        = 0;
    char *expected    = NULL;
    char *result      = NULL;
};

size_t get_one_test_skip_non_letters(void *voidptr_test, const char *buffer);

int run_one_test_skip_non_letters(void *voidptr_test);

void failed_test_report_skip_non_letters(const void *voidptr_test);

//compare_lines_lex-decl----------------------------------------------

const size_t MAXLEN_COMPARE_LINES_LEX = 20;
struct CompareLinesLexArgs {
    char str1[MAXLEN_COMPARE_LINES_LEX] = {};
    char str2[MAXLEN_COMPARE_LINES_LEX] = {};
    int expected_default          = 0;
    int expected_skip_non_letters = 0;
    int expected_neglect_case     = 0;
    int expected_reverse_order    = 0;
    int result_default            = 0;
    int result_skip_non_letters   = 0;
    int result_neglect_case       = 0;
    int result_reverse_order      = 0;
};

size_t get_one_test_compare_lines_lex(void *voidptr_test, const char *buffer);

int run_one_test_compare_lines_lex(void *voidptr_test);

void failed_test_report_compare_lines_lex(const void *voidptr_test);

//main--------------------------------------------------------------------------

int main() {
    unit_test("count_chars_str",
              "ccs_tests.txt",
              sizeof(CountCharsStrArgs),
              get_one_test_count_chars_str,
              run_one_test_count_chars_str,
              failed_test_report_count_chars_str);

    unit_test("skip_non_letters",
              "snl_tests.txt",
              sizeof(SkipNonLettersArgs),
              get_one_test_skip_non_letters,
              run_one_test_skip_non_letters,
              failed_test_report_skip_non_letters);

    unit_test("compare_lines_lexicographic",
              "cll_tests.txt",
              sizeof(CompareLinesLexArgs),
              get_one_test_compare_lines_lex,
              run_one_test_compare_lines_lex,
              failed_test_report_compare_lines_lex);

    return 0;
}

#define IS_STRING_EMPTY(str) \
if (!strcmp(str, "empty")) { \
    strcpy(str, "");         \
}

//count_chars_str-def----------------------------------------------------------

size_t get_one_test_count_chars_str(void *voidptr_test, const char *buffer) {
    CountCharsStrArgs *test = (CountCharsStrArgs*) voidptr_test;
    int bytes_read = 0;
    int result = sscanf(buffer,
                        "%s %s %lu %lu %lu %n",
                        test->str,
                        test->counting_chars,
                        &test->exp_no_repeated,
                        &test->exp_repeated,
                        &test->exp_repeated_null,
                        &bytes_read);
    ASSERT(result == 5 || result == EOF, "cannot read all arguments");
    if (result == EOF) return 0;

    IS_STRING_EMPTY(test->str);

    return (size_t) bytes_read;
}

int run_one_test_count_chars_str(void *voidptr_test) {
    CountCharsStrArgs *test = (CountCharsStrArgs*) voidptr_test;

    size_t res_no_repeated
        = count_chars_str(test->str, test->counting_chars, 0, 0);
    size_t res_repeated
        = count_chars_str(test->str, test->counting_chars, 0, 1);
    size_t res_repeated_null
        = count_chars_str(test->str, test->counting_chars, 1, 1);
    test->res_no_repeated   = res_no_repeated;
    test->res_repeated      = res_repeated;
    test->res_repeated_null = res_repeated_null;
    return (res_no_repeated   == test->exp_no_repeated) &&
           (res_repeated      == test->exp_repeated)    &&
           (res_repeated_null == test->exp_repeated_null);
}

void failed_test_report_count_chars_str(const void *voidptr_test) {
    const CountCharsStrArgs *test = (const CountCharsStrArgs*) voidptr_test;

    printf("str: %s\n"
           "counting chars: %s\n"
           "exp no repeated = %lu\n"
           "res no repeated = %lu\n"
           "exp repeated = %lu\n"
           "res repeated = %lu\n"
           "exp repeated null = %lu\n"
           "res repeated null = %lu\n",
           test->str,
           test->counting_chars,
           test->exp_no_repeated,
           test->res_no_repeated,
           test->exp_repeated,
           test->res_repeated,
           test->exp_repeated_null,
           test->res_repeated_null);
}

//skip_non_letters-def---------------------------------------------------------

size_t get_one_test_skip_non_letters(void *voidptr_test, const char *buffer) {
    SkipNonLettersArgs *test = (SkipNonLettersArgs*) voidptr_test;
    int start_index    = 0;
    int finish_index   = 0;
    int expected_index = 0;
 
    int bytes_read = 0;
    int result = sscanf(buffer,
                        "%s %d %d %d %d %n",
                        test->str,
                        &start_index,
                        &finish_index,
                        &test->step,
                        &expected_index,
                        &bytes_read);
    ASSERT(result == 5 || result == EOF, "cannot read all arguments");
    if (result == EOF) return 0;

    IS_STRING_EMPTY(test->str);
    test->start    = test->str + start_index;
    test->finish   = test->str + finish_index;
    test->expected = test->str + expected_index;

    return (size_t) bytes_read;
}

int run_one_test_skip_non_letters(void *voidptr_test) {
    SkipNonLettersArgs *test = (SkipNonLettersArgs*) voidptr_test;

    test->result = skip_non_letters(test->start, test->finish, test->step);
    return (test->result == test->expected);
}

void failed_test_report_skip_non_letters(const void *voidptr_test) {
    const SkipNonLettersArgs *test = (const SkipNonLettersArgs*) voidptr_test;

    printf("str            = %s\n"
           "start index    = %ld\n"
           "finish index   = %ld\n"
           "step           = %d\n"
           "expected index = %ld\n"
           "result index   = %ld\n",
           test->str,
           test->start  - test->str,
           test->finish - test->str,
           test->step,
           test->expected - test->str,
           test->result - test->str);
}

//compare_lines_lex-def--------------------------------------------------------

size_t get_one_test_compare_lines_lex(void *voidptr_test, const char *buffer) {
    CompareLinesLexArgs *test = (CompareLinesLexArgs*) voidptr_test;
 
    int bytes_read = 0;
    int result = sscanf(buffer,
                        "%s %s %d %d %d %d %n",
                        test->str1,
                        test->str2,
                        &test->expected_default,
                        &test->expected_skip_non_letters,
                        &test->expected_neglect_case,
                        &test->expected_reverse_order,
                        &bytes_read);
    ASSERT(result == 6 || result == EOF, "cannot read all arguments");
    if (result == EOF) return 0;

    EVAL(MAP(IS_STRING_EMPTY, test->str1, test->str2))

    return (size_t) bytes_read;
}

int run_one_test_compare_lines_lex(void *voidptr_test) {
    CompareLinesLexArgs *test = (CompareLinesLexArgs*) voidptr_test;

    char *left1  = test->str1;
    char *left2  = test->str2;
    char *right1 = strchr(test->str1, '\0');
    char *right2 = strchr(test->str2, '\0');
    test->result_default          = compare_lines_lexicographic(left1, right1, left2, right2, 0, 0);
    test->result_skip_non_letters = compare_lines_lexicographic(left1, right1, left2, right2, 1, 0);
    test->result_neglect_case     = compare_lines_lexicographic(left1, right1, left2, right2, 0, 1);
    test->result_reverse_order    = compare_lines_lexicographic(right1 - 1, left1 - 1, right2 - 1, left2 - 1, 0, 0);
    test->result_default          = (test->result_default <  0) ? -1 :
                                    (test->result_default == 0) ?  0 : 1;
    test->result_skip_non_letters = (test->result_skip_non_letters <  0) ? -1 :
                                    (test->result_skip_non_letters == 0) ?  0 : 1;
    test->result_neglect_case     = (test->result_neglect_case <  0) ? -1 :
                                    (test->result_neglect_case == 0) ?  0 : 1;
    test->result_reverse_order    = (test->result_reverse_order <  0) ? -1 :
                                    (test->result_reverse_order == 0) ?  0 : 1;

    return (test->expected_default          == test->result_default)          &&
           (test->expected_skip_non_letters == test->result_skip_non_letters) &&
           (test->expected_neglect_case     == test->result_neglect_case)     &&
           (test->expected_reverse_order    == test->result_reverse_order);
}

void failed_test_report_compare_lines_lex(const void *voidptr_test) {
    const CompareLinesLexArgs *test = (const CompareLinesLexArgs*) voidptr_test;

    printf("str1                      = %s\n"
           "str2                      = %s\n"
           "expected default          = %2d\n"
           "result   default          = %2d\n\n"
           "expected skip non-letters = %2d\n"
           "result   skip non-letters = %2d\n\n"
           "expected neglect case     = %2d\n"
           "result   neglect case     = %2d\n\n"
           "expected reverse order    = %2d\n"
           "result   reverse order    = %2d\n",
           test->str1,
           test->str2,
           test->expected_default,
           test->result_default,

           test->expected_skip_non_letters,
           test->result_skip_non_letters,
           
           test->expected_neglect_case,
           test->result_neglect_case,
           
           test->expected_reverse_order,
           test->result_reverse_order);
}

#undef IS_STRING_EMPTY

#include "../../error_handling/undef_error_handling.h"
