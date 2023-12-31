#include "Sieve.h"
#include "math.h"

static void _cast_out(Bfd bfd, i64 p)
{
    for (i64 k = 2 * p; k < Bfd_n_bits(bfd); k += p)
    {
        Bfd_bit_clear(bfd, k);
    }
}

static i64 _next_p(Bfd bfd, i64 p)
{
    ++ p;
    while ((p < Bfd_n_bits(bfd)) && (! Bfd_bit(bfd, p))) ++ p;

    return p;
}

#define MIN_SIZE 3
Sieve Sieve_new(i64 size)
{
    Bfd bfd;

    size = size < MIN_SIZE ? MIN_SIZE : size; 
    bfd = Bfd_new1(size);

    Bfd_bit_clear(bfd, 0);
    Bfd_bit_clear(bfd, 1);

    for (i64 p = 2; p < Bfd_n_bits(bfd); p = _next_p(bfd, p))
    {
        _cast_out(bfd, p);
    }

    return (Sieve) {bfd};
}

Sieve Sieve_new_n_primes(i64 n_primes)
{
    i64 size; 

    size = n_primes * math_log2(n_primes);

    return Sieve_new(size);
}

void Sieve_del(Sieve * sieve)
{
    Bfd_del(& sieve->bfd);
    to0(sieve, Sieve);
}

u64 Sieve_size(Sieve sieve)
{
    return Bfd_n_bits(sieve.bfd);
}

bool Sieve_is_prime(Sieve sieve, u64 n)
{
    return Bfd_bit(sieve.bfd, n);
}

u64 Sieve_nth_prime(Sieve sieve, i64 n)
{
    i64 count;

    count = 0;
    for (u64 k = 2; k < Sieve_size(sieve); k ++)
    {
        if (Sieve_is_prime(sieve, k)) count ++;
        if (count == n + 1) return k;
    }

    return 0;
}

Vec Sieve_primes_lt(Sieve sieve, u64 n)
{
    Vec vec;
    
    vec = Vec_new(u64);
    n = n < Sieve_size(sieve) ? n : Sieve_size(sieve);
    
    for (u64 k = 2; k < n; k ++)
    {
        if (Sieve_is_prime(sieve, k)) Vec_push(& vec, k, u64);
    }

    return vec;
}

Vec Sieve_primes(Sieve sieve, u64 count)
{
    Vec vec;
    u64 k;

    k = 2;
    vec = Vec_new(u64);

    while (count && (k < Sieve_size(sieve)))
    {
        if (Sieve_is_prime(sieve, k))
        {
            Vec_push(& vec, k, u64);
            count --;
        }

        k ++;
    }

    return vec;
}

Vec Sieve_to_Vec(Sieve sieve)
{
    return Sieve_primes_lt(sieve, Sieve_size(sieve));
}
