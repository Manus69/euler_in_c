#include "i64.h"
#include <stdio.h>

void i64_dbg(i64 x)
{
    printf("%ld ", x);
}

void i64_dbgf(const void * ptr)
{
    i64_dbg(deref(i64) ptr);
}
