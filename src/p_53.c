#include "euler.h"

#define N   101
#define CAP 1000000

static i64 pt[N][N];

static void _fill(void)
{
    i64 top, top_left;

    pt[0][0] = 1;

    for (i64 row = 1; row < N; row ++)
    {
        pt[row][0] = 1;
        for (i64 col = 1; col <= row; col ++)
        {
            top = pt[row - 1][col];
            top_left = pt[row - 1][col - 1];

            if (top == NO_IDX || top_left == NO_IDX) pt[row][col] = NO_IDX;
            else
            {
                pt[row][col] = top + top_left > CAP ? NO_IDX : top + top_left;
            }
        }
    }
}

static inline i64 _count(void)
{
    i64 count;

    count = 0;
    for (i64 k = 0; k < N; k ++)
    {
        for (i64 w = 0; w < N; w ++)
        {
            count += pt[k][w] == NO_IDX;
        }
    }

    return count;
}

void p_53(void)
{
    _fill();
    i64_dbg(_count());
}