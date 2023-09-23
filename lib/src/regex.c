#include "regex.h"
#include "regex_private.h"

static inline RegexMatch RegexMatch_init(i64 idx, i64 len)
{
    return (RegexMatch)
    {
        .idx = idx,
        .len = len,
    };
}

static inline RegexMatch RegexMatch_no_match()
{
    return RegexMatch_init(NO_IDX, NO_IDX);
}

static inline bool _no_match(RegexMatch match)
{
    return match.len == NO_IDX;
}

static inline i64 _match_digit(const byte * cstr, i64 len)
{
    for (i64 k = 0; k < len; k ++)
    {
        if (! byte_is_numeric(cstr[k])) return k;
    }

    return len;
}

static inline i64 _match_exact(const byte * restrict cstr, i64 len, const byte * restrict pattern, i64 p_len)
{
    if (len < p_len) return 0;

    return cstr_cmp_len(cstr, len, pattern, p_len) == 0 ? p_len : 0;
}

static inline i64 _match_word(const byte * cstr, i64 len)
{
    for (i64 k = 0; k < len; k ++)
    {
        if (! byte_is_alpha(cstr[k])) return k;
    }

    return len;
}




