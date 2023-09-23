#include "euler.h"

#define N 1000000

static u64 _product(Str str)
{
    u64 x;

    x = 1;
    for (i64 k = 1; k <= N; k *= 10)
    {
        x *= (deref(byte) Str_get(str, k - 1)) - '0';
    }

    return x;
}

void p_40(void)
{
    Str str;
    Str current;

    str = Str_new_capacity(N);
    for (u64 x = 1; ; x ++)
    {
        current = u64_to_Str(x);
        Str_append_Str(& str, current);
        Str_del(& current);

        if (Str_len(str) > N) break;
    }

    u64_dbg(_product(str));
    Str_del(& str);
}