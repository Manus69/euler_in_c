#ifndef U8_H
#define U8_H

#include "def.h"
#include "macro.h"

Putf_gen(u8)
Swapf_gen(u8)

i64     u8_cmp(u8 lhs, u8 rhs);
i64     u8_cmpf(const void * lhs, const void * rhs);
void    u8_to_bin_buff_le(byte * buff, u8 x);
void    u8_dbg(u8 x);
void    u8_dbgf(const void * x);

#endif