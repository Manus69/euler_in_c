#include "Vec.h"
#include "mem.h"
#include "View.h"

#define VEC_DC (1 << 4)

Vec Vec_new_capacity(i64 capacity, i64 item_size)
{
    return (Vec)
    {
        .data = mem_alloc0(capacity * item_size),
        .item_size = item_size,
        .idx = 0,
        .capacity = capacity,
    };
}

Vec Vec_new_item_size(i64 item_size)
{
    return Vec_new_capacity(VEC_DC, item_size);
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

i64 Vec_capacity(Vec vec)
{
    return vec.capacity - vec.idx;
}

i64 Vec_allocated_size(Vec vec)
{
    return vec.capacity * vec.item_size;
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
    return Vec_get(* vec, -- vec->idx);
}

void Vec_extend(Vec * vec, i64 len)
{
    mem_extend(& vec->data, Vec_allocated_size(* vec), len * vec->item_size);
    vec->capacity += len;
}

void Vec_double(Vec * vec)
{
    Vec_extend(vec, vec->capacity);
}

void Vec_reserve(Vec * vec, i64 capacity)
{
    if (Vec_capacity(* vec) < capacity) Vec_extend(vec, capacity);
}

View Vec_view(Vec vec, i64 idx, i64 len)
{
    return View_init(Vec_get(vec, idx), vec.item_size, len);
}

View Vec_to_view(Vec vec)
{
    return Vec_view(vec, 0, vec.idx);
}

i64 Vec_max_idx(Vec vec, Cmpf cmp)
{
    return View_max_idx(Vec_to_view(vec), cmp);
}

void Vec_map(Vec vec, F f)
{
    View_map(Vec_to_view(vec), f);
}

void Vec_fold(void * target, Vec vec, Putf op)
{
    View_fold(target, Vec_to_view(vec), op);
}