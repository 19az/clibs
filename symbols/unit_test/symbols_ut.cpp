
#include "stdio.h"

#include "../symbols.h"
#include "../../error_handling/error_handling.h"
#include "../../unit_testing/unit_testing.h"

const size_t MAXLEN = 100;

struct SkipNoLettersArgs {
    char *str[MAXLEN] = {};
    int   step        = 0;
    char *expected    = NULL;
    char *result      = NULL;
};

size_t get_one_test_skip_no_letters(void *voidptr_test, const char *buffer);

int run_one_test_skip_no_letters(void *voidptr_test);

void failed_test_report_skip_no_letters(const void *voidptr_test);

const char *tests_filename = "skip_no_letters_tests.txt";

int main() {
    unit_test("skip_no_letters",
              tests_filename,
              sizeof(SkipNoLettersArgs),
              get_one_test_skip_no_letters,
              run_one_test_skip_no_letters,
              failed_test_report_skip_no_letters);

    return 0;
}

get_one_test_skip_no_letters(void *voidptr_test, const char *buffer) {
    SkipNoLettersArgs *test = (SkipNoLettersArgs*) voidptr_test;
    int expected_offset = 0;

    size_t bytes_read = 0;
    int result =sscanf(buffer,
                       "%s %d %d %n",
                       &test->str,
                       &test->step,
                       &expected_offset,
                       &bytes_read);
    ASSERT(result == 4 || result == EOF, "cannot read all arguments");

    test->expected = test->str + expected_offset;

    return bytes_read;
}

run_one_test_skip_no_letters(void *voidptr_test) {
    SkipNoLettersArgs *test = (SkipNoLettersArgs*) voidptr_test;

    char *result = skip_no_letters(test->str, test);
}

#include "../../error_handling/undef_error_handling.h"
