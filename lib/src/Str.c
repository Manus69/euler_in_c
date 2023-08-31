#include "Str.h"
#include "mem.h"
#include "Slc.h"
#include "math.h"
#include "macro.h"
#include "cstr.h"

#include <string.h>

#define STR_DC (1 << 4)

Str Str_new_size(i64 size)
{
    return (Str)
    {
        .bytes = mem_alloc0(size),
        .len = 0,
        .size = size,
    };
}

Str Str_new(void)
{
    return Str_new_size(STR_DC);
}

Str Str_from_cstr_len(byte * cstr, i64 len)
{
    Str str;

    str = Str_new_size(len + 1);
    memcpy(str.bytes, cstr, len);
    str.len = len;

    return str;
}

Str Str_from_cstr(byte * cstr)
{
    return Str_from_cstr_len(cstr, strlen(cstr));
}

Str Str_from_Slc(Slc slc)
{
    return Str_from_cstr_len(slc.ptr, slc.size);
}

void Str_del(Str * str)
{
    mem_del(str->bytes);
    to0(str, Str);
}

i64 Str_len(Str str)
{
    return str.len;
}

i64 Str_size(Str str)
{
    return str.size;
}

i64 Str_capacity(Str str)
{
    return str.size - str.len - 1;
}

void Str_set_len(Str * str, i64 len)
{
    str->len = len;
    str->bytes[len] = '\0';
}

byte * Str_get(Str str, i64 idx)
{
    return str.bytes + idx;
}

byte * Str_cstr(Str str)
{
    return str.bytes;
}

Slc Str_slice(Str str, i64 idx, i64 len)
{
    return Slc_init(str.bytes + idx, len);
}

Slc Str_to_Slc(Str str)
{
    return Str_slice(str, 0, str.len);
}

static inline void _resize(Str * str, i64 extra_len)
{
    u64 new_size;

    new_size = math_next_pow2(str->len + extra_len + 1);
    mem_extend_to_size0((void **) & str->bytes, str->size, new_size);
    str->size = new_size;
}

void Str_reserve(Str * str, i64 capacity)
{
    if (Str_capacity(* str) < capacity) _resize(str, capacity);
}

void Str_append_cstr_len(Str * str, const byte * cstr, i64 len)
{
    if (Str_capacity(* str) < len) _resize(str, len);

    memcpy(str->bytes + str->len, cstr, len);
    str->len += len;
}

void Str_append_cstr(Str * str, const byte * cstr)
{
    return Str_append_cstr_len(str, cstr, strlen(cstr));
}

void Str_append_Slc(Str * str, Slc slc)
{
    return Str_append_cstr_len(str, slc.ptr, slc.size);
}

void Str_append_Str(Str * str, Str rhs)
{
    return Str_append_cstr_len(str, rhs.bytes, rhs.len);
}

Str Str_join_cstr(const byte * cstrs [])
{
    Str             str;
    const byte *    current;

    str = Str_new();
    while ((current = * cstrs ++)) Str_append_cstr(& str, current);

    return str;
}

Str Str_repeat_cstr_len(const char * cstr, i64 len, i64 n_times)
{
    Str str;

    str = Str_new_size(len * n_times + 1);
    while (n_times --) Str_append_cstr_len(& str, cstr, len);

    return str;
}

Str Str_repeat_cstr(const char * cstr, i64 n_times)
{
    return Str_repeat_cstr_len(cstr, strlen(cstr), n_times);
}

i64 Str_findc(Str str, byte x)
{
    return cstr_findc_len(str.bytes, str.len, x);
}

i64 Str_find_cstr_len(Str str, const byte * cstr, i64 len)
{
    return cstr_find_cstr_len(str.bytes, str.len, cstr, len);
}

i64 Str_find_cstr(Str str, const byte * cstr)
{
    return Str_find_cstr_len(str, cstr, strlen(cstr));
}

Str Str_replace_cstr_len(Slc slc, const byte * from, i64 from_len, const byte * to, i64 to_len)
{
    Str str;
    i64 idx;

    str = Str_new_size(slc.size);
    while ((idx = Slc_find_cstr_len(slc, from, from_len)) != NO_IDX)
    {
        Str_append_cstr_len(& str, slc.ptr, idx);
        Str_append_cstr_len(& str, to, to_len);
        Slc_shift(& slc, idx + from_len);
    }

    Str_append_Slc(& str, slc);

    return str;
}

Str Str_replace_cstr(Slc slc, const byte * from, const byte * to)
{
    return Str_replace_cstr_len(slc, from, strlen(from), to, strlen(to));
}

void Str_replace(Str * str, const byte * from, const byte * to)
{
    Str new;

    new = Str_replace_cstr(Str_to_Slc(* str), from, to);
    Str_del(str);
    * str = new;
}