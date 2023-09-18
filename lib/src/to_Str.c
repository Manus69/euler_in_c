#include "to_Str.h"
#include "cstr.h"
#include <stdio.h>

Str u64_to_Str(u64 x)
{
    byte    buff[1 << 5] = {};
    i64     len;

    len = sprintf(buff, "%zu", x);

    return Str_from_cstr_len(buff, len);
}

Str u64_to_Str_bin(u64 x)
{
    byte        buff[1 << 6] = {};
    const byte  digits[] = {'0', '1'};
    i64         idx;
    
    idx = 0;
    do
    {
        buff[idx ++] = digits[x & 1];
        x >>= 1;
    }
    while (x);

    cstr_rev_len(buff, idx);
    
    return Str_from_cstr_len(buff, idx);
}