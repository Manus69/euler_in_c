#include "euler.h"

#define N 1000000

static bool _is_palindrome(const byte * cstr, i64 len)
{
    i64 left;
    i64 right;

    left = 0;
    right = len - 1;

    while (left < right)
    {
        if (cstr[left] != cstr[right]) return false;
        left ++;
        right --;
    }

    return true;

}

void p_36(void)
{
    u64 sum;
    Str str;

    sum = 0;
    for (u64 k = 1; k < N; k ++)
    {
        if (k % 2 == 0 || k % 10 == 0) continue;

        str = u64_to_Str(k);
        if (! _is_palindrome(Str_first(str), Str_len(str)))
        {
            Str_del(& str);
            continue;
        }
        
        Str_del(& str);
        str = u64_to_Str_bin(k);
        if (_is_palindrome(Str_first(str), Str_len(str))) sum += k;
        Str_del(& str);
    }

    u64_dbg(sum);
}