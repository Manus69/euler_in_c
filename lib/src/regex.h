#ifndef REGEX_H
#define REGEX_H

#include "def.h"
#include "Vec.h"
#include "Str.h"

//'static'! w + . '(' * ')'

typedef struct RegexMatch       RegexMatch;
typedef struct RegexParseResult RegexParseResult;

struct RegexMatch
{
    i64 idx;
    i64 len;
};

struct RegexParseResult
{
    Vec     tokens;
    STATUS  status;
};

void                RegexParseResult_del(RegexParseResult * rpr);
RegexParseResult    Regex_compile_StrSlc(StrSlc slc);
RegexParseResult    Regex_compile_cstr_len(const byte * cstr, i64 len);
RegexParseResult    Regex_compile_cstr(const byte * cstr);
RegexMatch          Regex_match_slice(StrSlc slc, RegexParseResult rpr);
RegexMatch          Regex_match_cstr_len(const byte * cstr, i64 len, RegexParseResult rpr);
RegexMatch          Regex_match_cstr(const byte * cstr, RegexParseResult rpr);
RegexMatch          Regex_match_slice_pattern(StrSlc slc, const byte * pattern);
RegexMatch          Regex_match_cstr_pattern(const byte * restrict cstr, const byte * pattern);
RegexMatch          Regex_match_Str_pattern(Str str, const byte * pattern);

#endif