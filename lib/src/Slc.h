#ifndef SLC_H
#define SLC_H

#include "def.h"
#include "macro.h"

typedef struct Slc Slc;

struct Slc
{
    void *  ptr;
    i64     size;
};

Putf_gen(Slc)
Swapf_gen(Slc)

Slc     Slc_init(void * ptr, i64 size);
i64     Slc_size(Slc slc);
bool    Slc_empty(Slc slc);
void *  Slc_get(Slc slc, i64 idx);
void *  Slc_first(Slc slc);
void    Slc_shift(Slc * slc, i64 shift);
Slc     Slc_slice(Slc slc, i64 idx, i64 size);
Slc     Slc_slice_from(Slc slc, i64 idx);
Slc     Slc_copy(Slc slc);
Slc     Slc_chop_front(Slc * slc, i64 size);
Slc     Slc_chop_all(Slc * slc);
Slc     Slc_chop_front_check(Slc * slc, i64 size);
Slc     Slc_chop_front_check_likely(Slc * slc, i64 size);

#endif