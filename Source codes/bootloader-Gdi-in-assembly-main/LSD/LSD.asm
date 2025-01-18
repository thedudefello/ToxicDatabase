;SE LO RIUTILIZZATE TAGGATEMI @MalwareLab150 
BITS 16
ORG 0x7C00

start:
   
    xor ax, ax
    mov ds, ax
    mov es, ax

   
    mov bx, 0xB800
    mov es, bx

    call clear_screen
    call random_colors

hang:
    jmp hang


clear_screen:
    mov di, 0
    mov cx, 8000
    mov ax, 0x0F20
rep stosw
    ret


random_colors:
    mov di, 0
    mov cx, 9000
.next_char:
    ; Genera colore casuale
    call get_random_byte
    and al, 0x0F
    mov ah, al

    
    call get_random_byte
    or al, 0x80 
    stosw
    loop .next_char
    ret


get_random_byte:
    in al, 0x40
    ret

times 510-($-$$) db 0 
dw 0xAA55  ; Firma del bootloader
