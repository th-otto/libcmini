/*
 * ctype.h
 *
 *  Created on: 29.05.2013
 *      Author: mfro
 */

#ifndef _CTYPE_H_
#define _CTYPE_H_

int toupper(int c);
int tolower(int c);
int isupper(int c);
int islower(int c);
int isspace(int c);
int isdigit(int c);

#define isdigit(c)	((unsigned char)(c) >= '0' && (unsigned char)(c) <= '9')
#define isupper(c)	((unsigned char)(c) >= 'A' && (unsigned char)(c) <= 'Z')
#define islower(c)	((unsigned char)(c) >= 'a' && (unsigned char)(c) <= 'z')
#define isalpha(c)	(isupper((c)) || islower(c))
#define tolower(c)	(isupper(c) ? ((c) + 'a' - 'A') : (c))
#define toupper(c)	(islower(c) ? ((c) - 'a' - 'A') : (c))

#define isspace(c)  (((c) == ' ') || ((c) == '\t') || ((c == '\n')) || ((c) == '\r') || ((c) == '\v'))

#endif /* CTYPE_H_ */
