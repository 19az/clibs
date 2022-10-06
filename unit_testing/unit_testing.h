
/// @file unit_testing.h
///
/// @brief Универсальная функция для юнит тестов

#ifndef UNIT_TESTING_H
#define UNIT_TESTING_H

#include <stddef.h>

/// @file unit_testing.h

/// @brief Conducts unit test for some function
///
/// @param[in] func_name string with function name
/// @param[in] tests_filename name of the file with tests
/// @param[in] size size of data for one test
/// @param[in] get_one_test_buf pointer to the function
/// which takes void ptr as places to store test data and const char ptr
/// as place from where load test data and returns number of read bytes
/// @param[in] run_one_test pointer to the function
/// which takes void ptr to a test data, runs test
/// and return 1 if test is passed or 0 if failed
/// @param[in] failed_test_report pointer to the function
/// which takes pointer to a test data and do report(prints
/// it in stdout or in a file, for example)
void unit_test(const char* func_name,
               const char* tests_filename,
               
               size_t size,

               size_t (*get_one_test_buf)   (void*, const char*),
               int    (*run_one_test)       (void*),
               void   (*failed_test_report) (const void*));

/// @brief Shows numbers of failed test after unit test
/// 
/// @param[in] results array with results of each test
/// @param[in] nTests number of tests
void report(const char* results, size_t nTests);

#endif /* UNIT_TESTING_H */

