#ifndef BYTE_H
#define BYTE_H

#include "def.h"

Swap_gen(byte)
Cmp_gen(byte)

bool byte_is_numeric(byte x);
bool byte_is_lower(byte x);
bool byte_is_upper(byte x);
bool byte_is_alpha(byte x);
bool byte_is_ws(byte x);
byte byte_to_lower(byte x);
byte byte_to_lower_check(byte x);

#endif