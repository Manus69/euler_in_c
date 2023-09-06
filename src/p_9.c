#include "euler.h"

bool _is_triplet(u64 a, u64 b, u64 c)
{
    return a * a + b * b == c * c;
}

#define N 1000
void p_9(void)
{
    i64 c;

    c = 0;
    for (i64 a = 1; a < N; a ++)
    {
        for (i64 b = a; b < N; b ++)
        {
            c = N - a - b;
            if ((c > 0) && _is_triplet(a, b, c))
            {
                return i64_dbg(a * b * c);
            }
        }
    }
}