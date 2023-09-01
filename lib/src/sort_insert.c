#include "sort.h"
#include "mem.h"

void sort_insert_f(View view, Putf put, Cmpf cmp)
{
    void *  buffer;
    i64     current;

    buffer = mem_alloc0(View_item_size(view));
    for (i64 sorted = 1; sorted < View_len(view); sorted ++)
    {
        put(buffer, View_get(view, sorted));
        for (current = sorted - 1; current >= 0; current --)
        {
            if (cmp(buffer, View_get(view, current)) >= 0) break;
            put(View_get(view, current + 1), View_get(view, current));
        }

        current ++;
        put(View_get(view, current), buffer);
    }

    mem_del(buffer);
}
