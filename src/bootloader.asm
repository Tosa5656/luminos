bits 16
org 0x7C00

KERNEL_SEGMENT equ 0x1000
KERNEL_SECTORS equ 10

_start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti
    
    mov [boot_drive], dl
    
    mov si, msg_loading
    call print_string
    
    mov bx, KERNEL_SEGMENT
    mov es, bx
    xor bx, bx
    mov al, KERNEL_SECTORS
    mov cl, 2
    call load_sectors
    
    mov si, msg_loaded
    call print_string
    
    call switch_to_pm
    
    jmp $

load_sectors:
    pusha
    
    mov ch, 0
    mov dh, 0
    mov dl, [boot_drive]
    mov ah, 0x02
    int 0x13
    jc .disk_error
    
    popa
    ret
    
.disk_error:
    mov si, msg_error
    call print_string
    jmp $

switch_to_pm:
    cli
    lgdt [gdt_descriptor]
    
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    
    jmp CODE_SEG:init_pm

bits 32
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    mov esp, 0x90000
    
    call clear_screen
    
    jmp 0x10000

clear_screen:
    pusha
    mov edi, 0xB8000
    mov ecx, 80*25
    mov ax, 0x0720
    rep stosw
    popa
    ret

bits 16
print_string:
    pusha
    mov ah, 0x0E
.loop:
    lodsb
    test al, al
    jz .done
    int 0x10
    jmp .loop
.done:
    popa
    ret

gdt_start:
    gdt_null:
        dd 0x0
        dd 0x0
    
    gdt_code:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 10011010b
        db 11001111b
        db 0x00
    
    gdt_data:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 10010010b
        db 11001111b
        db 0x00
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

boot_drive db 0
msg_loading db "Loading kernel... ", 0
msg_loaded db "OK", 0x0D, 0x0A, 0
msg_error db "Disk error!", 0

times 510 - ($ - $$) db 0
dw 0xAA55