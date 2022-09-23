
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../line.h"
#include "../../../../unit_testing/unit_testing.h"

#include "../../../../error_handling/error_handling.h"

//leni-decl---------------------------------------------------------------------

const size_t MAXLEN_LINE = 20;

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
              sizeof(char[MAXLEN_LINE]),
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

    char *test = (char*) voidptr_test;

    int bytes_read = 0;
    int ret = sscanf(buffer, "%s %n", test, &bytes_read);
    ASSERT(ret == 1 || ret == EOF);
    
    size_t len = strlen(test);
    for (size_t i = 0; i < len; i++) {
        if (test[i] == 'N') test[i] = '\n';
    }

    return (size_t) bytes_read;
}

int run_one_test_line(void *voidptr_test) {
    ASSERT(voidptr_test != NULL);

    char *test = (char*) voidptr_test;

    size_t n_lines = 0;
    Line *lines = (Line*) parse_buffer_lines(test, &n_lines);
    
    printf("\nNumber of Lines: %lu\n", n_lines);

    for (size_t line = 0; line < n_lines; line++) {
        printf("Size: %2lu line: ", lines[line].len);
        print_line_stream(stdout, lines + line);
    }

    free(lines);
    return 1;
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

    *strchr(test->str1, '\0') = '\n';
    *strchr(test->str2, '\0') = '\n';

    return (size_t) bytes_read;
}

int run_one_test_comp_lex(void *voidptr_test) {
    ASSERT(voidptr_test != NULL);

    CompLexArgs *test = (CompLexArgs*) voidptr_test;

    size_t n_lines = 0;
    Line *line1 = (Line*) parse_buffer_lines(test->str1, &n_lines);
    Line *line2 = (Line*) parse_buffer_lines(test->str2, &n_lines);

    int res_dir = compare_lines_lex(line1, line2);
    int res_rev = compare_lines_reverse_lex(line1, line2);
    test->res_dir_order = (res_dir > 0) ? 1 : (res_dir == 0) ? 0 : -1;
    test->res_rev_order = (res_rev > 0) ? 1 : (res_rev == 0) ? 0 : -1;

    free(line1);
    free(line2);
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
