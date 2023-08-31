#include "./lib/libEuler.h"

#include <stdio.h>

#define _FILE "txt.txt"

//word trim

int main()
{
    Str s = io_read_file(_FILE);
    Vec v = Slc_split(Str_to_Slc(s), '\n');
    // dbg_Vec(& v, (F) dbg_Slc_n);
    Slc slc = deref(Slc) Vec_last(v);
    dbg_Slc_n(& slc);
    Str_del(& s);
    Vec_del(& v);
}