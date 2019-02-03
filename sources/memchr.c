#include <string.h>

#ifndef NO_CONST
#  ifdef __GNUC__
#    define NO_CONST(p) __extension__({ union { const void *cs; void *s; } x; x.cs = p; x.s; })
#  else
#    define NO_CONST(p) ((void *)(p))
#  endif
#endif

void *memchr(const void *s, int ucharwanted, size_t size)
{
	const char *scan;
	size_t n;

	scan = (const char *) s;
	for (n = size; n > 0; n--)
		if (*scan == (char) ucharwanted)
			return NO_CONST(scan);
		else
			scan++;

	return NULL;
}
