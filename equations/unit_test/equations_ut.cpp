

/// @file equations_ut.cpp

#include <math.h>
#include <stdio.h>

#include "../equations.h"
#include "../../error_report/error_report.h"
#include "../../unit_testing/unit_testing.h"

const char *tests_filename_se = "sesut.txt";
const char *tests_filename_le = "lesut.txt";

/// Struct to represent arguments for unit test for se_solve()
struct SETestArgs {
    double a         = NAN; ///< 1st coef
    double b         = NAN; ///< 2nd coef
    double c         = NAN; ///< 3rd coef
    int nRoots_exp   = 0;   ///< expected number of roots
    double root1_exp = NAN; ///< expected 1st root
    double root2_exp = NAN; ///< expected 2nd root
    int nRoots_res   = 0;   ///< resulted number of roots
    double root1_res = NAN; ///< resulted 1st root
    double root2_res = NAN; ///< resulted 2nd root
};

/// Struct to represent arguments for unit test for le_solve()
struct LETestArgs {
    double a        = NAN; ///< 1ts coef
    double b        = NAN; ///< 2nd coef
    int nRoots_exp  = 0;   ///< expected number of roots
    double root_exp = NAN; ///< expected root
    int nRoots_res  = 0; ///< resulted number of roots
    double root_res = NAN; ///< resulted root
};

/// @brief Gets one test for se_solve_ut() from buffer
///
/// @param[out] test void pointer to struct with args
/// @param[in] buffer buffer with text
///
/// @return number of read bytes on success,
/// -1 if some of given args are NULL 
size_t get_one_test_buf_se(void *test, const char *buffer);

/// @brief Runs 1 test from unit test for se_solve()
///
/// @param[in/out] voidptr_test pointer to struct SETestArgs
///
/// @return 1 if test is passed,
/// 0 if test is not passed,
/// 2 if test == NULL
char run_test_se(void *voidptr_test);

/// @brief Prints args of failed test in unit test for se_solve()
///
/// @param[in] voidptr_test void pointer to the struct SETestArgs
void failed_test_report_se(const void *voidptr_test);

/// @brief Gets one test for le_solve_ut() from buffer
///
/// @param[out] test void pointer to struct with args
/// @param[in] buffer buffer with text
///
/// @return number of read bytes on success,
/// -1 if some of given args are NULL 
size_t get_one_test_buf_le(void *test, const char *buffer);
                                              
/// @brief Runs 1 test from unit test for le_solve()
///
/// @param[in/out] voidptr_test void pointer to struct LETestArgs
///
/// @return 1 if test is passed,
/// 0 if test is not passed,
/// 2 if test == NULL
char run_test_le(void *voidptr_test);

/// @brief Prints args of failed test in unit test for le_solve()
///
/// @param[in] voidptr_test void pointer to the struct LETestArgs
void failed_test_report_le(const void *voidptr_test);

int main(void) {
    unit_test("se_solve()",
              tests_filename_se,
              sizeof(SETestArgs),
              get_one_test_buf_se,
              run_test_se,
              failed_test_report_se);

    unit_test("le_solve()",
              tests_filename_le,
              sizeof(LETestArgs),
              get_one_test_buf_le,
              run_test_le,
              failed_test_report_le);

    return 0;
}

size_t get_one_test_buf_se(void *voidptr_test, const char *buffer) {
    if (voidptr_test == NULL) {
        ERROR_REPORT("test == NULL")
        return 0;
    }
    if (buffer == NULL) {
        ERROR_REPORT("buffer == NULL")
        return 0;
    }

    SETestArgs *test = (SETestArgs*) voidptr_test;
    int bytes_read = 0;
    sscanf(buffer,
           "%lg %lg %lg %d %lg %lg %n",
           &test->a,
           &test->b,
           &test->c,
           &test->nRoots_exp,
           &test->root1_exp,
           &test->root2_exp,
           &bytes_read);

    if (bytes_read < 0) {
        ERROR_REPORT("error in sscanf")
        return 0;
    }

    return (size_t) bytes_read;
}

char run_test_se(void *voidptr_test) {
    if (voidptr_test == NULL) {
        ERROR_REPORT("test == NULL")
        return 2;
    }

    SETestArgs *test = (SETestArgs*) voidptr_test;
    double root1_exp = test->root1_exp;
    double root2_exp = test->root2_exp;
    double root1_res = NAN;
    double root2_res = NAN;
    int nRoots_res = se_solve(test->a,
                              test->b,
                              test->c,
                              &root1_res,
                              &root2_res);

    char result = (nRoots_res == test->nRoots_exp);
    if (result) {
        if (nRoots_res == 1) (result && is_equal(root1_res, root1_exp));
        if (nRoots_res == 2) (result && is_equal(root2_res, root2_exp));
    }

    test->nRoots_res = nRoots_res;
    test->root1_res  = root1_res;
    test->root2_res  = root2_res;
    return result;
}

void failed_test_report_se(const void *voidptr_test) {
    if (voidptr_test == NULL) {
        ERROR_REPORT("test == NULL")
        return;
    }

    const SETestArgs *test = (const SETestArgs*) voidptr_test;
    printf("a           = %lg\n"
           "b           = %lg\n"
           "c           = %lg\n"
           "nRoots(exp) = %d\n"
           "root1(exp)  = %lg\n"
           "root2(exp)  = %lg\n"
           "nRoots(res) = %d\n"
           "root1(res)  = %lg\n"
           "root2(res)  = %lg\n",
           test->a,
           test->b,
           test->c,
           test->nRoots_exp,
           test->root1_exp,
           test->root2_exp,
           test->nRoots_res,
           test->root1_res,
           test->root2_res);
}

size_t get_one_test_buf_le(void *voidptr_test, const char *buffer) {
    if (voidptr_test == NULL) {
        ERROR_REPORT("test == NULL")
        return 0;
    }
    if (buffer == NULL) {
        ERROR_REPORT("buffer == NULL")
        return 0;
    }

    LETestArgs *test = (LETestArgs*) voidptr_test;
    int bytes_read = 0;
    sscanf(buffer,
           "%lg %lg %d %lg %n",
           &test->a,
           &test->b,
           &test->nRoots_exp,
           &test->root_exp,
           &bytes_read);

    if (bytes_read < 0) {
        ERROR_REPORT("error in sscanf")
        return 0;
    }

    return (size_t) bytes_read;
}

char run_test_le(void *voidptr_test) {
    if (voidptr_test == NULL) {
        ERROR_REPORT("test == NULL")
        return 2;
    }

    LETestArgs *test = (LETestArgs*) voidptr_test;
    double root_exp = test->root_exp;
    double root_res = NAN;
    int nRoots_res = le_solve(test->a,
                              test->b,
                              &root_res);
    char result = (nRoots_res == test->nRoots_exp);
    if (result) {
        if (nRoots_res == 1) (result && is_equal(root_res, root_exp));
    }

    test->nRoots_res = nRoots_res;
    test->root_res  = root_res;
    return result;
}

void failed_test_report_le(const void *voidptr_test) {
    if (voidptr_test == NULL) {
        ERROR_REPORT("test == NULL")
        return;
    }

    const LETestArgs *test = (const LETestArgs*) voidptr_test;
    printf("a           = %lg\n"
           "b           = %lg\n"
           "nRoots(exp) = %d\n"
           "root(exp)   = %lg\n"
           "nRoots(res) = %d\n"
           "root(res)   = %lg\n",
           test->a,
           test->b,
           test->nRoots_exp,
           test->root_exp,
           test->nRoots_res,
           test->root_res);
}
