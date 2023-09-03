#include "test.h"

#define TXT_FILE "../txt.txt"

void _i64_test(i64 n)
{
    Vec v = Vec_new(i64);
    for (i64 k = 0; k < n; k ++)
    {
        Vec_push(& v, n - k, i64);
    }

    sort_quick(Vec_to_view(v), i64);
    // sort_quick_f(Vec_to_view(v), (Putf) i64_put, (Swapf) i64_swap, (Cmpf) _test_cmp);
    // Vec_map(& v, (F) i64_dbgf);
    i64_dbgf(Vec_last(v));  

    Vec_del(& v);
}

void _Str_test()
{
    Str s = io_read_file(TXT_FILE);
    Vec v = Str_split_slices(s, '\n');

    sort_quick(Vec_to_view(v), StrSlc);
    // Vec_map(& v, (F) StrSlc_dbg);
    StrSlc_dbgf(Vec_last(v));
    
    Str_del(& s);
    Vec_del(& v);
}