#include "euler.h"

#define N 10001
void p_7(void)
{
    Sieve   sieve;
    u64     prime;

    sieve = Sieve_new_n_primes(N);
    prime = Sieve_nth_prime(sieve, N - 1);
    Sieve_del(& sieve);
    u64_dbg(prime);
}