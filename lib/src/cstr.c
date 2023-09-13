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

void cstr_rev_len(byte * cstr, i64 len)
{
    for (i64 k = 0; k < len / 2; k ++)
    {
        swap_ptr(cstr + k, cstr + len - k - 1, byte);
    }
}

void cstr_rev(byte * cstr)
{
    return cstr_rev_len(cstr, strlen(cstr));
}

void cstr_sort_insert(byte * cstr, i64 len)
{
    byte    buffer;
    i64     current;

    for (i64 sorted = 1; sorted < len; sorted ++)
    {
        buffer = cstr[sorted];
        for (current = sorted - 1; current >= 0; current --)
        {
            if (buffer >= cstr[current]) break;
            cstr[current + 1] = cstr[current];
        }

        current ++;
        cstr[current] = buffer;
    }
}

static i64 _find_first_greater(const byte * cstr, i64 len, byte x)
{
    for (i64 k = len - 1; k >= 0; k --)
    {
        if (cstr[k] > x) return k;
    }

    return NO_IDX;
}

STATUS cstr_next_perm_len(byte * cstr, i64 len)
{
    STATUS  status;
    i64     idx;

    if (len < 2) return STATUS_OK;
    if (len == 2 && cstr[0] >= cstr[1]) return STATUS_OK;
    if (len == 2)
    {
        swap_ptr(cstr, cstr + 1, byte);
        return STATUS_NOT_OK;
    }

    status = cstr_next_perm_len(cstr + 1, len - 1);
    if (status == STATUS_OK)
    {
        if (cstr[0] >= cstr[1]) return STATUS_OK;
        if ((idx = _find_first_greater(cstr + 1, len - 1, cstr[0])) == NO_IDX) return STATUS_OK;

        swap_ptr(cstr, cstr + idx + 1, byte);
        // cstr_sort_insert(cstr + 1, len - 1);
        cstr_rev_len(cstr + 1, len - 1);

        return STATUS_NOT_OK;
    }

    return status;
}

STATUS cstr_next_perm(byte * cstr)
{
    return cstr_next_perm_len(cstr, strlen(cstr));
}