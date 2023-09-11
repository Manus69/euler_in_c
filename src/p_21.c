#include "euler.h"

#define N 10000

static u64 div_sum_tbl[N];

u64 _div_sum(u64 x)
{
    Vec divisors;
    u64 sum;

    sum = 0;
    divisors = math_divisors(x);    
    Vec_fold(& sum, divisors, u64_addf);
    Vec_del(& divisors);

    return sum - x;
}

u64 _is_amicable(u64 x)
{
    u64 sum;

    sum = div_sum_tbl[x];
    if (sum < N && sum != x && div_sum_tbl[sum] == x) return sum;

    return 0;
}

u64 _amicable_sum()
{
    u64 sum;

    sum = 0;
    for (i64 k = 1; k < N; k ++)
    {
        sum += _is_amicable(k);
    }

    return sum;
}

void p_21(void)
{
    u64     sum;

    for (i64 k = 1; k < N; k ++)
    {
        div_sum_tbl[k] = _div_sum(k);
    }

    sum = _amicable_sum();
    u64_dbg(sum);
}