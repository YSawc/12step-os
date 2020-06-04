#include "lib.h"
#include "defines.h"
#include "serial.h"

int putc(unsigned char c) {
  if (c == '\n')
    serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
  return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

int puts(unsigned char *s) {
  while (*s)
    putc(*(s++));
  return 0;
}

void *memset(void *b, int c, long len) {
  char *p;
  for (p = b; len > 0; len--)
    *(p++) = c;
  return b;
}

void *memcpy(void *dst, const void *str, long len) {
  char *d = dst;
  const char *s = str;
  for (long l = len; l > 0; l--)
    *(d++) = *(s++);
  return dst;
}

int memcmp(const void *b1, const void *b2, long len) {
  const char *p1 = b1, *p2 = b2;
  for (long l = len; l > 0; l--) {
    if (*p1 != *p2)
      return (*p1 > *p2) ? 1 : -1;
    p1++;
    p2++;
  }
  return 0;
}

int strlen(const char *s) {
  int len;
  for (len = 0; *s; s++, len++)
    ;
  return len;
}

char *strcpy(char *dst, const char *src) {
  char *d = dst;
  for (const char *s = src;; dst++, s++) {
    *dst = *s;
    if (!s)
      break;
  }
  return d;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 || *s2) {
    if (*s1 != *s2)
      return (*s1 > *s2) ? 1 : -1;
    s1++;
    s2++;
  }
  return 0;
}

int strncmp(char *s1, const char *s2, int len) {
  int l = len;
  while ((*s1 || *s2) && (l > 0)) {
    if (*s1 != *s2)
      return (*s1 > *s2) ? 1 : -1;
    s1++;
    s2++;
    l--;
  }
  return 0;
}
