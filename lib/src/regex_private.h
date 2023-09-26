#ifndef REGEX_PRIVATE_H
#define REGEX_PRIVATE_H

#include "regex.h"

#define L_STAR  '*'
#define L_CHAR  '.'
#define L_QUOTE '\''
#define L_DGT   'd'
#define L_WS    's'
#define L_WORD  'w'
#define L_ZO    '?'
#define L_OM    '+'
#define L_NOT   '!'

typedef enum    RegexCNT         RegexCNT;
typedef enum    RegexTT          RegexTT;
typedef struct  RegexToken       RegexToken;

enum RegexCNT
{
    CNT_ZERO,
    CNT_ZERO_OR_ONE,
    CNT_ONE,
    CNT_ONE_OR_MORE,
};

enum RegexTT
{
    TT_VOID,
    TT_BRICK,
    TT_STAR,
    TT_CHAR,
    TT_ALPHA,
    TT_DIGIT,
    TT_SPACE,
    TT_WORD,
    TT_STR,
};

struct RegexToken
{
    RegexTT     type;
    RegexCNT    count;

    union
    {
        StrSlc slc;
    };
};

#endif