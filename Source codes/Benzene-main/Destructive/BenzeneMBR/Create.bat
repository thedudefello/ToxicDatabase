@echo off
title Benzene MBR
color 0a

:Check
if not exist Build md Build >nul
if exist disk.img goto QEMU
if exist Build\frames.bin del Build\frames.bin /F /Q >nul
if exist Build\song.bin del Build\song.bin /F /Q >nul
if exist Build\special.bin del Build\special.bin /F /Q >nul
if exist Build\stage2-uncompressed.bin del Build\stage2-uncompressed.bin /F /Q >nul
if exist Build\stage2-compressed.bin del Build\stage2-compressed.bin /F /Q >nul
cls


:Start
Data\Image\png2bin.exe Data\Image\Special\01.png Build\special.bin
Data\Song\midi2bin.exe Data\Song\midi2bin.mid Build\song.bin
cd Data\Image\Frames >nul
if exist 11.png ..\png2bin.exe 00.png 01.png 02.png 03.png 04.png 05.png 06.png 07.png 08.png 09.png 10.png 11.png ..\..\..\Build\frames.bin & goto Next
if exist 10.png ..\png2bin.exe 00.png 01.png 02.png 03.png 04.png 05.png 06.png 07.png 08.png 09.png 10.png ..\..\..\Build\frames.bin & goto Next
if exist 09.png ..\png2bin.exe 00.png 01.png 02.png 03.png 04.png 05.png 06.png 07.png 08.png 09.png ..\..\..\Build\frames.bin & goto Next
if exist 08.png ..\png2bin.exe 00.png 01.png 02.png 03.png 04.png 05.png 06.png 07.png 08.png ..\..\..\Build\frames.bin & goto Next
if exist 07.png ..\png2bin.exe 00.png 01.png 02.png 03.png 04.png 05.png 06.png 07.png ..\..\..\Build\frames.bin & goto Next
if exist 06.png ..\png2bin.exe 00.png 01.png 02.png 03.png 04.png 05.png 06.png ..\..\..\Build\frames.bin & goto Next
if exist 05.png ..\png2bin.exe 00.png 01.png 02.png 03.png 04.png 05.png ..\..\..\Build\frames.bin & goto Next
if exist 04.png ..\png2bin.exe 00.png 01.png 02.png 03.png 04.png ..\..\..\Build\frames.bin & goto Next
if exist 03.png ..\png2bin.exe 00.png 01.png 02.png 03.png ..\..\..\Build\frames.bin & goto Next
if exist 02.png ..\png2bin.exe 00.png 01.png 02.png ..\..\..\Build\frames.bin & goto Next
if exist 01.png ..\png2bin.exe 00.png 01.png ..\..\..\Build\frames.bin & goto Next
if exist 00.png ..\png2bin.exe 00.png ..\..\..\Build\frames.bin & goto Next



:Next
cd ..\..\Source >nul
..\..\Programs\nasm.exe -f bin main.asm -o ..\..\Build\stage2-uncompressed.bin
..\..\Programs\compress.exe ..\..\Build\stage2-uncompressed.bin ..\..\Build\stage2-compressed.bin >nul
..\..\Programs\nasm.exe -o ..\..\disk.img bootloader.asm
cd ..\.. >nul


:QEMU
pause
Programs\QEMU\qemu -s -soundhw pcspk -fda disk.img
exit
