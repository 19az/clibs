#ifndef EQUATIONS_UT_H
#define EQUATIONS_UT_H

#include <math.h>

/// @file equations.h

const int MAXNTESTS     = 1e2; ///< max number of tests in unit test for se_solve()
const int MAXBUFFERSIZE = 1e3; ///< max len of file with unit test for se_solve()

const char tests_filename_se[] = "sesut.txt"; ///< name of the file with tests for se_solve()
const char tests_filename_le[] = "lesut.txt"; ///< name of the file with tests for le_solve()

/// Struct to represent arguments for unit test for se_solve()
struct SETestArgs {
    double a     = NAN; ///< 1st coef
    double b     = NAN; ///< 2nd coef
    double c     = NAN; ///< 3rd coef
    int nRoots   = 0;   ///< number of roots
    double root1 = NAN; ///< 1st root
    double root2 = NAN; ///< 2nd root
};

/// @brief Gets one test for se_solve_ut() from buffer
///
/// @param[out] test pointer to struct with args
/// @param[in] buffer buffer with text
///
/// @return number of read bytes on success,
/// -1 if some of given args are NULL 
int get_one_test_se(SETestArgs *test, const char *buffer);

/// @brief Runs 1 test from unit test for se_solve()
///
/// @param[in] test pointer to struct with args
/// @param[out] nRoots pointer to the number of roots result
/// @param[out] root1 pointer to the 1st root result
/// @param[out] root2 pointer to the 2nd root result
///
/// @return 1 if test is passed,
/// 0 if test is not passed,
/// -1 if some of given args are NULL
int run_test_se(SETestArgs *test, int* nRoots, double *root1, double *root2);

/// @brief Unit test for se_solve()
///
/// @note Shows report after tests using unit_test_report()
void se_solve_ut();

/// Struct to represent arguments for unit test for le_solve()
struct LETestArgs {
    double a    = NAN; ///< 1ts coef
    double b    = NAN; ///< 2nd coef
    int nRoots  = 0;   ///< number of roots
    double root = NAN; ///< root
};

/// @brief Gets one test for le_solve_ut() from buffer
///
/// @param[out] test pointer to struct with args
/// @param[in] buffer buffer with text
///
/// @return number of read bytes on success,
/// -1 if some of given args are NULL 
int get_one_test_le(LETestArgs *test, const char *buffer);
                                              
/// @brief Runs 1 test from unit test for le_solve()
///
/// @param[in] test pointer to struct with args
/// @param[out] nRoots pointer to the number of roots result
/// @param[out] root1 pointer to the 1st root result
///
/// @return 1 if test is passed,
/// 0 if test is not passed,
/// -1 if some of given args are NULL
int run_test_le(LETestArgs *test, int* nRoots, double *root1);

/// @brief Unit test for le_solve()
/// 
/// @note Shows report after tests using unit_test_report()
void le_solve_ut();

/// @brief Shows report after unit test
///
/// @param[in] tests  array of results of unit tests
void unit_test_report(int *report);


#endif /* EQUATIONS_UT_H */
