#ifndef RNG_H
#define RNG_H

#include "def.h"

u32 rng_spcg_next(u64 * state);
u64 rng_xor_next(u64 * state);

#endif