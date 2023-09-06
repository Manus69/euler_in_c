#include "euler.h"

static u64 _pyramidal(u64 n)
{
    return n * (n + 1) * (2 * n + 1) / 6;
}

static u64 _sum_squared(u64 n)
{
    u64 sum;

    sum = math_arith_prog_sum(n);

    return sum * sum;
}

#define N 100
void p_6(void)
{
    u64_dbg(_sum_squared(N) - _pyramidal(N));
}