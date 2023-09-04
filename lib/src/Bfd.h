#ifndef BFD_H
#define BFD_H

#include "def.h"
#include "macro.h"

typedef struct Bfd Bfd;

struct Bfd
{
    u8 *    field;
    i64     size;
};

Putf_gen(Bfd)
Swapf_gen(Bfd)

Bfd     Bfd_new0(i64 n_bits);
Bfd     Bfd_new1(i64 n_bits);
void    Bfd_del(Bfd * bfd);
i64     Bfd_n_bits(Bfd bfd);
bool    Bfd_bit(Bfd bfd, i64 n);
void    Bfd_bit_set(Bfd bfd, i64 n);
void    Bfd_bit_clear(Bfd bfd, i64 n);
void    Bfd_bit_toggle(Bfd bfd, i64 n);
void    Bfd_extend(Bfd * bfd, i64 n_bits);
bool    Bfd_bit_check(Bfd bfd, i64 n);
void    Bfd_dbg(Bfd bfd);

#endif