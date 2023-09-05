#include "euler.h"

static u64 _highest_cd_power(u64 low, u64 high, u64 p)
{
    u64 max_power;
    u64 power;

    max_power = 0;
    while (low < high)
    {
        if ((power = math_prime_divisor_power(low, p)) > max_power) max_power = power;
        low ++;
    }

    return max_power;
}

static u64 _lcm(u64 low, u64 high)
{
    Sieve   sieve;
    Vec     primes;
    u64     p;
    u64     power;
    u64     lcm;

    sieve = Sieve_new(high);
    primes = Sieve_primes_lt(sieve, high);
    lcm = 1;

    for (i64 k = 0; k < Vec_len(primes); k ++)
    {
        p = deref(u64) Vec_get(primes, k);
        power = _highest_cd_power(low, high, p);
        lcm *= math_pow(p, power);
    }

    Sieve_del(& sieve);
    Vec_del(& primes);

    return lcm;
}

#define N 20
void p_5(void)
{
    u64_dbg(_lcm(1, N + 1));
}