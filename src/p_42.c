#include "euler.h"

#define FILE "./src/p_42_words.txt"

static u64 _to_number(StrSlc slc)
{
    u64 x;

    x = 0;
    for (i64 k = 1; k < StrSlc_len(slc) - 1; k ++)
    {
        x += (deref(byte) StrSlc_get(slc, k)) - 'A' + 1;
    }

    return x;
}

static bool _is_triangular(const StrSlc * slc)
{
    u64 x;

    x = _to_number(* slc);

    return math_is_triangular(x);
}

void p_42(void)
{
    Str str;
    Vec slices;
    u64 total;

    str = io_read_file(FILE);
    slices = Str_split_slices(str, ',');
    total = 0;

    for (i64 k = 0; k < Vec_len(slices); k ++)
    {
        total += _is_triangular(Vec_get(slices, k));
    }

    u64_dbg(total);
    
    Vec_del(& slices);
    Str_del(& str);
}