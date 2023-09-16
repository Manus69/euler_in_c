#include "u8.h"
#include <stdio.h>

i64 u8_cmp(u8 lhs, u8 rhs)
{
    return lhs < rhs ? -1 : lhs > rhs;
}

i64 u8_cmpf(const void * lhs, const void * rhs)
{
    return u8_cmp(deref(u8) lhs, deref(u8) rhs);
}

void u8_to_bin_buff_le(byte * buff, u8 x)
{
    const byte * digits = "01";

    for (u64 k = 0; k < __CHAR_BIT__; k ++)
    {
        buff[k] = digits[x & 1];
        x >>= 1;
    }
}

void u8_dbg(u8 x)
{
    printf("%u ", x);
}

void u8_dbgf(const void * x)
{
    return u8_dbg(deref(u8) x);
}