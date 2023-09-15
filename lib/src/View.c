#include "View.h"
#include "mem.h"

View View_init(void * ptr, i64 item_size, i64 len)
{
    return (View)
    {
        .ptr = ptr,
        .item_size = item_size,
        .len = len,
    };
}

i64 View_len(View view)
{
    return view.len;
}

i64 View_item_size(View view)
{
    return view.item_size;
}

i64 View_size(View view)
{
    return view.len * view.item_size;
}

bool View_empty(View view)
{
    return view.len == 0;
}

void * View_get(View view, i64 idx)
{
    return view.ptr + idx * view.item_size;
}

void * View_first(View view)
{
    return view.ptr;
}

void * View_last(View view)
{
    return View_get(view, view.len - 1);
}

View View_view(View view, i64 idx, i64 len)
{
    return View_init(View_get(view, idx), view.item_size, len);
}

View View_view_from(View view, i64 idx)
{
    return View_view(view, idx, view.len - idx);
}

i64 View_max_idx(View view, Cmpf cmp)
{
    i64 max_idx;

    max_idx = 0;
    for (i64 k = 1; k < view.len; k ++)
    {
        if (cmp(View_get(view, k), View_get(view, max_idx)) > 0) max_idx = k;
    }

    return max_idx;
}

void View_map(View view, F f)
{
    mem_raw_map(f, view.ptr, View_size(view), view.item_size);
}

void View_fold(void * target, View view, Putf op)
{
    mem_raw_fold(target, View_first(view), op, View_size(view), view.item_size);
}

i64 View_find(View view, const void * item, Cmpf cmp)
{
    for (i64 k = 0; k < View_len(view); k ++)
    {
        if (cmp(View_get(view, k), item) == 0) return k;
    }

    return NO_IDX;
}