#include "idt.h"
#include <stddef.h>

static struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idt_ptr;
static interrupt_handler_t interrupt_handlers[IDT_ENTRIES];

void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags)
{
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].flags = flags | IDT_FLAG_PRESENT;
}

void idt_init(void)
{
    for (int i = 0; i < IDT_ENTRIES; i++)
        interrupt_handlers[i] = NULL;

    idt_ptr.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
    idt_ptr.base = (uint32_t)&idt;
    
    idt_load((uint32_t)&idt_ptr);
}

void register_interrupt_handler(uint8_t interrupt, interrupt_handler_t handler)
{
    if (interrupt < IDT_ENTRIES)
        interrupt_handlers[interrupt] = handler;
}

interrupt_handler_t get_interrupt_handler(uint8_t interrupt)
{
    if (interrupt < IDT_ENTRIES)
        return interrupt_handlers[interrupt];
    return NULL;
}
