#ifndef DEF_H
#define DEF_H

#include <stdint.h>

#define NO_IDX          (-1)

#define Putf_gen(type) \
static inline void type ## _put(type * target, const type * src) \
{* target = * src;}

#define Swapf_gen(type) \
static inline void type ## _swap(type * lhs, type * rhs) \
{type _t = * lhs; * lhs = * rhs; * rhs = _t;}

typedef enum STATUS     STATUS;
typedef int_fast64_t    i64;
typedef uint_fast64_t   u64;
typedef char            byte;
typedef void            (* F)(void *);
typedef void            (* Putf)(void *, const void *);
typedef void            (* Swapf)(void *, void *);
typedef i64             (* Cmpf)(const void *, const void *);

enum STATUS
{
    STATUS_OK,
    STATUS_NOT_OK,
};

#endif