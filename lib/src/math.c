#include "math.h"

u64 math_next_pow2(u64 x)
{
    return ((u64) 1) << (sizeof(x) * __CHAR_BIT__ - __builtin_clzl(x | 1));
}