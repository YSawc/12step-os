#include "defines.h"

extern void start();

// interrupt function
// http://www.picosystems.net/dl/ds/device/HD64F3069.pdf#%5B%7B%22num%22%3A388%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-189%2C890%2C1%5D
// works as reset vector
void (*vectors[])() = {
    start, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};
