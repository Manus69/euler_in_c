#include "Set.h"
#include "Pair.h"
#include <stdlib.h>

#define SET_DC                  (1 << 4)
#define SET_DENSITY_THRESHOLD   (1 << 2)

Set Set_new_capacity(i64 capacity, i64 item_size)
{
    return (Set) {.htbl = Htbl_new_capacity(capacity, item_size)};
}

Set Set_new_item_size(i64 item_size)
{
    return Set_new_capacity(SET_DC, item_size);
}

void Set_del(Set * set)
{
    Htbl_del(& set->htbl);
}

i64 Set_size(Set set)
{
    return Htbl_n_items(set.htbl);
}

void * Set_get_hashed(Set set, const void * item, u64 hash, Cmpf cmp)
{
    return Htbl_get_hashed(set.htbl, item, hash, cmp);
}

void * Set_get(Set set, const void * item, Cmpf cmp, Hashf hash)
{
    return Set_get_hashed(set, item, hash(item), cmp);
}

bool Set_contains_hashed(Set set, const void * item, u64 hash, Cmpf cmp)
{
    return Set_get_hashed(set, item, hash, cmp);
}

bool Set_contains(Set set, const void * item, Cmpf cmp, Hashf hash)
{
    return Set_contains_hashed(set, item, hash(item), cmp);
}

STATUS Set_include(Set * restrict set, const void * restrict item, Putf put, Cmpf cmp, Hashf hash)
{
    u64 hash_val;

    hash_val = hash(item);
    if (! Set_contains_hashed(* set, item, hash_val, cmp))
    {
        if (unlikely(Htbl_density(set->htbl) > SET_DENSITY_THRESHOLD))
            Htbl_double_capacity(& set->htbl, put, hash);
        
        Htbl_insert_hashed(& set->htbl, item, hash_val, put);

        return STATUS_DONE;
    }

    return STATUS_NOT_DONE;
}

void Set_map(Set set, F f)
{
    Htbl_map(set.htbl, f);
}