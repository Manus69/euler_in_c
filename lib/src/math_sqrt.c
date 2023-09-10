#include "math.h"
#include <math.h>

#define EPS     1e-10
#define INIT    1.0

double _sqrt(double root, double a)
{
    double f;

    f = root * root - a;
    if (double_abs(f) < EPS) return root;

    return _sqrt(root - (f / (2 * root)), a);
}

double math_sqrt(double a)
{
    if (unlikely(a < 0)) return NAN;

    return _sqrt(INIT, a);
}