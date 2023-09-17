#ifndef HTBL_H
#define HTBL_H

#include "Vec.h"

typedef struct Htbl Htbl;

struct Htbl
{
    Vec *   buckets;
    i64     n_buckets;
    i64     item_size;
    i64     n_items;
};

Putf_gen(Htbl)
Swapf_gen(Htbl)

Htbl    Htbl_new_capacity(i64 capacity, i64 item_size);
void    Htbl_del(Htbl * htbl);
i64     Htbl_n_items(Htbl htbl);
i64     Htbl_density(Htbl htbl);
void *  Htbl_get_hashed(Htbl htbl, const void * item, u64 hash, Cmpf cmp);
void *  Htbl_get(Htbl htbl, const void * item, Cmpf cmp, Hashf hash);
bool    Htbl_contains_hashed(Htbl htbl, const void * item, u64 hash, Cmpf cmp);
bool    Htbl_contains(Htbl htbl, const void * item, Cmpf cmp, Hashf hash);
void    Htbl_resize(Htbl * htbl, i64 capacity, Putf put, Hashf hash);
void    Htbl_double_capacity(Htbl * htbl, Putf put, Hashf hash);
void    Htbl_insert_hashed(Htbl * restrict htbl, const void * restrict item, u64 hash, Putf put);
void    Htbl_insert(Htbl * restrict htbl, const void * restrict item, Putf put, Hashf hash);
void    Htbl_map(Htbl htbl, F f);

#endif