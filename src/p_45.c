#include "euler.h"

static i64 _check_root(i64 a, i64 b, i64 c)
{
    i64 disc;
    i64 root;

    if ((disc = b * b - 4 * a * c) < 0) return NO_IDX;
    root = math_sqrt_int(disc);

    return root * root == disc ? root : NO_IDX;
}

static inline bool _is_tri(u64 x)
{
    i64 root;

    if ((root = _check_root(1, 1, - 2 * x)) == NO_IDX) return false;

    return (root - 1) % 2 == 0;
}

static inline bool _is_pent(u64 x)
{
    i64 root;

    if ((root = _check_root(3, -1, - 2 * x)) == NO_IDX) return false;

    return (1 + root) % 6 == 0;
}

static inline bool _is_hex(u64 x)
{
    i64 root;

    if ((root = _check_root(2, -1, -1 * x)) == NO_IDX) return false;

    return (1 + root) % 4 == 0;
}

#define START 144

void p_45(void)
{
    u64 hex;

    for (u64 n = START; ; n ++)
    {
        hex = n * (2 * n - 1);
        if (_is_pent(hex) && _is_tri(hex)) break;
    }

    u64_dbg(hex);
}