#include "euler.h"
#include <assert.h>

#define FILE    "./src/p_11.txt"
#define N_ROWS  20
#define N_COLS  20
#define LEN     2
#define N       4

static u64 _parse(StrSlc slc)
{
    if (* StrSlc_first(slc) == '0') return u64_parse_cstr_len(StrSlc_get(slc, 1), StrSlc_len(slc) - 1);

    return u64_parse_cstr_len(StrSlc_first(slc), StrSlc_len(slc));
}

static Tbl _get_tbl(const byte * file_name)
{
    Str str;
    Tbl tbl;
    Vec split;

    str = io_read_file(file_name);
    Str_replace_cstr_in_situ(& str, "\n", " ");
    split = Str_split_slices(str, ' ');
    assert(N_ROWS * N_COLS == Vec_len(split));
    tbl = Tbl_new(N_ROWS, N_COLS, u64);

    for (i64 n = 0; n < Vec_len(split); n ++)
    {
        Tbl_set_nth(tbl, n, _parse(deref(StrSlc) Vec_get(split, n)), u64);
    }

    Str_del(& str);
    Vec_del(& split);

    return tbl;
}

static u64 _down(Tbl tbl, i64 row, i64 col)
{
    u64 x;

    if (row + N >= Tbl_n_rows(tbl)) return 0;

    x = 1;
    for (i64 k = 0; k < N; k ++)
    {
        x *= deref(u64) Tbl_get(tbl, row + k, col);
    }

    return x;
}

static u64 _right(Tbl tbl, i64 row, i64 col)
{
    u64 x;

    if (col + N >= Tbl_n_cols(tbl)) return 0;

    x = 1;
    for (i64 k = 0; k < N; k ++)
    {
        x *= deref(u64) Tbl_get(tbl, row, col + k);
    }

    return x;
}

static u64 _top_right(Tbl tbl, i64 row, i64 col)
{
    u64 x;

    if (row + N >= Tbl_n_rows(tbl)) return 0;
    if (col + N >= Tbl_n_cols(tbl)) return 0;

    x = 1;
    for (i64 k = 0; k < N; k ++)
    {
        x *= deref(u64) Tbl_get(tbl, row + k, col + k);
    }

    return x;
}

static u64 _top_left(Tbl tbl, i64 row, i64 col)
{
    u64 x;

    if (row + N >= Tbl_n_rows(tbl)) return 0;
    if (col - N < 0) return 0;

    x = 1;
    for (i64 k = 0; k < N; k ++)
    {
        x *= deref(u64) Tbl_get(tbl, row + k, col - k);
    }

    return x;
}

static u64 _max_in_table(Tbl tbl)
{
    Vec vec;
    i64 max_idx;
    u64 max;

    vec = Vec_new(u64);
    for (i64 row = 0; row < Tbl_n_rows(tbl); row ++)
    {
        for (i64 col = 0; col < Tbl_n_cols(tbl); col ++)
        {
            Vec_push(& vec, _right(tbl, row, col), u64);
            Vec_push(& vec, _down(tbl, row, col), u64);
            Vec_push(& vec, _top_right(tbl, row, col), u64);
            Vec_push(& vec, _top_left(tbl, row, col), u64);
        }
    }

    max_idx = Vec_max_idx(vec, u64_cmpf);
    max = deref(u64) Vec_get(vec, max_idx);
    Vec_del(& vec);

    return max;
}

void p_11(void)
{
    Tbl tbl;
    u64 max;

    tbl = _get_tbl(FILE);
    max = _max_in_table(tbl);

    Tbl_del(& tbl);
    u64_dbg(max);
}