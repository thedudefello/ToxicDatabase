org 0x7c00
bits 16

mov [BOOT_DRIVE], dl ;MDP - Save boot drive
%include "Data\decompress.asm" ;Include decompressor part

;The decompressor will jump here if it's done
compressorDone:

;Set video mode
mov ax, 13h
int 10h

;Set source address to uncompresed data
mov bx, daddr
mov ds, bx
mov si, uncompressed    

;Get the color table length
mov ah, 0
lodsb

mov bx, 0
mov cx, ax

;Load the color table
setcolor:
    mov dx, 0x3C8
    mov al, bl
    out dx, al
    inc bx
    
    mov dx, 0x3C9
    
    lodsb
    out dx, al
    lodsb
    out dx, al
    lodsb
    out dx, al
    
    loop setcolor

;Set destination address to the video memory
mov bx, 0xA000
mov es, bx
mov di, 0

;Put the pixel data into the video memory
mov cx, 32000
rep movsw

;=====================================================================================================================

Keypress:
    mov ah, 86h               ;AH = 86
    mov cx, 50                ;Set for timeout 50
    int 15h                   ;Wait function

    mov ah, 0h                ;AH = 0
    cmp ah, 0h                ;Check same or not same
    jne Keypress              ;If same continue else abort

    xor ah,ah                 ;AH = 0
    int 16h                   ;Wait for key
    cmp ah, 01h               ;Scan code 1 = Escape
    jne Keypress              ;If Escape not pressed get another key

    mov ah, 2h
    int 16h                   ;Query keyboard status flags
    and al, 0b00001111        ;Mask all the key press flags
    cmp al, 0b00001100        ;Check if ONLY Control and Alt are pressed and make sure Left and/or Right Shift are not being pressed
    jne Keypress              ;If not go back and wait for another keystroke ; Otherwise Control-Alt-Escape has been pressed

;=====================================================================================================================

RestoreMBR:
    ; Setup segments
    xor ax, ax                  ; AX=0
    mov ds, ax                  ; DS=ES=0 because we use an org of 0x7c00 - Segment<<4+offset = 0x0000<<4+0x7c00 = 0x07c00
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00              ; SS:SP= 0x0000:0x7c00 stack just below bootloader

    ;Read sector - 2th
    mov bx, buffer            ;ES: BX must point to the buffer
    mov dl, [BOOT_DRIVE]      ;Use boot drive passed to bootloader by BIOS in DL
    mov dh, 0                 ;Head number
    mov ch, 0                 ;Track number
    mov cl, 2                 ;Sector number - (2th)
    mov al, 1                 ;Number of sectors to read
    mov ah, 2                 ;Read function number
    int 13h

    ;Write sector - 1th
    mov bx, buffer            ;ES: BX must point to the buffer
    mov dl, [BOOT_DRIVE]      ;Use boot drive passed to bootloader by BIOS in DL
    mov dh, 0                 ;Head number
    mov ch, 0                 ;Track number
    mov cl, 1                 ;Sector number - (1th)
    mov al, 2                 ;Number of sectors to write
    mov ah, 3                 ;Write function number
    int 13h

    ;Read sector for zero filling
    mov bx, buffer            ;ES: BX must point to the buffer
    mov dl, [BOOT_DRIVE]      ;Use boot drive passed to bootloader by BIOS in DL
    mov dh, 0                 ;Head number
    mov ch, 0                 ;Track number
    mov cl, 2                 ;Sector number - (2th)
    mov al, 1                 ;Number of sectors to read
    mov ah, 2                 ;Read function number
    int 13h

    mov byte [SECTOR_NUMBER], 3

.loop:                        ;Fill sectors with zero
    mov bx, buffer            ;ES: BX must point to the buffer
    mov dl, [BOOT_DRIVE]      ;Use boot drive passed to bootloader by BIOS in DL
    mov cl, [SECTOR_NUMBER]   ;Sector number - (1th)
    mov al, 1                 ;Number of sectors to write
    mov ah, 3                 ;Write function number
    int 13h

    inc byte [SECTOR_NUMBER]
    cmp byte [SECTOR_NUMBER], 65
    jne .loop
    

RebootPC:
    xor ax, ax
    mov es, ax
    mov bx, 1234
    mov [es:0472], bx
    cli
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, ax
    mov ax, 2
    push ax
    mov ax, 0xf000
    push ax
    mov ax, 0xfff0
    push ax
    iret

;=====================================================================================================================

buffer: equ 0x4f00            ;Address for 
daddr: equ 0x07e0             ;Base address of the data (compressed and uncompressed)
compressed: equ 0x0000        ;Address offset to load the compressed data
BOOT_DRIVE: dd 0              ;Address where save the boot drive
SECTOR_NUMBER: dd 0           ;Sector number where write

times 510 - ($ - $$) db 0     ;Fill the data with zeros until we reach 510 bytes
dw 0xAA55                     ;Add the boot sector signature
db 'ORIGINAL MBR'             ;Original MBR
times 1024 - ($ - $$) db 0    ;Fill the data with zeros until we reach 1024 bytes - original sector place

comp: incbin "Image\Custom.bin" ;Include the compressed data (it will go right after the original MBR)
compsize: equ $-comp ;Size of the compressed data
uncompressed: equ compressed+compsize ;Put the uncompressed data right after the compressed data

times 32768 - ($ - $$) db 0 ;Fill the rest of the disk image so it reaches 32768 bytes