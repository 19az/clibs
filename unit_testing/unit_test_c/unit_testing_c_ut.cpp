#include <stdio.h>

#include "../unit_testing.h"

/// Read one block of args for test from buffer
///
/// @param[out] voidptr_test void pointer to the place
/// where store test data
/// @param[in] buffer text buffer
///
/// @return number of read bytes
size_t get_one_test_buf(void *voidptr_test, const char *buffer);

/// @brief Checks if given number is equal to 42
///
/// @param[in] data void pointer to the number
///
/// @return 1 if given number is equal to 42,
/// 0 otherwise
char run_test(void *data);

/// @brief Prints to the stdout given number
/// and then prints "ans = 42\n"
///
/// @param[in] data void pointer to the number
void failed_test_report(const void *data);

const char *func_name = "test_func";
const char *tests_filename = "test.txt";
const char results[5] = {};

int main() {
    int nTest = 0;
    scanf("%d", &nTest);
    switch (nTest) {
        case 1:  unit_test(func_name, NULL,           sizeof(int), get_one_test_buf, run_test, failed_test_report);
                 break;
        case 2:  unit_test(func_name, tests_filename, 0,           get_one_test_buf, run_test, failed_test_report);
                 break;
        case 3:  unit_test(func_name, tests_filename, sizeof(int), 0,                run_test, failed_test_report);
                 break;
        case 4:  unit_test(func_name, tests_filename, sizeof(int), get_one_test_buf, NULL,     failed_test_report);
                 break;
        case 5:  unit_test(func_name, tests_filename, sizeof(int), get_one_test_buf, run_test, NULL);
                 break;
        case 6:  unit_test(func_name, tests_filename, sizeof(int), get_one_test_buf, run_test, failed_test_report);
                 break;
        case 7:  report(NULL, 0);
                 break;
        case 8:  report(results, 0);
                 break;
        default: break;
    }

    return 0;
}

size_t get_one_test_buf(void *voidptr_test, const char *buffer) {
   int *test = (int*) voidptr_test;
   int bytes_read = 0;
   sscanf(buffer, "%d %n", test, &bytes_read);
   return (size_t) bytes_read;
}

char run_test(void *data) {
    return *((const int*) data) == 42;
}

void failed_test_report(const void *data) {
    printf("result = %d\n"
           "ans = 42\n", 
           *((const int*) data));
}
