#include "./lib/libEuler.h"

#include <stdio.h>

#define TXT_FILE    "txt.txt"
#define TEST_FILE   "./lib/src/sort_test.c"

i64 i64_cmp(const i64 * lhs, const i64 * rhs)
{
    return * lhs - * rhs;
}

//word trim
//header gen
//code align

int main()
{
    Str s = io_read_file(TEST_FILE);
    dbg_Str_n(& s);

    Str_replace_list(& s, (const byte * []) to_list0("TYPE", "Slc"));
    dbg_Str_n(& s);

    Str_del(& s);
}