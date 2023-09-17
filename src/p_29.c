#include "euler.h"

#define N 100

void p_29(void)
{
    Set     set;
    Bigu    x;

    set = Set_new(Bigu);
    for (u64 base = 2; base <= N; base ++)
    {
        for (u64 pow = 2; pow <= N; pow ++)
        {
            x = Bigu_pow_u64(base, pow);
            if (Set_include(& set, & x, Bigu_putf, Bigu_cmpf, Bigu_hashf) == STATUS_NOT_DONE)
            {
                Bigu_del(& x);
            }
        }
    }

    i64_dbg(Set_size(set));
    Set_map(set, (F) Bigu_del);
    Set_del(& set);
}