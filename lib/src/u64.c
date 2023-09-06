#include "u64.h"
#include "byte.h"
#include <string.h>
#include <stdio.h>

i64 u64_cmp(u64 lhs, u64 rhs)
{
    return lhs < rhs ? -1 : lhs > rhs;
}

i64 u64_cmpf(const void * lhs, const void * rhs)
{
    return u64_cmp(deref(u64) lhs, deref(u64) rhs);
}

u64 u64_parse_cstr_len(const byte * cstr, i64 len)
{
    u64 result;

    if (len == 0) return 0;
    if (* cstr == '0') return 0;

    result = 0;
    for (i64 k = 0; k < len; k ++)
    {
        if (! byte_is_numeric(cstr[k])) return 0;
        result *= 10;
        result += cstr[k] - '0';
    }

    return result;
}

u64 u64_parse_cstr(const byte * cstr)
{
    return u64_parse_cstr_len(cstr, strlen(cstr));
}

void u64_dbg(u64 x)
{
    printf("%zu ", x);
}

void u64_dbgf(const void * x)
{
    u64_dbg(deref(u64) x);
}