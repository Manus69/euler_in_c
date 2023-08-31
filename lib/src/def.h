#ifndef DEF_H
#define DEF_H

#include <stdint.h>

#define NO_IDX          (-1)


typedef enum STATUS     STATUS;
typedef int_fast64_t    i64;
typedef uint_fast64_t   u64;
typedef char            byte;
typedef void            (* F)(void *);
typedef i64             (* Cmp)(const void *, const void *);
typedef byte *          cstr_pair[2];

enum STATUS
{
    STATUS_OK,
    STATUS_NOT_OK,
};

#endif