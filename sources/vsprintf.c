#include <stdio.h>
#include <stdarg.h>
#include "lib.h"

int vsprintf(char *str, const char *format, va_list va)
{
	struct _mem_stream stream;

	stream.xstring = str;
	stream.xestring = 0;

	doprnt(__addchar, &stream, format, va);
	*stream.xstring = '\0';

	return stream.xstring - str;
}
