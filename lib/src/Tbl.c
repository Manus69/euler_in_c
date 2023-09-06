#include "Tbl.h"
#include "mem.h"

Tbl Tbl_new_item_size(i64 n_rows, i64 n_cols, i64 item_size)
{
    return (Tbl)
    {
        .data = mem_alloc0(n_rows * n_cols * item_size),
        .item_size = item_size,
        .n_rows = n_rows,
        .n_cols = n_cols,
    };
}

void Tbl_del(Tbl * tbl)
{
    mem_del(tbl->data);
    to0(tbl, Tbl);
}

i64 Tbl_size(Tbl tbl)
{
    return tbl.item_size * tbl.n_rows * tbl.n_cols;
}

static inline i64 _idx(i64 row, i64 col, i64 item_size, i64 n_cols)
{
    return (n_cols * row + col) * item_size;
}

void * Tbl_get(Tbl tbl, i64 row, i64 col)
{
    i64 idx;

    idx = _idx(row, col, tbl.item_size, tbl.n_cols);

    return tbl.data + idx;
}

void * Tbl_nth(Tbl tbl, i64 n)
{
    return tbl.data + n * tbl.item_size;
}

void * Tbl_row(Tbl tbl, i64 row)
{
    return Tbl_get(tbl, row, 0);
}

void Tbl_map(Tbl tbl, F f)
{
    mem_raw_map(f, tbl.data, Tbl_size(tbl), tbl.item_size);
}