#include "math.h"
#include <math.h>
#include <stdio.h>

#define EPS     1e-10
#define INIT    1.0
#define DLIM    (1 << 5)

double _sqrt(double root, double a, unsigned depth)
{
    double f;

    if (unlikely(depth > DLIM)) return root;

    f = root * root - a;
    if (double_abs(f) < EPS) return root;

    return _sqrt(root - (f / (2 * root)), a, depth + 1);
}

double math_sqrt(double a)
{
    if (unlikely(a < 0)) return NAN;

    return _sqrt(a / 2, a, 0);
}

static u64 _sqrt_bisect(u64 n, u64 low, u64 high)
{
    u64 mid;

    if (low >= high) return low;

    if ((mid = (high + low) / 2) == low) return low;
    if (mid * mid < n) return _sqrt_bisect(n, mid, high);
    if (mid * mid > n) return _sqrt_bisect(n, 0, mid);

    return mid;
}

u64 math_sqrt_int(u64 n)
{
    return _sqrt_bisect(n, 0, n);
}