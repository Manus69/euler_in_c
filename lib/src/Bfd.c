#include "Bfd.h"
#include "mem.h"
#include "macro.h"
#include "u8.h"
#include <string.h>
#include <stdio.h>

#define pattern(n) _mask_table[(n) % __CHAR_BIT__]
static const u8 _mask_table[__CHAR_BIT__] = 
{
    1, 2, 4, 8, 16, 32, 64, 128,
};

static inline i64 _index(i64 bit)
{
    return bit / __CHAR_BIT__;
}

static inline u8 * _cell(Bfd bfd, i64 bit)
{
    return bfd.field + _index(bit);
}

Bfd Bfd_new(i64 n_bits)
{
    return (Bfd)
    {
        .field = mem_alloc0(_index(n_bits) + 1),
        .size = _index(n_bits) + 1,
    };
}

void Bfd_del(Bfd * bfd)
{
    mem_del(bfd->field);
    to0(bfd, Bfd);
}

bool Bfd_bit(Bfd bfd, i64 n)
{
    return (deref(u8) _cell(bfd, n)) & pattern(n);
}

void Bfd_bit_set(Bfd bfd, i64 n)
{
    (deref(u8) _cell(bfd, n)) |= pattern(n);
}

void Bfd_bit_clear(Bfd bfd, i64 n)
{
    (deref(u8) _cell(bfd, n)) &= (~ pattern(n));
}

void Bfd_bit_toggle(Bfd bfd, i64 n)
{
    (deref(u8) _cell(bfd, n)) ^= pattern(n);
}

void Bfd_extend(Bfd * bfd, i64 n_bits)
{
    i64 size;

    size = _index(n_bits) + 1;

    mem_extend((void **) & bfd->field, bfd->size, size);
    bfd->size += size;
    memset(bfd->field + bfd->size, 0, size);
}

bool Bfd_bit_check(Bfd bfd, i64 n)
{
    return _index(n) < bfd.size ? Bfd_bit(bfd, n) : 0;
}

void Bfd_dbg(Bfd bfd)
{
    byte buff[__CHAR_BIT__] = {};

    for (i64 k = 0; k < bfd.size; k ++)
    {
        u8_to_bin_buff_le(buff, bfd.field[k]);
        printf("%.*s ", __CHAR_BIT__, buff);
    }

    printf("\n");
}