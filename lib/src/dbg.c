#include "dbg.h"
#include "Slc.h"
#include "mem.h"

#include <stdio.h>

void dbg_Str(const Str * str, byte sep)
{
    printf("%s%c", Str_cstr(* str), sep);
}

void dbg_Str_n(const Str * str)
{
    dbg_Str(str, '\n');
}

void dbg_Slc(const Slc * slc, byte sep)
{
    printf("%.*s%c", (int) slc->size, (byte *) Slc_ptr(* slc), sep);
}

void dbg_Slc_n(const Slc * slc)
{
    dbg_Slc(slc, '\n');
}

void dbg_i64(const i64 * x)
{
    printf("%ld ", * x);
}

void dbg_View(const View * view, F f)
{
    View_map(* view, f);
    printf("\n");
}

void dbg_Vec(const Vec * vec, F f)
{
    dbg_View((View *) vec, f);
    printf("\n");
}