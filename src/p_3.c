#include "euler.h"

#define N 600851475143

void p_3(void)
{
    Vec divisors;

    divisors = math_prime_divisors(N);
    u64_dbgf(Vec_last(divisors));
    Vec_del(& divisors);
}