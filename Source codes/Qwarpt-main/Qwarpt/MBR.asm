BITS    16
ORG     0x7c00
jmp start
; Sleepmod code
start:
        call clear_screen
        mov ax,cs
        mov ds,ax
        mov si,msg

        call print

print:
        push ax
        cld
next:
        mov al,[si]
        cmp al,0
        je done
        call printchar
        inc si
        jmp next
done:
        jmp $

printchar:
        mov ah,0x0e
        int 0x10
        ret

clear_screen:
        mov ah, 0x07
        mov al, 0x00
        mov bh, 0x01
        mov cx, 0x0000 
        mov dx, 0x184f
        int 0x10
        ret

;Why creating unnecessary spaces
msg:            db        "Connection Lost Reconnecting To Operating System *Windows 7*",0
times 510 - ($-$$) db 0
dw        0xaa55
