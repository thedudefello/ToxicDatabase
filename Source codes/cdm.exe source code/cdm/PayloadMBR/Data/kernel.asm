;Modified by pankoza to remove the useless MBR restoring code
org 0x7c00
bits 16

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

.halt:
    hlt

    mov ah,86h
    mov cx,50
    int 15h

    jmp .halt

;=====================================================================================================================
buffer: equ 0x4f00            ;Address for 
daddr: equ 0x07e0             ;Base address of the data (compressed and uncompressed)
compressed: equ 0x0000        ;Address offset to load the compressed data
BOOT_DRIVE: dd 0              ;Address where save the boot drive
SECTOR_NUMBER: dd 0           ;Sector number where write

times 510 - ($ - $$) db 0     ;Fill the data with zeros until we reach 510 bytes
dw 0xAA55                     ;Add the boot sector signature
db 'AAAAAAAAAAAA'             
times 1024 - ($ - $$) db 0    ;Fill the data with zeros until we reach 1024 bytes

comp: incbin "Image\Custom.bin" ;Include the compressed data
compsize: equ $-comp ;Size of the compressed data
uncompressed: equ compressed+compsize ;Put the uncompressed data right after the compressed data

times 32768 - ($ - $$) db 0 ;Fill the rest of the disk image so it reaches 32768 bytes