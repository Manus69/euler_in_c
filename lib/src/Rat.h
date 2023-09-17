#ifndef RAT_H
#define RAT_H

#include "def.h"

typedef struct Rat Rat;

struct Rat
{
    i64 top;
    u64 bot;
};

Swap_gen(Rat)
Put_gen(Rat)

Rat     Rat_init(i64 top, u64 bot);
Rat     Rat_one(void);
Rat     Rat_zero(void);
bool    Rat_eq(Rat lhs, Rat rhs);
i64     Rat_cmp(Rat lhs, Rat rhs);
i64     Rat_cmpf(const void * lhs, const void * rhs);
Rat     Rat_add(Rat lhs, Rat rhs);
Rat     Rat_mult(Rat lhs, Rat rhs);
Rat     Rat_inv(Rat rat);
Rat     Rat_scale(Rat rat, i64 x);
Rat     Rat_subt(Rat lhs, Rat rhs);
Rat     Rat_pow(Rat rat, u64 exp);
double  Rat_as_decimal(Rat rat);
void    Rat_addf(void * lhs, const void * rhs);
void    Rat_multf(void * lhs, const void * rhs);
void    Rat_dbg(Rat rat);
void    Rat_dbgf(const void * rat);

#endif