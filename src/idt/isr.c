#include "isr.h"
#include "idt.h"
#include "../vga/vga.h"
#include <stddef.h>
#include <stdint.h>

extern void isr0(), isr1(), isr2(), isr3(), isr4(), isr5(), isr6(), isr7();
extern void isr8(), isr9(), isr10(), isr11(), isr12(), isr13(), isr14(), isr15();
extern void isr16(), isr17(), isr18(), isr19(), isr20(), isr21(), isr22(), isr23();
extern void isr24(), isr25(), isr26(), isr27(), isr28(), isr29(), isr30(), isr31();
extern void irq0(), irq1(), irq2(), irq3(), irq4(), irq5(), irq6(), irq7();
extern void irq8(), irq9(), irq10(), irq11(), irq12(), irq13(), irq14(), irq15();

static void pic_send_eoi(uint8_t irq)
{
    if (irq >= 8)
    {
        __asm__ volatile("movb $0x20, %al");
        __asm__ volatile("outb %al, $0xA0");
    }

    __asm__ volatile("movb $0x20, %al");
    __asm__ volatile("outb %al, $0x20");
}

static void pic_init(void)
{
    __asm__ volatile("movb $0x11, %al");
    __asm__ volatile("outb %al, $0x20");
    
    __asm__ volatile("movb $0x20, %al");
    __asm__ volatile("outb %al, $0x21");
    
    __asm__ volatile("movb $0x04, %al");
    __asm__ volatile("outb %al, $0x21");
    
    __asm__ volatile("movb $0x01, %al");
    __asm__ volatile("outb %al, $0x21");
    
    __asm__ volatile("movb $0x11, %al");
    __asm__ volatile("outb %al, $0xA0");
    
    __asm__ volatile("movb $0x28, %al");
    __asm__ volatile("outb %al, $0xA1");
    
    __asm__ volatile("movb $0x02, %al");
    __asm__ volatile("outb %al, $0xA1");
    
    __asm__ volatile("movb $0x01, %al");
    __asm__ volatile("outb %al, $0xA1");
    
    __asm__ volatile("movb $0xFC, %al");
    __asm__ volatile("outb %al, $0x21");
    
    __asm__ volatile("movb $0xFF, %al");
    __asm__ volatile("outb %al, $0xA1");
}

void interrupt_handler(struct interrupt_frame* frame)
{
    interrupt_handler_t handler = get_interrupt_handler(frame->int_no);
    
    if (handler != NULL)
        handler(frame);
    else
    {
        print("Unhandled interrupt: ");
        print_hex(frame->int_no);
        print("\n");
    }
    
    if (frame->int_no >= 32 && frame->int_no < 48)
        pic_send_eoi(frame->int_no - 32);
}

// Обработчики исключений
void isr_handler_divide_by_zero(struct interrupt_frame* frame)
{
    print("Exception: Divide by Zero\n");
}

void isr_handler_debug(struct interrupt_frame* frame)
{
    print("Exception: Debug\n");
}

void isr_handler_nmi(struct interrupt_frame* frame)
{
    print("Exception: NMI\n");
}

void isr_handler_breakpoint(struct interrupt_frame* frame)
{
    print("Exception: Breakpoint\n");
}

void isr_handler_overflow(struct interrupt_frame* frame)
{
    print("Exception: Overflow\n");
}

void isr_handler_bounds(struct interrupt_frame* frame)
{
    print("Exception: Bounds Check\n");
}

void isr_handler_invalid_opcode(struct interrupt_frame* frame)
{
    print("Exception: Invalid Opcode\n");
}

void isr_handler_device_not_available(struct interrupt_frame* frame)
{
    print("Exception: Device Not Available\n");
}

void isr_handler_double_fault(struct interrupt_frame* frame)
{
    print("Exception: Double Fault\n");
}

void isr_handler_invalid_tss(struct interrupt_frame* frame)
{
    print("Exception: Invalid TSS\n");
}

void isr_handler_segment_not_present(struct interrupt_frame* frame)
{
    print("Exception: Segment Not Present\n");
}

void isr_handler_stack_fault(struct interrupt_frame* frame)
{
    print("Exception: Stack Fault\n");
}

void isr_handler_general_protection_fault(struct interrupt_frame* frame)
{
    print("Exception: General Protection Fault\n");
    print("Error code: ");
    print_hex(frame->err_code);
    print("\n");
}

void isr_handler_page_fault(struct interrupt_frame* frame)
{
    print("Exception: Page Fault\n");
    print("Error code: ");
    print_hex(frame->err_code);
    print("\n");
}

void isr_handler_fpu_error(struct interrupt_frame* frame)
{
    print("Exception: FPU Error\n");
}

void isr_handler_alignment_check(struct interrupt_frame* frame)
{
    print("Exception: Alignment Check\n");
}

void isr_handler_machine_check(struct interrupt_frame* frame)
{
    print("Exception: Machine Check\n");
}

void isr_handler_simd_exception(struct interrupt_frame* frame)
{
    print("Exception: SIMD Floating-Point Exception\n");
}

void irq_handler_timer(struct interrupt_frame* frame)
{
    print(".");
}

void irq_handler_keyboard(struct interrupt_frame* frame)
{
    uint8_t scancode;
    __asm__ volatile("inb %%dx, %%al" : "=a"(scancode) : "d"((uint16_t)0x60));
    
    if (scancode < 0x80)
    {
        
    }
}

void isr_init(void)
{
    pic_init();
    
    idt_set_gate(0, (uint32_t)isr0, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(1, (uint32_t)isr1, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(2, (uint32_t)isr2, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(3, (uint32_t)isr3, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(4, (uint32_t)isr4, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(5, (uint32_t)isr5, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(6, (uint32_t)isr6, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(7, (uint32_t)isr7, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(8, (uint32_t)isr8, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(9, (uint32_t)isr9, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(10, (uint32_t)isr10, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(11, (uint32_t)isr11, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(12, (uint32_t)isr12, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(13, (uint32_t)isr13, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(14, (uint32_t)isr14, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(15, (uint32_t)isr15, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(16, (uint32_t)isr16, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(17, (uint32_t)isr17, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(18, (uint32_t)isr18, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(19, (uint32_t)isr19, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(20, (uint32_t)isr20, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(21, (uint32_t)isr21, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(22, (uint32_t)isr22, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(23, (uint32_t)isr23, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(24, (uint32_t)isr24, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(25, (uint32_t)isr25, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(26, (uint32_t)isr26, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(27, (uint32_t)isr27, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(28, (uint32_t)isr28, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(29, (uint32_t)isr29, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(30, (uint32_t)isr30, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(31, (uint32_t)isr31, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    
    idt_set_gate(32, (uint32_t)irq0, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(33, (uint32_t)irq1, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(34, (uint32_t)irq2, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(35, (uint32_t)irq3, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(36, (uint32_t)irq4, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(37, (uint32_t)irq5, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(38, (uint32_t)irq6, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(39, (uint32_t)irq7, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(40, (uint32_t)irq8, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(41, (uint32_t)irq9, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(42, (uint32_t)irq10, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(43, (uint32_t)irq11, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(44, (uint32_t)irq12, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(45, (uint32_t)irq13, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(46, (uint32_t)irq14, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    idt_set_gate(47, (uint32_t)irq15, 0x08, IDT_FLAG_INTERRUPT | IDT_FLAG_RING0);
    
    register_interrupt_handler(0, isr_handler_divide_by_zero);
    register_interrupt_handler(1, isr_handler_debug);
    register_interrupt_handler(2, isr_handler_nmi);
    register_interrupt_handler(3, isr_handler_breakpoint);
    register_interrupt_handler(4, isr_handler_overflow);
    register_interrupt_handler(5, isr_handler_bounds);
    register_interrupt_handler(6, isr_handler_invalid_opcode);
    register_interrupt_handler(7, isr_handler_device_not_available);
    register_interrupt_handler(8, isr_handler_double_fault);
    register_interrupt_handler(10, isr_handler_invalid_tss);
    register_interrupt_handler(11, isr_handler_segment_not_present);
    register_interrupt_handler(12, isr_handler_stack_fault);
    register_interrupt_handler(13, isr_handler_general_protection_fault);
    register_interrupt_handler(14, isr_handler_page_fault);
    register_interrupt_handler(16, isr_handler_fpu_error);
    register_interrupt_handler(17, isr_handler_alignment_check);
    register_interrupt_handler(18, isr_handler_machine_check);
    register_interrupt_handler(19, isr_handler_simd_exception);
    
    register_interrupt_handler(32, irq_handler_timer);
    register_interrupt_handler(33, irq_handler_keyboard);
}
