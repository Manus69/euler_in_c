#include "head_gen.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define N_PROBLEMS  100
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
    Str_append_cstr(& str, P_HEADER F_TYPEDEF);

    for (i64 k = 0; k <= n; k ++)
    {
        len = sprintf(buff, "%ld", k);
        Str_append_cstr(& str, F_PREFIX F_NAME "_");
        Str_append_cstr_len(& str, buff, len);
        Str_append_cstr(& str, F_SUFFIX);
    }

    return str;
}

#define F_TABLE_NAME    " call_table"
#define F_TABLE_START   "\nstatic const " F_TYPENAME F_TABLE_NAME "[] = \n{\n"
#define F_TABLE_END     "};\n"
static Str _gen_table(i64 n)
{
    byte    buff[1 << 5] = {};
    Str     str;
    i64     len;

    str = Str_new();
    Str_append_cstr(& str, F_TABLE_START);

    for (i64 k = 0; k <= n; k ++)
    {
        len = sprintf(buff, "%ld", k);
        Str_append_cstr(& str, "\t" F_NAME);
        Str_append_cstr_len(& str, buff, len);
        Str_append_cstr(& str, ",\n");
    }

    Str_append_cstr(& str, F_TABLE_END);
    Str_append_cstr(& str, P_FOOTER);

    return str;
}

void generate_header(const byte * name, i64 n_problems)
{
    Str top;
    Str bot;
    int fd;

    top = _gen_prototypes(n_problems);
    bot = _gen_table(n_problems);
    Str_append_Str(& top, bot);

    if ((fd = open(name, O_RDWR | O_CREAT, 0666)) >= 0)
    {
        io_write_fd(top, fd);
    }

    Str_del(& top);
    Str_del(& bot);
}