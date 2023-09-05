#include "Pair.h"
#include "mem.h"
#include <stdio.h>

Pair Pair_new_size(i64 first_size, i64 second_size)
{
    i64 size;

    size = max(first_size, second_size);
    return (Pair)
    {
        .data = mem_alloc0(size * 2),
        .item_size = size,
    };
}

void Pair_del(Pair * pair)
{
    mem_del(pair->data);
    to0(pair, Pair);
}

void * Pair_get(Pair pair, bool n)
{
    return pair.data + n * pair.item_size;
}
