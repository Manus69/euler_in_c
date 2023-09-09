#include "euler.h"

#define N 1000000

static u64 * chain_tbl;

static inline u64 _next(u64 x)
{
    return x % 2 ? 3 * x + 1 : x / 2;
}

static u64 _compute_chain(u64 x)
{
    u64 len;

    if (x < N && chain_tbl[x]) return chain_tbl[x];

    len = 1 + _compute_chain(_next(x));
    
    if (x < N) chain_tbl[x] = len;

    return len;
}

void p_14(void)
{
    u64 max;
    u64 n;
    u64 current;

    chain_tbl = mem_alloc0(N * sizeof(u64));
    chain_tbl[1] = 1;
    chain_tbl[2] = 2;

    n = 0;
    max = 0;
    for (i64 k = 1; k < N; k ++)
    {
        current = _compute_chain(k);
        if (current > max)
        {
            max = current;
            n = k;
        }
    }

    u64_dbg(n);
}