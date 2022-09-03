#include <math.h>
#include <stdio.h>

#include "equations.h"

int is_equal(double a, double b) {
    return (fabs(a - b) < EPS);
}

void swap(double *a, double *b) {
    double swap = *a;
    *a = *b;
    *b = swap;
}

int se_solve(double a, double b, double c, double *root1, double *root2) {
    if (root1 == NULL ||
        root2 == NULL ||
        root1 == root2)
        return ERR_NULL_ARGS_EQUATIONS;
    if (!std::isfinite(a) ||
        !std::isfinite(b) ||
        !std::isfinite(c))
        return ERR_COEF_EQUATIONS;

    int nRoots = 0;
    if (is_equal(a, 0)) {
        nRoots = le_solve(b, c, root1);
    } else {
        if (is_equal(b, 0)) {
            if (is_equal(c, 0)) {
                *root1 = 0;
                nRoots = 1;
            } else {
                double squared_x = -c/a;
                if (squared_x > 0) {
                    *root1 = -sqrt(squared_x);
                    *root2 = -*root1;
                    nRoots = 2;
                } else {
                    nRoots = 0;
                }
            }
        } else {
            if (is_equal(c, 0)) {
                *root1 = 0;
                *root2 = -b/a;
                if (*root1 > *root2)
                    swap(root1, root2);
                nRoots = 2;
            } else {
                double squared_discr = b*b - 4*a*c;
                if (is_equal(squared_discr, 0)) {
                    *root1 = -b/(2*a);
                    nRoots = 1;
                } else if (squared_discr < 0) {
                    nRoots = 0;
                } else {
                    double discr = sqrt(squared_discr);
                    *root1 = (-b - discr)/(2*a);
                    *root2 = (-b + discr)/(2*a);
                    nRoots = 2;
                }
            }
        }
    }

    return nRoots;
}

int le_solve(double a, double b, double* root) {
    if (root == NULL)
        return ERR_NULL_ARGS_EQUATIONS;
    if (!std::isfinite(a) ||
        !std::isfinite(b))
        return ERR_COEF_EQUATIONS;

    int nRoots = 0;
    if (is_equal(a, 0)) {
        nRoots = (is_equal(b, 0)) ? INF_ROOTS_EQUATIONS : 0;
    } else {
        *root = -b/a;
        nRoots = 1;
    }
    return nRoots;
}
