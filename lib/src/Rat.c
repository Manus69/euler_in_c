#include "Rat.h"
#include "math.h"
#include "i64.h"
#include <assert.h>
#include <stdio.h>

Rat Rat_init(i64 top, u64 bot)
{
    u64 gcd;

    assert(bot);
    gcd = math_gcd(math_abs(top), bot);

    return (Rat)
    {
        .top = top / gcd,
        .bot = bot / gcd,
    };
}

bool Rat_eq(Rat lhs, Rat rhs)
{
    return lhs.top == rhs.top && lhs.bot == rhs.bot;
}

i64 Rat_cmp(Rat lhs, Rat rhs)
{
    Rat _lhs;
    Rat _rhs;

    _lhs = Rat_init(lhs.top * rhs.bot, lhs.bot * rhs.bot);
    _rhs = Rat_init(rhs.top * lhs.bot, rhs.bot * lhs.bot);

    return i64_cmp(_lhs.top, _rhs.top);
}

i64 Rat_cmpf(const void * lhs, const void * rhs)
{
    return Rat_cmp(deref(Rat) lhs, deref(Rat) rhs);
}

Rat Rat_add(Rat lhs, Rat rhs)
{
    return Rat_init(lhs.top * rhs.bot + rhs.top * rhs.bot, lhs.bot * rhs.bot);
}

Rat Rat_mult(Rat lhs, Rat rhs)
{
    return Rat_init(lhs.top * rhs.top, lhs.bot * rhs.bot);
}

Rat Rat_inv(Rat rat)
{
    assert(rat.top);

    return Rat_init(rat.bot, rat.top);
}

Rat Rat_scale(Rat rat, i64 x)
{
    return Rat_init(rat.top * x, rat.bot);
}

Rat Rat_subt(Rat lhs, Rat rhs)
{
    return Rat_add(lhs, Rat_scale(rhs, -1));
}

Rat Rat_pow(Rat rat, u64 exp)
{
    Rat result;

    result = Rat_init(math_pow(rat.top, exp), math_pow(rat.bot, exp));
    if (rat.top < 0 && exp % 2) result = Rat_scale(result, -1);

    return result;
}

double Rat_as_decimal(Rat rat)
{
    return (double) rat.top / (double) rat.bot;
}

void Rat_dbg(Rat rat)
{
    printf("%ld / %zu ", rat.top, rat.bot);
}

void Rat_dbgf(const void * rat)
{
    Rat_dbg(deref(Rat) rat);
}