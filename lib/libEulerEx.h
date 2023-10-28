#ifndef LIB_EULER_EX_H
#define LIB_EULER_EX_H

#include <stdint.h>
#include <stdbool.h>

typedef enum STATUS     STATUS;
typedef int_fast64_t    i64;
typedef uint_fast64_t   u64;
typedef uint_fast8_t    u8;
typedef char            byte;
typedef void            (* F)(void *);
typedef void            (* Putf)(void *, const void *);
typedef void            (* Swapf)(void *, void *);
typedef i64             (* Cmpf)(const void *, const void *);
typedef u64             (* Hashf)(const void * );
typedef struct Slc      Slc;
typedef struct View     View;
typedef struct Vec      Vec;
typedef struct StrSlc   StrSlc;
typedef struct Str      Str;

enum STATUS
{
    STATUS_OK,
    STATUS_NOT_OK,
    STATUS_DONE,
    STATUS_NOT_DONE,
    STATUS_FUCKED,
};

struct Slc
{
    void *  ptr;
    i64     size;
};

struct View
{
    void *  ptr;
    i64     item_size;
    i64     len;
};

struct Vec
{
    void *  data;
    i64     item_size;
    i64     idx;
    i64     capacity;
};

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

#define NO_IDX          (-1)
#define nl              printf("\n");
#define likely(x)       __builtin_expect((x), 1)
#define unlikely(x)     __builtin_expect((x), 0)
#define deref(type)     * (type *)
#define to0(x, type)    deref(type) x = (type) {0}  
#define to_list0(...)   {__VA_ARGS__, 0}

#define max(x, y)       ({typeof(x) _x = x; typeof(y) _y = y; _x > _y ? _x : _y;})
#define min(x, y)       ({typeof(x) _x = x; typeof(y) _y = y; _x < _y ? _x : _y;})

#define is_pow2(x)      (__builtin_popcountl((unsigned long) x) == 1)

#define next_pow2(x) \
(1ul << (sizeof(unsigned long) * __CHAR_BIT__ - __builtin_clzl(((unsigned long)(x)) | 1)))

#define put_(dst, src, type) (deref(type) dst = deref(type) src)

#define Put_gen(type) \
static inline void type ## _put(type * dst, const type * src) \
{* dst = * src;}

#define Putf_gen(type) \
static inline void type ## _putf(void * dst, const void * src) {put_(dst, src, type);}

#define swap_ptr(lhs, rhs, type) \
{type _t = deref(type) (lhs); deref(type) (lhs) = deref(type) (rhs); deref(type) (rhs) = _t;}

#define Swap_gen(type) \
static inline void type ## _swap(type * lhs, type * rhs) \
{type _t = * lhs; * lhs = * rhs; * rhs = _t;}

#define Swapf_gen(type) \
static inline void type ## _swapf(void * lhs, void * rhs) swap_ptr(lhs, rhs, type)

#define Cmp_gen(type) \
static inline i64 type ## _cmp(type lhs, type rhs) \
{return lhs - rhs;}

#define Cmpf_gen(type) \
Cmp_gen(type) \
static inline i64 type ## _cmpf(const void * lhs, const void * rhs) \
{return type ## _cmp(deref(type) lhs, deref(type) rhs);}

#define Pair_struct_gen(l_type, r_type) \
typedef struct \
{ \
    l_type left; \
    r_type right; \
} Pair_ ## l_type ## _ ## r_type; \
Putf_gen(Pair_ ## l_type ## _ ## r_type) \
Swapf_gen(Pair_ ## l_type ## _ ## r_type)

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
i64     cstr_find_cstr(const byte * haystack, const byte * needle);
i64     cstr_find_cstr_ci(const byte * haystack, const byte * needle);
void    cstr_rev_len(byte * cstr, i64 len);
void    cstr_rev(byte * cstr);
void    cstr_sort_insert(byte * cstr, i64 len);
STATUS  cstr_next_perm_len(byte * cstr, i64 len);
STATUS  cstr_next_perm(byte * cstr);

#define Str_vjoin(...) Str_join_cstr((const byte * []){__VA_ARGS__, NULL})

Putf_gen(StrSlc)
Putf_gen(Str)
Swapf_gen(StrSlc)
Swapf_gen(Str)

const char *    StrSlc_get(StrSlc slc, i64 idx);
const char *    StrSlc_first(StrSlc slc);
i64     StrSlc_cmp(StrSlc lhs, StrSlc rhs);
i64     StrSlc_cmpf(const void * lhs, const void * rhs);
StrSlc  StrSlc_from_cstr_len(const byte * cstr, i64 len);
StrSlc  StrSlc_from_cstr(const byte * cstr);
StrSlc  StrSlc_brick(void);
bool    StrSlc_is_brick(StrSlc slc);
char    StrSlc_get_c(StrSlc slc, i64 idx);
char    StrSlc_first_c(StrSlc slc);
i64     StrSlc_len(StrSlc slc);
bool    StrSlc_empty(StrSlc slc);
void    StrSlc_shift(StrSlc * slc, i64 shift);
StrSlc  StrSlc_shifted(StrSlc slc, i64 shift);
void    StrSlc_shrink(StrSlc * slc, i64 shrink);
StrSlc  StrSlc_slice(StrSlc slc, i64 idx, i64 len);
StrSlc  StrSlc_slice_from(StrSlc slc, i64 idx);
StrSlc  StrSlc_copy(StrSlc slc);
StrSlc  StrSlc_chop_front(StrSlc * slc, i64 len);
StrSlc  StrSlc_chop_all(StrSlc * slc);
StrSlc  StrSlc_chop_front_check(StrSlc * slc, i64 len);
i64     StrSlc_find_c(StrSlc slc, byte x);
i64     StrSlc_find_slice(StrSlc haystack, StrSlc needle);
i64     StrSlc_find_cstr_len(StrSlc slc, const byte * cstr, i64 len);
i64     StrSlc_find_cstr(StrSlc slc, const byte * cstr);
i64     StrSlc_find_cstr_len(StrSlc slc, const byte * cstr, i64 len);
i64     StrSlc_find_cstr(StrSlc slc, const byte * cstr);
i64     StrSlc_find_cstr_len_ci(StrSlc slc, const byte * cstr, i64 len);
i64     StrSlc_find_cstr_ci(StrSlc slc, const byte * cstr);
i64     StrSlc_find_slice_ci(StrSlc haystack, StrSlc needle);
i64     StrSlc_find_slice_from(StrSlc haystack, i64 idx, StrSlc needle);
i64     StrSlc_find_slice_ci_from(StrSlc haystack, i64 idx, StrSlc needle);
i64     StrSlc_find_ws(StrSlc slc);
bool    StrSlc_starts_with_slice(StrSlc lhs, StrSlc rhs);
bool    StrSlc_starts_with_c(StrSlc slc, byte x);
bool    StrSlc_starts_with_cstr_len(StrSlc slc, const byte * cstr, i64 len);
bool    StrSlc_starts_with_cstr(StrSlc slc, const byte * cstr);
bool    StrSlc_starts_with_cstr_len_ci(StrSlc slc, const byte * cstr, i64 len);
bool    StrSlc_starts_with_slice_ci(StrSlc lhs, StrSlc rhs);
void    StrSlc_trim_front_one(StrSlc * slc, byte x);
void    StrSlc_trim_front_cstr_len(StrSlc * slc, const byte * cstr, i64 len);
void    StrSlc_trim_front_cstr(StrSlc * slc, const byte * cstr);
bool    StrSlc_ends_with_c(StrSlc slc, byte x);
bool    StrSlc_ends_with_cstr_len(StrSlc slc, const byte * cstr, i64 len);
bool    StrSlc_ends_with_cstr(StrSlc slc, const byte * cstr);
void    StrSlc_trim_back_one(StrSlc * slc, byte x);
void    StrSlc_trim_back_cstr_len(StrSlc * slc, const byte * cstr, i64 len);
void    StrSlc_trim_back_cstr(StrSlc * slc, const byte * cstr);
i64     StrSlc_trim_front_ws(StrSlc * slc);
i64     StrSlc_trim_back_ws(StrSlc * slc);
StrSlc  StrSlc_split_next(StrSlc * slc, byte x);
Vec     StrSlc_split(StrSlc slc, byte x);
StrSlc  StrSlc_in_brackets(StrSlc slc, byte ob, byte cb);
StrSlc  StrSlc_in_brackets_any(StrSlc slc);
void    StrSlc_dbg(StrSlc slc);
void    StrSlc_dbgf(const void * slc);

i64     Str_cmp(Str lhs, Str rhs);
i64     Str_cmpf(const void * lhs, const void * rhs);
Str     Str_new_capacity(i64 capacity);
Str     Str_new(void);
Str     Str_from_cstr_len(const byte * cstr, i64 len);
Str     Str_from_cstr(const byte * cstr);
STATUS  Str_next_perm(Str str);
void    Str_del(Str * str);
i64     Str_len(Str str);
i64     Str_capacity(Str str);
char *  Str_get(Str str, i64 idx);
char *  Str_first(Str str);
void    Str_extend(Str * str, i64 len);
void    Str_resize(Str * str, i64 size);
void    Str_reserve(Str * str, i64 len);
void    Str_reserve_agro(Str * str, i64 len);
StrSlc  Str_slice(Str str, i64 idx, i64 len);
StrSlc  Str_to_slice(Str str);
Vec     Str_split_slices(Str str, byte x);
void    Str_append_cstr_len(Str * str, const byte * cstr, i64 len);
void    Str_append_cstr(Str * str, const byte * cstr);
void    Str_append_Slc(Str * str, StrSlc slc);
void    Str_append_Str(Str * lhs, Str rhs);
Str     Str_join_cstr(const byte * cstrs[]);
Str     StrSlc_replace_cstr_len(StrSlc slc, const byte * what, i64 w_len, const byte * to, i64 t_len);
Str     StrSlc_replace_cstr(StrSlc slc, const byte * what, const byte * to);
Str     Str_replace_cstr_len(Str str, const byte * what, i64 w_len, const byte * to, i64 t_len);
Str     Str_replace_cstr(Str str, const byte * what, const byte * to);
void    Str_replace_cstr_in_situ(Str * str, const byte * what, const byte * to);
Str     Str_repeat_cstr_len(const byte * cstr, i64 len, i64 count);
Str     Str_repeat_cstr(const byte * cstr, i64 count);
void    Str_rev(Str str);
void    Str_dbg(Str str);
void    Str_dbgf(const void * str);

Putf_gen(Slc)
Swapf_gen(Slc)

Slc     Slc_init(void * ptr, i64 size);
i64     Slc_size(Slc slc);
bool    Slc_empty(Slc slc);
void *  Slc_get(Slc slc, i64 idx);
void *  Slc_first(Slc slc);
void    Slc_shift(Slc * slc, i64 shift);
Slc     Slc_slice(Slc slc, i64 idx, i64 size);
Slc     Slc_slice_from(Slc slc, i64 idx);
Slc     Slc_copy(Slc slc);
Slc     Slc_chop_front(Slc * slc, i64 size);
Slc     Slc_chop_all(Slc * slc);
Slc     Slc_chop_front_check(Slc * slc, i64 size);
Slc     Slc_chop_front_check_likely(Slc * slc, i64 size);

Putf_gen(View)
Swapf_gen(View)

View    View_init(void * ptr, i64 item_size, i64 len);
i64     View_len(View view);
i64     View_item_size(View view);
i64     View_size(View view);
bool    View_empty(View view);
void *  View_get(View view, i64 idx);
void *  View_first(View view);
void *  View_last(View view);
View    View_view(View view, i64 idx, i64 len);
View    View_view_from(View view, i64 idx);
i64     View_max_idx(View view, Cmpf cmp);
void    View_map(View view, F f);
void    View_fold(void * target, View view, Putf op);
i64     View_find(View view, const void * item, Cmpf cmp);

Putf_gen(Vec)
Swapf_gen(Vec)

Vec     Vec_new_capacity(i64 capacity, i64 item_size);
Vec     Vec_new_item_size(i64 item_size);
void    Vec_del(Vec * vec);
i64     Vec_len(Vec vec);
i64     Vec_capacity(Vec vec);
i64     Vec_allocated_size(Vec vec);
i64     Vec_max_idx(Vec vec, Cmpf cmp);
void *  Vec_get(Vec vec, i64 idx);
void *  Vec_first(Vec vec);
void *  Vec_last(Vec vec);
void *  Vec_pop(Vec * vec);
void    Vec_pushf(Vec * restrict vec, const void * restrict item, Putf put);
void    Vec_extend(Vec * vec, i64 len);
void    Vec_double(Vec * vec);
void    Vec_reserve(Vec * vec, i64 capacity);
void    Vec_map(Vec vec, F f);
void    Vec_fold(void * target, Vec vec, Putf op);
View    Vec_view(Vec vec, i64 idx, i64 len);
View    Vec_to_view(Vec vec);
i64     Vec_find(Vec vec, const void * item, Cmpf cmp);

#define Vec_new(type) Vec_new_item_size(sizeof(type))

#define Vec_push(vec_ptr, item, type) \
{ \
    if (unlikely(Vec_capacity(* vec_ptr) == 0)) Vec_double(vec_ptr); \
    deref(type) Vec_get((* vec_ptr), (vec_ptr)->idx ++) = item; \
}

#endif