#include "./lib/libEuler.h"

#include <stdio.h>

#define TXT_FILE    "txt.txt"
#define TEST_FILE   "./lib/src/sort_test.c"

i64 i64_cmp(const i64 * lhs, const i64 * rhs)
{
    return * lhs - * rhs;
}

Putf_gen(i64)
Swapf_gen(i64)

//word trim
//header gen
//code align
//regex

int main()
{
    i64 n = 1 << 25;
    Vec v = Vec_new(i64);

    for (i64 k = 0; k < n; k ++)
    {
        Vec_push(& v, n - k, i64);
    }

    sort_quick(Vec_to_View(v), i64);
    // dbg_Vec(& v, (F) dbg_i64);
    n = deref(i64) Vec_last(v);
    dbg_i64(& n);
    
    Vec_del(& v);
}