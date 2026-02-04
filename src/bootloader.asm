bits 16
org 0x7C00

_start:
    cli

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    sti

    mov si, hello_world
    call print_string

    jmp $

print_string:
    pusha
    mov ah, 0x0E
.print_char:
    lodsb
    test al, al
    jz .print_done
    int 0x10
    jmp .print_char
.print_done:
    popa
    ret

hello_world db "Hello, World!", 0x0D, 0x0A, 0

times 510 - ($ - $$) db 0
dw 0xAA55