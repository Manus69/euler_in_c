#ifndef SORT_H
#define SORT_H

#include "View.h"

#define sort_insert(view, type) \
sort_insert_f(view, type ## _putf, type ## _cmpf)

#define sort_quick(view, type) \
sort_quick_f(view, type ## _putf, type ## _swapf, type ## _cmpf)

void sort_insert_f(View view, Putf put, Cmpf cmp);
void sort_quick_f(View view, Putf put, Swapf swap, Cmpf cmp);

#endif