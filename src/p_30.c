#include "euler.h"

#define POW 5
#define N   10
#define MAX 1000000

static u64 powers[N];

static inline u64 _digit_power(u64 digit)
{
    return powers[digit];
}

static void _init()
{
    for (u64 k = 0; k < N; k ++)
    {
        powers[k] = math_pow(k, POW);
    }
}

static u64 _compute_sum(u64 x)
{
    u64 sum;

    sum = 0;
    while (x)
    {
        sum += _digit_power(x % 10);
        x /= 10;
    }

    return sum;
}

void p_30(void)
{
    Vec vec;
    u64 x;

    _init();
    vec = Vec_new(u64);

    for (u64 k = 2; k < MAX; k ++)
    {
        if (k == _compute_sum(k)) Vec_push(& vec, k, u64);
    }

    x = 0;
    
    Vec_fold(& x, vec, u64_addf);
    u64_dbg(x);
    Vec_del(& vec);
}