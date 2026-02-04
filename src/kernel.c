#include "vga/vga.h"
#include "idt/idt.h"
#include "idt/isr.h"

void kernel_main(void)
{
    vga_init();
    print("Initializing VGA driver...\n");

    idt_init();
    isr_init();
    enable_interrupts();
    print("Initializing IDT...\n");

    print("LuminOS Kernel inited!");
}