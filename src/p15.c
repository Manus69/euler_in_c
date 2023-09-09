#include "euler.h"

#define N 20

static u64 tbl[N + 1][N + 1];

u64 _compute_paths(u64 row, u64 col)
{
    u64 paths;

    if (col == N) return 1;
    if (row == N) return 1;

    if (tbl[row][col]) return tbl[row][col];

    paths = _compute_paths(row + 1, col) + _compute_paths(row, col + 1);
    tbl[row][col] = paths;

    return paths;
}

void p_15(void)
{
    u64_dbg(_compute_paths(0, 0));
}