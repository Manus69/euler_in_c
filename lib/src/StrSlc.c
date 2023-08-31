#include "Str.h"
#include "Slc.h"
#include "cstr.h"

#include <string.h>

i64 Slc_cmp(const Slc * lhs, const Slc * rhs)
{
    return cstr_cmp_len(lhs->ptr, lhs->size, rhs->ptr, rhs->size);
}

Slc Slc_from_cstr_len(byte * cstr, i64 len)
{
    return Slc_init(cstr, len);
}

Slc Slc_from_cstr(byte * cstr)
{
    return Slc_from_cstr_len(cstr, strlen(cstr));
}

i64 Slc_find_byte(Slc slc, byte x)
{
    return cstr_findc_len(slc.ptr, slc.size, x);
}

i64 Slc_find_cstr_len(Slc slc, const byte * cstr, i64 len)
{
    return cstr_find_cstr_len(slc.ptr, slc.size, cstr, len);
}

Slc Slc_chop_next(Slc * slc, byte x)
{
    i64 idx;
    Slc chop;

    if ((idx = Slc_find_byte(* slc, x)) == NO_IDX) return Slc_chop_all(slc);

    chop = Slc_chop_left(slc, idx);
    Slc_shift(slc, 1);

    return chop;
}

Vec Slc_split(Slc slc, byte x)
{
    Slc current;
    Vec vec;

    vec = Vec_new(Slc);
    while (Slc_empty(slc) == false)
    {
        current = Slc_chop_next(& slc, x);
        Vec_push(& vec, current, Slc);
    }

    return vec;
}