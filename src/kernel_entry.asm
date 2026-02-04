bits 32

global _start
extern kernel_main

section .text
_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    
    call kernel_main
    
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
kernel_stack:
    resb KERNEL_STACK_SIZE
KERNEL_STACK_SIZE equ 8192