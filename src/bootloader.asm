bits 16
org 0x7C00

times 510 - ($ - $$) db 0
dw 0xAA55