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