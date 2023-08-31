#ifndef MATH_H
#define MATH_H

#include "def.h"

#define max(x, y)   ({typeof(x) _x = x; typeof(y) = _y; _x > _y ? _x : _y;})
#define min(x, y)   ({typeof(x) _x = x; typeof(y) = _y; _x < _y ? _x : _y;})

__attribute__((const))
u64 math_next_pow2(u64 x);

#endif