#include "Slc.h"

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

void * Slc_get(Slc slc, i64 idx)
{
    return slc.ptr + idx;
}

void * Slc_first(Slc slc)
{
    return slc.ptr;
}

void Slc_shift(Slc * slc, i64 shift)
{
    slc->ptr += shift;
    slc->size -= shift;
}

Slc Slc_slice(Slc slc, i64 idx, i64 size)
{
    return Slc_init(Slc_get(slc, idx), size);
}

Slc Slc_slice_from(Slc slc, i64 idx)
{
    return Slc_slice(slc, idx, slc.size - idx);
}

Slc Slc_copy(Slc slc)
{
    return Slc_init(slc.ptr, slc.size);
}

Slc Slc_chop_front(Slc * slc, i64 size)
{
    Slc chop;

    chop = Slc_init(slc->ptr, size);
    Slc_shift(slc, size);

    return chop;
}

Slc Slc_chop_all(Slc * slc)
{
    Slc chop;

    chop = Slc_copy(* slc);
    Slc_shift(slc, slc->size);

    return chop;
}

Slc Slc_chop_front_check(Slc * slc, i64 size)
{
    return size < slc->size ? Slc_chop_front(slc, size) : Slc_chop_all(slc);
}

Slc Slc_chop_front_check_likely(Slc * slc, i64 size)
{
    if (likely(slc->size < size)) return Slc_chop_front(slc, size);

    return Slc_chop_all(slc);
}