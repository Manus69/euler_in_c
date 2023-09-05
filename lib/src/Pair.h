#ifndef PAIR_H
#define PAIR_H

#include "def.h"

//this sucks dick
typedef struct Pair Pair;

struct Pair
{
    void *  data;
    i64     item_size;
};

Putf_gen(Pair)
Swapf_gen(Pair)

Pair    Pair_new_size(i64 first_size, i64 second_size);
void    Pair_del(Pair * pair);
void *  Pair_get(Pair pair, bool n);

#define Pair_set(pair, n, item, type) \
{deref(type) Pair_get(pair, n) = item;}

#define Pair_set_both(pair, left, second, l_type, r_type) \
{Pair_set(pair, 0, left, l_type); Pair_set(pair, 1, second, r_type);}

#define Pair_new_type(l_type, r_type)  Pair_new_size(sizeof(l_type), sizeof(r_type))

#define Pair_new(left, second, l_type, r_type) \
({ \
    Pair _p = Pair_new_type(l_type, r_type); \
    Pair_set_both(_p, left, second, l_type, r_type); \
    _p; \
})

#define Pair_struct_gen(l_type, r_type) \
typedef struct \
{ \
    l_type left; \
    r_type right; \
} Pair_ ## l_type ## _ ## r_type; \
Putf_gen(Pair_ ## l_type ## _ ## r_type) \
Swapf_gen(Pair_ ## l_type ## _ ## r_type)


#endif