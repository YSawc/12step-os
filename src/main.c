#include "defines.h"
#include "lib.h"
#include "serial.h"

int main() {
  serial_init(SERIAL_DEFAULT_DEVICE);

  puts((unsigned char *)"Hello world!\n");

  while (1) // roop while
    ;

  return 0;
}
