#ifndef EQUATIONS_UT_H
#define EQUATIONS_UT_H

#include <math.h>

/// @file equations_ut.h

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
int get_one_test_buf_se(void *test, const char *buffer);

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
int get_one_test_buf_le(void *test, const char *buffer);
                                              
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

#endif /* EQUATIONS_UT_H */
