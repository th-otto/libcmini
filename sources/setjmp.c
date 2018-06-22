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
	__asm__ __volatile__(
		"	movem.l	%%d2-%%d7/%%a2-%%a7,4(%[regs])	\n\t"
#ifdef __mcffpu__
		"	fmovem.d %%fp0-%%fp7,52(%[regs])	\n\t"
#endif
#ifdef __HAVE_68881__
		"	fmovem.x %%fp0-%%fp7,52(%[regs])	\n\t"
#endif
		:							/* output */
		: [regs] "a" (a0)	/* input */
		: "memory"
	);
	buf[0] = (long)__builtin_return_address(0);
	return 0;
}

void longjmp(jmp_buf buf, int val)
{
	register int d0 asm("%d0") = val;
	register long *a0 asm("%a0") = buf;
	
	if (val == 0)	/* avoid infinite loop */
		val = 1;

	__asm__ __volatile__(
		"	movem.l	4(%[a0]),%%d2-%%d7/%%a2-%%a7	\n\t"
#ifdef __mcffpu__
		"	fmovem.d 52(%[a0]),%%fp0-%%fp7	\n\t"
#endif
#ifdef __HAVE_68881__
		"	fmovem.x 52(%[a0]),%%fp0-%%fp7	\n\t"
#endif
		"	move.l	(%[a0]),%[a0]	\n\t"
		"	jmp (%[a0])								\n\t"
		:							/* output */
		: [a0]"a"(a0), "d" (d0)
		: /* not reached; so no need to declare any clobbered regs */
	);
	__builtin_unreachable();
};
