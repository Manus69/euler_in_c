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
};

typedef i64 (* MatchF)(StrSlc, RegexState);
typedef i64 (* FindF)(StrSlc, RegexState);

static inline i64 _match(StrSlc slc, RegexState state);

static inline RegexToken _state_token(RegexState state)
{
    return deref(RegexToken) Vec_get(* state.tokens, state.vec_idx);
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

static inline RegexState _state_next(RegexState state,i64 vec_inc)
{
    state.vec_idx += vec_inc;

    return state;
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

static inline i64 _match_next(StrSlc slc, RegexState state, i64 slc_inc, i64 vec_inc)
{
    i64 match;

    state = _state_next(state, vec_inc);
    slc = StrSlc_shifted(slc, slc_inc);
    match = _match(slc, state);

    return match == NO_IDX ? NO_IDX : slc_inc + match;
}

static inline i64 _match_star(StrSlc slc, RegexState state)
{
    i64 match;

    if (slc.len == 0) return 0;
    if ((match = _match_next(slc, state, 0, 1)) != NO_IDX) return match;
    if ((match = _match_star(StrSlc_shifted(slc, 1), state)) != NO_IDX) return 1 + match;

    return NO_IDX;
}

static inline i64 _find_star(StrSlc slc, RegexState state)
{
    (void) slc;
    (void) state;

    return 0;
}

static inline i64 _match_str_once(StrSlc slc, RegexState state, bool (* startf)(StrSlc, StrSlc))
{
    RegexToken token;

    token = _state_token(state);
    if (! startf(slc, token.slc)) return NO_IDX;

    return _match_next(slc, state, token.slc.len, 1);
}

static inline i64 _match_str_not(StrSlc slc, RegexState state, bool (* startf)(StrSlc, StrSlc))
{
    RegexToken token;

    token = _state_token(state);
    if (startf(slc, token.slc)) return NO_IDX;

    return _match_next(slc, state, 0, 1);
}

static inline i64 _match_strf(StrSlc slc, RegexState state, bool (* startf)(StrSlc, StrSlc))
{
    RegexToken token;

    token = _state_token(state);
    if (token.count == CNT_ONE) return _match_str_once(slc, state, startf);
    if (token.count == CNT_ZERO) return _match_str_not(slc, state, startf);

    return NO_IDX;
}

static inline i64 _match_str(StrSlc slc, RegexState state)
{
    return _match_strf(slc, state, StrSlc_starts_with_slice);
}

static inline i64 _match_str_ci(StrSlc slc, RegexState state)
{
    return _match_strf(slc, state, StrSlc_starts_with_slice_ci);
}

static inline i64 _find_strf(StrSlc slc, RegexState state, i64 (* findf)(StrSlc, StrSlc))
{
    RegexToken  token;

    token = _state_token(state);
    if (token.count == CNT_ONE || token.count == CNT_ONE_OR_MORE)
    {
        return findf(slc, token.slc); 
    }

    return 0;
}

static inline i64 _find_str_ci(StrSlc slc, RegexState state)
{
    return _find_strf(slc, state, StrSlc_find_slice_ci);
}

static inline i64 _find_str(StrSlc slc, RegexState state)
{
    return _find_strf(slc, state, StrSlc_find_slice);
}

static inline i64 _match_end(StrSlc slc, RegexState state)
{
    (void) state;

    return slc.len == 0 ? 0 : NO_IDX;
}

static inline i64 _match_char_once(StrSlc slc, RegexState state)
{
    if (slc.len == 0) return NO_IDX;

    return _match_next(slc, state, 1, 1);
}

static inline i64 _match_char_zo(StrSlc slc, RegexState state)
{
    i64 match;

    if ((match = _match_next(slc, state, 0, 1)) != NO_IDX) return match;

    return _match_char_once(slc, state);     
}

static inline i64 _match_char_om(StrSlc slc, RegexState state)
{
    i64 match;

    if (slc.len == 0) return NO_IDX;
    if ((match = _match_char_once(slc, state)) != NO_IDX) return match;
    if ((match = _match_char_om(StrSlc_shifted(slc, 1), state)) == NO_IDX) return NO_IDX;

    return 1 + match;
}

static inline i64 _match_char(StrSlc slc, RegexState state)
{
    RegexToken token;

    token = _state_token(state);
    if (token.count == CNT_ONE) return _match_char_once(slc, state);
    if (token.count == CNT_ZERO_OR_ONE) return _match_char_zo(slc, state);
    if (token.count == CNT_ONE_OR_MORE) return _match_char_om(slc, state);

    return NO_IDX;
}

static inline MatchF _get_matchf(RegexTT type)
{
    if (type == TT_STAR) return _match_star;
    if (type == TT_STR) return _match_str;
    if (type == TT_STR_CI) return _match_str_ci;
    if (type == TT_END) return _match_end;
    if (type == TT_CHAR) return _match_char;

    return NULL;
}

static inline FindF _get_findf(RegexTT type)
{
    if (type == TT_STR) return _find_str;
    if (type == TT_STR_CI) return _find_str_ci;

    return _find_star;
}

static inline i64 _match(StrSlc slc, RegexState state)
{
    MatchF matchf;

    if (_state_no_tokens(state)) return 0;
    if ((matchf = _get_matchf(_state_token(state).type)) == NULL) return NO_IDX;

    return matchf(slc, state);
}

//to do
// RegexMatch Regex_match_slice(StrSlc slc, RegexParseResult rpr)
// {
//     RegexState state;

//     if (rpr.status == STATUS_FUCKED) return RegexMatch_no_match();
//     state = (RegexState)
//     {
//         .tokens = & rpr.tokens,
//     };

//     (void) state;
//     return RegexMatch_no_match();
// }

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

//to do
// Vec Regex_match_all(StrSlc slc, const byte * pattern)
// {

// }

// Vec Regex_match_all_slices(StrSlc slc, const byte * pattern)
// {

// }

void RegexMatch_dbg(RegexMatch match)
{
    printf("(%ld %ld) ", match.idx, match.len);
}