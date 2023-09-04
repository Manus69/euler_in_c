#include "u8.h"

void u8_to_bin_buff_le(byte * buff, u8 x)
{
    const byte * digits = "01";

    for (u64 k = 0; k < __CHAR_BIT__; k ++)
    {
        buff[k] = digits[x & 1];
        x >>= 1;
    }
}