#include "Bfd.h"
#include "mem.h"
#include "macro.h"

static inline i64 _index(i64 bit)
{
    return bit / sizeof(u64);
}

