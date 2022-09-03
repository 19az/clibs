#include <math.h>
#include <stdio.h>

#include "../../unit_testing/colorful_text.h"
#include "../../rwfile/rwfile.h"
#include "../equations.h"
#include "equations_ut.h"

int get_one_test_se(SETestArgs *test, const char *buffer) {
    int bytes_read = 0;
    sscanf(buffer,
           "%lg %lg %lg %d %lg %lg %n",
           &test->a,
           &test->b,
           &test->c,
           &test->nRoots,
           &test->root1,
           &test->root2,
           &bytes_read);

    return bytes_read;
}

int run_test_se(SETestArgs *test, int *nRoots, double *root1, double *root2) {
    *nRoots = se_solve(test->a, test->b, test->c, root1, root2);
    int result = (*nRoots == test->nRoots);
    if (result) {
        if (*nRoots == 1) result *= is_equal(*root1, test->root1);
        if (*nRoots == 2) result *= is_equal(*root2, test->root2);
    }
    return result;
}

void se_solve_ut() {
    YELLOW(printf("\nUnit test for se_solve()\n");)

    int file_size = get_file_size(tests_filename_se);
    switch (file_size) {
        case 0:  printf("File with tests is empty\n");
                 return;
        case -2: printf("Cannot get stat of file with tests\n");
                 return;
        case -3: printf("tests_file_name is NULL\n");
                 return;
        default: break;
    }

    char buffer[MAXBUFFERSIZE];
    int bytes_read = read_file(tests_filename_se, buffer, (size_t) file_size);
    switch (bytes_read) {
        case 0:  printf("Error occured during reading file with tests\n");
                 return;
        case -1: printf("Cannot open file with tests\n");
                 return;
        case -3: printf("buffer == NULL\n");
                 return;
        default: break;
    }
    buffer[file_size] = '\0';

    SETestArgs test;
    int results[MAXNTESTS];
    bytes_read = 0;
    char *buffer_ptr = buffer;
    for (int i = 0; (bytes_read = get_one_test_se(&test, buffer_ptr)) > 0; ++i) {
        buffer_ptr += bytes_read;
        printf("Test # %2d ... ", i);

        int nRoots = 0;
        double root1 = NAN;
        double root2 = NAN;
        results[i] = (run_test_se(&test, &nRoots, &root1, &root2) == 1);
        results[i + 1] = -1;
        if (results[i]) {
            GREEN(printf("OK\n");)
        } else {
            RED(printf("FAILED\n");)
            printf("a           = %lg\n"
                   "b           = %lg\n"
                   "c           = %lg\n"
                   "nRoots(exp) = %d\n"
                   "root1(exp)  = %lg\n"
                   "root2(exp)  = %lg\n"
                   "nRoots(res) = %d\n"
                   "root1(res)  = %lg\n"
                   "root2(res)  = %lg\n",
                   test.a,
                   test.b,
                   test.c,
                   test.nRoots,
                   test.root1,
                   test.root2,
                   nRoots,
                   root1,
                   root2);
        }
    }

    unit_test_report(results);
    YELLOW(printf("Unit test is over\n\n");)
}

int get_one_test_le(LETestArgs *test, const char *buffer) {
    int bytes_read = 0;
    sscanf(buffer,
           "%lg %lg %d %lg %n",
           &test->a,
           &test->b,
           &test->nRoots,
           &test->root,
           &bytes_read);

    return bytes_read;
}

int run_test_le(LETestArgs *test, int *nRoots, double *root) {
    *nRoots = le_solve(test->a, test->b, root);
    int result = (*nRoots == test->nRoots);
    if (result && (*nRoots == 1)) 
        result = is_equal(*root, test->root);

    return result;
}

void le_solve_ut() {
    YELLOW(printf("\nUnit test for le_solve()\n");)

    int file_size = get_file_size(tests_filename_le);
    switch (file_size) {
        case 0:  printf("File with tests is empty\n");
                 return;
        case -2: printf("Cannot get stat of file with tests\n");
                 return;
        case -3: printf("tests_file_name is NULL\n");
                 return;
        default: break;
    }

    char buffer[MAXBUFFERSIZE];
    int bytes_read = read_file(tests_filename_le, buffer, (size_t) file_size);
    switch (bytes_read) {
        case 0:  printf("Error occured during reading file with tests\n");
                 return;
        case -1: printf("Cannot open file with tests\n");
                 return;
        case -3: printf("buffer == NULL\n");
                 return;
        default: break;
    }
    buffer[file_size] = '\0';

    LETestArgs test;
    int results[MAXNTESTS];
    bytes_read = 0;
    char *buffer_ptr = buffer;
    for (int i = 0; (bytes_read = get_one_test_le(&test, buffer_ptr)) > 0; ++i) {
        buffer_ptr += bytes_read;
        printf("Test # %2d ... ", i);

        int nRoots = 0;
        double root = NAN;
        results[i] = (run_test_le(&test, &nRoots, &root) == 1);
        results[i + 1] = -1;
        if (results[i]) {
            GREEN(printf("OK\n");)
        } else {
            RED(printf("FAILED\n");)
            printf("a           = %lg\n"
                   "b           = %lg\n"
                   "nRoots(exp) = %d\n"
                   "root(exp)   = %lg\n"
                   "nRoots(res) = %d\n"
                   "root(res)   = %lg\n",
                   test.a,
                   test.b,
                   test.nRoots,
                   test.root,
                   nRoots,
                   root);
        }
    }

    unit_test_report(results);
    YELLOW(printf("Unit test is over\n\n");)
}

void unit_test_report(int *report) {
    int none_failed_test = 1;
    RED(printf("Failed tests numbers: ");)
    for (int i = 0; report[i] != -1; ++i) {
        if (!report[i]) {
            none_failed_test = 0;
            RED(printf("%d ", i);)
        }
    }
    if (none_failed_test) {
        RED(printf("None");)
    }
    printf("\n");
}

int main(void) {
    se_solve_ut();
    le_solve_ut();

    return 0;
}
