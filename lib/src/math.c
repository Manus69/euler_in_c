#include "math.h"

u64 math_log2(u64 x)
{
    return sizeof(x) * __CHAR_BIT__ - __builtin_clzl(x) - 1; 
}

u64 math_arith_prog_sum(u64 n)
{
    return ((n + 1) * n) / 2;
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

    vec = Vec_new(u64);
    for (u64 k = 1; k * k <= x; k ++)
    {
        if (x % k == 0) Vec_push(& vec, k, u64);
    }

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
