#ifndef REGEX_H
#define REGEX_H

#include "def.h"

//to do
//keywords:
// star : *
// any char 0 or 1 : . ?
// any char 1 : .
// any char 1 or many : . +
// word : w
// digit : d
// space : s
// literal : ''
// or : |
// starts ? ends?

//'static'! w + . '(' * ')'

typedef struct RegexMatch RegexMatch;

struct RegexMatch
{
    i64 idx;
    i64 len;
};


#endif