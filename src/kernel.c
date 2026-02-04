#include "vga/vga.h"
#include "idt/idt.h"
#include "idt/isr.h"
#include "drivers/timer/timer.h"
#include "panic.h"

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
    
    print_centered("LuminOS Kernel initialized!", get_color_code(DEFAULT_VGA_TEXT_COLOR, DEFAULT_VGA_BACKGROUND_COLOR));
    timer_wait(2000);
    panic("Welcome to LuminOS!");
}