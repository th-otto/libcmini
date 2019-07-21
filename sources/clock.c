#include <time.h>
#include <mint/osbind.h>

#define _hz_200                ((volatile unsigned long *) 0x4baL)

clock_t clock(void)
{
	long ssp;
	clock_t ret;

	ssp = Super(0L);

	ret = *_hz_200;

	Super(ssp);

	return ret;
}

