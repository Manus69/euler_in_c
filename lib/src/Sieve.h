#ifndef SIEVE_H
#define SIEVE_H

#include "Bfd.h"
#include "Vec.h"

typedef struct Sieve Sieve;

struct Sieve
{
    Bfd bfd;
};

Sieve Sieve_new(i64 size);
void Sieve_del(Sieve * sieve);
u64 Sieve_size(Sieve sieve);
bool Sieve_is_prime(Sieve sieve, u64 n);
Vec Sieve_primes_lt(Sieve sieve, u64 n);
Vec Sieve_primes(Sieve sieve, u64 count);
Vec Sieve_to_Vec(Sieve sieve);

#endif