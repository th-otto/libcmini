#include <stdio.h>
#include "lib.h"


int __flshfp(FILE *stream, int c)
{
	return putc(c, stream);
}
