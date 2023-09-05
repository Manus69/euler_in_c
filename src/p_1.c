#include "euler.h"

#define N 1000

void p_1(void)
{
    i64 sum;

    sum = 0;
    for (i64 k = 1; k < N; k ++)
    {
        sum += ((k % 3 == 0) || (k % 5 == 0)) * k;
    }

    i64_dbg(sum);
}