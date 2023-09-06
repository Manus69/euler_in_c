#include "euler.h"

#define N 2000000
void p_10(void)
{
    Sieve   sieve;
    Vec     primes;
    u64     sum;

    sieve = Sieve_new(N);
    primes = Sieve_primes_lt(sieve, N);
    sum = 0;

    Vec_fold(& sum, primes, u64_addf);

    Sieve_del(& sieve);
    Vec_del(& primes);

    u64_dbg(sum);
}