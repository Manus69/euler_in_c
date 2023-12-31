#include "def.h"
#include "macro.h"

Putf_gen(u64)
Swapf_gen(u64)

i64     u64_cmp(u64 lhs, u64 rhs);
i64     u64_cmpf(const void * lhs, const void * rhs);
u64     u64_parse_cstr_len(const byte * cstr, i64 len);
u64     u64_parse_cstr(const byte * cstr);
void    u64_dbg(u64 x);
void    u64_dbgf(const void * x);