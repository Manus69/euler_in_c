#include "euler.h"

#define N 100

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

static void _get_powers(u64 x, Sieve sieve, Htbl * htbl)
{

}

void p_29(void)
{
    // Sieve sieve;
    // Htbl  htbl;

    // sieve = Sieve_new(N * N);
    // htbl = Htbl_new_capacity(N * N, sizeof(PowStr));

    


    // Sieve_del(& sieve);

    Set set;

    set = Set_new(Bigu);

    for (u64 base = 2; base <= N; base ++)
    {
        for (u64 pow = 2; pow <= N; pow ++)
        {
            Bigu bu = Bigu_pow_u64(base, pow);
            Set_include(& set, & bu, Bigu_putf, Bigu_cmpf, Bigu_hashf);
        }
    }

    Set_map(set, (F) Bigu_del);
    Set_del(& set);
}