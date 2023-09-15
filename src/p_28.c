#include "euler.h"

#define N 1001

static u64 _corner_sum(u64 k)
{
    return 16 * k * k + 4 * k + 4;
}

void p_28(void)
{
    u64 sum;
    u64 max_idx;

    max_idx = (N - 1) / 2;
    sum = 0;

    for (u64 k = 1; k <= max_idx; k ++)
    {
        sum += _corner_sum(k);
    }

    sum ++;
    u64_dbg(sum);
}