#include "euler.h"

static inline bool _is_pentagonal(u64 x)
{
    u64 rooted;
    u64 root;

    rooted = 1 + 24 * x;
    root = math_sqrt_int(rooted);
    if (root * root != rooted) return false;

    return (1 + root) % 6 == 0;
}

static inline u64 _pentagonal(u64 n)
{
    return n * (3 * n - 1) / 2;
}

void p_44(void)
{
    

}