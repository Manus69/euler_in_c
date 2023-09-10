#include "euler.h"

#define N 1000

static u64 _sum(Str str)
{
    const byte *    cstr;
    u64             sum;

    sum = 0;
    cstr = Str_first(str);

    while (* cstr)
    {
        sum += * cstr - '0';
        cstr ++;
    }

    return sum;
}

void p_16(void)
{
    Bigu    base;
    Bigu    power;
    Str     str;

    base = Bigu_new(2);
    power = Bigu_pow(base, N);

    Bigu_del(& base);

    str = Bigu_to_Str(power);
    u64_dbg(_sum(str));

    Str_del(& str);
    Bigu_del(& power);
}