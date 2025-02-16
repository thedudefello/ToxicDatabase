@echo off
rm -f disk.flp
rm -f kernel.bin
rm -f bootloader.bin
nasm -o bootloader.bin bootloader.asm
nasm -o kernel.bin kernel.asm
dd if=/dev/zero of=disk.flp bs=512 count=2880
dd if=bootloader.bin of=disk.flp conv=notrunc
dd if=kernel.bin of=disk.flp conv=notrunc bs=512 seek=1
copy disk.flp /b disk.img
qemu-system-i386 -fda disk.flp
rm -f disk.flp
rm -f kernel.bin
rm -f bootloader.bin
