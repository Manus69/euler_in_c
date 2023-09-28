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
Putf_gen(Str)
Swapf_gen(StrSlc)
Swapf_gen(Str)

i64             StrSlc_cmp(StrSlc lhs, StrSlc rhs);
i64             StrSlc_cmpf(const void * lhs, const void * rhs);
StrSlc          StrSlc_from_cstr_len(const byte * cstr, i64 len);
StrSlc          StrSlc_from_cstr(const byte * cstr);
StrSlc          StrSlc_brick(void);
bool            StrSlc_is_brick(StrSlc slc);
const char *    StrSlc_get(StrSlc slc, i64 idx);
char            StrSlc_get_c(StrSlc slc, i64 idx);
const char *    StrSlc_first(StrSlc slc);
i64             StrSlc_len(StrSlc slc);
bool            StrSlc_empty(StrSlc slc);
void            StrSlc_shift(StrSlc * slc, i64 shift);
StrSlc          StrSlc_shifted(StrSlc slc, i64 shift);
void            StrSlc_shrink(StrSlc * slc, i64 shrink);
StrSlc          StrSlc_slice(StrSlc slc, i64 idx, i64 len);
StrSlc          StrSlc_slice_from(StrSlc slc, i64 idx);
StrSlc          StrSlc_copy(StrSlc slc);
StrSlc          StrSlc_chop_front(StrSlc * slc, i64 len);
StrSlc          StrSlc_chop_all(StrSlc * slc);
StrSlc          StrSlc_chop_front_check(StrSlc * slc, i64 len);
i64             StrSlc_find_c(StrSlc slc, byte x);
i64             StrSlc_find_slice(StrSlc haystack, StrSlc needle);
i64             StrSlc_find_cstr_len(StrSlc slc, const byte * cstr, i64 len);
i64             StrSlc_find_cstr(StrSlc slc, const byte * cstr);
i64             StrSlc_find_cstr_len(StrSlc slc, const byte * cstr, i64 len);
i64             StrSlc_find_cstr(StrSlc slc, const byte * cstr);
i64             StrSlc_find_cstr_len_ci(StrSlc slc, const byte * cstr, i64 len);
i64             StrSlc_find_cstr_ci(StrSlc slc, const byte * cstr);
i64             StrSlc_find_slice_ci(StrSlc haystack, StrSlc needle);
i64             StrSlc_find_ws(StrSlc slc);
bool            StrSlc_starts_with_slice(StrSlc lhs, StrSlc rhs);
bool            StrSlc_starts_with_c(StrSlc slc, byte x);
bool            StrSlc_starts_with_cstr_len(StrSlc slc, const byte * cstr, i64 len);
bool            StrSlc_starts_with_cstr(StrSlc slc, const byte * cstr);
bool            StrSlc_starts_with_cstr_len_ci(StrSlc slc, const byte * cstr, i64 len);
bool            StrSlc_starts_with_slice_ci(StrSlc lhs, StrSlc rhs);
void            StrSlc_trim_front_one(StrSlc * slc, byte x);
void            StrSlc_trim_front_cstr_len(StrSlc * slc, const byte * cstr, i64 len);
void            StrSlc_trim_front_cstr(StrSlc * slc, const byte * cstr);
bool            StrSlc_ends_with_c(StrSlc slc, byte x);
bool            StrSlc_ends_with_cstr_len(StrSlc slc, const byte * cstr, i64 len);
bool            StrSlc_ends_with_cstr(StrSlc slc, const byte * cstr);
void            StrSlc_trim_back_one(StrSlc * slc, byte x);
void            StrSlc_trim_back_cstr_len(StrSlc * slc, const byte * cstr, i64 len);
void            StrSlc_trim_back_cstr(StrSlc * slc, const byte * cstr);
i64             StrSlc_trim_front_ws(StrSlc * slc);
i64             StrSlc_trim_back_ws(StrSlc * slc);
StrSlc          StrSlc_split_next(StrSlc * slc, byte x);
Vec             StrSlc_split(StrSlc slc, byte x);
StrSlc          StrSlc_in_brackets(StrSlc slc, byte ob, byte cb);
StrSlc          StrSlc_in_brackets_any(StrSlc slc);
void            StrSlc_dbg(StrSlc slc);
void            StrSlc_dbgf(const void * slc);

i64             Str_cmp(Str lhs, Str rhs);
i64             Str_cmpf(const void * lhs, const void * rhs);
Str             Str_new_capacity(i64 capacity);
Str             Str_new(void);
Str             Str_from_cstr_len(const byte * cstr, i64 len);
Str             Str_from_cstr(const byte * cstr);
STATUS          Str_next_perm(Str str);
void            Str_del(Str * str);
i64             Str_len(Str str);
i64             Str_capacity(Str str);
char *          Str_get(Str str, i64 idx);
char *          Str_first(Str str);
void            Str_extend(Str * str, i64 len);
void            Str_resize(Str * str, i64 size);
void            Str_reserve(Str * str, i64 len);
void            Str_reserve_agro(Str * str, i64 len);
StrSlc          Str_slice(Str str, i64 idx, i64 len);
StrSlc          Str_to_slice(Str str);
Vec             Str_split_slices(Str str, byte x);
void            Str_append_cstr_len(Str * str, const byte * cstr, i64 len);
void            Str_append_cstr(Str * str, const byte * cstr);
void            Str_append_Slc(Str * str, StrSlc slc);
void            Str_append_Str(Str * lhs, Str rhs);
Str             Str_join_cstr(const byte * cstrs[]);
Str             StrSlc_replace_cstr_len(StrSlc slc, const byte * what, i64 w_len, const byte * to, i64 t_len);
Str             StrSlc_replace_cstr(StrSlc slc, const byte * what, const byte * to);
Str             Str_replace_cstr_len(Str str, const byte * what, i64 w_len, const byte * to, i64 t_len);
Str             Str_replace_cstr(Str str, const byte * what, const byte * to);
void            Str_replace_cstr_in_situ(Str * str, const byte * what, const byte * to);
Str             Str_repeat_cstr_len(const byte * cstr, i64 len, i64 count);
Str             Str_repeat_cstr(const byte * cstr, i64 count);
void            Str_rev(Str str);
void            Str_dbg(Str str);
void            Str_dbgf(const void * str);

#endif