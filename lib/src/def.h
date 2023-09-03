#ifndef DEF_H
#define DEF_H

#include <stdint.h>
#include "macro.h"

#define NO_IDX          (-1)

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