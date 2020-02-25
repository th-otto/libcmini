#include <ctype.h>

int (islower)(int c)
{
	return (unsigned char)(c) >= 'a' && (unsigned char)(c) <= 'z';
}
