#include <stdio.h>
#include <stdarg.h>
#include "lib.h"

struct _mem_stream { char *xstring; char *xestring; };

int vsprintf(char *str, const char *format, va_list va)
{
	struct _mem_stream stream;

	stream.xstring = str;
	stream.xestring = 0;

	doprnt(__addchar, &stream, format, va);
	*stream.xstring++ = '\0';

	/* -1 on the account of terminating 0 */
	return stream.xstring - str - 1;
}
