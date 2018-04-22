#include <stdlib.h>
#include <mint/osbind.h>
#include "lib.h"

int putchar(int c)
{
	(void) Cconout(c);
	return 1;
}
