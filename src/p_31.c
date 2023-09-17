#include "euler.h"

#define N   8
#define MAX 200

static i64 coins[N] = {1, 2, 5, 10, 20, 50, 100, 200};
static i64 tbl[MAX + 1][N + 1];

static i64 _n_ways(i64 val, i64 n_coins)
{
    i64 lhs;
    i64 rhs;

    if (val < 0) return 0;
    if (n_coins == 0) return val == 0;

    if (tbl[val][n_coins]) return tbl[val][n_coins];

    lhs = _n_ways(val, n_coins - 1);
    rhs = _n_ways(val - coins[n_coins - 1], n_coins);

    tbl[val][n_coins] = lhs + rhs;
    
    return lhs + rhs;
}

void p_31(void)
{
    i64_dbg(_n_ways(MAX, N));
}