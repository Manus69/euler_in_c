#include "sort.h"
#include <stdlib.h>

#define LEN_LIMIT (1 << 5)

static inline i64 _pick_pivot_idx(View view)
{
    return rand() % View_len(view);
}

static i64 _partition(View view, Swapf swap, Cmpf cmp)
{
    void *  pivot;
    i64     pivot_idx;

    pivot = View_last(view);
    pivot_idx = _pick_pivot_idx(view);
    swap(pivot, View_get(view, pivot_idx));
    pivot_idx = -1;

    for (i64 current = 0; current < View_len(view); current ++)
    {
        if (cmp(View_get(view, current), pivot) < 0)
        {
            pivot_idx ++;
            swap(View_get(view, current), View_get(view, pivot_idx));
        }
    }

    pivot_idx ++;
    swap(View_get(view, pivot_idx), pivot);

    return pivot_idx;
}


void sort_quick_f(View view, Putf put, Swapf swap, Cmpf cmp)
{
    i64 pivot_idx;

    if (View_len(view) < LEN_LIMIT) return sort_insert_f(view, put, cmp);

    pivot_idx = _partition(view, swap, cmp);

    sort_quick_f(View_view(view, 0, pivot_idx), put, swap, cmp);
    sort_quick_f(View_view_from(view, pivot_idx + 1), put, swap, cmp);
}