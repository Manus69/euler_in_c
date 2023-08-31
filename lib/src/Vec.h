#ifndef VEC_H
#define VEC_H

#include "def.h"
#include "macro.h"

#define Vec_new(type) Vec_new_item_size(sizeof(type))

typedef struct Vec Vec;

struct Vec
{
    void *  data;
    i64     item_size;
    i64     idx;
    i64     size_in_items;
};

Vec     Vec_own(void * data, i64 item_size, i64 data_size);
Vec     Vec_new_n_items(i64 item_size, i64 n_items);
void    Vec_shift_idx(Vec * vec, i64 shift);
void    Vec_del(Vec * vec);
Vec     Vec_new_item_size(i64 item_size);
i64     Vec_len(Vec vec);
i64     Vec_len_in_bytes(Vec vec);
i64     Vec_capacity(Vec vec);
void *  Vec_get(Vec vec, i64 idx);
void *  Vec_first(Vec vec);
void *  Vec_last(Vec vec);
void *  Vec_pop(Vec * vec);
void *  Vec_pop_all(Vec * vec);
void    Vec_extend(Vec * vec, i64 len);
void    Vec_double_capacity(Vec * vec);
void    Vec_reserve(Vec * vec, i64 len);
void    Vec_push_many(Vec * vec, const void * src, i64 len);

#define Vec_set(vec, idx, item, type) (deref(type) Vec_get(vec, idx) = item)
#define Vec_push(vec_ptr, item, type) \
{ \
    if (unlikely(Vec_capacity(* (vec_ptr)) == 0)) Vec_double_capacity(vec_ptr); \
    Vec_set(* (vec_ptr), (vec_ptr)->idx ++, item, type); \
}

#endif