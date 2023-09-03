#include "Str.h"
#include "cstr.h"
#include <string.h>
#include <stdio.h>

i64 StrSlc_cmp(StrSlc lhs, StrSlc rhs)
{
    return cstr_cmp_len(lhs.cstr, lhs.len, rhs.cstr, rhs.len);
}

i64 StrSlc_cmpf(const void * lhs, const void * rhs)
{
    return StrSlc_cmp(deref(StrSlc) lhs, deref(StrSlc) rhs);
}

StrSlc StrSlc_from_cstr_len(const byte * cstr, i64 len)
{
    return (StrSlc)
    {
        .cstr = cstr,
        .len = len,
    };
}

StrSlc StrSlc_from_cstr(const byte * cstr)
{
    return StrSlc_from_cstr_len(cstr, strlen(cstr));
}

const char * StrSlc_get(StrSlc slc, i64 idx)
{
    return slc.cstr + idx;
}

const char * StrSlc_first(StrSlc slc)
{
    return slc.cstr;
}

i64 StrSlc_len(StrSlc slc)
{
    return slc.len;
}

bool StrSlc_empty(StrSlc slc)
{
    return slc.len == 0;
}

void StrSlc_shift(StrSlc * slc, i64 shift)
{
    slc->cstr += shift;
    slc->len -= shift;
}

StrSlc StrSlc_slice(StrSlc slc, i64 idx, i64 len)
{
    return StrSlc_from_cstr_len(slc.cstr + idx, len);
}

StrSlc StrSlc_copy(StrSlc slc)
{
    return StrSlc_from_cstr_len(slc.cstr, slc.len);
}

StrSlc StrSlc_chop_front(StrSlc * slc, i64 len)
{
    StrSlc chop;

    chop = StrSlc_slice(* slc, 0, len);
    StrSlc_shift(slc, len);

    return chop;
}

StrSlc StrSlc_chop_all(StrSlc * slc)
{
    StrSlc chop;

    chop = StrSlc_copy(* slc);
    StrSlc_shift(slc, slc->len);

    return chop;
}

StrSlc StrSlc_chop_front_check(StrSlc * slc, i64 len)
{
    return len < slc->len ? StrSlc_chop_front(slc, len) : StrSlc_chop_all(slc);
}

i64 StrSlc_find_c(StrSlc slc, byte x)
{
    return cstr_find_c_len(slc.cstr, slc.len, x);
}

StrSlc StrSlc_split_next(StrSlc * slc, byte x)
{
    i64     idx;
    StrSlc  chop;

    if ((idx = StrSlc_find_c(* slc, x)) == NO_IDX) return StrSlc_chop_all(slc);

    chop = StrSlc_chop_front(slc, idx);
    StrSlc_shift(slc, 1);

    return chop;
}

Vec StrSlc_split(StrSlc slc, byte x)
{
    Vec     vec;

    vec = Vec_new(StrSlc);

    while (! StrSlc_empty(slc))
    {
        Vec_push(& vec, StrSlc_split_next(& slc, x), StrSlc);
    }

    return vec;
}

void StrSlc_dbg(StrSlc slc)
{
    printf("%.*s ", (int) StrSlc_len(slc), slc.cstr);
}

void StrSlc_dbgf(const void * slc)
{
    StrSlc_dbg(deref(StrSlc) slc);
}
