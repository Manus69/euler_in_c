#include "euler.h"

static bool _is_palindrome_buff(const byte * buff, i64 len)
{
    for (i64 k = 0; k < len / 2; k ++)
    {
        if (buff[k] != buff[len - k - 1]) return false;
    }

    return true;
}

#define BUFF_SIZE 1 << 5
static bool _is_palindrome(u64 x)
{
    i64     len;
    byte    buff[BUFF_SIZE] = {};

    len = sprintf(buff, "%zu", x);

    return _is_palindrome_buff(buff, len);
}

static u64 _largest_palindrome(u64 low, u64 high)
{
    u64 product;
    u64 max;

    max = 0;
    for (u64 x = low; x < high; x ++)
    {
        for (u64 y = x; y < high; y ++)
        {
            product = x * y;
            if ((product > max) && _is_palindrome(product)) max = product;
        }
    }

    return max;
}

#define LOW     100
#define HIGH    1000 

void p_4(void)
{
    u64_dbg(_largest_palindrome(LOW, HIGH));
}