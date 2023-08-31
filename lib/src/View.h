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

i64     View_size(View view);
void *  View_get(View view, i64 idx);
void    View_map(View view, F f);

#endif