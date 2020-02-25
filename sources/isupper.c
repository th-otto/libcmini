#include <ctype.h>

int (isupper)(int c)
{
	return (unsigned char)(c) >= 'A' && (unsigned char)(c) <= 'Z';
}
