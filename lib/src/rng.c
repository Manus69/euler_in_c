#include "rng.h"

u32 rng_spcg_next(u64 * state)
{
    const u64   M = 0x9b60933458e17d7d;
    const u64   A = 0xd737232eeccdf7ed;
    u64         val;
    u64         shift;

    val = * state * M + A;
    shift = 29 - (val >> 61);
    * state = val;

    return val >> shift;
}

u64 rng_xor_next(u64 * state)
{
    const u64   C = 0x2545f4914f6cdd1d;
    u64         x;

    x = * state;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    * state = x;

    return x * C;
}