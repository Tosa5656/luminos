all: lumin.img

lumin.img: bootloader.bin kernel.bin
	dd if=/dev/zero of=lumin.img bs=512 count=2880 2>/dev/null
	dd if=temp/bootloader.bin of=lumin.img conv=notrunc 2>/dev/null
	dd if=temp/kernel.bin of=lumin.img bs=512 seek=1 conv=notrunc 2>/dev/null

bootloader.bin: mkdirs
	nasm -f bin src/bootloader.asm -o temp/bootloader.bin

vga.o:
	gcc -m32 -c src/vga/vga.c -o temp/vga.o -ffreestanding -nostdlib -fno-pie

kernel.bin: mkdirs vga.o
	nasm -f elf32 src/kernel_entry.asm -o temp/kernel_entry.o
	gcc -m32 -c src/kernel.c -o temp/kernel.o -ffreestanding -nostdlib -fno-pie
	ld -m elf_i386 -Ttext=0x10000 -o temp/kernel.elf temp/kernel_entry.o temp/kernel.o temp/vga.o
	objcopy -O binary temp/kernel.elf temp/kernel.bin

mkdirs:
	@mkdir -p temp