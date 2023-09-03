#ifndef I64_H
#define I64_H

#include "def.h"
#include "macro.h"

Putf_gen(i64)
Put_gen(i64)
Swapf_gen(i64)
Swap_gen(i64)
Cmpf_gen(i64)

void i64_dbg(i64 x);
void i64_dbgf(const void * ptr);

#endif