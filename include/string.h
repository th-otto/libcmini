/*
 * string.h
 *
 *  Created on: 29.05.2013
 *      Author: mfro
 */

#ifndef _STRING_H_
#define _STRING_H_

#include <stdlib.h>

char *strcat(char *dst, const char *src);
char *strcpy(char *dst, const char *src);
size_t strlen(const char *s);
char *strncat(char *dst, const char *src, size_t max);
int strcmp(const char *s1, const char *s2);
int stricmp(const char *s1, const char *s2);
int strcasecmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t max);
int strnicmp(const char *s1, const char *s2, size_t max);
int strncasecmp(const char *s1, const char *s2, size_t max);
char *strncpy(char *dst, const char *src, size_t max);
char *strdup(const char *s1);
char *strndup(const char *s1, size_t n);
char *strchr(const char *s, int c);
char *strstr(const char *s, const char *wanted);
size_t strspn(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);
char *strpbrk(const char *s, const char *breakat);
char *index(const char *s, int c);
char *strrchr(const char *s, int c);
char *rindex(const char *s, int c);
size_t strnlen(const char* s, size_t maxlen);

void bzero(void *s, size_t n);
void bcopy(const void *src, void *dst, size_t n);
void *memset(void *b, int c, size_t len);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memchr(const void *ptr, int ch, size_t count);
void *memrchr(const void *s, int ucharwanted, size_t size);

char *strerror(int errnum);
char* strerror_r(int errnum, char *buf, size_t bufsize);

char *strrev(char *);
char *strlwr(char *);
char *strupr(char *);

char *basename(const char *filename);
char *dirname(char *path);

char *strtok(char *s1, const char* s2);
char *strtok_r(char *s, const char *delim, char **scanpoint);

#endif /* _STRING_H_ */
