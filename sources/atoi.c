/*
 * atoi.c
 *
 *  Created on: 29.05.2013
 *      Author: mfro
 */

#include <string.h>
#include <ctype.h>

int atoi(const char *c)
{
    int value = 0;

    while (isspace(*c)) c++;

    while (isdigit(*c))
    {
        value *= 10;
        value += (int) (*c - '0');
        c++;
    }
    return value;
}
