#include <stdlib.h>
#include <string.h>

static char const _numstr[] = "0123456789ABCDEF";

#ifdef __MSHORT__
char *itoa(int value, char *buffer, int radix)
{
	char *p = buffer;
	int neg = 0;

	if (value < 0)
	{
		neg = 1;
	}
	do {
		*p++ = _numstr[value % radix];
	} while ((value /= radix) != 0);

	if (neg)
		*p++ = '-';
	*p = '\0';

	return strrev(buffer);
}
#endif
