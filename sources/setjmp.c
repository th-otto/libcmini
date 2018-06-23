#include <setjmp.h>

/*
 * must be compiled with -fomit-frame-pointer,
 * otherwise we save the fp of the setjmp function
 * instead of the callers
 */

#pragma GCC optimize "-fomit-frame-pointer"

int setjmp(jmp_buf buf)
{
	register long *a0 asm("%a0") = buf;
	register void *a1 asm("%a1") = __builtin_return_address(0);
	__asm__ __volatile__(
		"	movem.l	%%d2-%%d7/%%a1-%%a7,(%[regs])	\n\t"
#ifdef __mcffpu__
		"	fmovem%.d %%fp0-%%fp7,52(%[regs])	\n\t"
#endif
#ifdef __HAVE_68881__
		"	fmovem%.x %%fp0-%%fp7,52(%[regs])	\n\t"
#endif
		:							/* output */
		: [regs] "a" (a0), "a"(a1)	/* input */
		: "memory"
	);
	return 0;
}

void longjmp(jmp_buf buf, int val)
{
	register int d0 asm("%d0") = val;
	register long *a0 asm("%a0") = buf;
	
	if (d0 == 0)	/* avoid infinite loop */
		d0 = 1;

	__asm__ __volatile__(
		"	movem.l	(%[a0]),%%d2-%%d7/%%a1-%%a7	\n\t"
#ifdef __mcffpu__
		"	fmovem%.d 52(%[a0]),%%fp0-%%fp7	\n\t"
#endif
#ifdef __HAVE_68881__
		"	fmovem%.x 52(%[a0]),%%fp0-%%fp7	\n\t"
#endif
		"	jmp (%%a1)								\n\t"
		:							/* output */
		: [a0]"a"(a0), "d" (d0)
		: /* not reached; so no need to declare any clobbered regs */
	);
	__builtin_unreachable();
}
