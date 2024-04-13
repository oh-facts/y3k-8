#ifndef YK_STRING_H
#define YK_STRING_H

#include "common.h"
#include <string.h>

#define CHAR_TO_INT(c) ((c) - '0')

internal inline b32 is_digit(char a)
{
    return (a >= '0' && a <= '9');
}

internal inline b32 is_alpha(char a)
{
    return ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'));
}

#endif