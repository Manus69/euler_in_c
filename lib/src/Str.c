#include "Str.h"
#include "cstr.h"
#include "mem.h"
#include <string.h>
#include <stdio.h>

#define STR_DC (1 << 4)

i64 Str_cmp(Str lhs, Str rhs)
{
    return cstr_cmp(lhs.cstr, rhs.cstr);
}

i64 Str_cmpf(const void * lhs, const void * rhs)
{
    return Str_cmp(deref(Str) lhs, deref(Str) rhs);
}

Str Str_new_capacity(i64 capacity)
{
    return (Str)
    {
        .cstr = mem_alloc0(capacity + 1),
        .idx = 0,
        .size = capacity,
    };
}

Str Str_new(void)
{
    return Str_new_capacity(STR_DC);
}

Str Str_from_cstr_len(const byte * cstr, i64 len)
{
    Str str;

    str = Str_new_capacity(len);
    memcpy(str.cstr, cstr, len);
    str.idx = len;

    return str;
}

Str Str_from_cstr(const byte * cstr)
{
    return Str_from_cstr_len(cstr, strlen(cstr));
}

void Str_del(Str * str)
{
    mem_del(str->cstr);
    to0(str, Str);
}

i64 Str_len(Str str)
{
    return str.idx;
}

i64 Str_capacity(Str str)
{
    return str.size - str.idx - 1;
}

char * Str_get(Str str, i64 idx)
{
    return str.cstr + idx;
}

char * Str_first(Str str)
{
    return str.cstr;
}

void Str_extend(Str * str, i64 len)
{
    str->size = mem_extend((void **) & str->cstr, str->size, len);
    memset(Str_get(* str, str->idx), 0, Str_capacity(* str));
}

void Str_resize(Str * str, i64 size)
{
    if (likely(size > str->size)) Str_extend(str, size - str->size);
}

void Str_reserve(Str * str, i64 len)
{
    if (Str_capacity(* str) < len) Str_extend(str, len);
}

void Str_reserve_agro(Str * str, i64 len)
{
    if (Str_capacity(* str) < len) Str_resize(str, next_pow2(str->size + len + 1));
}

StrSlc Str_slice(Str str, i64 idx, i64 len)
{
    return StrSlc_from_cstr_len(str.cstr + idx, len);
}

StrSlc Str_to_slice(Str str)
{
    return Str_slice(str, 0, str.idx);
}

Vec Str_split_slices(Str str, byte x)
{
    return StrSlc_split(Str_to_slice(str), x);
}

void Str_append_cstr_len(Str * str, const byte * cstr, i64 len)
{
    if (unlikely(Str_capacity(* str) < len)) Str_reserve_agro(str, len);

    memcpy(Str_get(* str, str->idx), cstr, len);
    str->idx += len;
}

void Str_append_cstr(Str * str, const byte * cstr)
{
    return Str_append_cstr_len(str, cstr, strlen(cstr));
}

void Str_append_Str(Str * lhs, Str rhs)
{
    return Str_append_cstr_len(lhs, Str_first(rhs), rhs.idx);
}

Str Str_join_cstr(const byte * cstrs[])
{
    Str             str;
    const byte *    current;

    str = Str_new();
    while ((current = * cstrs ++)) Str_append_cstr(& str, current);

    return str;
}

void Str_dbg(Str str)
{
    printf("%s ", str.cstr);
}

void Str_dbgf(const void * str)
{
    Str_dbg(deref(Str) str);
}