#include "vga/vga.h"

void kernel_main(void)
{
    vga_init();
 
    print("Text 1\nText 2");
}