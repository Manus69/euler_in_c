#include "euler.h"
#define FILE "./src/p_13.txt"

static Vec _read_file()
{
    Str str;
    Vec lines;
    Vec vec;

    str = io_read_file(FILE);
    lines = Str_split_slices(str, '\n');
    vec = Vec_new(Bigu);

    for (i64 k = 0; k < Vec_len(lines); k ++)
    {
        Vec_push(& vec, Bigu_from_StrSlc_ptr(Vec_get(lines, k)), Bigu);
    }

    Str_del(& str);
    Vec_del(& lines);

    return vec;
}

void p_13(void)
{
    Vec     ints;
    Bigu    bigu;

    ints = _read_file();
    bigu = Bigu_new(0);

    for (i64 k = 0; k < Vec_len(ints); k ++)
    {
        Bigu_plus(& bigu, deref(Bigu) Vec_get(ints, k));
    }

    Bigu_dbg(bigu);

    Bigu_del(& bigu);
    Vec_map(ints, (F) Bigu_del);
    Vec_del(& ints);
}