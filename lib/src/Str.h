#ifndef STR_H
#define STR_H

#include "def.h"
#include "Vec.h"

#define Str_vjoin(...) Str_join_cstr((const byte * []){__VA_ARGS__, NULL})

typedef struct Str      Str;
typedef struct StrSlc   StrSlc;

struct StrSlc
{
    const byte *    cstr;
    i64             len;
};

struct Str
{
    byte *  cstr;
    i64     idx;
    i64     size;
};

Putf_gen(StrSlc)
Swapf_gen(StrSlc)
Putf_gen(Str)
Swapf_gen(Str)

i64 StrSlc_cmp(StrSlc lhs, StrSlc rhs);
i64 StrSlc_cmpf(const void * lhs, const void * rhs);
StrSlc StrSlc_from_cstr_len(const byte * cstr, i64 len);
StrSlc StrSlc_from_cstr(const byte * cstr);
const char * StrSlc_get(StrSlc slc, i64 idx);
const char * StrSlc_first(StrSlc slc);
i64 StrSlc_len(StrSlc slc);
bool StrSlc_empty(StrSlc slc);
void StrSlc_shift(StrSlc * slc, i64 shift);
StrSlc StrSlc_slice(StrSlc slc, i64 idx, i64 len);
StrSlc StrSlc_copy(StrSlc slc);
StrSlc StrSlc_chop_front(StrSlc * slc, i64 len);
StrSlc StrSlc_chop_all(StrSlc * slc);
StrSlc StrSlc_chop_front_check(StrSlc * slc, i64 len);
i64 StrSlc_find_c(StrSlc slc, byte x);
StrSlc StrSlc_split_next(StrSlc * slc, byte x);
Vec StrSlc_split(StrSlc slc, byte x);
void StrSlc_dbg(StrSlc slc);
void StrSlc_dbgf(const void * slc);

i64 Str_cmp(Str lhs, Str rhs);
i64 Str_cmpf(const void * lhs, const void * rhs);
Str Str_new_capacity(i64 capacity);
Str Str_new(void);
Str Str_from_cstr_len(const byte * cstr, i64 len);
Str Str_from_cstr(const byte * cstr);
void Str_del(Str * str);
i64 Str_len(Str str);
i64 Str_capacity(Str str);
char * Str_get(Str str, i64 idx);
char * Str_first(Str str);
void Str_extend(Str * str, i64 len);
void Str_resize(Str * str, i64 size);
void Str_reserve(Str * str, i64 len);
void Str_reserve_agro(Str * str, i64 len);
StrSlc Str_slice(Str str, i64 idx, i64 len);
StrSlc Str_to_slice(Str str);
Vec Str_split_slices(Str str, byte x);
void Str_append_cstr_len(Str * str, const byte * cstr, i64 len);
void Str_append_cstr(Str * str, const byte * cstr);
void Str_append_Str(Str * lhs, Str rhs);
Str Str_join_cstr(const byte * cstrs[]);
void Str_dbg(Str str);
void Str_dbgf(const void * str);


#endif