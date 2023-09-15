#include "Htbl.h"
#include "math.h"
#include "mem.h"
#include <stdlib.h>

#define HTBL_DC                 (1 << 5)
#define HTBL_BUCKET_DC          (1 << 2)
#define HTBL_DENSITY_THRESHOLD  (1 << 2)

Htbl Htbl_new_capacity(i64 item_size, i64 capacity)
{
    capacity = is_pow2(capacity) ? capacity : (i64) next_pow2(capacity);

    return (Htbl)
    {
        .buckets = mem_alloc0(sizeof(Vec) * capacity),
        .item_size = item_size,
        .n_buckets = capacity,
    };
}

static void _del(void * ptr)
{
    if (ptr) Vec_del(ptr);
}

void Htbl_del(Htbl * htbl)
{
    mem_raw_map(_del, htbl->buckets, htbl->n_buckets * sizeof(Vec), sizeof(Vec));
    mem_del(htbl->buckets);
    to0(htbl, Htbl);
}

Vec * Htbl_bucket(Htbl htbl, i64 idx)
{
    return htbl.buckets + idx;
}

static inline i64 _idx(const void * item, i64 len, Hashf hash)
{
    return hash(item) % len;
}

void * Htbl_get(Htbl htbl, const void * item, Cmpf cmp, Hashf hash)
{
    Vec *   bucket;
    i64     idx;

    if ((bucket = Htbl_bucket(htbl, _idx(item, htbl.n_buckets, hash))) == NULL) return NULL;
    if ((idx = Vec_find(* bucket, item, cmp)) == NO_IDX) return NULL;

    return Vec_get(* bucket, idx);
}

bool Htbl_contains(Htbl htbl, const void * item, Cmpf cmp, Hashf hash)
{
    return Htbl_get(htbl, item, cmp, hash);
}

void Htbl_insert(Htbl htbl, const void * item, Putf put, Hashf hash)
{
    i64     idx;
    Vec *   bucket;

    idx = _idx(item, htbl.n_buckets, hash);
    if (! (bucket = Htbl_bucket(htbl, idx)))
    {
        htbl.buckets[idx] = Vec_new_capacity(HTBL_BUCKET_DC, htbl.item_size);
        bucket = htbl.buckets + idx;
    }

    Vec_pushf(bucket, item, put);
}

