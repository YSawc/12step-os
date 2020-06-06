#include "defines.h"
#include "lib.h"
#include "serial.h"

void init_static_region() {
  extern int erodata, data_start, edata, bss_start, ebss;

  // copy rom data to ram data for static variables.
  _memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
  _memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

  serial_init(SERIAL_DEFAULT_DEVICE);
}

int main() {
  /* init_static_region(); */

  _puts((unsigned char *)"Hello world!\n");

  while (1)
    ;

  return 0;
}
