#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

int putc(unsigned char c);
int puts(unsigned char *s);
void *memset(void *b, int c, long len);
void *memcpy(void *dst, const void *str, long len);
int memcmp(const void *b1, const void *b2, long len);

#endif
