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

#define math_abs_gen(type) \
static inline type type ## _abs(type x) \
{return x >= 0 ? x : - x;}

#define math_abs(x) (x >= 0 ? x : - x)

math_sum_gen(u64)
math_sum_gen(i64)
math_addf_gen(i64)
math_addf_gen(u64)
math_abs_gen(double)
math_addf_gen(double)
math_abs_gen(i64)

u64     math_log2(u64 x);
u64     math_log10(u64 x);
u64     math_arith_prog_sum(u64 n);
bool    math_is_nat(double x);
double  quadratic_root_plus(double a, double b, double c);
u64     math_is_square(u64 x);
u64     math_is_triangular(u64 n);
u64     math_factorial(u64 n);
u64     math_gcd(u64 x, u64 y);
u64     math_lcm(u64 x, u64 y);
u64     math_pow(u64 base, u64 exp);
u64     math_n_choose_k(u64 n, u64 k);
Vec     math_divisors(u64 x);
Vec     math_divisors_proper(u64 x);
Vec     math_divisors_sorted(u64 x);
Vec     math_prime_divisors(u64 x);
u64     math_prime_divisor_power(u64 x, u64 p);
Vec     math_prime_divisor_pairs(u64 x);

double  math_sqrt(double a);

#endif