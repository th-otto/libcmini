#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#if defined(__MSHORT__) || defined(__PUREC__) || defined(__AHCC__)

extern char const __atoi_numstr[];

char *ltoa(long value, char *buffer, int radix);

char *ltoa(long value, char *buffer, int radix)
{
	char *p;
	int neg = 0;
	char tmpbuf[12];
	short i = 0;

	if (value < 0)
	{
		neg = 1;
		value = -value;
	}
	do {
		tmpbuf[i++] = __atoi_numstr[value % radix];
	} while ((value /= radix) != 0);

	if (neg)
		tmpbuf[i++] = '-';
	p = buffer;
	while (--i >= 0)	/* reverse it back  */
		*p++ = tmpbuf[i];
	*p = '\0';

	return buffer;
}

#endif
