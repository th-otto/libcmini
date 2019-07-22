#include <stdio.h>
#include <unistd.h>
#include <mint/osbind.h>
#include <sys/types.h>
#include "lib.h"

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	long ret = Fwrite(FILE_GET_HANDLE(stream), size * nmemb, ptr);
	return ret < 0 ? 0 : ret / size;
}
