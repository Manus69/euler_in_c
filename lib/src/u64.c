#include "u64.h"
#include "byte.h"
#include <string.h>
#include <stdio.h>

i64 u64_parse_cstr_len(const byte * cstr, i64 len)
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

i64 u64_parse_cstr(const byte * cstr)
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