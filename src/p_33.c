#include "euler.h"

#define LOW     10
#define HIGH    100

static bool _is_cancellable(i64 top, i64 bot)
{
    Rat rat;
    Rat x;

    if (top % 10 == 0 || bot % 10 == 0) return false;

    rat = Rat_init(top, bot);
    x = Rat_init(0, 1);

    if (top % 10 == bot / 10)
    {
        x = Rat_init(top / 10, bot % 10);
    }
    else if (top / 10 == bot % 10)
    {
        x = Rat_init(top % 10, bot / 10);
    }

    return Rat_eq(rat, x);
}

void p_33(void)
{
    Vec vec;
    Rat rat;

    vec = Vec_new(Rat);
    for (i64 top = LOW; top < HIGH; top ++)
    {
        for (i64 bot = top + 1; bot < HIGH; bot ++)
        {
            if (_is_cancellable(top, bot)) Vec_push(& vec, Rat_init(top, bot), Rat);
        }
    }

    rat = Rat_one();
    Vec_fold(& rat, vec, Rat_multf);
    u64_dbg(rat.bot);
    Vec_del(& vec);
}