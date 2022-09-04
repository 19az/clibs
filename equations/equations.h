#ifndef EQUATIONS_H
#define EQUATIONS_H

/// @file equations.h

const double EPS = 1e-10; ///< Precision of equality of two numbers

/// @brief Checks if two double numbers are equal
/// 
/// @param[in] a 1st double number
/// @param[in] b 2nd double number
///
/// @return 1 if equal and 0 otherwise
///
/// @note uses EPS as valid precision
int is_equal(double a, double b);

/// @brief Swaps two double numbers
///
/// @param[in] a pointer to the 1st number
/// @param[in] b pointer to the 2nd number
void swap(double *a, double *b);

/// Return codes for se_solve() and le_solve():
enum retcodes_equations
{
INF_ROOTS_EQUATIONS      = -1, ///< infinite number of roots
ERR_COEF_EQUATIONS       = -2, ///< some coefficients are not finite
};
                                                        
/// @brief Solves square equation
/// 
/// @param[in]  a 1st coef
/// @param[in]  b 2nd coef
/// @param[in]  c 3rd coef
/// @param[out] root1 pointer to the 1st root
/// @param[out] root2 pointer to the 2nd root
///
/// @return number of roots on success,
/// -1 if there are infinite number of roots
/// -2 if some given coefficients are not finite numbers
int se_solve(double a, double b, double c, double *root1, double *root2);

/// @brief Solves linear equation
///
/// @param[in]  a 1st coef
/// @param[in]  b 2nd coef
/// @param[out] root pointer to the root
///
/// @return number of roots on success,
/// -1 if there are infinite number of roots,
/// -2 if some given coefficients are not finite numbers,
int le_solve(double a, double b, double *root);

#endif /* EQUATIONS_H */
