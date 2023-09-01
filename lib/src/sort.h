#ifndef SORT_H
#define SORT_H

#include "View.h"

#define sort_insert(view, type) \
sort_insert_f(view, (Putf) type ## _put, (Cmpf) type ## _cmp)

#define sort_quick(view, type) \
sort_quick_f(view, (Putf) type ## _put, (Swapf) type ## _swap, (Cmpf) type ## _cmp)

void sort_insert_f(View view, Putf put, Cmpf cmp);
void sort_quick_f(View view, Putf put, Swapf swap, Cmpf cmp);

#endif