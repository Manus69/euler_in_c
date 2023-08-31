#include "View.h"
#include "mem.h"

i64 View_size(View view)
{
    return view.len * view.item_size;
}

void * View_get(View view, i64 idx)
{
    return view.ptr + idx * view.item_size;
}

void View_map(View view, F f)
{
    mem_raw_map(f, view.ptr, View_size(view), view.item_size);
}