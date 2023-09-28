#include "regex.h"
#include "regex_private.h"
#include "cstr.h"
#include "byte.h"
#include <string.h>
#include <stdio.h>

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

static inline bool _state_last_token(RegexState state)
{
    return _state_tokens_remainig(state) == 1;
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

static inline RegexState _match_str_one(StrSlc slc, RegexState state, bool (* f_start)(StrSlc, StrSlc))
{
    StrSlc  strslc;
    i64     len;

    strslc = _state_token(state).slc;
    len = StrSlc_len(strslc);

    if (f_start(slc, strslc))
    {
        return _match(StrSlc_shifted(slc, len), _state_next(state, len, 1));
    }

    return state;
}

static inline RegexState _match_str_zo(StrSlc slc, RegexState state, bool (* f_start)(StrSlc, StrSlc))
{
    RegexState next_state;

    next_state = _match(slc, _state_next(state, 0, 1));
    if (_state_match_found(next_state)) return next_state;

    return _match_str_one(slc, state, f_start);
}

static inline RegexState _match_str_om(StrSlc slc, RegexState state, bool (* f_start)(StrSlc, StrSlc))
{
    RegexState  next_state;
    StrSlc      strslc;
    i64         len;

    strslc = _state_token(state).slc;
    len = StrSlc_len(strslc);

    if (! f_start(slc, strslc)) return state;
    StrSlc_shift(& slc, len);

    next_state = _match(slc, _state_next(state, len, 1));
    if (_state_match_found(next_state)) return next_state;

    return _match_str_om(slc, _state_next(state, len, 0), f_start);
}

static inline RegexState _match_str_zero(StrSlc slc, RegexState state, bool (* f_start)(StrSlc, StrSlc))
{
    if (f_start(slc, _state_token(state).slc)) return state;

    return _match(slc, _state_next(state, 0, 1));
}

static inline RegexState _match_str(StrSlc slc, RegexState state, bool (* f_start)(StrSlc, StrSlc))
{
    RegexToken token;

    token = _state_token(state);
    if (token.count == CNT_ONE) return _match_str_one(slc, state, f_start);
    if (token.count == CNT_ZERO) return _match_str_zero(slc, state, f_start);
    if (token.count == CNT_ZERO_OR_ONE) return _match_str_zo(slc, state, f_start);
    if (token.count == CNT_ONE_OR_MORE) return _match_str_om(slc, state, f_start);

    return state;
}

static inline RegexState _match_star(StrSlc slc, RegexState state)
{
    RegexState next_state;

    next_state = _match(slc, _state_next(state, 0, 1));
    if (_state_match_found(next_state)) return next_state;

    return _match_star(StrSlc_shifted(slc, 1), _state_next(state, 1, 0));
}

static RegexState _match(StrSlc slc, RegexState state)
{
    RegexToken token;

    if (_state_no_tokens(state)) return state;
    token = _state_token(state);

    if (token.type == TT_STAR) return _match_star(slc, state);
    if (token.type == TT_STR) return _match_str(slc, state, StrSlc_starts_with_slice);
    if (token.type == TT_STR_CI) return _match_str(slc, state, StrSlc_starts_with_slice_ci);

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

RegexMatch Regex_match_Str(Str str, RegexParseResult rpr)
{
    return Regex_match_slice(Str_to_slice(str), rpr);
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

void RegexMatch_dbg(RegexMatch match)
{
    printf("(%ld %ld) ", match.idx, match.len);
}