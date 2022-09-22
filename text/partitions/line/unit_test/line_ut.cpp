
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../line.h"
#include "../../../../unit_testing/unit_testing.h"

#include "../../../../error_handling/error_handling.h"

//leni-decl---------------------------------------------------------------------

size_t get_one_test_line(void *voidptr_test, const char *buffer);

int run_one_test_line(void *voidptr_test);

void failed_test_report_line(const void *voidptr_test);

//comp_lex-decl-----------------------------------------------------------------

const size_t MAXLEN_COMP_LEX = 20;

struct CompLexArgs {
    char str1[MAXLEN_COMP_LEX] = {};
    char str2[MAXLEN_COMP_LEX] = {};
    int exp_dir_order = 0;
    int res_dir_order = 0;
    int exp_rev_order = 0;
    int res_rev_order = 0;
};

size_t get_one_test_comp_lex(void *voidptr_test, const char *buffer);

int run_one_test_comp_lex(void *voidptr_test);

void failed_test_report_comp_lex(const void *voidptr_test);

//main--------------------------------------------------------------------------

int main() {
    unit_test("get, set and print",
              "line_test.txt",
              sizeof(const char*),
              get_one_test_line,
              run_one_test_line,
              failed_test_report_line);

    unit_test("comp lex",
              "comp_lex_test.txt",
              sizeof(CompLexArgs),
              get_one_test_comp_lex,
              run_one_test_comp_lex,
              failed_test_report_comp_lex);

    return 0;
}

//line-def----------------------------------------------------------------------

size_t get_one_test_line(void *voidptr_test, const char *buffer) {
    ASSERT(voidptr_test != NULL);
    ASSERT(buffer       != NULL);

    const char **test = (const char**) voidptr_test;
    *test = buffer;

    return (size_t) (strchr(buffer, '\n') - buffer + 1);
}

int run_one_test_line(void *voidptr_test) {
    ASSERT(voidptr_test != NULL);

    const char **test = (const char**) voidptr_test;

    Line line = {};
    set_line(&line, *test);

    printf("\nLine: ");
    print_line_stream(stdout, &line);
    printf("Size: %lu\n", line.len);

    return ((size_t) (strchr(*test, '\n') - *test) == line.len) ? 1 : 0;
}

void failed_test_report_line(const void *voidptr_test) {
    ASSERT(voidptr_test != NULL);
}

//comp_lex-def------------------------------------------------------------------

size_t get_one_test_comp_lex(void *voidptr_test, const char *buffer) {
    ASSERT(voidptr_test != NULL);
    ASSERT(buffer       != NULL);

    CompLexArgs *test = (CompLexArgs*) voidptr_test;

    int bytes_read = 0;
    int sscanf_ret = sscanf(buffer,
                            "%s %s %d %d %n",
                            test->str1,
                            test->str2,
                            &test->exp_dir_order,
                            &test->exp_rev_order,
                            &bytes_read);
    ASSERT(sscanf_ret == 4);

    if (strcmp(test->str1, "empty") == 0) {
        test->str1[0] = '\n';
        test->str1[1] = '\0';
    } else {
        *strchr(test->str1, '\0') = '\n';
    }
    if (strcmp(test->str2, "empty") == 0) {
        test->str2[0] = '\n';
        test->str2[1] = '\0';
    } else {
        *strchr(test->str2, '\0') = '\n';
    }

    return (size_t) bytes_read;
}

int run_one_test_comp_lex(void *voidptr_test) {
    ASSERT(voidptr_test != NULL);

    CompLexArgs *test = (CompLexArgs*) voidptr_test;

    Line line1 = {};
    Line line2 = {};
    set_line(&line1, test->str1);
    set_line(&line2, test->str2);

    int res_dir = compare_lines_lex(&line1, &line2);
    int res_rev = compare_lines_reverse_lex(&line1, &line2);
    test->res_dir_order = (res_dir > 0) ? 1 : (res_dir == 0) ? 0 : -1;
    test->res_rev_order = (res_rev > 0) ? 1 : (res_rev == 0) ? 0 : -1;

    return (test->res_dir_order == test->exp_dir_order &&
            test->res_rev_order == test->exp_rev_order); 
}

void failed_test_report_comp_lex(const void *voidptr_test) {
    ASSERT(voidptr_test != NULL);

    const CompLexArgs *test = (const CompLexArgs*) voidptr_test;

    printf("str1: %s\n"
           "str2: %s\n"
           "Expected direct order: %d\n"
           "Result   direct order: %d\n\n"
           "Expected reverse order: %d\n"
           "Result   reverse order: %d\n",
           test->str1,
           test->str2,
           test->exp_dir_order,
           test->res_dir_order,
           test->exp_rev_order,
           test->res_dir_order);
}

#include "../../../../error_handling/undef_error_handling.h"
