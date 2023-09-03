#include "def.h"
#include "math.h"
#include <string.h>

i64 cstr_cmp_len(const byte * lhs, i64 lhs_len, const byte * rhs, i64 rhs_len)
{
    i64 len;

    len = min(lhs_len, rhs_len);
    for (i64 k = 0; k < len; k ++)
    {
        if (lhs[k] != rhs[k]) return lhs[k] - rhs[k];
    }

    return rhs_len > lhs_len ? -1 : lhs_len > rhs_len;
}

i64 cstr_cmp(const byte * lhs, const byte * rhs)
{
    return strcmp(lhs, rhs);
}

i64 cstr_find_c_len(const byte * cstr, i64 len, byte x)
{
    for (i64 k = 0; k < len; k ++)
    {
        if (cstr[k] == x) return k;
    }

    return NO_IDX;
}

i64 cstr_find_c(const byte * cstr, byte x)
{
    return cstr_find_c_len(cstr, strlen(cstr), x);
}

i64 cstr_find_cstr_len(const byte * haystack, i64 h_len, const byte * needle, i64 n_len)
{
    for (i64 k = 0; k < h_len; k ++)
    {
        for (i64 w = 0; w < n_len; w ++)
        {
            if (haystack[k + w] != needle[w]) break;
            if (w + 1 == n_len) return k;
        }
    }

    return NO_IDX;
}