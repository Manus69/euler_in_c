#include "Htbl.h"
#include "math.h"
#include "mem.h"
#include <stdlib.h>

#define HTBL_DC                 (1 << 5)
#define HTBL_BUCKET_DC          (1 << 2)
#define HTBL_DENSITY_THRESHOLD  (1 << 2)

static void _init_buckets(Vec * buckets, i64 n_buckets, i64 item_size)
{
    for (i64 k = 0; k < n_buckets; k ++)
    {
        buckets[k] = Vec_new_capacity(HTBL_BUCKET_DC, item_size);
    }
}

Htbl Htbl_new_capacity(i64 capacity, i64 item_size)
{
    Vec * buckets;

    capacity = is_pow2(capacity) ? capacity : (i64) next_pow2(capacity);

    buckets = mem_alloc0(sizeof(Vec) * capacity);
    _init_buckets(buckets, capacity, item_size);

    return (Htbl)
    {
        .buckets = buckets,
        .n_buckets = capacity,
        .item_size = item_size,
        .n_items = 0,
    };
}

void Htbl_del(Htbl * htbl)
{
    mem_raw_map((F) Vec_del, htbl->buckets, htbl->n_buckets * sizeof(Vec), sizeof(Vec));
    mem_del(htbl->buckets);
    to0(htbl, Htbl);
}

i64 Htbl_n_items(Htbl htbl)
{
    return htbl.n_items;
}

i64 Htbl_density(Htbl htbl)
{
    return htbl.n_items / htbl.n_buckets;
}

void * Htbl_get_hashed(Htbl htbl, const void * item, u64 hash, Cmpf cmp)
{
    i64 idx;

    idx = Vec_find(htbl.buckets[hash % htbl.n_buckets], item, cmp);

    return idx == NO_IDX ? NULL : Vec_get(htbl.buckets[hash % htbl.n_buckets], idx);
}

void * Htbl_get(Htbl htbl, const void * item, Cmpf cmp, Hashf hash)
{
    return Htbl_get_hashed(htbl, item, hash(item), cmp);
}

bool Htbl_contains_hashed(Htbl htbl, const void * item, u64 hash, Cmpf cmp)
{
    return Htbl_get_hashed(htbl, item, hash, cmp);
}

bool Htbl_contains(Htbl htbl, const void * item, Cmpf cmp, Hashf hash)
{
    return Htbl_get(htbl, item, cmp, hash);
}

static void _rehash_bucket(Htbl * htbl, Vec bucket, Putf put, Hashf hash)
{
    for (i64 k = 0; k < Vec_len(bucket); k ++)
    {
        Htbl_insert(htbl, Vec_get(bucket, k), put, hash);
    }
}

static void _resize(Htbl * htbl, i64 n_buckets, Putf put, Hashf hash)
{
    Htbl new_table;

    new_table = Htbl_new_capacity(htbl->item_size, n_buckets);
    for (i64 k = 0; k < htbl->n_buckets; k ++)
    {
        _rehash_bucket(& new_table, htbl->buckets[k], put, hash);
    }

    Htbl_del(htbl);
    * htbl = new_table;
}

void Htbl_resize(Htbl * htbl, i64 capacity, Putf put, Hashf hash)
{
    _resize(htbl, capacity, put, hash);
}

void Htbl_double_capacity(Htbl * htbl, Putf put, Hashf hash)
{
    _resize(htbl, htbl->n_buckets * 2, put, hash);
}

static void _insert(Htbl * restrict htbl, const void * restrict item, u64 hash, Putf put)
{
    i64 idx;

    idx = hash % htbl->n_buckets;
    Vec_pushf(htbl->buckets + idx, item, put);
    htbl->n_items ++;
}

void Htbl_insert_hashed(Htbl * restrict htbl, const void * restrict item, u64 hash, Putf put)
{
    _insert(htbl, item, hash, put);
}

void Htbl_insert(Htbl * restrict htbl, const void * restrict item, Putf put, Hashf hash)
{
    Htbl_insert_hashed(htbl, item, hash(item), put);
}

void Htbl_map(Htbl htbl, F f)
{
    for (i64 k = 0; k < htbl.n_buckets; k ++)
    {
        Vec_map(htbl.buckets[k], f);
    }
}