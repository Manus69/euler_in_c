#include "euler.h"

#define MOD 10000000000UL
#define N   1000

static inline u64 _pow_mod(u64 base, u64 exp, u64 mod)
{
    u64 result;

    result = 1;
    while (exp --)
    {
        result = (result * base) % mod;
    }

    return result;
}

void p_48(void)
{
    u64 sum;
    u64 term;

    sum = 0;
    for (u64 x = 1; x <= N; x ++)
    {
        term = _pow_mod(x, x, MOD);
        sum = (sum + term) % MOD;
    }

    u64_dbg(sum);
}