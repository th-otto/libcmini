#include <stdio.h>

int fflush(FILE *stream)
{
	stream->__pushback = EOF;
	stream->__pushed_back = 0;
	return 0;
}

