#include "euler.h"

#define TXT_FILE        "txt.txt"
#define SRC_TEST_FILE   "./lib/src/regex_match.c"

void _i64_test(i64 n)
{
    Vec v = Vec_new(i64);
    for (i64 k = 0; k < n; k ++)
    {
        Vec_push(& v, n - k, i64);
    }

    sort_quick(Vec_to_view(v), i64);
    // sort_quick_f(Vec_to_view(v), (Putf) i64_put, (Swapf) i64_swap, (Cmpf) _test_cmp);
    // Vec_map(& v, (F) i64_dbgf);
    i64_dbgf(Vec_last(v));  

    Vec_del(& v);
}

void _Str_test()
{
    Str s = io_read_file(TXT_FILE);
    Vec v = Str_split_slices(s, '\n');

    sort_quick(Vec_to_view(v), StrSlc);
    // Vec_map(& v, (F) StrSlc_dbg);
    StrSlc_dbgf(Vec_last(v));
    
    Str_del(& s);
    Vec_del(& v);
}

void _Bfd_test()
{
    i64 n = 10;
    Bfd bfd = Bfd_new0(n);

    Bfd_bit_set(bfd, 1);
    Bfd_dbg(bfd);
    
    Bfd_bit_clear(bfd, 1);
    Bfd_dbg(bfd);

    Bfd_bit_set(bfd, 11);
    Bfd_bit_toggle(bfd, 9);
    Bfd_dbg(bfd);

    Bfd_del(& bfd);
}

void _Sieve_test(u64 n)
{
    Sieve s = Sieve_new(n);
    Vec v = Sieve_to_Vec(s);

    // Vec_map(v, (F) u64_dbgf);
    u64_dbgf(Vec_last(v));

    Sieve_del(& s);
    Vec_del(& v);
}

void _fold_test(i64 n)
{
    Vec v = Vec_new(i64);
    for (i64 k = 0; k <= n; k ++)
    {
        Vec_push(& v, k, i64);
    }

    i64 x = 0;
    Vec_fold(& x, v, i64_addf);
    Vec_del(& v);
    
    i64_dbg(x);
    u64_dbg(math_arith_prog_sum(n));
}

void _Pair_test()
{
    i64 n = 1 << 25;
    Vec v = Vec_new(Pair);
    for (i64 k = 0; k < n; k ++)
    {
        Pair p = Pair_new(k, -k, i64, i64);
        Vec_push(& v, p, Pair);
    }

    Pair p = deref(Pair) Vec_last(v);
    i64_dbgf(Pair_get(p, 0));
    i64_dbgf(Pair_get(p, 1));

    Vec_map(v, (F) Pair_del);
    Vec_del(& v);
}

Pair_struct_gen(i64, i64)

void _Pair_typed_test()
{
    i64 n = 1 << 25;
    Vec v = Vec_new(Pair_i64_i64);
    for (i64 k = 0; k < n; k ++)
    {
        Pair_i64_i64 p = {k , -k};
        Vec_push(& v, p, Pair_i64_i64);

    }

    Pair_i64_i64 x = deref(Pair_i64_i64) Vec_last(v);
    printf("%ld %ld\n", x.left, x.right);

    Vec_del(& v);
}

void _Deck_test(i64 n)
{
    Deck d = Deck_new(i64);
    for (i64 k = 0; k < n; k ++)
    {
        Deck_push_right(& d, k, i64);
        Deck_push_left(& d, k, i64);
    }

    sort_quick(Deck_to_View(d), i64);
    // Deck_map(d, (F) i64_dbgf);
    i64_dbgf(Deck_last(d));

    Deck_del(& d);
}

void _Bigu_test()
{
    Bigu x, y, z;

    x = Bigu_new(999);
    y = Bigu_new(9);
    z = Bigu_mult(x, y);

    Bigu_dbg(z);

    mem_vmap((F) Bigu_del, & x, & y, & z);

    x = Bigu_from_cstr("1001");
    Bigu_dbg(x);

    y = Bigu_from_cstr("69");
    Bigu_dbg(y);

    z = Bigu_mult(x, y);
    Bigu_dbg(z);

    mem_vmap((F) Bigu_del, & x, & y, & z);

    Str s = Str_repeat_cstr("9", 3000);
    x = Bigu_from_cstr(Str_first(s));
    y = Bigu_from_cstr(Str_first(s));
    Bigu_dbg(y);

    z = Bigu_mult(x, y);
    Bigu_dbg(z);

    Str_del(& s);
    mem_vmap((F) Bigu_del, & x, & y, & z);

}

void _sqrt_test()
{
    i64 n = 100;
    for (i64 k = 0; k < n; k ++)
    {
        double x = math_sqrt(k);
        printf("%ld %f\n", k, x);
    }
}

// void _Regex_test_0()
// {
//     RegexParseResult rpr = Regex_compile_cstr("^ . + <1> * $");
//     RegexMatch m = Regex_match_cstr("ass\n 1 \n x", rpr);

//     RegexMatch_dbg(m);
//     RegexParseResult_del(& rpr);
// }

// void _Regex_test_1()
// {
//     Str str = io_read_file(TXT_FILE);
//     Vec vec = Regex_match_all_slices(Str_to_slice(str), "^ * <gnu> * $");

//     Vec_map(vec, (F) StrSlc_dbgf);

//     Vec_del(& vec);
//     Str_del(& str);
// }

// void _Regex_test_2()
// {
//     StrSlc slc = StrSlc_from_cstr("int main()\n{\nreturn 0;\n}");
//     Vec vec = Regex_match_all_slices(slc, "^ * ')'");

//     Vec_map(vec, (F) StrSlc_dbgf);
//     Vec_del(& vec);
// }

// void _Regex_test_3()
// {
//     Str str = io_read_file(SRC_TEST_FILE);
//     Vec vec = Regex_match_all_slices(Str_to_slice(str), "'static' ! * ')' $");

//     Vec_map(vec, (F) StrSlc_dbgf);
//     Vec_del(& vec);
//     Str_del(& str);
// }