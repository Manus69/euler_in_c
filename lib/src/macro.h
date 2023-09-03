#ifndef MACRO_H
#define MACRO_H

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
{type _t = deref(type) lhs; deref(type) lhs = deref(type) rhs; deref(type) rhs = _t;}

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


#endif