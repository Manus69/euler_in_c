#include "regex_private.h"
#include <string.h>
#include <assert.h>

static inline void _skip_ws(StrSlc * slc)
{
    while (StrSlc_get_c(* slc, 0) == ' ') StrSlc_shift(slc, 1);
}

static inline bool _is_cnt_modifier(char x)
{
    return x == L_ZO || x == L_OM || x == L_NOT;
}

static inline RegexCNT _get_cnt(StrSlc * slc)
{
    char x;

    if (! _is_cnt_modifier((x = StrSlc_get_c(* slc, 0)))) return CNT_ONE;
    StrSlc_shift(slc, 1);

    if (x == L_NOT) return CNT_ZERO;
    if (x == L_ZO) return CNT_ZERO_OR_ONE;
    if (x == L_OM) return CNT_ONE_OR_MORE;

    assert(0);
}

static inline RegexToken _void(StrSlc * slc)
{
    StrSlc_shift(slc, 1);

    return (RegexToken) {.type = TT_VOID};
}

static inline RegexToken _star(StrSlc * slc)
{
    StrSlc_shift(slc, 1);

    return (RegexToken) {.type = TT_STAR};
}

static inline RegexToken _char(StrSlc * slc)
{
    RegexCNT cnt;

    StrSlc_shift(slc, 1);
    _skip_ws(slc);
    cnt = _get_cnt(slc);

    return (RegexToken) {.type = TT_CHAR, .count = cnt};
}

static inline RegexToken _word(StrSlc * slc)
{
    RegexCNT cnt;

    StrSlc_shift(slc, 1);
    _skip_ws(slc);
    cnt = _get_cnt(slc);

    return (RegexToken) {.type = TT_WORD, .count = cnt};
}

static inline RegexToken _str(StrSlc * slc)
{
    i64         len;
    StrSlc      literal;
    RegexCNT    cnt;

    StrSlc_shift(slc, 1);
    if ((len = StrSlc_find_c(* slc, L_QUOTE)) == NO_IDX) return (RegexToken) {.type = TT_BRICK};
    literal = StrSlc_slice(* slc, 0, len);
    StrSlc_shift(slc, len + 1);
    cnt = _get_cnt(slc);

    return (RegexToken) {.type = TT_STR, .count = cnt, .slc = literal};
}

static RegexToken _next(StrSlc * slc)
{
    char x;

    _skip_ws(slc);
    if (! StrSlc_len(* slc)) return (RegexToken) {.type = TT_VOID};

    x = StrSlc_get_c(* slc, 0);
    if (x == L_STAR) return _star(slc);
    if (x == L_CHAR) return _char(slc);
    if (x == L_QUOTE) return _str(slc);
    if (x == L_WORD) return _word(slc);
    
    return (RegexToken) {.type = TT_BRICK};
}

Vec Regex_compile_StrSlc(StrSlc slc)
{
    Vec         tokens;
    RegexToken  token;

    tokens = Vec_new(RegexToken);
    while (true)
    {
        if ((token = _next(& slc)).type == TT_VOID) break;

    }

    return tokens;
}

Vec Regex_compile_cstr_len(const byte * cstr, i64 len)
{

}

Vec Regex_compile_cstr(const byte * cstr)
{
    return Regex_compile_cstr_len(cstr, strlen(cstr));
}
