#include "regex.h"
#include "regex_private.h"
#include "cstr.h"
#include <assert.h>
#include <string.h>

typedef struct RegexState RegexState;

struct RegexState
{
    const Vec * tokens;
    i64         vec_idx;
    i64         match_idx;
    i64         match_len;
};

static RegexState _match(StrSlc slc, RegexState state);

static inline RegexState _state_next(RegexState state, i64 match_inc, i64 vec_inc)
{
    state.match_len += match_inc;
    state.vec_idx += vec_inc;

    return state;
}

static inline RegexToken _state_token(RegexState state)
{
    return deref(RegexToken) Vec_get(* state.tokens, state.vec_idx);
}

static inline bool _state_matching(RegexState state)
{
    return state.match_idx != NO_IDX;
}

static inline i64 _state_tokens_remainig(RegexState state)
{
    return Vec_len(* state.tokens) - state.vec_idx;
}

static inline bool _state_no_tokens(RegexState state)
{
    return _state_tokens_remainig(state) <= 0;
}

static inline bool _state_match_found(RegexState state)
{
    return _state_no_tokens(state) && _state_matching(state);
}

static inline RegexMatch RegexMatch_init(i64 idx, i64 len)
{
    return (RegexMatch)
    {
        .idx = idx,
        .len = len,
    };
}

static inline RegexMatch RegexMatch_no_match(void)
{
    return RegexMatch_init(NO_IDX, NO_IDX);
}

static inline bool _no_match(RegexMatch match)
{
    return match.len == NO_IDX;
}

static RegexState _match_str(StrSlc slc, RegexState state)
{
    RegexToken  token;
    i64         idx;
    i64         len;

    token = _state_token(state);
    len = StrSlc_len(token.slc);

    if (! _state_matching(state))
    {
        if ((idx = StrSlc_find_slice(slc, token.slc)) == NO_IDX) return state;
        state.match_idx = idx;

        return _match(StrSlc_slice_from(slc, idx), _state_next(state, len, 1));
    }
    if (! StrSlc_starts_with_slice(slc, token.slc)) return state;
    
    StrSlc_shift(& slc, len);
    return _match(slc, _state_next(state, len, 1));
}

static RegexState _match_star(StrSlc slc, RegexState state)
{
    RegexState next_state;

    if (StrSlc_len(slc) == 0) return state;
    if (! _state_matching(state))
    {
        return _match(slc, _state_next(state, 0, 1));
    }

    next_state = _match(slc, _state_next(state, 0, 1));
    if (_state_match_found(next_state)) return next_state;

    StrSlc_shift(& slc, 1);
    state.match_len ++;

    return _match_star(slc, state);
}

static RegexState _match(StrSlc slc, RegexState state)
{
    RegexToken token;

    if (_state_no_tokens(state)) return state;

    token = _state_token(state);
    if (token.type == TT_STAR)
    {
        return _match_star(slc, state);
    }
    if (token.type == TT_STR) return _match_str(slc, state);

    return state;
}

RegexMatch Regex_match_slice(StrSlc slc, RegexParseResult rpr)
{
    RegexState state;

    if (rpr.status == STATUS_FUCKED) return RegexMatch_no_match();
    state = (RegexState)
    {
        .tokens = & rpr.tokens,
        .match_idx = NO_IDX,
    };

    state = _match(slc, state);
    return _state_match_found(state) ? 
            RegexMatch_init(state.match_idx, state.match_len) : 
            RegexMatch_no_match();
}

RegexMatch Regex_match_cstr_len(const byte * cstr, i64 len, RegexParseResult rpr)
{
    return Regex_match_slice(StrSlc_from_cstr_len(cstr, len), rpr);
}

RegexMatch Regex_match_cstr(const byte * cstr, RegexParseResult rpr)
{
    return Regex_match_cstr_len(cstr, strlen(cstr), rpr);
}

RegexMatch Regex_match_slice_pattern(StrSlc slc, const byte * pattern)
{
    RegexParseResult    rpr;
    RegexMatch          match;

    rpr = Regex_compile_cstr(pattern);
    match = Regex_match_slice(slc, rpr);
    RegexParseResult_del(& rpr);    

    return match;
}

RegexMatch Regex_match_cstr_pattern(const byte * restrict cstr, const byte * pattern)
{
    return Regex_match_slice_pattern(StrSlc_from_cstr(cstr), pattern);
}

RegexMatch Regex_match_Str_pattern(Str str, const byte * pattern)
{
    return Regex_match_slice_pattern(Str_to_slice(str), pattern);
}
