#ifndef PTR_H
#define PTR_H

#include "def.h"

typedef struct Ptr Ptr;

struct Ptr
{
    void *  ptr;
    i64     size;
};

#endif