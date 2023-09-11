#include "euler.h"

#define N 100

void p_20(void)
{
    Bigu    x;
    Str     str;

    x = Bigu_factorial(N);
    str = Bigu_to_Str(x);

    u64_dbg(sum_digits(Str_first(str)));

    Str_del(& str);
    Bigu_del(& x);
}