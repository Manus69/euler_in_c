#include "Str.h"
#include "cstr.h"
#include "mem.h"
#include "u8.h"
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

void Str_append_Slc(Str * str, StrSlc slc)
{
    Str_append_cstr_len(str, slc.cstr, slc.len);
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

void Str_rev(Str str)
{
    byte * lhs;
    byte * rhs;

    lhs = Str_first(str);
    rhs = Str_get(str, Str_len(str) - 1);

    while (lhs < rhs)
    {
        swap_ptr(lhs, rhs, byte);
        lhs ++;
        rhs --;
    }
}

Str StrSlc_replace_cstr_len(StrSlc slc, const byte * what, i64 w_len, const byte * to, i64 t_len)
{
    Str result;
    i64 idx;

    result = Str_new_capacity(slc.len);

    while ((idx = StrSlc_find_cstr_len(slc, what, w_len)) != NO_IDX)
    {
        Str_append_cstr_len(& result, slc.cstr, idx);
        Str_append_cstr_len(& result, to, t_len);
        StrSlc_shift(& slc, idx + w_len);
    }

    Str_append_Slc(& result, slc);

    return result;
}

Str StrSlc_replace_cstr(StrSlc slc, const byte * what, const byte * to)
{
    return StrSlc_replace_cstr_len(slc, what, strlen(what), to, strlen(to));
}

Str Str_replace_cstr_len(Str str, const byte * what, i64 w_len, const byte * to, i64 t_len)
{
    return StrSlc_replace_cstr_len(Str_to_slice(str), what, w_len, to, t_len);
}

Str Str_replace_cstr(Str str, const byte * what, const byte * to)
{
    return Str_replace_cstr_len(str, what, strlen(what), to, strlen(to));
}

void Str_replace_cstr_in_situ(Str * str, const byte * what, const byte * to)
{
    Str new;

    new = Str_replace_cstr(* str, what, to);
    Str_del(str);
    * str = new;
}

Str Str_repeat_cstr_len(const byte * cstr, i64 len, i64 count)
{
    Str str;

    str = Str_new_capacity(len * count);
    for (i64 k = 0; k < count; k ++) Str_append_cstr_len(& str, cstr, len);

    return str;
}

Str Str_repeat_cstr(const byte * cstr, i64 count)
{
    return Str_repeat_cstr_len(cstr, strlen(cstr), count);
}

STATUS Str_next_perm(Str str)
{
    return cstr_next_perm_len(str.cstr, str.idx);
}

void Str_dbg(Str str)
{
    printf("%s ", str.cstr);
}

void Str_dbgf(const void * str)
{
    Str_dbg(deref(Str) str);
}