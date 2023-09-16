#include "euler.h"

#define N 5

typedef struct PowStr PowStr;

struct PowStr
{
    u8 *    pows;
    i64     len;
};

void PowStr_dbg(PowStr ps)
{
    for (i64 k = 0; k < ps.len; k ++)
    {
        printf("%u ", ps.pows[k]);
    }
    nl;
}

void PowStr_del(PowStr * ps)
{
    mem_del(ps->pows);
    to0(ps, PowStr);
}

i64 PowStr_cmp(PowStr lhs, PowStr rhs)
{
    if (lhs.len != rhs.len) return i64_cmp(lhs.len, rhs.len);

    for (i64 k = 1; k < lhs.len; k ++)
    {
        if (lhs.pows[k] != rhs.pows[k]) return u8_cmp(lhs.pows[k], rhs.pows[k]);
    }

    return 0;
}

i64 PowStr_cmpf(const void * lhs, const void * rhs)
{
    return PowStr_cmp(deref(PowStr) lhs, deref(PowStr) rhs);
}

u64 PowStr_hash(PowStr ps)
{
    return cstr_hash_djb_len((const byte *) ps.pows, ps.len);
}

u64 PowStr_hashf(const void * ps)
{
    return PowStr_hash(deref(PowStr) ps);
}

static PowStr _powstr(u64 x, u8 * pows)
{
    u64 p;
    u64 pow;
    i64 len;

    len = 0;
    p = 2;

    while (x > 1)
    {
        pow = 0;
        while (x % p == 0)
        {
            len = p + 1;
            pow ++;
            x /= p;
        }

        pows[p] = pow;
        p ++;
    }

    return (PowStr) {pows, len};
}

PowStr PowStr_new(u64 x, Sieve sieve)
{
    u8 *    pows;

    pows = mem_alloc0(N + 1);
    pows[1] = 1;

    if (unlikely(x == 1)) return (PowStr) {pows, 2};
    if (Sieve_is_prime(sieve, x))
    {
        pows[x] = 1;
        return (PowStr) {pows, x + 1};
    }

    return _powstr(x, pows);
}

void p_29(void)
{
    Sieve sieve;

    sieve = Sieve_new(N * N);
    PowStr ps = PowStr_new(20, sieve);
    PowStr_dbg(ps);
    PowStr_del(& ps);


    Sieve_del(& sieve);
}