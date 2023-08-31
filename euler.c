#include "./lib/libEuler.h"

#include <stdio.h>

//word trim

int main()
{
    Vec v = Vec_new(i64);
    i64 n = 1 << 25;
    Vec_reserve(& v, n);
    for (i64 k = 0; k < n; k ++)
    {
        Vec_push(& v, n - k, i64);
    }

    // dbg_Vec(& v, (F) dbg_i64);
    n = deref(i64) Vec_last(v);
    dbg_i64(& n);
    Vec_del(& v);
}