#include "euler.h"

#define N   1000000
#define SS  (N * 10)

static u64 _rotate(u64 x)
{
    u64 digit;
    u64 base;

    base = math_pow(10, math_log10(x));
    digit = x / base;

    x = x - (base * digit);
    x = x * 10 + digit;

    return x;
}

static bool _check_even_digit(u64 x)
{
    char    buff[1 << 5] = {};
    i64     len;

    len = sprintf(buff, "%zu", x);
    for (i64 k = 1; k < len; k ++)
    {
        if ((buff[k] - '0') % 2 == 0) return true;
    }

    return false;
}

static bool _is_circular(u64 p, Sieve sieve)
{
    u64 n_digits;
    u64 next;

    n_digits = math_log10(p) + 1;
    if (n_digits == 1) return true;
    if (_check_even_digit(p)) return false;

    for (u64 k = 0; k < n_digits - 1; k ++)
    {
        next = _rotate(p);
        if (! Sieve_is_prime(sieve, next)) return false;
        p = next;
    }

    return true;
}

void p_35(void)
{
    Sieve   sieve;
    u64     total;

    total = 0;
    sieve = Sieve_new(SS);
    for (u64 k = 2; k < N; k ++)
    {
        if (Sieve_is_prime(sieve, k) && _is_circular(k, sieve)) total ++;
    }

    u64_dbg(total);
    Sieve_del(& sieve);
}