#ifndef VEC_H
#define VEC_H

#include "def.h"
#include "macro.h"
#include "View.h"

#define Vec_new(type) Vec_new_item_size(sizeof(type))

typedef struct Vec Vec;

struct Vec
{
    void *  data;
    i64     item_size;
    i64     idx;
    i64     capacity;
};

Putf_gen(Vec)
Swapf_gen(Vec)

Vec     Vec_new_capacity(i64 capacity, i64 item_size);
Vec     Vec_new_item_size(i64 item_size);
void    Vec_del(Vec * vec);
i64     Vec_len(Vec vec);
i64     Vec_capacity(Vec vec);
i64     Vec_allocated_size(Vec vec);
void *  Vec_get(Vec vec, i64 idx);
void *  Vec_first(Vec vec);
void *  Vec_last(Vec vec);
void    Vec_extend(Vec * vec, i64 len);
void    Vec_double(Vec * vec);
void    Vec_map(Vec vec, F f);
void    Vec_fold(void * target, Vec vec, Putf op);
View    Vec_view(Vec vec, i64 idx, i64 len);
View    Vec_to_view(Vec vec);

#define Vec_push(vec_ptr, item, type) \
{ \
    if (unlikely(Vec_capacity(* vec_ptr) == 0)) Vec_double(vec_ptr); \
    deref(type) Vec_get((* vec_ptr), (vec_ptr)->idx ++) = item; \
}

#endif