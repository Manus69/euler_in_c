#ifndef SLC_H
#define SLC_H

#include "def.h"

typedef struct Slc Slc;

struct Slc
{
    void *  ptr;
    i64     size;
};

Slc     Slc_init(void * ptr, i64 size);
Slc     Slc_chop_left(Slc * slc, i64 size);
Slc     Slc_chop_all(Slc * slc);
Slc     Slc_chop_left_check(Slc * slc, i64 size);
Slc     Slc_chop_left_check_likely(Slc * slc, i64 size);
Slc     Slc_slice(Slc slc, i64 idx, i64 size);
Slc     Slc_from_Slc(Slc slc);
i64     Slc_size(Slc slc);
void *  Slc_ptr(Slc slc);
void *  Slc_get(Slc slc, i64 idx);
void    Slc_shift(Slc * slc, i64 size);
bool    Slc_empty(Slc slc);

Putf_gen(Slc)

#endif