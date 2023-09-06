#include "euler.h"

#define N 500
void p_12(void)
{
    Vec divisors;
    u64 n;

    for (u64 x = 1; ; x ++)
    {
        n = math_arith_prog_sum(x);
        divisors = math_divisors(n);

        // Vec_map(divisors, (F) u64_dbgf);
        // nl;
    
        if (Vec_len(divisors) > N) break;
        Vec_del(& divisors);
    }

    Vec_del(& divisors);
    u64_dbg(n);
}