#ifndef STR_H
#define STR_H

#include "def.h"
#include "Slc.h"

#define Str_vjoin(...) Str_join_cstr((const byte * []){__VA_ARGS__, NULL})

typedef struct Str Str;

struct Str
{
    byte *  bytes;
    i64     len;
    i64     size;
};

Str     Str_new_size(i64 size);
Str     Str_new(void);
Str     Str_from_cstr_len(byte * cstr, i64 len);
Str     Str_from_cstr(byte * cstr);
Str     Str_from_Slc(Slc slc);
Str     Str_join_cstr(const byte * cstrs []);
Str     Str_repeat_cstr_len(const char * cstr, i64 len, i64 n_times);
Str     Str_repeat_cstr(const char * cstr, i64 n_times);
Str     Str_replace_cstr_len(Slc slc, const byte * from, i64 from_len, const byte * to, i64 to_len);
Str     Str_replace_cstr(Slc slc, const byte * from, const byte * to);
void    Str_replace(Str * str, const byte * from, const byte * to);
void    Str_set_len(Str * str, i64 len);
void    Str_reserve(Str * str, i64 capacity);
i64     Str_len(Str str);
i64     Str_size(Str str);
i64     Str_capacity(Str str);
byte *  Str_get(Str str, i64 idx);
byte *  Str_cstr(Str str);
Slc     Str_slice(Str str, i64 idx, i64 len);
Slc     Str_to_Slc(Str str);
void    Str_append_cstr_len(Str * str, const byte * cstr, i64 len);
void    Str_append_cstr(Str * str, const byte * cstr);
void    Str_append_Slc(Str * str, Slc slc);
void    Str_append_Str(Str * str, Str rhs);
void    Str_del(Str * str);
i64     Slc_find_byte(Slc slc, byte x);
i64     Slc_find_cstr_len(Slc slc, const byte * cstr, i64 len);
Slc     Slc_chop_next(Slc * slc, byte x);


#endif