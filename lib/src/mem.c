#include "mem.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

void * mem_alloc0(i64 size)
{
    void * ptr;

    ptr = calloc(size, 1);
    assert(ptr);

    return ptr;
}

void mem_del(void * ptr)
{
    free(ptr);
}

void mem_extend_to_size(void ** ptr, i64 size, i64 new_size)
{
    (void) size;
    * ptr = realloc(* ptr, new_size);
    assert(* ptr);
}

void mem_extend(void ** ptr, i64 size, i64 extra_size)
{
    mem_extend_to_size(ptr, size, size + extra_size);
}

void mem_extend0(void ** ptr, i64 size, i64 extra_size)
{
    mem_extend(ptr, size, extra_size);
    memset(* ptr + size, 0, extra_size);
}

void mem_extend_to_size0(void ** ptr, i64 size, i64 new_size)
{
    mem_extend0(ptr, size, new_size - size);
}

void mem_arr_map(void (* f)(void *), void * arr[])
{
    void * current;

    while ((current = * arr ++)) f(current);
}

void mem_raw_map(void (* f)(void *), void * data, i64 size, i64 step)
{
    while (size > 0)
    {
        f(data);
        data += step;
        size -= step;
    }
}

void * mem_dup(const void * ptr, i64 size)
{
    return memcpy(mem_alloc0(size), ptr, size);
}
