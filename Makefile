all: lumin.img

clean:
	rm -rf temp lumin.img

lumin.img: bootloader.bin kernel.bin
	dd if=/dev/zero of=lumin.img bs=512 count=2880 2>/dev/null
	dd if=temp/bootloader.bin of=lumin.img conv=notrunc 2>/dev/null
	dd if=temp/kernel.bin of=lumin.img bs=512 seek=1 conv=notrunc 2>/dev/null

bootloader.bin: mkdirs
	nasm -f bin src/bootloader.asm -o temp/bootloader.bin

vga.o:
	gcc -m32 -c src/vga/vga.c -o temp/vga.o -ffreestanding -nostdlib -fno-pie -fno-stack-protector

idt_asm.o:
	nasm -f elf32 src/idt/idt.asm -o temp/idt_asm.o

idt.o:
	gcc -m32 -c src/idt/idt.c -o temp/idt.o -ffreestanding -nostdlib -fno-pie -fno-stack-protector

isr.o:
	gcc -m32 -c src/idt/isr.c -o temp/isr.o -ffreestanding -nostdlib -fno-pie -fno-stack-protector

timer.o:
	gcc -m32 -c src/drivers/timer/timer.c -o temp/timer.o -ffreestanding -nostdlib -fno-pie -fno-stack-protector

kernel.bin: mkdirs vga.o idt_asm.o idt.o isr.o timer.o
	nasm -f elf32 src/kernel_entry.asm -o temp/kernel_entry.o
	gcc -m32 -c src/kernel.c -o temp/kernel.o -ffreestanding -nostdlib -fno-pie -fno-stack-protector
	ld -m elf_i386 -T linker.ld -o temp/kernel.elf temp/kernel_entry.o temp/kernel.o temp/vga.o temp/idt_asm.o temp/idt.o temp/isr.o temp/timer.o
	objcopy -O binary temp/kernel.elf temp/kernel.bin

mkdirs:
	@mkdir -p temp