#include <stdlib.h>

#include "colorful_text.h"
#include "unit_testing.h"
#include "../error_report/error_report.h"
#include "../rwfile/rwfile.h"
#include "../strings/strings.h"

void unit_test(const char *func_name,
               const char *tests_filename,
               size_t size,
               size_t (*get_one_test_buf) (void*, const char*),
               char (*run_one_test) (void*),
               void (*failed_test_report) (const void*)) {
    if (tests_filename == NULL) {
        ERROR_REPORT("tests_filename == NULL")
        return;
    } else if (size == 0) {
        ERROR_REPORT("size == 0")
        return;
    } else if (get_one_test_buf == NULL) {
        ERROR_REPORT("get_one_test_buf == NULL")
        return;
    } else if (run_one_test == NULL) {
        ERROR_REPORT("run_one_test == NULL")
        return;
    } else if (failed_test_report == NULL) {
        ERROR_REPORT("failed_test_report == NULL")
        return;
    }

    int file_size = get_file_size(tests_filename);
    if (file_size == 0) {
        ERROR_REPORT("file with tests is empty")
        return;
    } else if (file_size == -2) {
        ERROR_REPORT("cannot get stat of file with tests")
        return;
    }

    char *buffer = (char*) calloc((size_t) file_size + 1, sizeof(char));
    if (buffer == NULL) {
        ERROR_REPORT("error in calloc")
        return;
    }

    int bytes_read_file = read_file(tests_filename, buffer, (size_t) file_size);
    switch (bytes_read_file) {
        case 0:  ERROR_REPORT("error occured during reading file with tests")
                 free(buffer);
                 return;
        case -1: ERROR_REPORT("cannot open file with tests")
                 free(buffer);
                 return;
        default: break;
    }
    buffer[file_size] = '\0';

    size_t nTests = count_char_str(buffer, '\n');
    unsigned char *tests = (unsigned char*) calloc(nTests, size);
    if (tests == NULL) {
        ERROR_REPORT("error in calloc")
            free(buffer);
        return;
    }

    size_t bytes_read_buf = 0;
    char *buffer_ptr = buffer;
    for (size_t i = 0; (bytes_read_buf = get_one_test_buf(tests + size*i, buffer_ptr)) > 0; i++) {
        buffer_ptr += bytes_read_buf;
    }

    YELLOW(printf("Unit test for func %s is started\n", func_name);)
    char *results = (char*) calloc(nTests, sizeof(char));
    if (results == NULL) {
        ERROR_REPORT("calloc error")
        free(buffer);
        free(tests);
        return;
    }
            
    for (size_t test = 0; test < nTests; test++) {
        YELLOW(printf("Test # %3lu: ", test + 1);)
        char result = (run_one_test(tests + size*test) == 1);
        results[test] = result;
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
    if (results == NULL) {
        ERROR_REPORT("results == NULL")
        return;
    } else if (nTests == 0) {
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
