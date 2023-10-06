#include "euler.h"

#define N 10

typedef struct Digits Digits;

struct Digits
{
    byte    digits[N];
    u8      count;
};

static inline void Digits_dbg(Digits digits)
{
    for (i64 k = 0; k < N; k ++) printf("(%ld : %d) ", k, digits.digits[k]);
    nl;
}

static inline bool Digits_eq(Digits lhs, Digits rhs)
{
    if (lhs.count != rhs.count) return false;

    for (i64 k = 0; k < N; k ++)
    {
        if (lhs.digits[k] != rhs.digits[k]) return false;
    }

    return true;
}

static inline Digits _digits(u64 x)
{
    Digits digits = {};

    do
    {
        digits.count ++;
        digits.digits[x % 10] ++;

        x = x / 10;
    }
    while (x);

    return digits;
}

static inline bool _check_multiples(u64 x)
{
    Digits  digits;
    Digits  ref_digits;
    u64     mult;

    ref_digits = _digits(x);
    for (u64 k = 2; k < 7; k ++)
    {
        mult = k * x;
        digits = _digits(mult);

        if (! Digits_eq(ref_digits, digits)) return false;
    }

    return true;
}

void p_52(void)
{
    for (u64 x = 1; ; x ++)
    {
        if (_check_multiples(x))
        {
            u64_dbg(x);
            break;
        }
    }


}