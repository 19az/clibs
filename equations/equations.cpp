#include <math.h>
#include <stdio.h>

#include "equations.h"
#include "../assert/my_assert.h"

int is_equal(double a, double b) {
    return (fabs(a - b) < EPS);
}

void swap(double *a, double *b) {
    ASSERT(a != NULL);
    ASSERT(b != NULL);
    if (a == b)
        return;

    double swap = *a;
    *a = *b;
    *b = swap;
}

int square_eq_solve(double a, double b, double c, double *root1, double *root2) {
    ASSERT(root1 != NULL);
    ASSERT(root2 != NULL);
    ASSERT(root1 != root2);
    if (!std::isfinite(a) ||
        !std::isfinite(b) ||
        !std::isfinite(c))
        return ERR_COEF_EQUATIONS;

    int n_roots = 0;
    if (is_equal(a, 0)) {
        n_roots = linear_eq_solve(b, c, root1);
    } else {
        if (is_equal(b, 0)) {
            if (is_equal(c, 0)) {
                *root1 = 0;
                n_roots = 1;
            } else {
                double squared_x = -c/a;
                if (squared_x > 0) {
                    *root1 = -sqrt(squared_x);
                    *root2 = -*root1;
                    n_roots = 2;
                } else {
                    n_roots = 0;
                }
            }
        } else /* is_equal(b, 0) */ {
            if (is_equal(c, 0)) {
                *root1 = 0;
                linear_eq_solve(a, b, root2);
                if (*root1 > *root2)
                    swap(root1, root2);
                n_roots = 2;
            } else {
                double squared_discr = b*b - 4*a*c;
                if (is_equal(squared_discr, 0)) {
                    *root1 = -b/(2*a);
                    n_roots = 1;
                } else if (squared_discr < 0) {
                    n_roots = 0;
                } else {
                    double discr = sqrt(squared_discr);
                    *root1 = (-b - discr)/(2*a);
                    *root2 = (-b + discr)/(2*a);
                    if (*root1 > *root2)
                        swap(root1, root2);
                    n_roots = 2;
                }
            }
        }
    }

    return n_roots;
}

int linear_eq_solve(double a, double b, double* root) {
    ASSERT(root != NULL);
    if (!std::isfinite(a) ||
        !std::isfinite(b))
        return ERR_COEF_EQUATIONS;

    int n_roots = 0;
    if (is_equal(a, 0)) {
        n_roots = (is_equal(b, 0)) ? INF_ROOTS_EQUATIONS : 0;
    } else {
        *root = -b/a;
        n_roots = 1;
    }
    return n_roots;
}
