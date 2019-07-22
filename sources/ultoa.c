#include <stdlib.h>
#include <string.h>

static char const _numstr[] = "0123456789ABCDEF";

char *ultoa(unsigned long value, char *buffer, int radix)
{
	char *p = buffer;

	do {
		*p++ = _numstr[value % radix];
	} while ((value /= radix) != 0);

	*p = '\0';

	return strrev(buffer);
}
