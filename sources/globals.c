#include "lib.h"

/* globals */

short _app = 1;
unsigned long _PgmSize;
BASEPAGE *_base=0;
/* BasPag for libcmini compatibility */
extern BASEPAGE *BasPag __attribute__((alias("_base")));

int errno;

char **environ;
long __libc_argc = 1;

static char *__libc_argv_default[] = { "unknown application", NULL };
char **__libc_argv = __libc_argv_default;

static FILE _StdInF =  { _IOMAGIC, NULL, NULL, NULL, NULL, 0, (void *)0, 0 };
static FILE _StdOutF = { _IOMAGIC, NULL, NULL, NULL, NULL, 0, (void *)1, 0 };
static FILE _StdErrF = { _IOMAGIC, NULL, NULL, NULL, NULL, 0, (void *)2, 0 };

FILE *stdin = &_StdInF;
FILE *stdout = &_StdOutF;
FILE *stderr = &_StdErrF;
