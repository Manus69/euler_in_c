#ifndef TBL_H
#define TBL_H

#include "def.h"

typedef struct Tbl Tbl;

struct Tbl
{
    void *  data;
    i64     item_size;
    i64     n_rows;
    i64     n_cols;
};

#define Tbl_new(n_rows, n_cols, type) Tbl_new_item_size(n_rows, n_cols, sizeof(type))
#define Tbl_set(tbl, row, col, item, type) (deref(type) Tbl_get(tbl, row, col) = item)
#define Tbl_set_nth(tbl, n, item, type) (deref(type) Tbl_nth(tbl, n) = item)

Tbl     Tbl_new_item_size(i64 n_rows, i64 n_cols, i64 item_size);
void    Tbl_del(Tbl * tbl);
i64     Tbl_size(Tbl tbl);
i64     Tbl_n_rows(Tbl tbl);
i64     Tbl_n_cols(Tbl tbl);
void *  Tbl_get(Tbl tbl, i64 row, i64 col);
void *  Tbl_nth(Tbl tbl, i64 n);
void *  Tbl_row(Tbl tbl, i64 row);
void    Tbl_map(Tbl tbl, F f);

#endif