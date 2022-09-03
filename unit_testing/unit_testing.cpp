#include <stdlib.h>

#include "../assert/my_assert.h"
#include "colorful_text.h"
#include "unit_testing.h"

void unit_test(const char *func_name,
               const void *tests,
               size_t size,
               size_t nTests,
               char (*run_one_test) (void*),
               void (*failed_test_report) (void*)) {
    ASSERT(tests != NULL)
    ASSERT(size != 0)
    ASSERT(nTests != 0)
    ASSERT(run_one_test != NULL)

    YELLOW(printf("Unit test for func %s is started\n", func_name);)
    char *results = (char*) calloc(nTests, sizeof(char));
    for (size_t test = 0; test < nTests; test++) {
        YELLOW(printf("Test # %lu: ");)
        char result = run_one_test(tests + size*test);
        results[test] = result;
        if (result) {
            GREEN(printf("Ok\n");)
        } else {
            RED(printf("Failed\n");)
            RED(failed_test_report(tests + size*test);)
        }
    }
    report(results);
    free(results, nTests);
    YELLOW(printf("Unit test is over\n\n");)
}

void report(const char *results, size_t nTests) {
    ASSERT(results != NULL)
    ASSERT(nTests != 0)

    char none_failed_tests = 1;
    RED(printf("Failed test numbers are: ");)
    for (size_t test = 0; test < nTests; test++) {
        if (results[test] == 0) {
            none_failed_tests = 0;
            RED(printf("%lu ", test);)
        }
    }
    if (none_failed_tests) {
        GREEN(printf("None");)
    }
    printf("\n");
}
