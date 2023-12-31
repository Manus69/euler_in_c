#include "euler.h"
#include <assert.h>

// static const byte * small_t = "3\n7 4\n2 4 6\n8 5 9 3";

typedef struct
{
    Vec     cells;
    i64     n;
} _T;

u8 * _T_get(_T t, i64 row, i64 col)
{
    return Vec_get(t.cells, math_arith_prog_sum(row) + col);
}

void _T_set(_T t, i64 row, i64 col, u8 value)
{
    * _T_get(t, row, col) = value;
}

static u8 _parse(const StrSlc slc)
{
    const byte * cstr;

    cstr = StrSlc_first(slc);

    if (StrSlc_len(slc) == 1) return cstr[0] - '0';

    return (cstr[0] - '0') * 10 + (cstr[1] - '0');
}

_T _new(Str * str)
{
    StrSlc  slc;
    Vec     vec;
    i64     n;

    Str_replace_cstr_in_situ(str, "\n", " ");
    slc = Str_to_slice(* str);
    StrSlc_trim_back_ws(& slc);

    vec = Vec_new(u8);

    while (StrSlc_empty(slc) == false)
    {
        Vec_push(& vec, _parse(StrSlc_split_next(& slc, ' ')), u8);
    }

    n = math_is_triangular(Vec_len(vec));
    assert(n);

    return (_T) {vec, n};
}

_T _from_file(const byte * name)
{
    Str str;
    _T  t;

    str = io_read_file(name);
    t = _new(& str);
    Str_del(& str);

    return t;
}

#define FILE "./src/p_18.txt"
#define N 100
static u64 path_table[N][N];

static u64 _compute_path(_T t, i64 row, i64 col)
{
    u64 lhs;
    u64 rhs;

    if (path_table[row][col]) return path_table[row][col];

    if (row == t.n - 1)
    {
        path_table[row][col] = deref(u8) _T_get(t, row, col);

        return path_table[row][col];
    }

    lhs = _compute_path(t, row + 1, col);
    rhs = _compute_path(t, row + 1, col + 1);

    path_table[row][col] = max(lhs, rhs) + deref(u8) _T_get(t, row, col);

    return path_table[row][col];
}

void p_18(void)
{
    _T  t;
    u64 path;


    t = _from_file(FILE);
    path = _compute_path(t, 0, 0);
    u64_dbg(path);

    Vec_del(& t.cells);
}