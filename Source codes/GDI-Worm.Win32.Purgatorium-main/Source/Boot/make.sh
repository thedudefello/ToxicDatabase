nasm -fbin Bootloader/boot.asm -o Binaries/boot.bin
nasm -fbin Kernel/kernel.asm -o Binaries/kernel.bin

cat Binaries/boot.bin Binaries/kernel.bin > Infernum.bin
