#include "head_gen.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define P_FILENAME  "p_table.h"
#define P_HEADER    "#ifndef P_TABLE_H\n#define P_TABLE_H\n\n"
#define F_TYPENAME  "fptr"
#define F_TYPEDEF   "typedef void (* " F_TYPENAME ")(void);\n\n"
#define F_PREFIX    "void "
#define F_NAME      "p"
#define F_SUFFIX    "(void);\n"
#define P_FOOTER    "\n#endif\n"

static Str _gen_prototypes(i64 n)
{
    byte    buff[1 << 5] = {};
    Str     str;
    i64     len;

    str = Str_new();
    Str_append_cstr(& str, P_HEADER);

    for (i64 k = 0; k <= n; k ++)
    {
        len = sprintf(buff, "%ld", k);
        Str_append_cstr(& str, F_PREFIX F_NAME "_");
        Str_append_cstr_len(& str, buff, len);
        Str_append_cstr(& str, F_SUFFIX);
    }

    return str;
}

void generate_header(const byte * name, i64 n_problems)
{
    Str str;

    str = _gen_prototypes(n_problems);
    Str_append_cstr(& str, P_FOOTER);
    io_write_to_file(name, str);
    Str_del(& str);
}