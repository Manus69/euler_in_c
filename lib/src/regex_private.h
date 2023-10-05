#ifndef REGEX_PRIVATE_H
#define REGEX_PRIVATE_H

#include "regex.h"

#define L_STAR  '*'
#define L_CHAR  '.'
#define L_STRL  '\''
#define L_STRR  L_STRL
#define L_CIL   '<'
#define L_CIR   '>'
#define L_DGT   'd'
#define L_ALPH  'a'
#define L_WS    's'
#define L_NLT   '$'
#define L_LSTRT '^'
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
    TT_END,
    TT_START,
    TT_WORD,
    TT_STR,
    TT_STR_CI,
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