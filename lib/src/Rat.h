#ifndef RAT_H
#define RAT_H

#include "def.h"

typedef struct Rat Rat;

struct Rat
{
    i64 top;
    u64 bot;
};

Swap_gen(Rat)
Put_gen(Rat)

#endif