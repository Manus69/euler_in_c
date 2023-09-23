#include "euler.h"

#define N 1000000

static u64 numbers[N];

static void _init(i64 n)
{
    for (i64 k = 1; k < n; k ++)
    {
        numbers[k] = (k * (3 * k - 1)) / 2;
    }
}

void p_44(void)
{
    _init(N);

    u64_dbg(numbers[8 - 1]);
}