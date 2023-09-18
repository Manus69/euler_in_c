#include "euler.h"

#define N 1000
static u64  n_sln_p[N];
static bool used[N][N][N];

static void _check_multiples(u64 a, u64 b, u64 c)
{
    u64 p;

    for (u64 x = 2; ; x ++)
    {
        p = x * a + x * b + x * c;
        if (p >= N) break;
        if (! used[x * a][x * b][x * c])
        {
            n_sln_p[p] ++;
            used[x * a][x * b][x * c] = true;
        }
    }
}

void p_39(void)
{
    u64     a, b, c;
    u64     p;
    View    view;

    for (u64 n = 1; n < N; n ++)
    {
        for (u64 m = n + 1; m < N; m ++)
        {
            a = m * m - n * n;
            b = 2 * m * n;
            c = m * m + n * n;
            p = a + b + c;

            if (p >= N) break;
            used[a][b][c] = true;
            n_sln_p[p] ++;
            _check_multiples(a, b, c);
        }
    }

    view = View_init(n_sln_p, sizeof(u64), N);
    i64_dbg(View_max_idx(view, u64_cmpf));
}