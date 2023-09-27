#ifndef CSTR_H
#define CSTR_H

#include "def.h"

i64     cstr_cmp_len(const byte * lhs, i64 lhs_len, const byte * rhs, i64 rhs_len);
i64     cstr_cmp(const byte * lhs, const byte * rhs);
u64     cstr_hash_djb_len(const byte * cstr, i64 len);
u64     cstr_hash_djb(const byte * cstr);
i64     cstr_find_c_len(const byte * cstr, i64 len, byte x);
i64     cstr_find_c(const byte * cstr, byte x);
i64     cstr_find_ws_len(const byte * cstr, i64 len);
i64     cstr_find_ws(const byte * cstr);
i64     cstr_find_cstr_len(const byte * haystack, i64 h_len, const byte * needle, i64 n_len);
i64     cstr_find_cstr_len_ci(const byte * haystack, i64 h_len, const byte * needle, i64 n_len);
void    cstr_rev_len(byte * cstr, i64 len);
void    cstr_rev(byte * cstr);
void    cstr_sort_insert(byte * cstr, i64 len);
STATUS  cstr_next_perm_len(byte * cstr, i64 len);
STATUS  cstr_next_perm(byte * cstr);

#endif