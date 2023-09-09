#include "BigInt.h"
#include "mem.h"
#include "math.h"
#include "i64.h"
#include "u64.h"
#include "Str.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define BIGU_DC     (1 << 2)
#define SSF         2
#define BASE        1000000

static inline Bigu _new(u64 x, i64 capacity)
{
    u64 * digits;

    digits = mem_alloc0(capacity * sizeof(u64));
    digits[0] = x % BASE;

    return (Bigu)
    {
        .digits = digits,
        .len = 1,
        .capacity = capacity,
    };
}

Bigu Bigu_new(u64 x)
{
    return _new(x, BIGU_DC);
}

Bigu Bigu_dup(Bigu bigu)
{
    return (Bigu)
    {
        .digits = mem_dup(bigu.digits, bigu.capacity * sizeof(u64)),
        .len = bigu.len,
        .capacity = bigu.capacity,
    };
}

void Bigu_del(Bigu * bigu)
{
    mem_del(bigu->digits);
    to0(bigu, Bigu);
}

i64 Bigu_cmp(Bigu lhs, Bigu rhs)
{
    if (lhs.len != rhs.len) return i64_cmp(lhs.len, rhs.len);

    for (i64 k = lhs.len - 1; k >= 0; k --)
    {
        if (lhs.digits[k] != rhs.digits[k]) return u64_cmp(lhs.digits[k], rhs.digits[k]);
    }

    return 0;
}

i64 Bigu_cmpf(const void * lhs, const void * rhs)
{
    return Bigu_cmp(deref(Bigu) lhs, deref(Bigu) rhs);
}

static inline void _to0(Bigu * bigu)
{
    bigu->digits[0] = 0;
    bigu->len = 1;
}

static inline bool _is0(Bigu bigu)
{
    return bigu.len == 1 && bigu.digits[0] == 0;
}

static i64 _capacity(Bigu bigu)
{
    return bigu.capacity - bigu.len;
}

static void _extend(Bigu * bigu, i64 len)
{
    mem_extend0((void **) & bigu->digits, bigu->capacity * sizeof(u64), len * sizeof(u64));
    bigu->capacity += len;
}

static void _double_capacity(Bigu * bigu)
{
    _extend(bigu, bigu->capacity);
}

static void _resize(Bigu * bigu, i64 capacity)
{
    assert(capacity > bigu->capacity);
    _extend(bigu, capacity - bigu->capacity);
}

static inline void _reserve(Bigu * bigu, i64 len)
{
    if (_capacity(* bigu) < len) _extend(bigu, len);
}

static void _enforce_capacity(Bigu * bigu, i64 capacity)
{
    if (bigu->capacity < capacity) _resize(bigu, capacity);
}

static void _enforce_capacity_agro(Bigu * bigu, i64 capacity)
{
    capacity = SSF * capacity;
    _enforce_capacity(bigu, capacity);
}

#define _compute(dst, lhs, rhs, op) \
{ \
    u64 x = lhs op rhs + carry; \
    dst = x % BASE; \
    carry = x / BASE; \
}

static i64 _scale(u64 * lhs, i64 len, u64 rhs)
{
    u64 carry;
    i64 k;

    carry = 0;
    for (k = 0; k < len; k ++) _compute(lhs[k], lhs[k], rhs, *)
    
    if (carry) lhs[k ++] = carry;

    return k;
}

static i64 _scale_buf(u64 * restrict buf, const u64 * restrict lhs, i64 len, u64 rhs)
{
    u64 carry;
    i64 k;

    carry = 0;
    for (k = 0; k < len; k ++) _compute(buf[k], lhs[k], rhs, *)

    if (carry) buf[k ++] = carry;

    return k;
}

static i64 _plus(u64 * lhs, const u64 * rhs, i64 rhs_len)
{
    u64 carry;
    i64 k;

    carry = 0;
    for (k = 0; k < rhs_len; k ++) _compute(lhs[k], lhs[k], rhs[k], +)
    for ( ; carry; k ++) _compute(lhs[k], lhs[k], 0, +)

    return k;
}

//l > r
static i64 _add(u64 * restrict buff, const u64 * lhs, i64 lhs_len, const u64 * rhs, i64 rhs_len)
{
    u64 carry;
    i64 k;

    carry = 0;
    for (k = 0; k < rhs_len; k ++) _compute(buff[k], lhs[k], rhs[k], +)
    for ( ; k < lhs_len; k ++) _compute(buff[k], lhs[k], 0, +)
    if (carry) buff[k ++] = carry;

    return k;
}

//l > r
static i64 _mult(u64 * restrict buff, const u64 * lhs, i64 lhs_len, const u64 * rhs, i64 rhs_len)
{
    u64 scratch[lhs_len + 1];
    i64 len;
    i64 k;

    for (k = 0; k < rhs_len; k ++)
    {
        len = _scale_buf(scratch, lhs, lhs_len, rhs[k]);
        len = k + _plus(buff + k, scratch, len);
    }

    return len;
}

Bigu Bigu_mult(Bigu lhs, Bigu rhs)
{
    Bigu result;

    result = _new(0, lhs.len + rhs.len + 1);
    result.len = lhs.len > rhs.len ?
                _mult(result.digits, lhs.digits, lhs.len, rhs.digits, rhs.len) :
                _mult(result.digits, rhs.digits, rhs.len, lhs.digits, lhs.len);
    
    return result;
}

void Bigu_plus_u64(Bigu * lhs, u64 rhs)
{
    i64 len;

    assert(rhs < BASE);

    if (unlikely(_capacity(* lhs)) == 0) _double_capacity(lhs);
    len = _plus(lhs->digits, & rhs, 1);

    if (len > lhs->len) lhs->len = len;
}

void Bigu_plus(Bigu * lhs, Bigu rhs)
{
    i64 len;

    _enforce_capacity_agro(lhs, lhs->len + rhs.len + 1);
    len = _plus(lhs->digits, rhs.digits, rhs.len);

    if (len > lhs->len) lhs->len = len;
}

Bigu Bigu_add(Bigu lhs, Bigu rhs)
{
    Bigu result;

    result = _new(0, max(lhs.len, rhs.len) + 1);
    result.len = lhs.len > rhs.len ? 
                _add(result.digits, lhs.digits, lhs.len, rhs.digits, rhs.len) :
                _add(result.digits, rhs.digits, rhs.len, lhs.digits, lhs.len);

    return result;
}

void Bigu_scale(Bigu * lhs, u64 rhs)
{
    assert(rhs < BASE);

    if (rhs == 0) return _to0(lhs);
    if (unlikely(_capacity(* lhs) == 0)) _double_capacity(lhs);

    lhs->len = _scale(lhs->digits, lhs->len, rhs);
}

Bigu Bigu_from_cstr_len(const byte * cstr, i64 len)
{
    Bigu bigu;

    bigu = _new(0, BIGU_DC);

    for (i64 k = 0; k < len; k ++)
    {
        Bigu_scale(& bigu, 10);
        Bigu_plus_u64(& bigu, cstr[k] - '0');
    }

    return bigu;
}

Bigu Bigu_from_cstr(const byte * cstr)
{
    return Bigu_from_cstr_len(cstr, strlen(cstr));
}

Bigu Bigu_from_StrSlc(StrSlc slc)
{
    return Bigu_from_cstr_len(StrSlc_first(slc), StrSlc_len(slc));
}

Bigu Bigu_from_StrSlc_ptr(const StrSlc * slc)
{
    return Bigu_from_StrSlc(* slc);
}

void Bigu_dbg(Bigu bigu)
{
    i64 k;

    k = bigu.len - 1;
    printf("%zu", bigu.digits[k]);
    k --;
    
    while (k >= 0)
    {
        printf("%0*d", (int) math_log10(BASE), (int) bigu.digits[k]);
        k --;
    }

    nl;
}

void Bigu_dbgf(const void * bigu)
{
    Bigu_dbg(deref(Bigu) bigu);
}