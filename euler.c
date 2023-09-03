#include    "./lib/libEuler.h"
#include    "./src/head_gen.h"
#include    "./src/test.h"
#define     F_TABLE_FILE    "./src/p_table.h"
#include    F_TABLE_FILE
#include    <stdio.h>

#define USE_MSG "Usage: ./_euler [problem number]"

static int _error(const byte * msg)
{
    return printf("%s\n", msg);
}

//word trim
//header gen
//code align
//regex

int main(int argc, char * argv[])
{
    u64 n;

    if (argc != 2) return _error(USE_MSG);
    if ((n = u64_parse_cstr(argv[1])) == 0) return _error(USE_MSG);

    call_table[n]();
}