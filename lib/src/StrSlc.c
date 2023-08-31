#include "Str.h"
#include "Slc.h"
#include "cstr.h"

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