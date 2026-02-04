#!/bin/bash
# build.sh

echo "Сборка загрузчика..."
nasm -f bin src/bootloader.asm -o boot.bin

echo "Сборка ядра..."
nasm -f elf32 src/kernel_entry.asm -o kernel_entry.o
gcc -m32 -c src/kernel.c -o kernel.o -ffreestanding -nostdlib -fno-pie
ld -m elf_i386 -Ttext=0x10000 -o kernel.elf kernel_entry.o kernel.o
objcopy -O binary kernel.elf kernel.bin

echo "Создание образа диска..."
dd if=/dev/zero of=disk.img bs=512 count=2880 2>/dev/null
dd if=boot.bin of=disk.img conv=notrunc 2>/dev/null
dd if=kernel.bin of=disk.img bs=512 seek=1 conv=notrunc 2>/dev/null

echo "Готово! Запуск: qemu-system-x86_64 -drive format=raw,file=disk.img"