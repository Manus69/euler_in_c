#include "template.h"
#include "io.h"

static inline Vec _get_prototypes(Str str)
{
    (void) str;

    return Vec_new(i64);
}

void template_header_gen(const byte * cfile, const byte * name, const byte * deps[])
{
    Str str;

    str = io_read_file(cfile);

    (void) str;
    (void) name;
    (void) deps;
}