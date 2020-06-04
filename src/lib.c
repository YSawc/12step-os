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
