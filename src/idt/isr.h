#include "idt.h"

void isr_init(void);

void interrupt_handler(struct interrupt_frame* frame);

void isr_handler_divide_by_zero(struct interrupt_frame* frame);
void isr_handler_debug(struct interrupt_frame* frame);
void isr_handler_nmi(struct interrupt_frame* frame);
void isr_handler_breakpoint(struct interrupt_frame* frame);
void isr_handler_overflow(struct interrupt_frame* frame);
void isr_handler_bounds(struct interrupt_frame* frame);
void isr_handler_invalid_opcode(struct interrupt_frame* frame);
void isr_handler_device_not_available(struct interrupt_frame* frame);
void isr_handler_double_fault(struct interrupt_frame* frame);
void isr_handler_invalid_tss(struct interrupt_frame* frame);
void isr_handler_segment_not_present(struct interrupt_frame* frame);
void isr_handler_stack_fault(struct interrupt_frame* frame);
void isr_handler_general_protection_fault(struct interrupt_frame* frame);
void isr_handler_page_fault(struct interrupt_frame* frame);
void isr_handler_fpu_error(struct interrupt_frame* frame);
void isr_handler_alignment_check(struct interrupt_frame* frame);
void isr_handler_machine_check(struct interrupt_frame* frame);
void isr_handler_simd_exception(struct interrupt_frame* frame);

void irq_handler_timer(struct interrupt_frame* frame);
void irq_handler_keyboard(struct interrupt_frame* frame);