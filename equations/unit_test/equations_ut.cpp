
#include <math.h>
#include <stdio.h>

#include "equations/equations.h"
#include "unit_testing/unit_testing.h"

const char *tests_filename_se = "sesut.txt";
const char *tests_filename_le = "lesut.txt";

struct SETestArgs {
    double a         = NAN;
    double b         = NAN;
    double c         = NAN;
    int nRoots_exp   = 0;
    double root1_exp = NAN;
    double root2_exp = NAN;
    int nRoots_res   = 0;
    double root1_res = NAN;
    double root2_res = NAN;
};

struct LETestArgs {
    double a        = NAN;
    double b        = NAN;
    int nRoots_exp  = 0;
    double root_exp = NAN;
    int nRoots_res  = 0;
    double root_res = NAN;
};

size_t get_one_test_buf_se(void *test, const char *buffer);

int run_test_se(void *voidptr_test);

void failed_test_report_se(const void *voidptr_test);

size_t get_one_test_buf_le(void *test, const char *buffer);
                                              
int run_test_le(void *voidptr_test);

void failed_test_report_le(const void *voidptr_test);

int main(void) {
    unit_test("square_eq_solve()",
              tests_filename_se,
              sizeof(SETestArgs),
              get_one_test_buf_se,
              run_test_se,
              failed_test_report_se);

    unit_test("linear_eq_solve()",
              tests_filename_le,
              sizeof(LETestArgs),
              get_one_test_buf_le,
              run_test_le,
              failed_test_report_le);

    return 0;
}

size_t get_one_test_buf_se(void *voidptr_test, const char *buffer) {
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

    return (size_t) bytes_read;
}

int run_test_se(void *voidptr_test) {
    SETestArgs *test = (SETestArgs*) voidptr_test;
    double root1_exp = test->root1_exp;
    double root2_exp = test->root2_exp;
    double root1_res = NAN;
    double root2_res = NAN;
    int nRoots_res = square_eq_solve(test->a,
                                     test->b,
                                     test->c,
                                     &root1_res,
                                     &root2_res);

    int result = (nRoots_res == test->nRoots_exp);
    if (result) {
        if (nRoots_res == 1) result = (result && is_equal(root1_res, root1_exp));
        if (nRoots_res == 2) result = (result && is_equal(root2_res, root2_exp));
    }

    test->nRoots_res = nRoots_res;
    test->root1_res  = root1_res;
    test->root2_res  = root2_res;
    return result;
}

void failed_test_report_se(const void *voidptr_test) {
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
    LETestArgs *test = (LETestArgs*) voidptr_test;
    int bytes_read = 0;
    sscanf(buffer,
           "%lg %lg %d %lg %n",
           &test->a,
           &test->b,
           &test->nRoots_exp,
           &test->root_exp,
           &bytes_read);

    return (size_t) bytes_read;
}

int run_test_le(void *voidptr_test) {
    LETestArgs *test = (LETestArgs*) voidptr_test;
    double root_exp = test->root_exp;
    double root_res = NAN;
    int nRoots_res = linear_eq_solve(test->a,
                                     test->b,
                                     &root_res);
    int result = (nRoots_res == test->nRoots_exp);
    if (result) {
        if (nRoots_res == 1) result = (result && is_equal(root_res, root_exp));
    }

    test->nRoots_res = nRoots_res;
    test->root_res  = root_res;
    return result;
}

void failed_test_report_le(const void *voidptr_test) {
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
