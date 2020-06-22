#include "elf.h"
#include "defines.h"
#include "lib.h"

/* ELF header of 32bit: https://wiki.osdev.org/ELF#Header */
struct elf_header {
  struct {
    unsigned char magic[4];
    unsigned char class;
    unsigned char format;
    unsigned char version;
    unsigned char abi;
    unsigned char abi_version;
    unsigned char reserve[7];
  } id; // front of header

  short type;
  short arch;
  long version;
  long entry_point;
  long program_header_offset;
  long section_header_offset;
  long flags;
  short header_si;
  short program_header_size;
  short program_header_num;
  short section_header_size;
  short section_header_num;
  short section_name_index;
};

/* https://wiki.osdev.org/ELF#Program_header */
struct elf_program_header {
  long type;
  long offset;
  long virtual_addr;
  long physical_addr;
  long file_size;
  long memory_size;
  long flags;
  long align;
};

static int elf_check(struct elf_header *header) {
  // read magic number.
  /* https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_layout */
  if (_memcmp(header->id.magic,
              "\x7f"
              "ELF", // same as "45" "4c" "46"
              4))
    return -1;

  if (header->id.class != 1 || header->id.format != 2 ||
      header->id.version != 1 || header->type != 2 || header->version != 1)
    return -1;

  /* https://web.stanford.edu/~ouster/cgi-bin/cs140-winter16/pintos/specs/sysv-abi-update.html/ch4.eheader.html
   */
  if ((header->arch != 46) && (header->arch != 47))
    return -1;

  return 0;
}

static int elf_load_program(struct elf_header *header) {
  int i;
  struct elf_program_header *phdr;

  for (i = 0; i < header->program_header_num; i++) {
    phdr = (struct elf_program_header *)((char *)header +
                                         header->program_header_offset +
                                         header->program_header_size * i);

    if (phdr->type != 1)
      continue;

    putxval(phdr->offset, 6);
    puts((unsigned char *)" ");
    putxval(phdr->virtual_addr, 8);
    puts((unsigned char *)" ");
    putxval(phdr->physical_addr, 8);
    puts((unsigned char *)" ");
    putxval(phdr->file_size, 5);
    puts((unsigned char *)" ");
    putxval(phdr->memory_size, 5);
    puts((unsigned char *)" ");
    putxval(phdr->flags, 2);
    puts((unsigned char *)" ");
    putxval(phdr->align, 2);
    puts((unsigned char *)"\n");
  }

  return 0;
}

int elf_load(char *buf) {
  struct elf_header *header = (struct elf_header *)buf;

  if (elf_check(header) < 0)
    return -1;

  if (elf_load_program(header) < 0)
    return -1;

  return 0;
}
