#include "lib.h"
#include <string.h>

char *strchr(const char *str, int charwanted)
{
	const char *p = str;
	char c;

	do
	{
		if ((c = *p++) == (char) charwanted)
			return NO_CONST(--p);
	} while (c);

	return NULL;
}

char *index(const char *str, int c) __attribute__((alias("strchr")));
