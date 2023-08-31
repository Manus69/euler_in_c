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

void View_map(View view, F f)
{
    mem_raw_map(f, view.ptr, View_size(view), view.item_size);
}