#include "Slc.h"
#include "macro.h"

Slc Slc_init(void * ptr, i64 size)
{
    return (Slc)
    {
        .ptr = ptr,
        .size = size,
    };
}

i64 Slc_size(Slc slc)
{
    return slc.size;
}

bool Slc_empty(Slc slc)
{
    return slc.size == 0;
}

void * Slc_ptr(Slc slc)
{
    return slc.ptr;
}

void * Slc_get(Slc slc, i64 idx)
{
    return slc.ptr + idx;
}

Slc Slc_slice(Slc slc, i64 idx, i64 size)
{
    return Slc_init(slc.ptr + idx, size);
}

Slc Slc_from_Slc(Slc slc)
{
    return Slc_slice(slc, 0, slc.size);
}

void Slc_shift(Slc * slc, i64 size)
{
    slc->ptr += size;
    slc->size -= size;
}

Slc Slc_chop_left(Slc * slc, i64 size)
{
    Slc chop;

    chop = Slc_slice(* slc, 0, size);
    Slc_shift(slc, size);

    return chop;
}

Slc Slc_chop_all(Slc * slc)
{
    return Slc_chop_left(slc, slc->size);
}

Slc Slc_chop_left_check(Slc * slc, i64 size)
{
    return size < slc->size ? Slc_chop_left(slc, size) : Slc_chop_all(slc);
}

Slc Slc_chop_left_check_likely(Slc * slc, i64 size)
{
    if (likely(size < slc->size)) return Slc_chop_left(slc, size);

    return Slc_chop_all(slc);
}