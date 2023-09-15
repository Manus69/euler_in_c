#ifndef HTBL_H
#define HTBL_H

#include "Vec.h"

typedef struct Htbl Htbl;

struct Htbl
{
    Vec *   buckets;
    i64     item_size;
    i64     n_buckets;
};

#endif