#ifndef SET_H
#define SET_H

#include "Htbl.h"

#define Set_new(type) Set_new_item_size(sizeof(type))

typedef struct Set Set;

struct Set
{
    Htbl htbl;
};

Put_gen(Set)
Swap_gen(Set)

Set     Set_new_capacity(i64 capacity, i64 item_size);
Set     Set_new_item_size(i64 item_size);
void    Set_del(Set * set);
i64     Set_size(Set set);
void *  Set_get_hashed(Set set, const void * item, u64 hash, Cmpf cmp);
void *  Set_get(Set set, const void * item, Cmpf cmp, Hashf hash);
bool    Set_contains_hashed(Set set, const void * item, u64 hash, Cmpf cmp);
bool    Set_contains(Set set, const void * item, Cmpf cmp, Hashf hash);
STATUS  Set_include(Set * restrict set, const void * restrict item, Putf put, Cmpf cmp, Hashf hash);
void    Set_map(Set set, F f);

#endif