[BITS    16]
[ORG 0x7C00]

%define KERNEL 0x7E00
%define SECTRS 0x0005
%define VIDMOD 0x0013

main:
        ;Setup Data and Extra segments
        xor ax, ax
        mov ds, ax
        mov es, ax

        ;Setup stack's pointer and segment
        mov sp, 0x7C00
        mov ss, ax

        call setvideomode
        call krnlsectors

        ;ES:BX
        jmp 0x0000:KERNEL

krnlsectors:
        ;Read sectors
        mov ah, 0x02
        mov al, SECTRS
        mov ch, 0x00
        mov cl, 0x02
        mov dh, 0x00

        xor bx, bx
        mov es, bx

        mov bx, KERNEL

        int 0x13

        ret

setvideomode:
        mov ax, VIDMOD
        int 0x10

        ret

times 510 - ($ - $$) db 0x00
dw 0xAA55
