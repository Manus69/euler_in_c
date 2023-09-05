#include "euler.h"

#define N 4000000

void p_2(void)
{
    u64 f0, f1, sum;

    f0 = 1;
    f1 = 2;
    sum = 0;

    while (f0 < N)
    {
        sum += (f0 % 2 == 0) * f0;
        f1 += f0;
        f0 = f1 - f0;
    }

    u64_dbg(sum);
}