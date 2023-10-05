#include "regex_private.h"
#include "byte.h"
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

    return CNT_ONE;
}

static inline RegexToken _get_token(StrSlc * slc, RegexTT type)
{
    StrSlc_shift(slc, 1);

    return (RegexToken) {.type = type};
}

static inline RegexToken _get_token_cnt(StrSlc * slc, RegexTT type)
{
    RegexToken  token;

    token = _get_token(slc, type);
    _skip_ws(slc);
    token.count = _get_cnt(slc);

    return token;
}

static inline RegexToken _void(StrSlc * slc)
{
    return _get_token(slc, TT_VOID);
}

static inline RegexToken _star(StrSlc * slc)
{
    return _get_token(slc, TT_STAR);
}

static inline RegexToken _nlt(StrSlc * slc)
{
    return _get_token(slc, TT_END);
}

static inline RegexToken _lstart(StrSlc * slc)
{
    return _get_token(slc, TT_START);
}

static inline RegexToken _char(StrSlc * slc)
{
    return _get_token_cnt(slc, TT_CHAR);
}

static inline RegexToken _alpha(StrSlc * slc)
{
    return _get_token_cnt(slc, TT_ALPHA);
}

static inline RegexToken _word(StrSlc * slc)
{
    return _get_token_cnt(slc, TT_WORD);
}

static inline RegexToken _digit(StrSlc * slc)
{
    return _get_token_cnt(slc, TT_DIGIT);
}

static inline RegexToken _str(StrSlc * slc)
{
    byte        ob;
    StrSlc      literal;
    RegexCNT    cnt;
    RegexTT     type;

    ob = StrSlc_get_c(* slc, 0);
    literal = StrSlc_in_brackets(* slc, ob, byte_matching_bracket(ob));

    if (StrSlc_is_brick(literal)) return (RegexToken) {.type = TT_BRICK};
    StrSlc_shift(slc, StrSlc_len(literal) + 2);
    type = ob == L_STRL ? TT_STR : TT_STR_CI;

    _skip_ws(slc);
    cnt = _get_cnt(slc);

    return (RegexToken) {.type = type, .count = cnt, .slc = literal};
}

static RegexToken _next(StrSlc * slc)
{
    char x;

    _skip_ws(slc);
    if (! StrSlc_len(* slc)) return (RegexToken) {.type = TT_VOID};

    x = StrSlc_get_c(* slc, 0);
    if (x == L_STAR) return _star(slc);
    if (x == L_STRL) return _str(slc);
    if (x == L_CIL) return _str(slc);
    if (x == L_CHAR) return _char(slc);
    if (x == L_WORD) return _word(slc);
    if (x == L_ALPH) return _alpha(slc);
    if (x == L_DGT) return _digit(slc);
    if (x == L_NLT) return _nlt(slc);
    if (x == L_LSTRT) return _lstart(slc);
    
    return (RegexToken) {.type = TT_BRICK};
}

static STATUS _check_tokens(Vec tokens)
{
    RegexToken token;

    if (Vec_len(tokens) == 0) return STATUS_FUCKED;
    if (Vec_len(tokens) == 1)
    {
        token = deref(RegexToken) Vec_first(tokens);
        if (token.type == TT_START) return STATUS_FUCKED;
        if (token.type == TT_END) return STATUS_FUCKED;
    }

    return STATUS_OK;
} 

RegexParseResult Regex_compile_StrSlc(StrSlc slc)
{
    Vec         tokens;
    RegexToken  token;
    STATUS      status;

    tokens = Vec_new(RegexToken);
    status = STATUS_OK;

    while (true)
    {
        if ((token = _next(& slc)).type == TT_VOID) break;
        if (Vec_len(tokens))
        {
            if ((deref(RegexToken) Vec_last(tokens)).type == TT_STAR && (token.type == TT_STAR)) continue;
            if ((deref(RegexToken) Vec_last(tokens)).type == TT_END) token.type = TT_BRICK;
            if (token.type == TT_START) token.type = TT_BRICK;
        }

        if (token.type == TT_BRICK) {status = STATUS_FUCKED; break;}
        Vec_push(& tokens, token, RegexToken);
    }

    if (status == STATUS_OK) status = _check_tokens(tokens);
    return (RegexParseResult) {.tokens = tokens, .status = status};
}

RegexParseResult Regex_compile_cstr_len(const byte * cstr, i64 len)
{
    return Regex_compile_StrSlc(StrSlc_from_cstr_len(cstr, len));
}

RegexParseResult Regex_compile_cstr(const byte * cstr)
{
    return Regex_compile_cstr_len(cstr, strlen(cstr));
}

void RegexParseResult_del(RegexParseResult * rpr)
{
    Vec_del(& rpr->tokens);
    to0(rpr, RegexParseResult);
}