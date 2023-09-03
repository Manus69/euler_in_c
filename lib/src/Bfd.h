#ifndef BFD_H
#define BFD_H

#include "def.h"

typedef struct Bfd Bfd;

struct Bfd
{
    u64 *   field;
    i64     len;
};

#endif