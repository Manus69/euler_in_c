#ifndef PAIR_H
#define PAIR_H

#include "def.h"

typedef struct Pair Pair;

struct Pair
{
    void *  data;
    i64     item_size;
};

#endif