#include <stdlib.h>
#include <sys/types.h>

int isatty (int handle);
extern ssize_t read (int __fd, void *__buf, size_t __nbytes);
extern ssize_t write (int __fd, __const void *__buf, size_t __n);
extern int open(const char *filename, int access, ...);
extern int close(int fd);
extern int unlink(const char *filename);
