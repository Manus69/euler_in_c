#include "math.h"
#include "sort.h"
#include "u64.h"
#include <math.h>

#define LOG10_2 0.301
#define EPS     1e-10

u64 math_log2(u64 x)
{
    return sizeof(x) * __CHAR_BIT__ - __builtin_clzl(x) - 1; 
}

u64 math_log10(u64 x)
{
    u64 log;

    log = 0;
    while (x >= 10)
    {
        log ++;
        x /= 10;
    }

    return log;
}

u64 math_arith_prog_sum(u64 n)
{
    return ((n + 1) * n) / 2;
}

bool math_is_nat(double x)
{
    double diff;

    diff = double_abs(x - (u64) x);

    return diff < EPS;
}

u64 math_is_square(u64 x)
{
    double root;

    root = math_sqrt(x);
    if (math_is_nat(root)) return (u64) root;

    return 0;
}

u64 math_is_triangular(u64 n)
{
    double root;

    root = math_sqrt(1 + 8 * n);
    if (math_is_nat(root)) return (-1 + (u64) root) / 2;

    return 0;
}

u64 math_factorial(u64 n)
{
    u64 nf;

    nf = 1;
    for (u64 k = 2; k <= n; k ++) nf *= k;

    return nf;
}

u64 math_gcd(u64 x, u64 y)
{
    while (x)
    {
        if (x < y) swap_ptr(& x, & y, u64);
        x = x % y;
    }

    return y;
}

u64 math_lcm(u64 x, u64 y)
{
    return x * y / math_gcd(x, y); 
}

u64 math_pow(u64 base, u64 exp)
{
    u64 partial;

    if (exp == 0) return 1;
    if (exp == 1) return base;
    
    if (exp % 2 == 0)
    {
        partial = math_pow(base, exp / 2);
        return partial * partial;
    }
    
    return base * math_pow(base, exp - 1);
}

Vec math_divisors(u64 x)
{
    Vec vec;
    u64 k;

    vec = Vec_new(u64);
    Vec_push(& vec, 1, u64);

    if (x == 1) return vec;

    for (k = 2; k * k < x; k ++)
    {
        if (x % k == 0)
        {
            Vec_push(& vec, k, u64);
            Vec_push(& vec, x / k, u64);
        }
    }

    if (k * k == x) Vec_push(& vec, k, u64);

    Vec_push(& vec, x, u64);

    return vec;
}

Vec math_divisors_proper(u64 x)
{
    Vec divisors;

    divisors = math_divisors(x);
    Vec_pop(& divisors);

    return divisors;
}

Vec math_divisors_sorted(u64 x)
{
    Vec vec;

    vec = math_divisors(x);
    sort_quick(Vec_to_view(vec), u64);

    return vec;
}

Vec math_prime_divisors(u64 x)
{
    Vec vec;

    vec = Vec_new(u64);
    for (u64 p = 2; p <= x; p ++)
    {
        while (x % p == 0)
        {
            Vec_push(& vec, p, u64);
            x /= p;
        }
    }

    return vec;
}

u64 math_prime_divisor_power(u64 x, u64 p)
{
    u64 power;

    power = 0;
    while (x % p == 0)
    {
        power ++;
        x /= p;
    }

    return power;
}

Pair_struct_gen(u64, u64)

Vec math_prime_divisor_pairs(u64 x)
{
    Vec             vec;
    Pair_u64_u64    pair;
    u64             power;

    vec = Vec_new(Pair_u64_u64);
    for (u64 p = 2; p <= x; p ++)
    {
        power = 0;
        while (x % p == 0)
        {
            power ++;
            x /= p;
        }

        if (power)
        {
            pair = (Pair_u64_u64) {p, power};
            Vec_push(& vec, pair, Pair_u64_u64);
        }
    }

    return vec;
}

u64 math_n_choose_k(u64 n, u64 k)
{
    u64 nk;

    if (unlikely(n < k)) return 0;

    nk = 1;
    for (u64 w = n; w > n - k; w --) nk *= w;

    return nk;
}

double quadratic_root_plus(double a, double b, double c)
{
    double d;

    if ((d = b * b - 4 * a * c) < 0) return NAN;
    
    return (- b + math_sqrt(d)) / (2 * a);
}
