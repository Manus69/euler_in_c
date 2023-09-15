#include "euler.h"
#include <string.h>

#define N 1000

static bool digits[N];

static void _to0()
{
    memset(digits, 0, N * sizeof(bool));
}

static u64 _detect_cycle(u64 len, u64 top, u64 bot)
{
    u64 digit;

    if (top == 0) return 0;
    if (digits[top]) return len;

    digits[top] = true;

    digit = (10 * top) % bot;
    
    return _detect_cycle(len + 1, digit, bot);
}

void p_26(void)
{
    u64 cycle;
    u64 max;
    i64 max_idx;

    max_idx = -1;
    max = 0;
    for (i64 k = 2; k < N; k ++)
    {
        _to0();
        cycle = _detect_cycle(0, 1, k);
        if (max < cycle)
        {
            max = cycle;
            max_idx = k;
        }
    }

    i64_dbg(max_idx);
}