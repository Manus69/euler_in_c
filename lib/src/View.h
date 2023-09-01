#ifndef VIEW_H
#define VIEW_H

#include "def.h"

typedef struct View View;

struct View
{
    void *  ptr;
    i64     item_size;
    i64     len;  
};

View    View_init(void * ptr, i64 item_size, i64 len);
i64     View_len(View view);
i64     View_item_size(View view);
i64     View_size(View view);
void *  View_get(View view, i64 idx);
void *  View_first(View view);
void *  View_last(View view);
void    View_map(View view, F f);
View    View_view(View view, i64 idx, i64 len);
View    View_to_View(View view);
View    View_view_from(View view, i64 idx);

#endif