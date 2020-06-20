#include "defines.h"
#include "elf.h"
#include "lib.h"
#include "serial.h"
#include "xmodem.h"

static void init_static_region() {
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
  puts((unsigned char *)"\n");
  util_puts((unsigned char *)"global_bss = ", global_bss, 0);
  puts((unsigned char *)"\n");
  util_puts((unsigned char *)"static_data = ", static_data, 0);
  puts((unsigned char *)"\n");
  util_puts((unsigned char *)"static_bss = ", static_bss, 0);
  puts((unsigned char *)"\n");
}

static int dump(char *buf, long size) {

  if (size < 0) {
    puts((unsigned char *)"no data.\n");
    return -1;
  }

  long i;
  for (i = 0; i < size; i++) {
    putxval(buf[i], 2);
    if ((i & 0xf) == 15) {
      puts((unsigned char *)"\n");
    } else {
      if ((i & 0xf) == 7)
        puts((unsigned char *)" ");
      puts((unsigned char *)" ");
    }
  }
  puts((unsigned char *)"\n");

  return 0;
}

static void wait() {
  volatile long i;
  for (i = 0; i < 300000; i++)
    ;
}

int main() {

  static char buf[16];
  static long size = -1;
  static unsigned char *loadbuf = NULL;
  extern int buffer_start;

  init_static_region();

  puts((unsigned char *)"bootloader started\n");

  while (1) {
    puts((unsigned char *)"> ");
    gets((unsigned char *)buf);

    if (!_strcmp(buf, "load")) {
      loadbuf = (unsigned char *)(&buffer_start);
      size = xmodem_recv((char *)loadbuf);
      wait();
      if (size < 0) {
        puts((unsigned char *)"\nXMODEM receive error!\n");
      } else {
        puts((unsigned char *)"\nXMODEM receive succeeded!\n");
      }
    } else if (!_strcmp(buf, "test")) {
      printval();
      global_data = 0x10;
      puts((unsigned char *)"global_data comparison started\n");
      icmp_(global_data, 0x10);
      global_bss = 0x30;
      puts((unsigned char *)"global_bss comparison started\n");
      icmp_(global_bss, 0x30);
      static_data = 0x20;
      puts((unsigned char *)"static_data comparison started\n");
      icmp_(static_data, 0x20);
      static_bss = 0x50;
      puts((unsigned char *)"static_bss comparison started\n");
      icmp_(static_bss, 0x50);
    } else if (!_strcmp(buf, "dump")) {
      util_puts((unsigned char *)"size: ", size, 0);
      puts((unsigned char *)"\n");
      dump((char *)loadbuf, size);
    } else if (!_strcmp(buf, "run")) {
      elf_load((char *)loadbuf);
    } else {
      puts((unsigned char *)"unknown.\n");
    }
  }

  return 0;
}
