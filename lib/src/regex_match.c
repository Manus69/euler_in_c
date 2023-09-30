#include "regex.h"
#include "regex_private.h"
#include "cstr.h"
#include "byte.h"
#include <string.h>
#include <stdio.h>

typedef struct RegexState RegexState;

struct RegexState
{
    const Vec *     tokens;
    const StrSlc *  slc;
    i64             vec_idx;
    i64             slc_idx;
    i64             match_idx;
    i64             match_len;
};

static inline RegexState _match(RegexState state);

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

static inline i64 _state_current_slc_len(RegexState state)
{
    return state.slc->len - state.slc_idx;
}

static inline bool _state_current_slc_empty(RegexState state)
{
    return _state_current_slc_len(state) == 0;
}

static inline bool _state_last_token(RegexState state)
{
    return _state_tokens_remainig(state) == 1;
}

static inline bool _state_match_found(RegexState state)
{
    return _state_no_tokens(state) && _state_matching(state);
}

static inline char _state_current_char(RegexState state)
{
    return StrSlc_get_c(* state.slc, state.slc_idx);
}

static inline StrSlc _state_current_slc(RegexState state)
{
    return StrSlc_slice_from(* state.slc, state.slc_idx);
}

static inline RegexState _state_next(RegexState state, i64 slc_inc, i64 m_inc, i64 vec_inc)
{
    state.slc_idx += slc_inc;
    state.match_len += m_inc;
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

static inline RegexState _find_str_once
(RegexState state, StrSlc needle, i64 (* findf)(StrSlc, i64, StrSlc))
{
    i64 idx;

    if ((idx = findf(_state_current_slc(state), state.slc_idx, needle)) == NO_IDX) return state;

    state.match_idx = state.slc_idx + idx;
    state = _state_next(state, idx + needle.len, needle.len, 1);

    return _match(state); 
}

static inline RegexState _match_str_once
(RegexState state, i64 (* findf)(StrSlc, i64, StrSlc), bool (* startf)(StrSlc, StrSlc))
{
    StrSlc needle;

    needle = _state_token(state).slc;
    if (! _state_matching(state)) return _find_str_once(state, needle, findf);
    if (! startf(_state_current_slc(state), needle)) return state;

    return _match(_state_next(state, needle.len, needle.len, 1));
}

static inline RegexState _find_str_not
(RegexState state, StrSlc needle, bool (* startf)(StrSlc, StrSlc))
{
    StrSlc      current;
    RegexState  next;

    while (true)
    {
        if ((current = _state_current_slc(state)).len == 0) return state;
        if (! startf(current, needle))
        {
            next = state;
            next.match_idx = state.slc_idx;
            next = _match(_state_next(next, 0, 0, 1));

            if (_state_match_found(next)) return next;
        }

        state.slc_idx ++;
    }
}

static inline RegexState _match_str_not
(RegexState state, bool (* startf)(StrSlc, StrSlc))
{
    StrSlc needle;

    needle = _state_current_slc(state);
    if (! _state_matching(state)) return _find_str_not(state, needle, startf);
    if (startf(_state_current_slc(state), needle)) return state;

    return _match(_state_next(state, needle.len, needle.len, 1));
}

static inline RegexState _match_str
(RegexState state, i64 (* findf)(StrSlc, i64, StrSlc), bool (* startf)(StrSlc, StrSlc))
{
    RegexToken token;

    token = _state_token(state);
    if (token.count == CNT_ONE) return _match_str_once(state, findf, startf);
    
    return state;
}

static inline RegexState _find_nl(RegexState state)
{
    i64 idx;

    if ((idx = StrSlc_find_c(_state_current_slc(state), '\n')) == NO_IDX) return state;
    state.match_idx = state.slc_idx + idx;

    return _match(_state_next(state, idx + 1, 1, 1));
}

static inline RegexState _match_nl(RegexState state)
{
    if (! _state_matching(state)) return _find_nl(state);
    if (_state_current_char(state) != '\n') return state;

    return _match(_state_next(state, 1, 1, 1));
}

static inline RegexState _find_end(RegexState state)
{
    state.match_idx = state.slc->len;

    return _state_next(state, state.slc->len, 0, 1);
}

static inline RegexState _match_end(RegexState state)
{
    if (! _state_matching(state)) return _find_end(state);
    if (_state_current_slc_empty(state)) return _state_next(state, 0, 0, 1);

    return state;
}

static inline RegexState _find_nlt(RegexState state)
{
    RegexState next;

    next = _find_nl(state);
    if (_state_match_found(next)) return next;

    return _find_end(state);
}

static inline RegexState _match_nlt(RegexState state)
{
    RegexState next;

    if (! _state_matching(state)) return _find_nlt(state);
    next = _match_nl(state);
    if (_state_match_found(next)) return next;

    return _match_end(state);
}

static inline RegexState _find_start(RegexState state)
{
    state.match_idx = 0;

    return _match(_state_next(state, 0, 0, 1));
}

static inline RegexState _match_start(RegexState state)
{
    if (! _state_matching(state)) return _find_lstart(state);

    return state;
}

static inline RegexState _find_lstart(RegexState state)
{
    i64 idx;

    if ((idx = StrSlc_find_c(state.slc, '\n')) == NO_IDX) return state;

    
}

static inline RegexState _match_lstart(RegexState state)
{

}

static inline RegexState _find_star(RegexState state)
{
    if (_state_last_token(state))
    {
        state.match_idx = state.slc_idx;
        return _state_next(state, state.slc->len, state.slc->len, 1);
    }

    return _match(_state_next(state, 0, 0, 1));
}

static inline RegexState _match_star(RegexState state)
{
    RegexState next;

    if (! _state_matching(state)) return _find_star(state);
    next = _match(_state_next(state, 0, 0, 1));
    if (_state_match_found(next)) return next;

    return _match_star(_state_next(state, 1, 1, 0));
}

static inline RegexState _match(RegexState state)
{
    RegexToken token;

    if (_state_no_tokens(state)) return state;

    token = _state_token(state);
    if (token.type == TT_STAR) return _match_star(state);
    if (token.type == TT_STR) return _match_str(state, StrSlc_find_slice_from, StrSlc_starts_with_slice);
    if (token.type == TT_STR_CI) return _match_str(state, StrSlc_find_slice_ci_from, StrSlc_starts_with_slice_ci);
    if (token.type == TT_NLT) return _match_nlt(state);

    return state;
}

RegexMatch Regex_match_slice(StrSlc slc, RegexParseResult rpr)
{
    RegexState state;

    if (rpr.status == STATUS_FUCKED) return RegexMatch_no_match();
    state = (RegexState)
    {
        .tokens = & rpr.tokens,
        .slc = & slc,
        .match_idx = NO_IDX,
    };

    state = _match(state);
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

Vec Regex_match_all_slices(StrSlc slc, const byte * pattern)
{
    Vec                 vec;
    RegexMatch          match;
    RegexParseResult    rpr;

    vec = Vec_new(RegexMatch);
    if ((rpr = Regex_compile_cstr(pattern)).status == STATUS_FUCKED) return vec;

    while (true)
    {
        if ((match = Regex_match_slice(slc, rpr)).idx == NO_IDX) break;
        Vec_push(& vec, StrSlc_slice(slc, match.idx, match.len), StrSlc);
        slc = StrSlc_slice_from(slc, match.idx + match.len);
    }

    RegexParseResult_del(& rpr);

    return vec;
}

void RegexMatch_dbg(RegexMatch match)
{
    printf("(%ld %ld) ", match.idx, match.len);
}