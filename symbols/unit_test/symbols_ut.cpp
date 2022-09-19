
#include "stdio.h"

#include "../symbols.h"
#include "../../error_handling/error_handling.h"
#include "../../unit_testing/unit_testing.h"

const size_t MAXLEN = 10;
struct SkipNoLettersArgs {
    char  str[MAXLEN] = {};
    char *start       = 0;
    char *finish      = 0;
    int   step        = 0;
    char *expected    = NULL;
    char *result      = NULL;
};

size_t get_one_test_skip_no_letters(void *voidptr_test, const char *buffer);

int run_one_test_skip_no_letters(void *voidptr_test);

void failed_test_report_skip_no_letters(const void *voidptr_test);

const char *tests_filename = "snl_tests.txt";

int main() {
    unit_test("skip_no_letters",
              tests_filename,
              sizeof(SkipNoLettersArgs),
              get_one_test_skip_no_letters,
              run_one_test_skip_no_letters,
              failed_test_report_skip_no_letters);

    return 0;
}

size_t get_one_test_skip_no_letters(void *voidptr_test, const char *buffer) {
    SkipNoLettersArgs *test = (SkipNoLettersArgs*) voidptr_test;
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

    test->start    = test->str + start_index;
    test->finish   = test->str + finish_index;
    test->expected = test->str + expected_index;
    return (size_t) bytes_read;
}

int run_one_test_skip_no_letters(void *voidptr_test) {
    SkipNoLettersArgs *test = (SkipNoLettersArgs*) voidptr_test;

    test->result = skip_no_letters(test->start, test->finish, test->step);
    return (test->result == test->expected);
}

void failed_test_report_skip_no_letters(const void *voidptr_test) {
    const SkipNoLettersArgs *test = (const SkipNoLettersArgs*) voidptr_test;

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

#include "../../error_handling/undef_error_handling.h"
