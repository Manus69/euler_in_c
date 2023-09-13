#include "euler.h"

#define N 1000

void p_25(void)
{
    Bigu    f0;
    Bigu    f1;
    Bigu    next;
    i64     n_digits;
    i64     k;

    f0 = Bigu_new(1);
    f1 = Bigu_new(1);

    for (k = 0; ; k ++)
    {
        n_digits = Bigu_n_decimal_digits(f1);
        if (n_digits >= N) break;

        next = Bigu_dup(f1);
        Bigu_plus(& f1, f0);
        Bigu_del(& f0);
        f0 = next;
    }

    i64_dbg(k + 2);

    Bigu_del(& f1);
    Bigu_del(& f0);
}