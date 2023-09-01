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

i64 View_item_size(View view)
{
    return view.item_size;
}

i64 View_size(View view)
{
    return view.len * view.item_size;
}

i64 View_len(View view)
{
    return view.len;
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

void View_map(View view, F f)
{
    mem_raw_map(f, view.ptr, View_size(view), view.item_size);
}

View View_view(View view, i64 idx, i64 len)
{
    return View_init(View_get(view, idx), view.item_size, len);
}

View View_to_View(View view)
{
    return View_init(view.ptr, view.item_size, view.len);
}

View View_view_from(View view, i64 idx)
{
    return View_init(View_get(view, idx), view.item_size, View_len(view) - idx);
}