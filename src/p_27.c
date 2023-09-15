#include "euler.h"
#include <assert.h>

#define N   (1 << 22)
#define CAP 1000

static i64 _eval(i64 b, i64 c, i64 x)
{
    return x * x + b * x + c;
}

static i64 _count_primes(i64 b, i64 c, Sieve sieve)
{
    i64 count;
    i64 eval;

    count = 0;
    for (i64 x = 0; x < CAP; x ++)
    {
        if ((eval = _eval(b, c, x)) < 0) break;

        if (Sieve_is_prime(sieve, eval)) count ++;
        else break;
    }

    return count;
}

void p_27(void)
{
    Sieve   sieve;
    i64     max;
    i64     current;
    i64     product;

    sieve = Sieve_new(N);
    max = 0;
    product = 0;

    for (i64 b = - CAP; b < CAP; b ++)
    {
        for (i64 c = -CAP; c < CAP; c ++)
        {
            current = _count_primes(b, c, sieve);
            if (max < current)
            {
                max = current;
                product = b * c;
            }
        }
    }

    i64_dbg(product);
    Sieve_del(& sieve);
}