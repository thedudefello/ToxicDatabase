@echo off
title CustomMBR Image
color 0a

:Chek
rename Image\*.png Custom.png
if exist disk.img goto QEMU
if exist Image\Custom.bin del Image\Custom.bin
cls

:Start
Programs\png2bin.exe Image\Custom.png Image\Custom.bin
Programs\compress.exe Image\Custom.bin Image\Custom.bin
Programs\nasm -o disk.img Data\kernel.asm
goto QEMU


:QEMU
pause
Programs\QEMU\qemu -s -soundhw pcspk -fda disk.img
exit