#include "vga/vga.h"
#include "idt/idt.h"
#include "idt/isr.h"
#include "drivers/timer/timer.h"

void kernel_main(void)
{
    vga_init();
    print("Initializing VGA driver...\n");

    print("Initializing IDT...\n");
    idt_init();
    isr_init();
    
    print("Initializing timer...\n");
    timer_init();
    
    enable_interrupts();

    print("LuminOS Kernel inited!\n");
    timer_wait(2000);
    print("LuminOS Kernel inited x2!\n");
}