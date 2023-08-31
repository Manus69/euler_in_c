#ifndef CSTR_H
#define CSTR_H

#include "def.h"

i64 cstr_findc_len(const byte * cstr, i64 len, byte x);
i64 cstr_findc(const byte * cstr, byte x);
i64 cstr_find_cstr_len(const byte * haystack, i64 h_len, const byte * needle, i64 n_len);

#endif