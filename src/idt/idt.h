#include <stdint.h>

struct idt_entry
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct interrupt_frame
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));

#define IDT_FLAG_PRESENT    0x80
#define IDT_FLAG_RING0      0x00
#define IDT_FLAG_RING3      0x60
#define IDT_FLAG_INTERRUPT  0x0E
#define IDT_FLAG_TRAP       0x0F

#define IDT_ENTRIES 256

void idt_init(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

typedef void (*interrupt_handler_t)(struct interrupt_frame*);

void register_interrupt_handler(uint8_t interrupt, interrupt_handler_t handler);
interrupt_handler_t get_interrupt_handler(uint8_t interrupt);

extern void idt_load(uint32_t);
extern void enable_interrupts(void);
extern void disable_interrupts(void);