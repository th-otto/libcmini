#include <stdlib.h>
#include <mint/osbind.h>
#include "lib.h"

int putchar(int c)
{
	return fputc(c, stdout);
}
