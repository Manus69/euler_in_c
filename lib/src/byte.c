#include "def.h"

bool byte_is_numeric(byte x)
{
    return x >= '0' && x <= '9';
}

bool byte_is_lower(byte x)
{
    return x >= 'a' && x <= 'z';
}

bool byte_is_upper(byte x)
{
    return x >= 'A' && x <= 'Z';
}

bool byte_is_alpha(byte x)
{
    return byte_is_lower(x) || byte_is_upper(x);
}

bool byte_is_ws(byte x)
{
    return x == ' ' || x == '\n' || x == '\t';
}

byte byte_to_lower(byte x)
{
    return x + ('a' - 'A');
}

byte byte_to_lower_check(byte x)
{
    return byte_is_upper(x) ? byte_to_lower(x) : x;
}

byte byte_matching_bracket(byte ob)
{
    if (ob == '(') return ')';
    if (ob == '{') return '}';
    if (ob == '[') return ']';
    if (ob == '<') return '>';
    if (ob == '\'') return '\'';
    if (ob == '"') return '"';

    return 0;
}