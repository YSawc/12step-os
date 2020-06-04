#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

int putc(unsigned char c);
int puts(unsigned char *s);
void *memset(void *b, int c, long len);
void *memcpy(void *dst, const void *str, long len);
int memcmp(const void *b1, const void *b2, long len);
int strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(char *dst, const char *src, int len);

#endif
