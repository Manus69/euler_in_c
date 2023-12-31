#ifndef BIGINT_H
#define BIGINT_H

#include "Str.h"

typedef struct Bigu Bigu;

struct Bigu
{
    u64 *   digits;
    i64     len;
    i64     capacity;
};

Putf_gen(Bigu)
Swapf_gen(Bigu)

Bigu    Bigu_new(u64 x);
Bigu    Bigu_dup(Bigu bigu);
void    Bigu_del(Bigu * bigu);
i64     Bigu_cmp(Bigu lhs, Bigu rhs);
i64     Bigu_cmpf(const void * lhs, const void * rhs);
u64     Bigu_hash(Bigu bigu);
u64     Bigu_hashf(const void * bigu);
i64     Bigu_n_decimal_digits(Bigu bigu);
Bigu    Bigu_mult(Bigu lhs, Bigu rhs);
Bigu    Bigu_pow(Bigu base, u64 pow);
Bigu    Bigu_pow_u64(u64 base, u64 pow);
Bigu    Bigu_factorial(u64 n);
void    Bigu_plus_u64(Bigu * lhs, u64 rhs);
void    Bigu_plus(Bigu * lhs, Bigu rhs);
Bigu    Bigu_add(Bigu lhs, Bigu rhs);
void    Bigu_scale(Bigu * lhs, u64 rhs);
Bigu    Bigu_from_cstr_len(const byte * cstr, i64 len);
Bigu    Bigu_from_cstr(const byte * cstr);
Bigu    Bigu_from_StrSlc(StrSlc slc);
Bigu    Bigu_from_StrSlc_ptr(const StrSlc * slc);
Str     Bigu_to_Str(Bigu bigu);
void    Bigu_dbg(Bigu bigu);
void    Bigu_dbgf(const void * bigu);

#endif