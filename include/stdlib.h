/*
 * stdlib.h
 *
 *  Created on: 31.05.2013
 *      Author: mfro
 */

#ifndef _STDLIB_H_
#define _STDLIB_H_

typedef unsigned long size_t;

extern int atoi(const char *c);
extern long atol(const char *c);
extern void *malloc(size_t size);
extern void *calloc(size_t nmemb, size_t size);
extern void *realloc(void *ptr, size_t size);
extern void free(void *ptr);

extern char *ltoa(long value, char *buffer, int radix);
extern char *ultoa(unsigned long value, char *buffer, int radix);
#define _ltoa(a, b, c) ltoa((a), (b), (c))
#define _ultoa(a, b, c) ultoa((a), (b), (c))

extern char *getenv(const char *name);

int atexit(void (*func)(void));
extern void exit(int status);
extern void abort(void);

#ifdef __MSHORT__
#define	RAND_MAX (0x7FFF)
#else
#define	RAND_MAX (0x7FFFFFFFL)
#endif

#define	EXIT_FAILURE	1	/* Failing exit status.  */
#define	EXIT_SUCCESS	0	/* Successful exit status.  */

extern void srand (unsigned int __seed);
extern int rand(void);
extern long lrand(void);
extern void srand48(long int seed);

extern long strtol(const char*, char**, int);
extern unsigned long strtoul(const char*, char**, int);
extern long long strtoll(const char*, char**, int);
extern unsigned long long strtoull(const char*, char**, int);

#define abs(j)  ((j) > 0 ? (j) : -(j))

#ifndef NULL
#define NULL	((void *) 0)
#endif

/* Returned by `div'.  */
typedef struct {
	int quot;			/* Quotient.  */
    int rem;			/* Remainder.  */
} div_t;

/* Returned by `ldiv'.  */
#ifndef __ldiv_t_defined
typedef struct {
	long int quot;		/* Quotient.  */
	long int rem;		/* Remainder.  */
} ldiv_t;
# define __ldiv_t_defined	1
#endif

div_t div (int __numer, int __denom) __attribute__ ((__const__));
ldiv_t ldiv (long int __numer, long int __denom) __attribute__ ((__const__));

void *bsearch(const void *key, const void *base, size_t num, size_t size, int (*cmp)(const void *, const void *));

int setenv(const char *name, const char *value, int replace);
int unsetenv(const char *name);

#endif /* _STDLIB_H_ */
