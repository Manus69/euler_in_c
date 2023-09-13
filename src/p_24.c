#include "euler.h"

#define N 1000000

void p_24(void)
{
    Str str;

    str = Str_from_cstr("0123456789");
    for (i64 k = 0; k < N - 1; k ++)
    {
        Str_next_perm(str);
    }

    Str_dbg(str);
    Str_del(& str);
}