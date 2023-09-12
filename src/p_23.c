#include "euler.h"

#define N 28123

static bool _is_obtainable_tbl[N];

static bool _is_abundant(u64 x, Sieve sieve)
{
    Vec divisors;
    u64 sum;

    if (Sieve_is_prime(sieve, x)) return false;

    sum = 0;
    divisors = math_divisors_proper(x);
    Vec_fold(& sum, divisors, u64_addf);
    sum = sum > x;

    Vec_del(& divisors);

    return sum;
}

static Vec _get_abundant_numbers()
{
    Vec     vec;
    Sieve   sieve;

    sieve = Sieve_new(N);
    vec = Vec_new(u64);
    Vec_reserve(& vec, N);

    for (u64 k = 1; k < N; k ++)
    {
        if (_is_abundant(k, sieve)) Vec_push(& vec, k, u64);
    }

    Sieve_del(& sieve);

    return vec;
}

static void _compute_obtainable(Vec abundant)
{
    u64 sum;

    for (i64 k = 0; k < Vec_len(abundant); k ++)
    {
        for (i64 w = k; w < Vec_len(abundant); w ++)
        {
            sum = deref(u64) Vec_get(abundant, k) + deref(u64) Vec_get(abundant, w);
            if (sum >= N) break;

            _is_obtainable_tbl[sum] = true;
        }
    }
}

static u64 _sum()
{
    u64 sum;

    sum = 0;
    for (i64 k = 0; k < N; k ++)
    {
        if (! _is_obtainable_tbl[k]) sum += k;
    }

    return sum;
}

void p_23(void)
{
    Vec abundant_numbers;
    u64 sum;

    abundant_numbers = _get_abundant_numbers();
    _compute_obtainable(abundant_numbers);
    sum = _sum();
    u64_dbg(sum);

    Vec_del(& abundant_numbers);
}