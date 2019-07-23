#include <stdio.h>

int feof(FILE *stream)
{
	return stream->__eof;
}
