#include "Str.h"
#include "cstr.h"
#include "byte.h"
#include <string.h>
#include <stdio.h>

i64 StrSlc_cmp(StrSlc lhs, StrSlc rhs)
{
    return cstr_cmp_len(lhs.cstr, lhs.len, rhs.cstr, rhs.len);
}

i64 StrSlc_cmpf(const void * lhs, const void * rhs)
{
    return StrSlc_cmp(deref(StrSlc) lhs, deref(StrSlc) rhs);
}

StrSlc StrSlc_from_cstr_len(const byte * cstr, i64 len)
{
    return (StrSlc)
    {
        .cstr = cstr,
        .len = len,
    };
}

StrSlc StrSlc_brick(void)
{
    return StrSlc_from_cstr_len(NULL, NO_IDX);
}

bool StrSlc_is_brick(StrSlc slc)
{
    return slc.len == NO_IDX;
}

StrSlc StrSlc_from_cstr(const byte * cstr)
{
    return StrSlc_from_cstr_len(cstr, strlen(cstr));
}

const char * StrSlc_get(StrSlc slc, i64 idx)
{
    return slc.cstr + idx;
}

char StrSlc_get_c(StrSlc slc, i64 idx)
{
    return deref(char) StrSlc_get(slc, idx);
}

const char * StrSlc_first(StrSlc slc)
{
    return slc.cstr;
}

char StrSlc_first_c(StrSlc slc)
{
    return * slc.cstr;
}

i64 StrSlc_len(StrSlc slc)
{
    return slc.len;
}

bool StrSlc_empty(StrSlc slc)
{
    return slc.len == 0;
}

void StrSlc_shift(StrSlc * slc, i64 shift)
{
    slc->cstr += shift;
    slc->len -= shift;
}

void StrSlc_shrink(StrSlc * slc, i64 shrink)
{
    slc->len -= shrink;
}

StrSlc StrSlc_shifted(StrSlc slc, i64 shift)
{
    StrSlc_shift(& slc, shift);

    return slc;
}

StrSlc StrSlc_slice(StrSlc slc, i64 idx, i64 len)
{
    return StrSlc_from_cstr_len(slc.cstr + idx, len);
}

StrSlc StrSlc_slice_from(StrSlc slc, i64 idx)
{
    return StrSlc_slice(slc, idx, slc.len - idx);
}

StrSlc StrSlc_copy(StrSlc slc)
{
    return StrSlc_from_cstr_len(slc.cstr, slc.len);
}

StrSlc StrSlc_chop_front(StrSlc * slc, i64 len)
{
    StrSlc chop;

    chop = StrSlc_slice(* slc, 0, len);
    StrSlc_shift(slc, len);

    return chop;
}

StrSlc StrSlc_chop_all(StrSlc * slc)
{
    StrSlc chop;

    chop = StrSlc_copy(* slc);
    StrSlc_shift(slc, slc->len);

    return chop;
}

StrSlc StrSlc_chop_front_check(StrSlc * slc, i64 len)
{
    return len < slc->len ? StrSlc_chop_front(slc, len) : StrSlc_chop_all(slc);
}

i64 StrSlc_find_c(StrSlc slc, byte x)
{
    return cstr_find_c_len(slc.cstr, slc.len, x);
}

i64 StrSlc_find_ws(StrSlc slc)
{
    return cstr_find_ws_len(slc.cstr, slc.len);
}

i64 StrSlc_find_slice(StrSlc haystack, StrSlc needle)
{
    return cstr_find_cstr_len(haystack.cstr, haystack.len, needle.cstr, needle.len);
}

i64 StrSlc_find_slice_from(StrSlc haystack, i64 idx, StrSlc needle)
{
    return StrSlc_find_slice(StrSlc_slice_from(haystack, idx), needle);
}

i64 StrSlc_find_cstr_len(StrSlc slc, const byte * cstr, i64 len)
{
    return cstr_find_cstr_len(slc.cstr, slc.len, cstr, len);
}

i64 StrSlc_find_cstr(StrSlc slc, const byte * cstr)
{
    return cstr_find_cstr_len(slc.cstr, slc.len, cstr, strlen(cstr));
}

i64 StrSlc_find_cstr_len_ci(StrSlc slc, const byte * cstr, i64 len)
{
    return cstr_find_cstr_len_ci(slc.cstr, slc.len, cstr, len);
}

i64 StrSlc_find_cstr_ci(StrSlc slc, const byte * cstr)
{
    return StrSlc_find_cstr_len_ci(slc, cstr, strlen(cstr));
}

i64 StrSlc_find_slice_ci(StrSlc haystack, StrSlc needle)
{
    return StrSlc_find_cstr_len_ci(haystack, needle.cstr, needle.len);
}

i64 StrSlc_find_slice_ci_from(StrSlc haystack, i64 idx, StrSlc needle)
{
    return StrSlc_find_slice_ci(StrSlc_slice_from(haystack, idx), needle);
}

bool StrSlc_starts_with_c(StrSlc slc, byte x)
{
    return * slc.cstr == x;
}

bool StrSlc_starts_with_cstr_len(StrSlc slc, const byte * cstr, i64 len)
{
    if (len > slc.len) return false;

    for (i64 k = 0; k < len; k ++)
    {
        if (slc.cstr[k] != cstr[k]) return false;
    }

    return true;
}

bool StrSlc_starts_with_cstr_len_ci(StrSlc slc, const byte * cstr, i64 len)
{
    if (len > slc.len) return false;

    for (i64 k = 0; k < len; k ++)
    {
        if (byte_to_lower_check(cstr[k]) != byte_to_lower_check(slc.cstr[k])) return false;
    }
    
    return true;
}

bool StrSlc_starts_with_slice(StrSlc lhs, StrSlc rhs)
{
    return StrSlc_starts_with_cstr_len(lhs, rhs.cstr, rhs.len);
}

bool StrSlc_starts_with_slice_ci(StrSlc lhs, StrSlc rhs)
{
    return StrSlc_starts_with_cstr_len_ci(lhs, rhs.cstr, rhs.len);
}

bool StrSlc_starts_with_cstr(StrSlc slc, const byte * cstr)
{
    return StrSlc_starts_with_cstr_len(slc, cstr, strlen(cstr));
}

void StrSlc_trim_front_one(StrSlc * slc, byte x)
{
    if (* slc->cstr == x) StrSlc_shift(slc, 1);
}

void StrSlc_trim_front_cstr_len(StrSlc * slc, const byte * cstr, i64 len)
{
    if (StrSlc_starts_with_cstr_len(* slc, cstr, len)) StrSlc_shift(slc, len);
}

void StrSlc_trim_front_cstr(StrSlc * slc, const byte * cstr)
{
    StrSlc_trim_front_cstr_len(slc, cstr, strlen(cstr));
}

bool StrSlc_ends_with_c(StrSlc slc, byte x)
{
    return * (slc.cstr + slc.len - 1) == x;
}

bool StrSlc_ends_with_cstr_len(StrSlc slc, const byte * cstr, i64 len)
{
    if (len > slc.len) return false;

    for (i64 k = 0; k < len; k ++)
    {
        if (slc.cstr[slc.len - k - 1] != cstr[len - k - 1]) return false;
    }

    return true;
}

bool StrSlc_ends_with_cstr(StrSlc slc, const byte * cstr)
{
    return StrSlc_ends_with_cstr_len(slc, cstr, strlen(cstr));
}

void StrSlc_trim_back_one(StrSlc * slc, byte x)
{
    if (StrSlc_ends_with_c(* slc, x)) StrSlc_shrink(slc, 1);
}

void StrSlc_trim_back_cstr_len(StrSlc * slc, const byte * cstr, i64 len)
{
    if (StrSlc_ends_with_cstr_len(* slc, cstr, len)) StrSlc_shrink(slc, len);
}

void StrSlc_trim_back_cstr(StrSlc * slc, const byte * cstr)
{
    StrSlc_trim_back_cstr_len(slc, cstr, strlen(cstr));
}

i64 StrSlc_trim_front_ws(StrSlc * slc)
{
    i64 k;

    for (k = 0; k < slc->len; k ++)
    {
        if (! byte_is_ws(slc->cstr[k])) break;
    }

    StrSlc_shift(slc, k);

    return k;
}

i64 StrSlc_trim_back_ws(StrSlc * slc)
{
    i64 idx;
    i64 len;

    len = 0;
    for (idx = slc->len - 1; idx >= 0; idx --)
    {
        if (! byte_is_ws(slc->cstr[idx])) break;
        len ++;
    }

    StrSlc_shrink(slc, len);

    return len;
}

StrSlc StrSlc_split_next(StrSlc * slc, byte x)
{
    i64     idx;
    StrSlc  chop;

    if ((idx = StrSlc_find_c(* slc, x)) == NO_IDX) return StrSlc_chop_all(slc);

    chop = StrSlc_chop_front(slc, idx);
    StrSlc_shift(slc, 1);

    return chop;
}

Vec StrSlc_split(StrSlc slc, byte x)
{
    Vec     vec;

    vec = Vec_new(StrSlc);

    while (! StrSlc_empty(slc))
    {
        Vec_push(& vec, StrSlc_split_next(& slc, x), StrSlc);
    }

    return vec;
}

static i64 _match_bracket(StrSlc slc, byte ob, byte cb)
{
    i64 ob_count;
    i64 cb_count;

    StrSlc_shift(& slc, 1);
    ob_count = 1;
    cb_count = 0;

    for (i64 k = 0; k < slc.len; k ++)
    {
        cb_count += (slc.cstr[k] == cb);
        if (ob_count == cb_count) return k;
        ob_count += (slc.cstr[k] == ob);
    }

    return NO_IDX;
}

StrSlc StrSlc_in_brackets(StrSlc slc, byte ob, byte cb)
{
    i64 idx;

    if (* slc.cstr != ob) return StrSlc_brick();
    if ((idx = _match_bracket(slc, ob, cb)) == NO_IDX) return StrSlc_brick();

    return StrSlc_slice(slc, 1, idx);
}

StrSlc StrSlc_in_brackets_any(StrSlc slc)
{
    byte ob;
    byte cb;

    ob = * slc.cstr;
    if (! (cb = byte_matching_bracket(ob))) return StrSlc_brick();

    return StrSlc_in_brackets(slc, ob, cb);
}

void StrSlc_dbg(StrSlc slc)
{
    if (! StrSlc_is_brick(slc)) printf("%.*s ", (int) StrSlc_len(slc), slc.cstr);
}

void StrSlc_dbgf(const void * slc)
{
    StrSlc_dbg(deref(StrSlc) slc);
}
