#include "serial.h"
#include "defines.h"

// http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A1633%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
#define SERIAL_SCI_NUM 3 // count of SCI

#define H8_3069F_SCI0 ((volatile struct h8_3069f_sci *)0xffffb0)
#define H8_3069F_SCI1 ((volatile struct h8_3069f_sci *)0xffffb8)
#define H8_3069F_SCI2 ((volatile struct h8_3069f_sci *)0xffffc0)

// http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A1645%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
struct h8_3069f_sci {
  volatile uint8_t smr;
  volatile uint8_t brr;
  volatile uint8_t scr;
  volatile uint8_t tdr;
  volatile uint8_t ssr;
  volatile uint8_t rdr;
  volatile uint8_t scmr;
};

// serial mode register
// http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A1660%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
#define H8_3069F_SCI_SMR_CKS_PER1 (0 << 0)
#define H8_3069F_SCI_SMR_CKS_PER4 (1 << 0)
#define H8_3069F_SCI_SMR_CKS_PER16 (2 << 0)
#define H8_3069F_SCI_SMR_CKS_PER64 (3 << 0)
#define H8_3069F_SCI_SMR_MP (1 << 2)
#define H8_3069F_SCI_SMR_STOP (1 << 3)
#define H8_3069F_SCI_SMR_OE (1 << 4)
#define H8_3069F_SCI_SMR_PE (1 << 5)
#define H8_3069F_SCI_SMR_CHR (1 << 6)
#define H8_3069F_SCI_SMR_CA (1 << 7)

// serial controll register
// http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A1672%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
#define H8_3069F_SCI_SCR_CKE0 (1 << 0)
#define H8_3069F_SCI_SCR_CKE1 (1 << 1)
#define H8_3069F_SCI_SCR_TEIE (1 << 2)
#define H8_3069F_SCI_SCR_MPIE (1 << 3)
#define H8_3069F_SCI_SCR_RE (1 << 4)
#define H8_3069F_SCI_SCR_TE (1 << 5)
#define H8_3069F_SCI_SCR_RIE (1 << 6)
#define H8_3069F_SCI_SCR_TIE (1 << 7)

// serial status register
// http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A1687%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
#define H8_3069F_SCI_SSR_MPBT (1 << 0)
#define H8_3069F_SCI_SSR_MPB (1 << 1)
#define H8_3069F_SCI_SSR_TEND (1 << 2)
#define H8_3069F_SCI_SSR_PER (1 << 3)
#define H8_3069F_SCI_SSR_FERERS (1 << 4)
#define H8_3069F_SCI_SSR_ORER (1 << 5)
#define H8_3069F_SCI_SSR_RDRF (1 << 6)
#define H8_3069F_SCI_SSR_TDRE (1 << 7)

// three canel
// http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A1639%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
static struct {
  volatile struct h8_3069f_sci *sci;
} regs[SERIAL_SCI_NUM] = {
    {H8_3069F_SCI0},
    {H8_3069F_SCI1},
    {H8_3069F_SCI2},
};

int serial_init(int idx) {
  volatile struct h8_3069f_sci *sci = regs[idx].sci;
  sci->scr = 0;
  sci->smr = 0;
  sci->brr = 64;
  sci->scr = H8_3069F_SCI_SCR_RE | H8_3069F_SCI_SCR_TE;
  sci->ssr = 0;

  return 0;
}

int serial_is_send_enable(int idx) {
  volatile struct h8_3069f_sci *sci = regs[idx].sci;
  return (sci->ssr & H8_3069F_SCI_SSR_TDRE);
  // http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A1687%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
}

int serial_send_byte(int idx, unsigned char c) {
  volatile struct h8_3069f_sci *sci = regs[idx].sci;
  while (!serial_is_send_enable(idx))
    ;
  sci->tdr = c;
  sci->ssr &= ~H8_3069F_SCI_SSR_TDRE; // TODO: memo

  return 0;
}

int serial_is_recv_enable(int idx) {
  volatile struct h8_3069f_sci *sci = regs[idx].sci;
  return (sci->ssr & H8_3069F_SCI_SSR_RDRF);
}

unsigned char serial_recv_byte(int idx) {
  volatile struct h8_3069f_sci *sci = regs[idx].sci;
  unsigned char c;

  while (!serial_is_recv_enable(idx))
    ;
  c = sci->rdr;
  // ssr :
  // http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A1687%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
  sci->ssr &= ~H8_3069F_SCI_SSR_RDRF;
  return c;
}
