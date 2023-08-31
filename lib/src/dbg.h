#ifndef DBG_H
#define DBG_H

#include "def.h"
#include "Str.h"
#include "Vec.h"
#include "View.h"

void dbg_Str(const Str * str, byte sep);
void dbg_Str_n(const Str * str);
void dbg_Slc(const Slc * slc, byte sep);
void dbg_Slc_n(const Slc * slc);
void dbg_i64(const i64 * x);
void dbg_View(const View * view, F f);
void dbg_Vec(const Vec * vec, F f);

#endif