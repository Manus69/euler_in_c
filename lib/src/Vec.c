#include "Vec.h"
#include "mem.h"
#include "math.h"

#include <string.h>

#define VEC_DC (1 << 4)

Vec Vec_own(void * data, i64 item_size, i64 data_size)
{
    return (Vec)
    {
        .data = data,
        .idx = 0,
        .item_size = item_size,
        .size_in_items = data_size / item_size,
    };
}

Vec Vec_new_n_items(i64 item_size, i64 n_items)
{
    return Vec_own(mem_alloc0(n_items * item_size), item_size, n_items * item_size);
}

void Vec_shift_idx(Vec * vec, i64 shift)
{
    vec->idx += shift;
}

Vec Vec_new_item_size(i64 item_size)
{
    return Vec_new_n_items(item_size, VEC_DC);
}

void Vec_del(Vec * vec)
{
    mem_del(vec->data);
    to0(vec, Vec);
}

i64 Vec_len(Vec vec)
{
    return vec.idx;
}

i64 Vec_len_in_bytes(Vec vec)
{
    return vec.idx * vec.item_size;
}

i64 Vec_capacity(Vec vec)
{
    return vec.size_in_items - vec.idx;
}

void * Vec_get(Vec vec, i64 idx)
{
    return vec.data + idx * vec.item_size;
}

void * Vec_first(Vec vec)
{
    return vec.data;
}

void * Vec_last(Vec vec)
{
    return Vec_get(vec, vec.idx - 1);
}

void * Vec_pop(Vec * vec)
{
    Vec_shift_idx(vec, -1);

    return Vec_get(* vec, vec->idx);
}

void * Vec_pop_all(Vec * vec)
{
    vec->idx = 0;

    return vec->data;
}

void Vec_extend(Vec * vec, i64 len)
{
    mem_extend((void **) & vec->data, vec->size_in_items * vec->item_size, len * vec->item_size);
    vec->size_in_items += len;
}

void Vec_double_capacity(Vec * vec)
{
    Vec_extend(vec, vec->size_in_items);
}

void Vec_reserve(Vec * vec, i64 len)
{
    if (Vec_capacity(* vec) < len) Vec_extend(vec, len);
}

void Vec_push_many(Vec * vec, const void * src, i64 len)
{
    Vec_reserve(vec, len);
    memcpy(Vec_get(* vec, vec->idx), src, len * vec->item_size);
    vec->idx += len;
}