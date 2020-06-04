#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

int _putc(unsigned char c);
int _puts(unsigned char *s);
int _putxval(unsigned long value, int column);
void *_memset(void *b, int c, long len);
void *_memcpy(void *dst, const void *str, long len);
int _memcmp(const void *b1, const void *b2, long len);
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(char *dst, const char *src, int len);

#endif
