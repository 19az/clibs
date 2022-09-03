#ifndef UNIT_TESTING_H
#define UNIT_TESTING_H

#include <stddef.h>

/// @file unit_testing.h

/// @brief Conducts unit test for some function
///
/// @param[in] func_name string with function name
/// @param[in] tests pointer to tests data
/// @param[in] size size of data for one test
/// @param[in] nTests number of tests
/// @param[in] run_one_test pointer to the function
/// which takes void ptr to a test data, runs test
/// and return 1 if test is passed or 0 if failed
/// @param[in] failed_test_report pointer to the function
/// which takes pointer to a test data and do report(prints
/// it in stdout or in a file, for example)
void unit_test(const char *func_name,
               const void *tests,
               size_t size,
               size_t nTests,
               char (*run_one_test) (const void*),
               void (*failed_test_report) (const void*));

/// @brief Shows numbers of failed test after unit test
/// 
/// @param[in] results array with results of each test
/// @param[in] nTests number f tests
void report(const char *results, size_t nTests);

#endif /* UNIT_TESTING_H */
