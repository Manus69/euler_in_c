#include "euler.h"
#include <assert.h>

#define FILE    "./src/p_11.txt"
#define N_ROWS  20
#define N_COLS  20
#define LEN     2

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

void p_11(void)
{
    Tbl tbl;

    tbl = _get_tbl(FILE);
    Tbl_map(tbl, (F) u64_dbgf);
    Tbl_del(& tbl);
}