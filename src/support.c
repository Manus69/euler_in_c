#include "euler.h"
#include <string.h>

u64 sum_digits_len(const byte * cstr, i64 len)
{
    u64 sum;

    sum = 0;
    for (i64 k = 0; k < len; k ++) sum += cstr[k] - '0';

    return sum;
}

u64 sum_digits(const byte * cstr)
{
    return sum_digits_len(cstr, strlen(cstr));
}