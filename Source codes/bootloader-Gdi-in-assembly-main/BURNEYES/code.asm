;se lo riutilizzate taggatemi @MalwareLab150
BITS 16
ORG 0x7C00

start:
 
    xor ax, ax
    mov ds, ax
    mov es, ax


    mov bx, 0xB800
    mov es, bx


    call clear_screen

    
    call animate_colors

hang:
   
    jmp hang


clear_screen:
    mov di, 0           
    mov cx, 2000        
    mov ax, 0x0720      
rep stosw               
    ret                 

animate_colors:
    mov cx, 2000        
    mov di, 0           

.next_frame:
    
    call get_random_byte
    and al, 0x0F        
    mov ah, al


    mov al, 0xDB
    stosw

    
    loop .next_frame


    call delay

   
    jmp animate_colors


get_random_byte:
    in al, 0x40        
    ret


delay:
    mov cx, 0xFFFF
.delay_loop:
    loop .delay_loop
    ret

; completa fino a 510 byte 
times 510-($-$$) db 0
; Firma del bootloader
dw 0xAA55
