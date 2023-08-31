#include "sort.h"
#include "mem.h"

#include <string.h>

void sort_insert_view(View view, Cmp cmp)
{
    void *  buffer;
    i64     current;

    buffer = mem_alloc0(View_item_size(view));
    for (i64 sorted = 1; sorted < View_len(view); sorted ++)
    {
        memcpy(buffer, View_get(view, sorted), View_item_size(view));
        for (current = sorted - 1; current >= 0; current --)
        {
            if (cmp(buffer, View_get(view, current)) >= 0) break;
            memcpy(View_get(view, current + 1), View_get(view, current), View_item_size(view));
        }

        current ++;
        memcpy(View_get(view, current), buffer, View_item_size(view));
    }

    mem_del(buffer);
}
