#include <stdio.h>
#include <stdarg.h>
#include "lib.h"

static int fpc(int c, void *fp)
{
	return fputc(c, (FILE *) fp);
}

int vfprintf(FILE *stream, const char *format, va_list ap)
{
	return doprnt(fpc, stream, format, ap);
}


