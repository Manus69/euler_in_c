#include "euler.h"

#define INITIAL "1023456789"

static u64 divisors[] = {17, 13, 11, 7, 5, 3, 2};

static bool _triplet_divisibility(const byte * cstr, u64 n)
{
    u64 x;

    if (* cstr == '0') x = u64_parse_cstr_len(cstr + 1, 2);
    else x = u64_parse_cstr_len(cstr, 3);

    return x % n == 0;
}

static bool _check_divisibilty(const byte * cstr)
{
    u64 divisor;
    i64 idx;

    idx = 0;
    for (i64 k = 7; k > 0; k --)
    {
        divisor = divisors[idx ++];
        if (! _triplet_divisibility(cstr, divisor)) return false;
        cstr ++;
    }

    return true;
}

void p_43(void)
{
    Str str;
    u64 sum;
    
    str = Str_from_cstr(INITIAL);
    sum = 0;

    while (Str_next_perm(str) != STATUS_DONE)
    {
        if (_check_divisibilty(Str_first(str)))
        {
            sum += u64_parse_cstr_len(Str_first(str), Str_len(str));
            Str_dbg(str);
            nl;
        }
    }

    u64_dbg(sum);
    Str_del(& str);
}