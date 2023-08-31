#ifndef MEM_H
#define MEM_H

#include "def.h"

#define mem_vmap(f, ...) mem_arr_map(f, (void * []){__VA_ARGS__, NULL})

void *  mem_alloc0(i64 size);
void *  mem_dup(const void * ptr, i64 size);
void    mem_del(void * ptr);
void    mem_extend_to_size(void ** ptr, i64 size, i64 new_size);
void    mem_extend(void ** ptr, i64 size, i64 extra_size);
void    mem_extend0(void ** ptr, i64 size, i64 extra_size);
void    mem_extend_to_size0(void ** ptr, i64 size, i64 new_size);
void    mem_arr_map(void (* f)(void *), void * arr[]);
void    mem_raw_map(void (* f)(void *), void * data, i64 size, i64 step);

#endif