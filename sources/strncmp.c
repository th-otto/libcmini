/*
 * strncmp.c
 *
 *  Created on: 29.05.2013
 *      Author: mfro
 */

#include <string.h>
#include <sys/types.h>

int strncmp(const char *s1, const char *s2, size_t max)
{
	register ssize_t count = max;
	register unsigned char c1, c2;
	
	do {
		c1 = (unsigned char) *s1++; c2 = (unsigned char) *s2++;
	} while (--count >= 0 && c1 && c1 == c2);
	if (count < 0)
		return(0);
	return c1 - c2;
}
