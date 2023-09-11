#ifndef EULER_H
#define EULER_H

#include "../lib/libEuler.h"
#include <stdio.h>

u64 sum_digits_len(const byte * cstr, i64 len);
u64 sum_digits(const byte * cstr);

void _i64_test(i64 n);
void _Str_test();
void _Bfd_test();
void _Sieve_test(u64 n);
void _fold_test(i64 n);
void _Pair_test();
void _Pair_typed_test();
void _Deck_test(i64 n);
void _Bigu_test();
void _sqrt_test();

#endif