#ifndef BIGINT_H
#define BIGINT_H

#include "Deck.h"

typedef struct Bigu Bigu;

struct Bigu
{
    u64 *   digits;
    i64     len;
    i64     capacity;
};

Bigu Bigu_new(u64 x);
Bigu Bigu_dup(Bigu bigu);
Bigu Bigu_from_cstr(const byte * cstr);
void Bigu_del(Bigu * bigu);
i64 Bigu_cmp(Bigu lhs, Bigu rhs);
Bigu Bigu_mult(Bigu lhs, Bigu rhs);
void Bigu_plus_u64(Bigu * lhs, u64 rhs);
void Bigu_plus(Bigu * lhs, Bigu rhs);
Bigu Bigu_add(Bigu lhs, Bigu rhs);
void Bigu_scale(Bigu * lhs, u64 rhs);
void Bigu_dbg(Bigu bigu);

#endif