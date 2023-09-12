#include "euler.h"

#define FILE "./src/p_22.txt"

u64 _score(StrSlc slc)
{
    u64     sum;
    byte    x;

    sum = 0;
    for (i64 k = 0; k < StrSlc_len(slc); k ++)
    {
        if ((x = deref(byte) StrSlc_get(slc, k)) == '"') continue;
        sum += x - 'A' + 1;
    }

    return sum;
}

u64 _score_ptr(const void * slc)
{
    return _score(deref(StrSlc) slc);
}

u64 _sum_scores(Vec vec)
{
    u64 sum;

    sum = 0;
    for (i64 k = 0; k < Vec_len(vec); k ++)
    {
        sum += _score_ptr(Vec_get(vec, k)) * (k + 1);
    }

    return sum;
}

void p_22(void)
{
    Str str;
    Vec slices;
    u64 sum;

    str = io_read_file(FILE);
    slices = Str_split_slices(str, ',');
    sort_quick(Vec_to_view(slices), StrSlc);
    sum = _sum_scores(slices);

    u64_dbg(sum);

    Vec_del(& slices);
    Str_del(& str);
}