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

int global_data = 0x10;
int global_bss;
static int static_data = 0x20;
static int static_bss;

static void printval(void) {
  util_puts((unsigned char *)"global_data = ", global_data, 0);
  util_puts((unsigned char *)"global_bss = ", global_bss, 0);
  util_puts((unsigned char *)"static_data = ", static_data, 0);
  util_puts((unsigned char *)"static_bss = ", static_bss, 0);
}

int main() {
  init_static_region();

  puts((unsigned char *)"Hello world!\n");
  printval();

  puts((unsigned char *)"Overwrite variables.\n");
  global_data = 0x20;
  global_bss = 0x30;
  static_data = 0x40;
  static_bss = 0x50;
  printval();

  while (1)
    ;

  return 0;
}
