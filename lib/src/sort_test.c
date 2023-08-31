#include "sort_test.h"

void sort_view_TYPE(View view)
{
    TYPE  buffer;
    i64   current;

    for (i64 sorted = 1; sorted < View_len(view); sorted ++)
    {
        buffer = deref(TYPE) View_get(view, sorted);
        for (current = sorted - 1; current >= 0; current --)
        {
            if (TYPE_cmp(& buffer, View_get(view, current)) >= 0) break;
            TYPE_set(View_get(view, current + 1), View_get(view, current));
        }

        current ++;
        TYPE_set(View_get(view, current), & buffer);
    }
}