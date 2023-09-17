#include "euler.h"

#define N       10
#define LIMIT   1000000

static u64 f_tbl[N];

static void _init(void)
{
    for (u64 k = 0; k < N; k ++) f_tbl[k] = math_factorial(k);
}

static u64 _digit_f_sum(u64 x)
{
    u64 sum;

    sum = 0;
    while (x)
    {
        sum += f_tbl[x % 10];
        x /= 10;
    }

    return sum;
}

void p_34(void)
{
    Vec vec;
    u64 x;

    _init();
    vec = Vec_new(u64);
    for (u64 k = 3; k < LIMIT; k ++)
    {
        if (_digit_f_sum(k) == k) Vec_push(& vec, k, u64);
    }

    x = 0;
    Vec_fold(& x, vec, u64_addf);
    u64_dbg(x);
    Vec_del(& vec);
}