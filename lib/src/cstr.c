#include "def.h"

#include <string.h>

i64 cstr_findc_len(const byte * cstr, i64 len, byte x)
{
    for (i64 k = 0; k < len; k ++)
    {
        if (cstr[k] == x) return k;
    }

    return NO_IDX;
}

i64 cstr_findc(const byte * cstr, byte x)
{
    return cstr_findc_len(cstr, strlen(cstr), x);
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