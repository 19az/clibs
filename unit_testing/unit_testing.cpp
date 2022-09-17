#include <stdlib.h>

#include "colorful_text.h"
#include "unit_testing.h"
#include "../rwfile/rwfile.h"
#include "../strings/strings.h"

#include "../error_handling/error_handling.h"

void unit_test(const char *func_name,
               const char *tests_filename,
               size_t size,
               size_t (*get_one_test_buf)   (void*, const char*),
               int    (*run_one_test)       (void*),
               void   (*failed_test_report) (const void*)) {
    ASSERT(tests_filename     != NULL, "tests_filename "     "is invalid");
    ASSERT(size               != 0   , "size "               "is 0");
    ASSERT(get_one_test_buf   != NULL, "get_one_test_buf "   "is invalid");
    ASSERT(run_one_test       != NULL, "run_one_test "       "is invalid");
    ASSERT(failed_test_report != NULL, "failed_test_report " "is invalid");

    int err = 0;
    size_t file_size = get_file_size(tests_filename, &err);
    ASSERT(file_size != 0, "file size is 0");
    ASSERT(err != 1, "cannot get file stat");
    ASSERT(err != 2, "bad file size");

    char *buffer = (char*) calloc(file_size + 1, sizeof(char));
    ASSERT(buffer, "error in calloc buffer");

    err = 0;
    size_t bytes_read_file = read_file(tests_filename, buffer, sizeof(char), file_size, &err);
    ASSERT(bytes_read_file > 0, "read less symbols than file_size");
    ASSERT(((err >> 2) & 1) != 1, "error during openning file");
    ASSERT(((err >> 3) & 1) != 1, "error during reading file");
    ASSERT(((err >> 4) & 1) != 1, "error during closing file");

    size_t nTests = count_char_str(buffer, '\n');
    unsigned char *tests = (unsigned char*) calloc(nTests, size);
    ASSERT(tests, "error in calloc tests")

    size_t bytes_read_buf = 0;
    char *buffer_ptr = buffer;
    for (size_t i = 0; (bytes_read_buf = get_one_test_buf(tests + size*i, buffer_ptr)) > 0; i++) {
        buffer_ptr += bytes_read_buf;
    }

    YELLOW(printf("Unit test for func %s is started\n", func_name);)
    char *results = (char*) calloc(nTests, sizeof(char));
    ASSERT(results, "error in calloc results");
            
    for (size_t test = 0; test < nTests; test++) {
        YELLOW(printf("Test # %3lu: ", test + 1);)
        int result = (run_one_test(tests + size*test) == 1);
        results[test] = (char) result;
        if (result) {
            GREEN(printf("Ok\n");)
        } else {
            RED(printf("Failed\n");)
            RED(failed_test_report(tests + size*test);)
        }
    }
    report(results, nTests);

    free(results);
    free(tests);
    free(buffer);
    YELLOW(printf("Unit test is over\n\n");)
}

void report(const char *results, size_t nTests) {
    ASSERT(results, "results is invalid");
    if (nTests == 0) {
        return;
    }

    char none_failed_tests = 1;
    RED(printf("Failed test numbers are: ");)
    for (size_t test = 0; test < nTests; test++) {
        if (results[test] == 0) {
            none_failed_tests = 0;
            RED(printf("%lu ", test + 1);)
        }
    }
    if (none_failed_tests) {
        GREEN(printf("None");)
    }
    printf("\n");
}

#include "../error_handling/undef_error_handling.h"
