#ifndef MATH_H
#define MATH_H

#include "def.h"
#include "Vec.h"
#include "Pair.h"

#define math_sum_gen(type) \
static inline type type ## _sum(const type * ptr, i64 n_items) \
{ \
    type sum = 0; \
    while (n_items --) sum += * ptr ++; \
    return sum; \
}

#define math_addf_gen(type) \
static inline void type ## _addf(void * target, const void * rhs) \
{deref(type) target += deref(type) rhs;}

math_sum_gen(u64)
math_sum_gen(i64)
math_addf_gen(i64)
math_addf_gen(u64)

u64 math_log2(u64 x);
u64 math_log10(u64 x);
u64 math_arith_prog_sum(u64 n);
u64 math_factorial(u64 n);
u64 math_gcd(u64 x, u64 y);
u64 math_lcm(u64 x, u64 y);
u64 math_pow(u64 base, u64 exp);
Vec math_divisors(u64 x);
Vec math_divisors_sorted(u64 x);
Vec math_prime_divisors(u64 x);
u64 math_prime_divisor_power(u64 x, u64 p);
Vec math_prime_divisor_pairs(u64 x);

#endif