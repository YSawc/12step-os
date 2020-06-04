#include "lib.h"
#include "defines.h"
#include "serial.h"

int _putc(unsigned char c) {
  if (c == '\n')
    serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
  return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

int _puts(unsigned char *s) {
  while (*s)
    _putc(*(s++));
  return 0;
}

int putxval(unsigned long value, int column) {
  unsigned char buf[9];
  unsigned char *p;

  p = buf + sizeof(buf) - 1;
  *(p--) = '\0';

  if (!value && !column)
    column++;

  while (value || column) {
    *(p--) = "0123456789abcdef"[value & 0xf]; // TODO: memo
    value >>= 4;
    if (column)
      column--;
  }

  _puts(p + 1);
  return 0;
}

void *_memset(void *b, int c, long len) {
  char *p;
  for (p = b; len > 0; len--)
    *(p++) = c;
  return b;
}

void *_memcpy(void *dst, const void *str, long len) {
  char *d = dst;
  const char *s = str;

  long l;
  for (l = len; l > 0; l--)
    *(d++) = *(s++);
  return dst;
}

int _memcmp(const void *b1, const void *b2, long len) {
  const char *p1 = b1, *p2 = b2;

  long l;
  for (l = len; l > 0; l--) {
    if (*p1 != *p2)
      return (*p1 > *p2) ? 1 : -1;
    p1++;
    p2++;
  }
  return 0;
}

int _strlen(const char *s) {
  int len;
  for (len = 0; *s; s++, len++)
    ;
  return len;
}

char *_strcpy(char *dst, const char *src) {
  char *d = dst;

  const char *s;
  for (s = src; s; dst++, s++)
    *dst = *s;
  return d;
}

int _strcmp(const char *s1, const char *s2) {
  while (*s1 || *s2) {
    if (*s1 != *s2)
      return (*s1 > *s2) ? 1 : -1;
    s1++;
    s2++;
  }
  return 0;
}

int _strncmp(char *s1, const char *s2, int len) {
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
