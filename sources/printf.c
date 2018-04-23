#include <stdlib.h>
#include <mint/osbind.h>
#include "lib.h"

int printf(const char *fmt, ...)
{
	int ret;

	va_list va;
	va_start(va, fmt);
	ret = doprnt((int (*)(int, void *)) putchar, NULL, fmt, va);
	va_end(va);

	return ret;
}
